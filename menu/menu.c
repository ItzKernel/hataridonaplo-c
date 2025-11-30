#include "menu.h"

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

int prompt_str_into_dest(char **dest) {
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

  return 0;
}

void print_event(Event *event) {
  char *date = date_to_str(event->date);
  char *time = time_to_str(event->time);
  printf("Datum: %s\n", date);
  printf("Idopont: %s\n", time);
  printf("Hely: %s\n", event->place);
  printf("Cim: %s\n", event->title);
  printf("Leiras: %s\n", event->description);
  free(date);
  free(time);
}
