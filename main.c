#include "main.h"

void print_help() {
  printf("hataridonaplo v%s\n\n", VERSION);

  printf("Hasznalat:\n");
  printf("\thataridonaplo\n");
  printf("\thataridonaplo adatbazis.csv\n");
  printf("\thataridonaplo --help\n\n");

  printf("Flagek:\n");
  printf("    --help\t-h:\t\thelp menu kiirasa\n");
}

int main(int argc, char **argv) {
#if DEBUG
  printf("args: %d\n", argc);
#endif

  char *db_file = "hataridonaplo.csv";

  // argument parsing
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      // int arglen = strlen(argv[i]);

      // if it's a flag
      if (argv[i][0] == '-') {
        // if the user is asking for a help menu
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
          print_help();
          return 0;
        }
      } else {
        db_file = argv[i];

        // break from the for loop because we don't want to
        // keep parsing after setting the database file
        break;
      }
    }
  }

#if DEBUG
  printf("Adatbazisfajl hasznalata: %s\n", db_file);
  printf("Allapot visszaallitasa...\n");
#endif

  State state;
  if (restore_state(&state, db_file) != 0) {
    printf("Hiba az allapot visszaallitasa soran. Kilepes...\n");
    return 0;
  }

#if DEBUG
  printf("Allapot visszaallitasa sikeres! A folytatashoz nyomj Entert.\n");
  // not using WAIT_FOR_ENTER macro because it apparently doesn't work well
  // outside a while loop
  getchar();
#endif

  state.menu_args = NULL;

  // yes, i do think that using function ptrs would've been a much nicer
  // approach but i thought i could get away with this simpler solution instead.
  menu_main(&state);

  sort_event_list(&state.event_list_head);
  if (save_state(&state) != 0) {
    printf("Hiba a mentes soran!\n");
  }

  free_event_list(state.event_list_head);

  return 0;
}
