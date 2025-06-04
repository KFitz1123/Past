#include "battleship.h"

#include <ctype.h>
#include <curses.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "socket.h"

int player;             // which player you are
int cur_player;         // the current player
int winner;             // the player who won the game
board_t* target_board;  // the target board of the player
board_t* ocean_board;   // the ocean board of the player
WINDOW* target_win;     // the window where the target board will be
WINDOW* ocean_win;      // the window where the ocean board will be
WINDOW* text_win;       // the window where text prompts will be
WINDOW* input_win;      // the window where text input is colected

void init_board(board_t* board) {
  // set grid values
  for (int r = 0; r < BOARD_SIZE; r++) {
    for (int c = 0; c < BOARD_SIZE; c++) {
      board->grid[r][c] = '~';
    }
  }

  board->num_ships = SHIPS_SIZE_2 + SHIPS_SIZE_3 + SHIPS_SIZE_4 + SHIPS_SIZE_5;
}

bool place_ship_at(board_t* board, char row, char col, char dir, size_t len, char ship_char) {
  // the in representations of the row and col
  int row_num = toupper(row) - 'A';
  int col_num = atoi(&col);
  int len_num = (int)len;

  // check position is in bounds
  if (row_num >= 0 && row_num < 10 && col_num >= 0 && col_num < 10) {
    // make a position to send to is_ship
    position_t* pos = malloc(sizeof(position_t));
    if (pos == NULL) {
      perror("Failed to malloc a pos");
      exit(EXIT_FAILURE);
    }
    pos->row = row_num;
    pos->col = col_num;

    if (dir == 'u') {  // boat going up from position
      // make sure that the boat is in bounds and does not overlap other boats
      for (; pos->row > row_num - len_num; pos->row--)
        if (pos->row < 0 || is_ship(board, pos)) {
          free(pos);
          return false;
        }

      // place the boat into it's position
      for (pos->row = row_num; pos->row > row_num - len_num; pos->row--)
        board->grid[pos->row][col_num] = ship_char;

      free(pos);
      return true;
    } else if (dir == 'd') {  // boat going down from position
      // make sure that the boat is in bounds and does not overlap other boats
      for (; pos->row < row_num + len_num; pos->row++)
        if (pos->row > 9 || is_ship(board, pos)) {
          free(pos);
          return false;
        }

      // place the boat into it's position
      for (pos->row = row_num; pos->row < row_num + len_num; pos->row++)
        board->grid[pos->row][col_num] = ship_char;

      free(pos);
      return true;
    } else if (dir == 'l') {  // boat going left from position
      // make sure that the boat is in bounds and does not overlap other boats
      for (; pos->col > col_num - len_num; pos->col--)
        if (pos->col < 0 || is_ship(board, pos)) {
          free(pos);
          return false;
        }

      // place the boat into it's position
      for (pos->col = col_num; pos->col > col_num - len_num; pos->col--)
        board->grid[row_num][pos->col] = ship_char;

      free(pos);
      return true;
    } else if (dir == 'r') {  // boat going right from position
      // make sure that the boat is in bounds and does not overlap other boats
      for (; pos->col < col_num + len_num; pos->col++)
        if (pos->col > 9 || is_ship(board, pos)) {
          free(pos);
          return false;
        }

      // place the boat into it's position
      for (pos->col = col_num; pos->col < col_num + len_num; pos->col++)
        board->grid[row_num][pos->col] = ship_char;

      free(pos);
      return true;
    }
  }

  return false;
}

void place_one_ship(board_t* board, size_t ship_size, char ship_char) {
  bool placed = false;
  // clear text window
  wclear(text_win);

  while (!placed) {  // loop taking input until ship is placed
    
    //wclear(text_win);

    // remake window box
    box(text_win, 0, 0);

    // print out input prompt
    mvwprintw(text_win, 1, 1, "You are placing a ship of length %lu.", ship_size);
    mvwprintw(
        text_win, 2, 1,
        "Enter a board position (i.e. B4) followed by a space and a direction (u, d, l, r): ");
    wrefresh(text_win);

    // place to store input
    char* line = malloc(sizeof(char) * 5);
    line[4] = '\0';

    // get input string
    mvwgetnstr(text_win, 3, 1, line, 4);

    char row = line[0];  // user input of row
    char col = line[1];  // user input of column
    char dir = line[3];  // user input of direction

    if (place_ship_at(board, row, col, dir, ship_size, ship_char))  // ship was placed
      placed = true;
    if(!placed){
      mvwprintw(text_win, 4, 1, "Invalid Input, try again");
      mvwprintw(text_win, 3, 1, "    ");
      wrefresh(text_win);
    }
      

    free(line);
  }
  wclear(text_win);
}

