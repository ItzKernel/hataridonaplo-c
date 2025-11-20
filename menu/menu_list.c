#include "menu.h"

MENU(menu_list, {
    CLEAR_SCREEN();

    printf("Esemenylista\n");
    printf("[0] Exit\n");
    printf("> ");
    scanf("%hhu", &choice);
    printf("\n");

    switch (choice) {
      case 0:
        return;
      default:
        printf("Hibas valasz!\n");
        WAIT_FOR_ENTER();
        break;
    }
});