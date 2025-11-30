#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

// won't make this a full-fledged menu because the specification doesn't specify
// it being one
void prompt_edit_event(Event *event) {
  unsigned char choice;

  printf("Melyiket tulajdonsagot szeretned modositani?\n");
  printf("[1] Datum\n");
  printf("[2] Ido\n");
  printf("[3] Hely\n");
  printf("[4] Cim\n");
  printf("[5] Leiras\n");
  printf("[0] Megse\n");
  printf("> ");
  scanf("%hhu", &choice);
  printf("\n");

  switch (choice) {
    case 1:
      if (prompt_date_into_dest(&event->date) != 0) {
        printf("Valami nem stimmel. Nem tortent modositas.\n");
        WAIT_FOR_ENTER();
      }
      break;
    case 2:
      if (prompt_time_into_dest(&event->time) != 0) {
        printf("Valami nem stimmel. Nem tortent modositas.\n");
        WAIT_FOR_ENTER();
      }
      break;
    case 3:
      prompt_str_into_dest(&event->place);
      break;
    case 4:
      prompt_str_into_dest(&event->title);
      break;
    case 5:
      prompt_str_into_dest(&event->description);
      break;
    default:
      break;
  }
}

MENU(menu_event, {
  CLEAR_SCREEN();

  printf("Esemeny\n");

  EventMenuData data = *(EventMenuData *)state->menu_args;
  Event *selected_event = find_event_by_index(state->event_list_head, data.id);
  print_event(selected_event);

  printf("\n[1] Modositas\n");
  printf("[2] Torles\n");
  printf("[0] Vissza\n");
  printf("> ");
  scanf("%hhu", &choice);
  printf("\n");

  switch (choice) {
    case 0:
      free(state->menu_args);
      return;
    case 1:
      prompt_edit_event(selected_event);
      break;
    case 2:
      remove_node(&state->event_list_head, data.id);
      free(state->menu_args);
      return;
    default:
      printf("Hibas valasz!\n");
      WAIT_FOR_ENTER();
      break;
  }
});
