#include "menu.h"

MENU(menu_main, {
  CLEAR_SCREEN();

  // TODO: use VERSION
  printf("Hataridonaplo 0.1\n");
  printf("[1] Esemenyek kilistazasa\n");
  printf("[2] Uj esemeny hozzaadasa\n");
  printf("[0] Kilepes\n");
  printf("> ");
  scanf("%hhu", &choice);
  printf("\n");

  switch (choice) {
    case 0:
      return;
    case 1:
      menu_list(s);
      break;
    case 2:
      printf("Meg nincs implementalva.\n");
      WAIT_FOR_ENTER();
      break;
    default:
      printf("Hibas valasz!\n");
      WAIT_FOR_ENTER();
      break;
  }
});
