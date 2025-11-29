#include "menu.h"


MENU(menu_event, {
  CLEAR_SCREEN();

  printf("Esemeny\n");

  printf("[0] Vissza [1] Modositas [2] Torles\n");
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

