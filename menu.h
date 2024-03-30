//menu.h
#include <stdio.h>
#include <string.h>

struct st_Book{
	char name[100]; // Channel name
	int count;	  // # of subscriptions
	int level;	  // index of level (0~4)
};

void displayMenu();

int loadData(struct st_channel* c[]); 
int findLevel(int num); 
void printStatistics(struct st_channel* c[], int size);
void printBook(struct st_channel* c[], int size);
void pickupRandomBooks(struct st_channel* c[], int size);
void searchBook(struct st_channel* c[], int size);
int addBook(struct st_channel* c[], int size);
void updateBook(struct st_channel* c[], int size);
int deleteBook(struct st_channel* c[], int size);
void makeReport(struct st_channel* c[], int size); 