void place_ships(board_t* board) {
  int ship_num = 1;
  int ships_to_place = SHIPS_SIZE_2;

  // place each ship of length 2
  for (ship_num = 1; ship_num <= ships_to_place; ship_num++) {
    place_one_ship(board, 2, ship_num + '0');
    print_board(board, ocean_win);
    wrefresh(ocean_win);
  }

  ships_to_place += SHIPS_SIZE_3;

  // place each ship of length 3
  for (; ship_num <= ships_to_place; ship_num++) {
    place_one_ship(board, 3, ship_num + '0');
    print_board(board, ocean_win);
    wrefresh(ocean_win);
  }

  ships_to_place += SHIPS_SIZE_4;

  // place each ship of length 4
  for (; ship_num <= ships_to_place; ship_num++) {
    place_one_ship(board, 4, ship_num + '0');
    print_board(board, ocean_win);
    wrefresh(ocean_win);
  }

  ships_to_place += SHIPS_SIZE_5;

  // place each ship of length 5
  for (; ship_num <= ships_to_place; ship_num++) {
    place_one_ship(board, 5, ship_num + '0');
    print_board(board, ocean_win);
    wrefresh(ocean_win);
  }
}

bool is_ship(board_t* board, position_t* pos) {
  // make char at pos into a string to stop atoi from reading the whole row
  char pos_char[2];
  pos_char[0] = board->grid[pos->row][pos->col];
  pos_char[1] = '\0';

  // turn the char at pos into an int
  int pos_num = atoi(pos_char);
  int total_ships = SHIPS_SIZE_2 + SHIPS_SIZE_3 + SHIPS_SIZE_4 + SHIPS_SIZE_5;

  // if pos contains a ship number
  if (pos_num > 0 && pos_num <= total_ships) return true;
  return false;
}

bool is_sunk(board_t* board, char ship_char) {
  // look through grid
  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int col = 0; col < BOARD_SIZE; col++) {
      if (board->grid[row][col] == ship_char) return false;  // found the ship
    }
  }

  return true;  // did not find the ship
}

void print_board(board_t* board, WINDOW* win) {
  int column_width = BOARD_WINDOW_WIDTH / (BOARD_SIZE + 1);
  int row_width = BOARD_WINDOW_HEIGHT / (BOARD_SIZE + 1);

  // print column indices
  for (int i = 0; i < BOARD_SIZE; i++)
    mvwprintw(win, 1, (i * column_width + column_width) + 1, "%d", i);

  for (int r = 0; r < BOARD_SIZE; r++) {
    mvwprintw(win, (r * row_width + row_width) + 1, 1, "%c", r + 65);  // print column indices
    for (int c = 0; c < BOARD_SIZE; c++) {
      mvwprintw(win, (r * row_width + row_width) + 1, (c * column_width + column_width) + 1, "%c",
                board->grid[r][c]);  // print current position
    }
  }

  wrefresh(win);
}

