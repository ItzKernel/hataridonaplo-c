#include "state.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int parse_date(Date *d, char *str) {
  int len = strlen(str);
  char *copy = malloc((len + 1) * sizeof(char));
  strncpy(copy, str, len);
  copy[len] = '\0';

  // use strtok_r because static storage is "meh"
  char *saveptr;
  char *token = strtok_r(copy, "-", &saveptr);

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

  free(copy);

  return 0;
}

int parse_time(Time *t, char *str) {
  int len = strlen(str);
  char *copy = malloc((len + 1) * sizeof(char));
  strncpy(copy, str, len);
  copy[len] = '\0';

  // use strtok_r because static storage is "meh"
  char *saveptr;
  char *token = strtok_r(copy, ":", &saveptr);

  if (token == NULL)
    return 1;
  t->hour = atoi(token);

  token = strtok_r(NULL, ":", &saveptr);
  if (token == NULL)
    return 1;
  t->minute = atoi(token);

  free(copy);

  return 0;
}

int validate_time(Time *t) {
  if (
    t->hour < 0 || 23 < t->hour || t->minute < 0 || 59 < t->minute
  ) return 1;

  return 0;
}

int validate_date(Date *d) {
  if (
    // couldn't possibly convert these insane years to unix timestamps lolol
    d->year < 0 || 9999 < d->year || d->month < 0 || 12 < d->month || d->day < 0 || 31 < d->day
  ) return 1;

  // edge cases (buh)

  // leap year
  if (d->month == 2) {
    if (d->year % 4 == 0 && 29 < d->day) return 1;
    else if (d->year % 4 != 0 && 28 < d->day) return 1;
  }

  if ((d->month == 4 || d->month == 6 || d->month == 9 || d->month == 11) && 30 < d->day)
    return 1;

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
    remove_newl(line_buf);
    parse_event(&e, line_buf);

    new->event = e;
    new->next = head;
    head = new;
  };

  state->db_file = filename;
  state->event_list_head = head;
  state->menu_args = NULL;

  return 0;
}

char* date_to_str(Date d) {
  char *str = malloc(11 * sizeof(char));
  sprintf(str, "%04d-%02d-%02d", d.year, d.month, d.day);
  str[10] = '\0';

  return str;
}

char* time_to_str(Time t) {
  char *str = malloc(6 * sizeof(char));
  sprintf(str, "%02d:%02d", t.hour, t.minute);
  str[5] = '\0';

  return str;
}

// returns a pointer because returning an event is optional!
Event* find_event_by_index(EventListNode *head, int index) {
  for (int i = 0; i < index; i++) {  
    if (head->next == NULL) return NULL;
    head = head->next;
  }

  return &head->event;
}

int remove_node(EventListNode **head_ptr, int index) {
  EventListNode *head = *head_ptr;

  if (index == 0) {
    EventListNode *next = head->next;
    *head_ptr = next;
    free_event_strings(&head->event);
    free(head);

    reindex(*head_ptr);
    return 0;
  }

  for (int i = 0; i < index - 1; i++) {  
    if (head->next == NULL) return 1; 
    head = head->next;
  }

  EventListNode *mod = head;
  EventListNode *del = head->next;
  head = head->next->next;
  mod->next = head;

  free_event_strings(&del->event);
  free(del);

  reindex(*head_ptr);

  return 0;
}

void reindex(EventListNode *head) {
  int i = 0;
  for (EventListNode *iter = head; iter != NULL; iter = iter->next) {
    iter->id = i;
    i++;
  }
}

int add_event(EventListNode *head, Event e) {
  EventListNode *iter = head;
  for (; iter->next != NULL; iter = iter->next);

  EventListNode *new = malloc(sizeof(EventListNode));
  new->event = e;
  new->id = iter->id + 1;
  new->next = NULL;

  iter->next = new;

  return 0;
}

void sort(EventListNode *head) {

}
