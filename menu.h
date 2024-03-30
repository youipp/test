//menu.h
#include <stdio.h>
#include <string.h>

struct st_Book{
	char name[100]; // Book name
	int count;	  // # of Words
	int level;	  // index of level (0~4)
};

void displayMenu();

int loadData(struct st_Book* c[]); 
int findLevel(int num); 
void printStatistics(struct st_Book* c[], int size);
void printBooks(struct st_Book* c[], int size);
void pickupRandomBooks(struct st_Book* c[], int size);
void searchBook(struct st_Book* c[], int size);
int addBook(struct st_Book* c[], int size);
void updateBook(struct st_Book* c[], int size);
int deleteBook(struct st_Book* c[], int size);
void makeReport(struct st_Book* c[], int size); 