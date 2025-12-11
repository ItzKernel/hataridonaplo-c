#include "menu.h"
#include <stdlib.h>

MENU(menu_add, {
  CLEAR_SCREEN();

  printf("Esemeny hozzaadasa\n");
  // me when ERROR UNUSED VARIABLE
  // gotta love -Wall -Werror
  choice = 1;
  choice = choice + 1;

  // hacky method to keep editing the same event
  Event *e;
  if (state->menu_args == NULL) {
    Event event;
    Date d;
    Time t;

    // obligated to use my own functions :p
    parse_date(&d, "2000-01-01");
    parse_time(&t, "00:00");
    event.date = d;
    event.time = t;
    event.place = malloc(1 * sizeof(char));
    event.title = malloc(1 * sizeof(char));
    event.description = malloc(1 * sizeof(char));
    event.place[0] = '\0';
    event.title[0] = '\0';
    event.description[0] = '\0';

    AddMenuData *data = malloc(sizeof(AddMenuData));
    data->event = event;
    state->menu_args = data;
    // printf("printing event to be saved\n");
    // print_event(&((AddMenuData*)state->menu_args)->event);
  }

  AddMenuData *data = (AddMenuData *)state->menu_args;
  e = &data->event;

  print_event(e);

  printf("\nMelyiket tulajdonsagot szeretned modositani?\n");
  printf("[1] Datum\n");
  printf("[2] Ido\n");
  printf("[3] Hely\n");
  printf("[4] Cim\n");
  printf("[5] Leiras\n");
  printf("[0] Hozzaad & Vissza\n");
  printf("> ");
  scanf("%hhu", &choice);
  printf("\n");

  switch (choice) {
  case 0:
    add_event(&state->event_list_head, *e);
    sort_event_list(&state->event_list_head);
    free(state->menu_args);
    state->menu_args = NULL;
    return;
  case 1:
    if (prompt_date_into_dest(&e->date) != 0) {
      printf("Valami nem stimmel. Nem tortent modositas.\n");
      WAIT_FOR_ENTER();
    }
    break;
  case 2:
    if (prompt_time_into_dest(&e->time) != 0) {
      printf("Valami nem stimmel. Nem tortent modositas.\n");
      WAIT_FOR_ENTER();
    }
    break;
  case 3:
    prompt_str_into_dest(&e->place);
    break;
  case 4:
    prompt_str_into_dest(&e->title);
    break;
  case 5:
    prompt_str_into_dest(&e->description);
    break;
  default:
    printf("Hibas valasz!\n");
    WAIT_FOR_ENTER();
    break;
  }
});
