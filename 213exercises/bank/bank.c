#include "bank.h"

#include <pthread.h>
 //pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
// Data associated with an account
typedef struct account {
  int balance;
  pthread_mutex_t lock;
} account_t;

// All of this bank's accounts
account_t accounts[NUM_ACCOUNTS];

// Initialize all of the accounts and any global state at this bank
void init_bank() {
  // Initialize each account
  for (size_t i = 0; i < NUM_ACCOUNTS; i++) {
    accounts[i].balance = 0;
    pthread_mutex_init(&accounts[i].lock, NULL);
  }
}

// Get the balance for a bank account
int get_balance(size_t account_id) {
  // Make sure the account id is valid
  if (account_id >= NUM_ACCOUNTS) return INVALID_ACCOUNT;

  // Return the balance
  return accounts[account_id].balance;
}

// Deposit funds to an account from an outside source
void deposit(size_t account_id, int amount) {
  // If the account id is invalid, return immediately
  if (account_id >= NUM_ACCOUNTS) return;

  // Add funds
  accounts[account_id].balance += amount;
}

// Transfer funds from one account to another
void transfer(size_t from_id, size_t to_id, int amount) {
  // If either account id is invalid, return immediately
  if (from_id >= NUM_ACCOUNTS || to_id >= NUM_ACCOUNTS) return;

  // If the from and to accounts are the same, return immediately
  if (from_id == to_id) return;

  // If the amount is zero or negative, return immediately
  if (amount <= 0) return;

  // Transfer funds
  size_t max;
  size_t min;
  if(to_id > from_id){
    max = to_id;
    min = from_id;
  }else{
    max = from_id;
    min = to_id;
  }
  pthread_mutex_lock(&accounts[min].lock);
  pthread_mutex_lock(&accounts[max].lock);
  accounts[from_id].balance = accounts[from_id].balance - amount;
  accounts[to_id].balance = accounts[to_id].balance + amount;
  pthread_mutex_unlock(&accounts[max].lock);
  pthread_mutex_unlock(&accounts[min].lock);



}

int audit(){
  int total = 0;
  for(int i = 0; i < NUM_ACCOUNTS; i++){
    pthread_mutex_lock(&accounts[i].lock);
  }
  for(int j = 0; j < NUM_ACCOUNTS; j++){
    total += accounts[j].balance;
  }
  for(int k = NUM_ACCOUNTS; k > 0; k--){
    pthread_mutex_unlock(&accounts[k - 1].lock);
  }
  return total;
}