void* battleship(void* arg) {
  initscr();
  // disables line buffering
  cbreak();

  // create windows
  target_win = newwin(BOARD_WINDOW_HEIGHT, BOARD_WINDOW_WIDTH, 0, 5);
  ocean_win =
      newwin(BOARD_WINDOW_HEIGHT, BOARD_WINDOW_WIDTH, 0, BOARD_WINDOW_WIDTH + BOARD_WINDOW_SPACING);
  text_win = newwin(TEXT_WINDOW_HEIGHT, TEXT_WINDOW_WIDTH, BOARD_WINDOW_HEIGHT + 1, 5);

  // making box border with default border styles
  box(target_win, 0, 0);
  box(ocean_win, 0, 0);
  box(text_win, 0, 0);

  // move and print in window
  mvwprintw(target_win, 0, 1, "Target Board");
  mvwprintw(ocean_win, 0, 1, "Ocean Board");

  // get the socket
  int socket_fd = *(int*)arg;

  // create space for both boards
  target_board = malloc(sizeof(board_t));
  ocean_board = malloc(sizeof(board_t));

  // check they were made
  if (target_board == NULL || ocean_board == NULL) {
    perror("Failed to malloc a board");
    exit(EXIT_FAILURE);
  }

  // initilize boards
  init_board(target_board);
  init_board(ocean_board);

  // print boards
  print_board(target_board, target_win);
  print_board(ocean_board, ocean_win);

  // refresh the windows
  wrefresh(target_win);
  wrefresh(ocean_win);
  wrefresh(text_win);

  // run game
  // place ships
  place_ships(ocean_board);

  bool valid_pos;    // checking valid position is given for attacks
  position_t* pos;   // pointer for position
  damage_t* damage;  // pointer for damage report
  char* line;        // pointer for input

  while (winner == 0) {
    valid_pos = false;

    pos = malloc(sizeof(position_t));  // get space for the position
    if (pos == NULL) {
      perror("Could not allocate space for the position");
      exit(EXIT_FAILURE);
    }

    damage = malloc(sizeof(damage_t));  // get space for damage report
    if (damage == NULL) {
      perror("Could not allocate space for the damage");
      exit(EXIT_FAILURE);
    }
    damage->hit = false;
    damage->sunk = false;

    // print boards
    print_board(target_board, target_win);
    print_board(ocean_board, ocean_win);

    // refresh the windows
    wrefresh(target_win);
    wrefresh(ocean_win);

    // check if it is your turn
    if (cur_player == player) {  // attacking turn
      bool ready = true;

      // tell other player you are ready
      if (write(socket_fd, &ready, sizeof(bool)) != sizeof(bool)) {
        // Writing failed, so return an error
        printf("Writing between intances failed!\n");
        exit(EXIT_FAILURE);
      }

      // clear text window
      wclear(text_win);

      // remake window box
      box(text_win, 0, 0);

      mvwprintw(text_win, 1, 1, "Waiting for other player...");
      wrefresh(text_win);

      // wait for other player to be ready
      if (read(socket_fd, &ready, sizeof(bool)) != sizeof(bool)) {
        // Reading failed. Return an error
        printf("Reading between intances failed!\n");
        exit(EXIT_FAILURE);
      }

      // keep getting input until it is valid
      while (!valid_pos) {
        // clear text window
        wclear(text_win);

        // remake window box
        box(text_win, 0, 0);

        // take input for guess
        mvwprintw(text_win, 1, 1, "Enter a board position to attack (i.e. B4):");
        wrefresh(text_win);

        line = malloc(sizeof(char) * 3);
        line[2] = '\0';

        // get input string
        mvwgetnstr(text_win, 2, 1, line, 2);

        int row = toupper(line[0]) - 'A';
        int col = atoi(&line[1]);
        // check input bounds
        if (row >= 0 && row < 10 && col >= 0 && col < 10) {
          // check that we have not guessed the position
          if (target_board->grid[row][col] != 'X' && target_board->grid[row][col] != 'O') {
            valid_pos = true;
            pos->row = row;
            pos->col = col;
          }
        }
      }

      // send attack to other player
      if (write(socket_fd, pos, sizeof(position_t)) != sizeof(position_t)) {
        // Writing failed, so return an error
        printf("Writing between intances failed!\n");
        exit(EXIT_FAILURE);
      }

      // receive damage
      if (read(socket_fd, damage, sizeof(damage_t)) != sizeof(damage_t)) {
        // Reading failed. Return an error
        printf("Reading between intances failed!\n");
        exit(EXIT_FAILURE);
      }

      // clear text window
      wclear(text_win);

      // remake window box
      box(text_win, 0, 0);

      // update target board
      if (damage->hit) {
        target_board->grid[pos->row][pos->col] = 'X';  // mark a hit

        // check if a ship was sunk
        if (damage->sunk) {
          target_board->num_ships--;  // remove a ship from target baord
          mvwprintw(text_win, 1, 1, "You sunk an enemy battleship!!! You get another turn.");
        } else
          mvwprintw(text_win, 1, 1, "You hit an enemy ship! You get another turn.");

        wrefresh(text_win);
      } else
        target_board->grid[pos->row][pos->col] = 'O';  // mark a miss

      // check if you won
      if (target_board->num_ships <= 0)
        winner = cur_player;
      else if (damage->hit)  // otherwise sleep if there was a hit
        sleep(1);
    } else {  // recieving turn
      bool ready = true;

      // tell other player you are ready
      if (write(socket_fd, &ready, sizeof(bool)) != sizeof(bool)) {
        // Writing failed, so return an error
        printf("Writing between intances failed!\n");
        exit(EXIT_FAILURE);
      }

      // clear text window
      wclear(text_win);

      // remake window box
      box(text_win, 0, 0);

      mvwprintw(text_win, 1, 1, "Waiting for other player...");
      wrefresh(text_win);

      // wait for other player to be ready
      if (read(socket_fd, &ready, sizeof(bool)) != sizeof(bool)) {
        // Reading failed. Return an error
        printf("Reading between intances failed!\n");
        exit(EXIT_FAILURE);
      }

      // get space for the position
      pos = malloc(sizeof(position_t));
      if (pos == NULL) {
        perror("Could not allocate space for the position");
        exit(EXIT_FAILURE);
      }

      // clear text window
      wclear(text_win);

      // remake window box
      box(text_win, 0, 0);

      mvwprintw(text_win, 1, 1, "Waiting for other player...");
      wrefresh(text_win);

      // receive attack
      if (read(socket_fd, pos, sizeof(position_t)) != sizeof(position_t)) {
        // Reading failed. Return an error
        printf("Reading between intances failed!\n");
        exit(EXIT_FAILURE);
      }

      // check if attack was a hit
      if (is_ship(ocean_board, pos)) {
        // ship was hit
        damage->hit = true;
        char ship_hit = ocean_board->grid[pos->row][pos->col];  // keep track of the hit ship
        ocean_board->grid[pos->row][pos->col] = 'X';            // update board

        // clear text window
        wclear(text_win);

        // remake window box
        box(text_win, 0, 0);

        // check if ship was sunk
        if (is_sunk(ocean_board, ship_hit)) {
          ocean_board->num_ships--;  // remove a ship from ocean board
          damage->sunk = true;
          mvwprintw(text_win, 1, 1, "Your battleship has been sunk!!!");
        } else
          mvwprintw(text_win, 1, 1, "Your battleship has been hit!!!");
        wrefresh(text_win);
      } else
        // ship was not hit
        ocean_board->grid[pos->row][pos->col] = 'O';

      // send damage to other player
      if (write(socket_fd, damage, sizeof(damage_t)) != sizeof(damage_t)) {
        // Writing failed, so return an error
        printf("Writing between intances failed!\n");
        exit(EXIT_FAILURE);
      }

      // check if you lost
      if (ocean_board->num_ships <= 0)
        winner = cur_player;
      else
        sleep(1);
    }

    // switch turns if no ship was hit
    if (!damage->hit) {
      if (cur_player == 1)
        cur_player = 2;
      else
        cur_player = 1;
    }
  }

  // clear text window
  wclear(text_win);

  // remake window box
  box(text_win, 0, 0);

  // print the winner
  mvwprintw(text_win, 1, 1, "Player %d has won!!!", winner);

  wrefresh(text_win);

  sleep(2);

  endwin();

  return NULL;
}

