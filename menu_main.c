#include "menu.h"

MENU(menu_main, {
  CLEAR_SCREEN();

  // TODO: use VERSION
  printf("Hataridonaplo 0.1\n");
  printf("\n[1] Esemenyek kilistazasa\n");
  printf("[2] Uj esemeny hozzaadasa\n");
  printf("[3] Hetek\n");
  printf("[4] Honapok\n");
  printf("[0] Kilepes mentessel\n");
  printf("[69] Kilepes mentes nelkul\n");
  printf("> ");
  scanf("%hhu", &choice);
  printf("\n");

  state->menu_args = NULL;

  switch (choice) {
  case 69:
    return;
  case 0:
    sort_event_list(&state->event_list_head);
    if (save_state(state) != 0) {
      printf("Hiba a mentes soran!\n");
    }
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
