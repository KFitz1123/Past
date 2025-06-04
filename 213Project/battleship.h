#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#define BOARD_SIZE 10
#define SHIPS_SIZE_2 1
#define SHIPS_SIZE_3 2
#define SHIPS_SIZE_4 1
#define SHIPS_SIZE_5 1
#define BOARD_WINDOW_WIDTH 23
#define BOARD_WINDOW_SPACING 44
#define BOARD_WINDOW_HEIGHT 13
#define TEXT_WINDOW_WIDTH 85
#define TEXT_WINDOW_HEIGHT 6

typedef struct position {
  int row;
  int col;
} position_t;

typedef struct damage {
  bool hit;
  bool sunk;
} damage_t;

typedef struct board {
  char grid[BOARD_SIZE][BOARD_SIZE];
  int num_ships;
} board_t;

/**
 * Initilizes a blank board.
 *
 * \param board A pointer to a board_t to initilize.
 */
void init_board(board_t* board);

/**
 * Tries to place a ship of a given length at a given position and direction on the board.
 *
 * \param board A pointer to a board_t where the ship will be placed.
 * \param row A character from A to J that represents the row to place the ship.
 * \param col A character from 0 to 9 that represents the column to place the ship.
 * \param dir A character in (u, d, l, r) that represents the direction the boat will face.
 * \param len The length of the boat being placed.
 * \param ship_char The character to place where the ship is placed.
 *
 * \returns If the ship was placed correctly, true. If the ship was unable to be placed, false.
 */
bool place_ship_at(board_t* board, char row, char col, char dir, size_t len, char ship_char);

/**
 * Allows the player to place one ship of certain size on the board.
 *
 * \param board A pointer to a board_t where the ships will be placed.
 * \param ship_size The size of the ships to be placed.
 * \param ship_char The character to place where the ship is placed.
 */
void place_one_ship(board_t* board, size_t ship_size, char ship_char);

/**
 * Allows the player to place all ships of each size on the board.
 *
 * \param board A pointer to a board_t where the ships will be placed.
 */
void place_ships(board_t* board);

/**
 * Checks if a given position is part of a ship.
 *
 * \param board A pointer to a board_t where the ships are placed.
 * \param pos The position on the board we are looking at.
 *
 * \returns true if the position is ship. Otherwise, false.
 */
bool is_ship(board_t* board, position_t* pos);

/**
 * Checks if a ship matching the given char is on the board.
 *
 * \param board A pointer to a board_t where the ships are placed.
 * \param ship_char The ship's character to look for.
 *
 * \returns true if there are no characters matching the given char on the board. Otherwise, false.
 */
bool is_sunk(board_t* board, char ship_char);

/**
 * Prints the given board.
 *
 * \param board A pointer to a board_t to print.
 * \param win A pointer to the window to print the board on.
 */
void print_board(board_t* board, WINDOW* win);

/**
 * Runs the battleship game until the host or guest wins.
 */
void* battleship(void* arg);

/**
 * Opens a port and waits for a guest to connect. Then creates a thread to run the host's battleship
 * game. Closes the port when the thread ends.
 */
void start_host();

/**
 * Connects to the host using the host's name and the port. Then creates a thread to run the guest's
 * battleship game. Closes connection when the thread ends.
 *
 * \param host_name The name of the host machine to connect to.
 * \param port The port number to connect to the host machine.
 */
void start_guest(char* host_name, unsigned short port);