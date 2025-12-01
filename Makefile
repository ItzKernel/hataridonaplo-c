srcs := main.c state.c util.c menu.c menu_main.c menu_list.c menu_event.c menu_add.c menu_weeks.c menu_months.c
hs := main.h state.h util.h menu.h

main: $(srcs) $(hs)
	cc -o main -Wall -Werror $(srcs) $(hs)
