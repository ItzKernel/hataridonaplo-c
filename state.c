#include "state.h"

#include <stdlib.h>
#include <unistd.h>

int parse_date(Date *d, char *str) {
  char *saveptr;
  // use strtok_r because static storage is "meh"
  char *token = strtok_r(str, "-", &saveptr);

  if (token == NULL)
    return 1;
  d->year = atoi(token);

  token = strtok_r(NULL, "-", &saveptr);
  if (token == NULL)
    return 1;
  d->month = atoi(token);

  token = strtok_r(NULL, "-", &saveptr);
  if (token == NULL)
    return 1;
  d->day = atoi(token);

  return 0;
}

int parse_time(Time *t, char *str) {
  char *saveptr;
  // use strtok_r because static storage is "meh"
  char *token = strtok_r(str, ":", &saveptr);

  if (token == NULL)
    return 1;
  t->hour = atoi(token);

  token = strtok_r(NULL, ":", &saveptr);
  if (token == NULL)
    return 1;
  t->minute = atoi(token);

  return 0;
}

// TODO: maybe add a limit for event string lengths
int parse_event(Event* e, char *str) {
  char *saveptr;
  // use strtok_r because static storage is "meh"
  char *token = strtok_r(str, ";", &saveptr);

  if (token == NULL)
    return 1;
  Date d;
  parse_date(&d, token);
  e->date = d;

  token = strtok_r(NULL, ";", &saveptr);
  if (token == NULL)
    return 1;
  Time t;
  parse_time(&t, token);
  e->time = t;

  token = strtok_r(NULL, ";", &saveptr);
  if (token == NULL)
    return 1;
  e->place = (char*) malloc((strlen(token) + 1) * sizeof(char));
  strcpy(e->place, token);

  token = strtok_r(NULL, ";", &saveptr);
  if (token == NULL)
    return 1;
  e->title = (char*) malloc((strlen(token) + 1) * sizeof(char));
  strcpy(e->title, token);

  token = strtok_r(NULL, ";", &saveptr);
  if (token == NULL)
    return 1;
  e->description = (char*) malloc((strlen(token) + 1) * sizeof(char));
  strcpy(e->description, token);

  return 0;
}

void free_event_strings(Event *e) {
  // TODO: handle if these are empty
  free(e->place);
  free(e->title);
  free(e->description);
}

void free_event_list(EventListNode *head) {
  EventListNode *iter = head;

  while (iter != NULL) {
    EventListNode *temp = iter->next;

    free_event_strings(&(iter->event));
    free(iter);
    iter = temp;
  }
}

int restore_state(State *state, char *filename) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("Nem sikerult megnyitni a fajlt");
    return 1;
  }

  EventListNode *head = NULL;

  char line_buf[1001];
  while (fgets(line_buf, 1001, fp) != NULL) {
    EventListNode *new = malloc(sizeof(EventListNode));
    Event e;
    parse_event(&e, line_buf);

    new->event = e;
    new->next = head;
    head = new;
  };

  state->db_file = filename;
  state->event_list_head = head;

  return 0;
}
