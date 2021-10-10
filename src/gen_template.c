#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_TEMPLATE_TYPE_STRING_SIZE 20

int verbose = 0;

void usage() {
  fprintf(stderr,
      "Usage: template -t TYPE [DEST]\n"
      "Ex:\n"
      "    template -t sdl2\n"
      "\n"
      );
}

int valid_template_type(const char *template_type, const char *templates_dir) {
  struct dirent *dir;
  DIR *d = opendir(templates_dir);
  if (d == NULL) {
    fprintf(stderr, "Could not open templates directory \"%s\"\n", templates_dir);
    exit(1);
  }

  if (verbose)
    printf("Searching for template \"%s\" in \"%s\"\n", template_type, templates_dir);

  int template_found = 0;
  while ((dir = readdir(d)) != NULL) {
    if (!strcmp(".", dir->d_name) || !strcmp("..", dir->d_name))
      continue;
    if (!strcmp(template_type, dir->d_name)) {
      template_found = 1;
      break;
    }
  }
  closedir(d);

  return template_found;
}

int main(int argc, char *argv[]) {

  int template_type_supplied = 0;
  char template_type[MAX_TEMPLATE_TYPE_STRING_SIZE];

  int opt;
  while ((opt = getopt(argc, argv, "t:v")) != -1) {
    switch (opt) {
      case 't':
        if (strlen(optarg) > sizeof(template_type) - 1) {
          fprintf(stderr, "Template type argument is too long!\n");
          return 1;
        }
        strncpy(template_type, optarg, sizeof(template_type) - 1);
        template_type[strlen(optarg)] = '\0';
        if (!valid_template_type(template_type, "../templates")) {
          fprintf(stderr, "Template \"%s\" not found\n", template_type);
          return 1;
        }

        if (verbose)
          printf("Found template \"%s\"\n", template_type);

        template_type_supplied = 1;
        break;
      case 'v':
        verbose = 1;
        break;
      default:
        usage();
        return 1;
    }
  }

  if (!template_type_supplied) {
    fprintf(stderr, "Must supply a template type\n\n");
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
