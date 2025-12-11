#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

// amazing
int get_week_number(Date d) {
  int days_in_months[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  // leap year handling
  if (d.year % 4 == 0) {
    days_in_months[2] = 29;
  }

  int day_of_year = d.day;
  // increment day by month days
  for (int i = 1; i < d.month; i++) {
    day_of_year += days_in_months[i];
  }

  return (day_of_year - 1) / 7 + 1;
}

typedef struct WeekInfo {
  int year;
  int week;
  struct WeekInfo *next;
} WeekInfo;

void free_week_list(WeekInfo *head) {
  WeekInfo *iter = head;

  while (iter != NULL) {
    WeekInfo *temp = iter->next;
    free(iter);
    iter = temp;
  }
}

int week_exists(WeekInfo *head, int year, int week) {
  for (WeekInfo *iter = head; iter != NULL; iter = iter->next) {
    if (iter->year == year && iter->week == week) {
      return 1;
    }
  }
  return 0;
}

void add_week_if_new(WeekInfo **head, int year, int week) {
  if (!week_exists(*head, year, week)) {
    WeekInfo *new = malloc(sizeof(WeekInfo));
    new->year = year;
    new->week = week;
    new->next = *head;
    *head = new;
  }
}

typedef struct WeekMenuData {
  int year;
  int week;
} WeekMenuData;

MENU(menu_week_events, {
  CLEAR_SCREEN();

  WeekMenuData *data = (WeekMenuData *)state->menu_args;
  if (data == NULL)
    return;

  printf("Hethez tartozo esemenyek (%d. ev %d. het)\n\n", data->year,
         data->week);

  int i = 0;
  for (EventListNode *iter = state->event_list_head; iter != NULL;
       iter = iter->next) {
    Event e = iter->event;
    int event_week = get_week_number(e.date);

    if (e.date.year == data->year && event_week == data->week) {
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
    printf("Nincsenek esemenyek ebben a hetben\n");
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
      WeekMenuData *saved_data = data;

      for (EventListNode *iter = state->event_list_head; iter != NULL;
           iter = iter->next) {
        Event e = iter->event;
        int event_week = get_week_number(e.date);

        if (e.date.year == saved_data->year && event_week == saved_data->week) {
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

MENU(menu_weeks, {
  CLEAR_SCREEN();

  printf("Hetek\n\n");

  WeekInfo *weeks = NULL;
  for (EventListNode *iter = state->event_list_head; iter != NULL;
       iter = iter->next) {
    Event e = iter->event;
    int week = get_week_number(e.date);
    add_week_if_new(&weeks, e.date.year, week);
  }

  int i = 0;
  for (WeekInfo *iter = weeks; iter != NULL; iter = iter->next) {
    printf("%d. %d. ev %d. het\n", i + 1, iter->year, iter->week);
    i++;
  }

  if (i == 0) {
    printf("Nincsenek esemenyek\n");
  } else if (i == 1) {
    printf("\n[1] Het kivalasztasa\n");
  } else {
    printf("\n[1-%d] Het kivalasztasa\n", i);
  }

  printf("[0] Vissza\n");
  printf("> ");
  scanf("%hhu", &choice);
  printf("\n");

  switch (choice) {
  case 0:
    free_week_list(weeks);
    return;
  default:
    if (i > 0 && choice >= 1 && choice <= i) {
      WeekInfo *selected = weeks;

      for (int j = 1; j < choice; j++)
        selected = selected->next;

      WeekMenuData *data = malloc(sizeof(WeekMenuData));
      data->year = selected->year;
      data->week = selected->week;
      state->menu_args = data;

      free_week_list(weeks);
      menu_week_events(state);
    } else {
      free_week_list(weeks);
      printf("Hibas valasz!\n");

      WAIT_FOR_ENTER();
    }
    break;
  }
});
