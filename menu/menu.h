#ifndef MENU_H
#define MENU_H

#include <stdbool.h>
#include "../state.h"
#include "../util.h"
#include "../debugmalloc.h"

#define MENU_DEFINITION(name) \
void name(State *state);

// TODO?: put screen clearing into the macro at the start of the while loop
#define MENU(name, logic) \
void name(State *state) { \
    unsigned char choice; \
    while (true) { \
        logic \
    } \
}

#define CLEAR_SCREEN() \
printf("\e[1;1H\e[2J");

#define WAIT_FOR_ENTER() \
while(getchar()!='\n'); \
getchar();

MENU_DEFINITION(menu_list);
MENU_DEFINITION(menu_main);
MENU_DEFINITION(menu_event);
MENU_DEFINITION(menu_add);

int prompt_date_into_dest(Date *dest);
int prompt_time_into_dest(Time *dest);
int prompt_str_into_dest(char **dest);

void print_event(Event *event);

#endif
