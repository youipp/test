//guest.c
#include "guest.h"

void addGuest(){
    int menu;
    printf("원하는 메뉴는? ");
    scanf("%d", &menu);
    return menu;
}

void displayGuest(int menu){
    if(menu == 1){
        printf("Pizza choice");
    }
    else{
        printf("Spaghetti choice");
    }
    printf("\n");
}