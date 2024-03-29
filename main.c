#include "guest.h"
#include "menu.h"

int main(){
    int menu;

    displayMenu();
    menu = addGuest();
    displayGuest(menu);
    return 0;
}