#include "menu.h"

MENU(menu_main, {
  CLEAR_SCREEN();

  // TODO: use VERSION
  printf("Hataridonaplo 0.1\n");
  printf("\n[1] Esemenyek kilistazasa\n");
  printf("[2] Uj esemeny hozzaadasa\n");
  printf("[3] Hetek\n");
  printf("[4] Honapok\n");
  printf("[0] Kilepes\n");
  printf("> ");
  scanf("%hhu", &choice);
  printf("\n");

  state->menu_args = NULL;

  switch (choice) {
  case 0:
    return;
  case 1:
    menu_list(state);
    break;
  case 2:
    menu_add(state);
    break;
  case 3:
    menu_weeks(state);
    break;
  case 4:
    menu_months(state);
    break;
  default:
    printf("Hibas valasz!\n");
    WAIT_FOR_ENTER();
    break;
  }
});
