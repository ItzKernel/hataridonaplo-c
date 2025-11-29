srcs := main.c state.c util.c menu/menu_main.c menu/menu_list.c
hs := main.h state.h util.h menu/menu.h #menu/menu_main.h menu/menu_list.h

main: $(srcs) $(hs)
	cc -o main -Wall -Werror $(srcs) $(hs)
