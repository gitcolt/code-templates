#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define MAX_TEMPLATE_TYPE_STRING_SIZE 20

void usage() {
  fprintf(stderr,
      "Usage: template -t TYPE [DEST]\n"
      "Ex:\n"
      "    template -t sdl2\n"
      "\n"
      );
}

int main(int argc, char *argv[]) {

  int template_type_supplied = 0;
  char template_type[MAX_TEMPLATE_TYPE_STRING_SIZE];

  int opt;
  while ((opt = getopt(argc, argv, "t:")) != -1) {
    switch (opt) {
      case 't':
        if (strlen(optarg) > sizeof(template_type) - 1) {
          fprintf(stderr, "Template type argument is too long!\n");
          usage();
          return 1;
        }
        strncpy(template_type, optarg, sizeof(template_type) - 1);
        template_type[strlen(optarg)] = '\0';
        printf("You chose template type %s\n", template_type);
        template_type_supplied = 1;
        break;
      default:
        usage();
        return 1;
    }
  }

  if (!template_type_supplied) {
    fprintf(stderr, "Must supply a template type\n");
    usage();
    return 1;
  }

  int num_non_option_args = argc - optind;
  if (num_non_option_args > 1) {
    usage();
    return 1;
  }

  const char *dest = (num_non_option_args == 1) ?
    argv[optind++] :
    ".";

  printf("dest: %s\n", dest);

  return 0;
}
