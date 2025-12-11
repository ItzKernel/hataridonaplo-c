#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

char *get_month_name(int month) {
  char *months[] = {"",        "Januar",   "Februar", "Marcius",   "Aprilis",
                    "Majus",   "Junius",   "Julius",  "Augusztus", "Szeptember",
                    "Oktober", "November", "December"};

  if (month >= 1 && month <= 12) {
    return months[month];
  }

  return "?";
}

typedef struct MonthInfo {
  int year;
  int month;
  struct MonthInfo *next;
} MonthInfo;

void free_month_list(MonthInfo *head) {
  MonthInfo *iter = head;
  while (iter != NULL) {
    MonthInfo *temp = iter->next;
    free(iter);
    iter = temp;
  }
}

int month_exists(MonthInfo *head, int year, int month) {
  for (MonthInfo *iter = head; iter != NULL; iter = iter->next) {
    if (iter->year == year && iter->month == month) {
      return 1;
    }
  }
  return 0;
}

void add_month_if_new(MonthInfo **head, int year, int month) {
  if (!month_exists(*head, year, month)) {
    MonthInfo *new = malloc(sizeof(MonthInfo));
    new->year = year;
    new->month = month;
    new->next = *head;
    *head = new;
  }
}

typedef struct MonthMenuData {
  int year;
  int month;
} MonthMenuData;

MENU(menu_month_events, {
  CLEAR_SCREEN();

  //
  MonthMenuData *data = (MonthMenuData *)state->menu_args;
  if (data == NULL)
    return;

  printf("Honaphoz tartozo esemenyek (%d. %s)\n\n", data->year,
         get_month_name(data->month));

  int i = 0;
  for (EventListNode *iter = state->event_list_head; iter != NULL;
       iter = iter->next) {
    Event e = iter->event;

    if (e.date.year == data->year && e.date.month == data->month) {
      char *date = date_to_str(e.date);
      char *time = time_to_str(e.time);

      printf("%d. | %s | %s | %s | %s | %s\n", iter->id + 1, date, time, e.place,
             e.title, e.description);

      free(date);
      free(time);
      i++;
    }
  }

  if (i == 0) {
    printf("Nincsenek esemenyek ebben a honapban\n");
  } else {
    printf("\n[Sorszam] Esemeny kivalasztasa\n");
  }

  printf("[0] Vissza\n");
  printf("> ");
  scanf("%hhu", &choice);
  printf("\n");

  switch (choice) {
  case 0:
    free(data);
    state->menu_args = NULL;
    return;
  default:
    if (i > 0 && choice >= 1) {
      MonthMenuData *saved_data = data;

      for (EventListNode *iter = state->event_list_head; iter != NULL;
           iter = iter->next) {
        Event e = iter->event;

        if (e.date.year == saved_data->year &&
            e.date.month == saved_data->month) {
          if (iter->id == choice - 1) {
            EventMenuData *event_data = malloc(sizeof(EventMenuData));
            event_data->id = iter->id;
            state->menu_args = event_data;
            menu_event(state);

            // restore state
            state->menu_args = saved_data;
            break;
          }
        }
      }
    } else {
      printf("Hibas valasz!\n");
      WAIT_FOR_ENTER();
    }
    break;
  }
});

MENU(menu_months, {
  CLEAR_SCREEN();

  printf("Honapok\n\n");

  MonthInfo *months = NULL;
  for (EventListNode *iter = state->event_list_head; iter != NULL;
       iter = iter->next) {
    Event e = iter->event;
    add_month_if_new(&months, e.date.year, e.date.month);
  }

  int i = 0;
  MonthInfo *iter = months;
  while (iter != NULL) {
    printf("%d. %d. %s\n", i + 1, iter->year, get_month_name(iter->month));
    i++;
    iter = iter->next;
  }

  if (i == 0) {
    printf("Nincsenek esemenyek\n");
  } else if (i == 1) {
    printf("\n[1] Honap kivalasztasa\n");
  } else {
    printf("\n[1-%d] Honap kivalasztasa\n", i);
  }

  printf("[0] Vissza\n");
  printf("> ");
  scanf("%hhu", &choice);
  printf("\n");

  switch (choice) {
  case 0:
    free_month_list(months);
    return;
  default:
    if (i > 0 && choice >= 1 && choice <= i) {
      MonthInfo *selected = months;

      for (int j = 1; j < choice; j++)
        selected = selected->next;

      MonthMenuData *data = malloc(sizeof(MonthMenuData));
      data->year = selected->year;
      data->month = selected->month;
      state->menu_args = data;

      free_month_list(months);
      menu_month_events(state);
    } else {
      free_month_list(months);
      printf("Hibas valasz!\n");

      WAIT_FOR_ENTER();
    }
    break;
  }
});
