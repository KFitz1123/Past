#ifndef __TICKET__
#define __TICKET__

#define MAX_LEN 50

typedef struct ticket ticket_t;

struct ticket
{
  int number;
  char identifier[MAX_LEN + 1];
  char problem[MAX_LEN + 1];
  char status[MAX_LEN + 1];
  char technician[MAX_LEN + 1];
  ticket_t *next;
};

/* => returns void
  preconditions:
    - none
  postconditions:
    - prints a list of menu options
*/
void printMenu(void);

/* => returns void
  preconditions:
    - 'newTicketPtr' needs to be a double pointer to the first
       ticket_t of new tickets
    - 'ticketIndex' needs to be a pointer to the ticket index
       integer
  postconditions:
    - queues a new ticket to the 'newTicketList' linked list
*/
void newTicket(ticket_t **newTicketPtr, int *ticketIndex);

/* => returns void
  preconditions:
    - 'newTicketPtr' needs to be a double pointer to the first
       ticket_t of new tickets
    - 'assignedTicketPtr' needs to be a double pointer to the first
       ticket_t of assigned tickets
  postconditions:
    - dequeues a new ticket from the 'newTicketList' linked list
    - queues that ticket to the 'assignedTicketList' linked list
    - assigns a technician to the ticket from stdin
    - updates ticket status to assigned
*/
void assignTicket(ticket_t **newTicketPtr, ticket_t **assignTicketPtr);

/* => returns void
  preconditions:
    - 'assignedTicketPtr' needs to be a double pointer to the first
       ticket_t of assigned tickets
    - 'completedTicketPtr' needs to be a double pointer to the first
       ticket_t of completed tickets
  postconditions:
    - if 'assignedTicketList' is empty, then returns void
    - asks the user for a ticket number to complete
    - if entered ticket number does not exist in 'assignedTicketList',
      then returns void
    - removes the ticket with specified 'ticketNumber' from the
      'assignedTicketList' linked list
    - queues that ticket to the 'completedTicketList' linked list
    - updates ticket status to completed
*/
void completeTicket(ticket_t **assignedTicketPtr, ticket_t **completedTicketPtr);

/* => returns void
  preconditions:
    - 'ticket' must be a pointer to the first element of a ticket_t
      linked list
  postconditions:
    - prints all tickets (with formatted contents) from the ticket list
*/
void printTickets(ticket_t *ticket);

#endif