#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// returns length
int prompt_search(char **search) {
  // if i dont initialize the buf like this, length check breaks for some reason
  char buf[128] = {0};
  printf("Mire keressunk?\n");
  // printf("> ");

  flush();

  scanf("%127[^\n]", buf);

  int len = strlen(buf);

  if (len == 0)
    return 0;

  *search = malloc((len + 1) * sizeof(char));
  // memcpy is supposed to do a better job than strcpy
  // because it also copies the null terminator
  // (buffer is initialized with zeroes so we're technically overindexing on purpose)
  strcpy(*search, buf);
  // *search[len - 1] = '\0';

  return len;
}

MENU(menu_list, {
  CLEAR_SCREEN();

  printf("Esemenylista\n");

  // we try to restore the search data (data remains null if we didnt set
  // anything)
  ListMenuData *data = (ListMenuData *)state->menu_args;
  char *search = NULL;
  if (data != NULL) {
    search = data->search;
  }

  int i = 0;
  for (EventListNode *iter = state->event_list_head; iter != NULL;
       iter = iter->next) {
    Event e = iter->event;
    char *date = date_to_str(e.date);
    char *time = time_to_str(e.time);

    // if there's data restored
    if (search != NULL) {
      if (strstr(e.title, search) != NULL)
        printf("%d. | %s | %s | %s | %s | %s\n", iter->id + 1, date, time, e.place,
               e.title, e.description);
    } else { // if not
      printf("%d. | %s | %s | %s | %s | %s\n", iter->id + 1, date, time, e.place,
             e.title, e.description);
    }

    free(date);
    free(time);

    i++;
  }

  if (i == 1) {
    printf("\n[1] Esemeny kivalasztasa\n");
  } else if (i > 1) {
    printf("\n[Sorszam] Esemeny kivalasztasa\n");
    printf("[%d] Kereses\n", i + 1);
  } else {
    printf("Az esemenyek listaja ures\n\n");
  }

  // bad UX but not going to fix
  printf("[0] Vissza\n");
  printf("> ");
  scanf("%hhu", &choice);
  printf("\n");

  if (choice == 0) {
    // on exit we clear the menu arg and return to main menu
    if (data != NULL) {
      if (data->search != NULL) {
        free(data->search);
        data->search = NULL;
      }
      free(data);
      data = NULL;
    }
    state->menu_args = NULL;
    return;
  } else if (i > 0 && choice >= 1 && choice <= i) {
    // we dont have to check here that the id exists,
    // we have everything in order anyway
    ListMenuData *saved_data = data;

    EventMenuData *event_data = malloc(sizeof(EventMenuData));
    event_data->id = choice - 1;

    state->menu_args = event_data;
    menu_event(state);

    // restore menu args
    state->menu_args = saved_data;
  } else if (choice == i + 1 && i > 1) {
    // on search we prompt the user and get a string back
    int len = prompt_search(&search);

    // if we dont get anything we can reset everything search-related
    if (len == 0) {
      if (data != NULL) {
        if (data->search != NULL) {
          free(data->search);
          data->search = NULL;
        }
        free(data);
        data = NULL;
      }
      state->menu_args = NULL;
    } else {
      state->menu_args = malloc(sizeof(ListMenuData));
      ((ListMenuData *)state->menu_args)->search = search;
    }
  }
});
