#include "menu.h"
#include <stdlib.h>


MENU(menu_list, {
  CLEAR_SCREEN();

  printf("Esemenylista\n");
  
  int i = 0;
  for (EventListNode *iter = state->event_list_head; iter != NULL; iter = iter->next) {
    Event e = iter->event;
    char* date = date_to_str(e.date);
    char* time = time_to_str(e.time);

    printf("%d. | %s | %s | %s | %s | %s\n", i + 1, date, time, e.place, e.title, e.description);

    free(date);
    free(time);

    i++;
  }

  if (i == 1)
    printf("\n[1] Esemeny kivalasztasa\n");
  else if (i > 1) {
    printf("\n[1-%d] Esemeny kivalasztasa\n", i);
  } else {
    printf("Az esemenyek listaja ures\n");
  }

  // bad UX but not going to fix
  printf("[%d] Kereses\n", i + 1);
  printf("[0] Vissza\n");
  printf("> ");
  scanf("%hhu", &choice);
  printf("\n");

  switch (choice) {
    case 0:
      return;
    default:
      if (i > 0 && choice >= 1 && choice <= i) {
        EventMenuData *data = malloc(sizeof(EventMenuData));

        data->id = choice - 1;

        state->menu_args = data;
        menu_event(state);
        break;
      }
      else if (choice == i + 1) {
        printf("kjahsdflksa\n");
      }

      printf("Hibas valasz!\n");
      WAIT_FOR_ENTER();
      break;
  }
});