void start_host() {
  // Open a server socket
  unsigned short port = 0;
  int server_socket_fd = server_socket_open(&port);
  if (server_socket_fd == -1) {
    perror("Server socket was not opened");
    exit(EXIT_FAILURE);
  }

  player = 1;
  printf("Battleship started on port %u.\n", port);

  // Start listening for connection from guest
  if (listen(server_socket_fd, 1)) {
    perror("listen failed");
    exit(EXIT_FAILURE);
  }

  // Wait for a guest to connect
  int guest_socket_fd = server_socket_accept(server_socket_fd);
  if (guest_socket_fd == -1) {
    perror("accept failed");
    exit(EXIT_FAILURE);
  }

  pthread_t host_thread;
  int* host_thread_input = malloc(sizeof(int));
  *host_thread_input = guest_socket_fd;

  // Create thread for new connection
  if (pthread_create(&host_thread, NULL, battleship, host_thread_input)) {
    perror("pthread_create failed");
    exit(2);
  }

  if (pthread_join(host_thread, NULL)) {
    perror("pthread_join failed");
    exit(2);
  }

  // Close server socket
  close(server_socket_fd);
}

void start_guest(char* host_name, unsigned short port) {
  // Connect to the host
  int socket_fd = socket_connect(host_name, port);
  if (socket_fd == -1) {
    perror("Failed to connect");
    exit(EXIT_FAILURE);
  }

  player = 2;

  pthread_t guest_thread;
  int* guest_thread_input = malloc(sizeof(int));
  *guest_thread_input = socket_fd;

  // Create thread for new connection
  if (pthread_create(&guest_thread, NULL, battleship, guest_thread_input)) {
    perror("pthread_create failed");
    exit(2);
  }

  if (pthread_join(guest_thread, NULL)) {
    perror("pthread_join failed");
    exit(2);
  }

  // Close socket
  close(socket_fd);
}

int main(int argc, char** argv) {
  cur_player = 1;
  winner = 0;

  if (argc == 1) {
    // run host
    start_host();
  } else if (argc == 3) {
    // run guest
    start_guest(argv[1], atoi(argv[2]));
  } else {
    fprintf(stderr, "Usage: %s <server name> <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  return 0;
}