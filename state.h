#ifndef STATE_H
#define STATE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "debug.h"

typedef struct Date {
  int year;
  int month;
  int day;
} Date;

typedef struct Time {
  int hour;
  int minute;
} Time;

typedef struct Event {
  Date date;
  Time time;
  char *place;
  char *title;
  char *description;
} Event;

typedef struct EventListNode {
  Event event;
  struct EventListNode *next;
} EventListNode;

typedef struct State {
  char* db_file;

  // events linked list
  EventListNode *event_list_head;
} State;

/*
 * @brief Makes a date from the input string.
 * @param d pointer to a date
 * @param str input string with format "YYYY-MM-DD"
 * @return 0 on success, non-zero value otherwise
 *
 * Modifies the input string.
 */
int parse_date(Date *d, char *str);

/*
 * @brief Makes a time from the input string.
 * @param d pointer to a time
 * @param str input string with format "hh:mm"
 * @return 0 on success, non-zero value otherwise
 *
 * Modifies the input string.
 */
int parse_time(Time *t, char *str);

void free_event_list(EventListNode *head);
int restore_state(State *state, char* filename);

#endif
