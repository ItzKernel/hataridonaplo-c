#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// if i dont do this, getchar in the prompt may read the previous buffered
// characters
void flush() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

int prompt_date_into_dest(Date *dest) {
  char buf[11];
  printf("Mi legyen az uj ertek?\n");
  printf("> ");

  flush();

  scanf("%10[^\n]", buf);

  Date d;
  if (parse_date(&d, buf) != 0 || validate_date(&d))
    return 1;

  *dest = d;

  return 0;
}

int prompt_time_into_dest(Time *dest) {
  char buf[6];
  printf("Mi legyen az uj ertek?\n");
  printf("> ");

  flush();

  scanf("%5[^\n]", buf);

  Time t;
  if (parse_time(&t, buf) != 0 || validate_time(&t))
    return 1;

  *dest = t;

  return 0;
}

void prompt_str_into_dest(char **dest) {
  char buf[128];
  printf("Mi legyen az uj ertek?\n");
  printf("> ");

  flush();

  scanf("%127[^\n]", buf);

  int len = strlen(buf);
  char *str = malloc((len + 1) * sizeof(char));
  strncpy(str, buf, len + 1);
  free(*dest);
  *dest = str;
}

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
  char *date = date_to_str(selected_event->date);
  char *time = time_to_str(selected_event->time);
  printf("Datum: %s\n", date);
  printf("Idopont: %s\n", time);
  printf("Hely: %s\n", selected_event->place);
  printf("Cim: %s\n", selected_event->title);
  printf("Leiras: %s\n", selected_event->description);
  free(date);
  free(time);

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
    default:
      printf("Hibas valasz!\n");
      WAIT_FOR_ENTER();
      break;
  }
});
