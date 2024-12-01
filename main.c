#include "lib.h"
#include <dlfcn.h> // For dynamic linking
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function pointer types for part1 and part2
typedef char *(*part_func)(char *input);

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <day>\n", argv[0]);
    return EXIT_FAILURE;
  }

  int day = atoi(argv[1]);
  if (day < 1 || day > 25) {
    fprintf(stderr, "Day must be between 1 and 25.\n");
    return EXIT_FAILURE;
  }

  // Load input for the day
  load_aoc_input(day);

  // get binary path from argv[0]
  char *binary_path = realpath(argv[0], NULL);
  if (!binary_path) {
    perror("Failed to get binary path");
    return EXIT_FAILURE;
  }

  // get the directory of the binary
  char *binary_dir = dirname(binary_path);

  // Construct the shared library path
  char lib_path[256];
  snprintf(lib_path, sizeof(lib_path), "%s/solutions/%d.so", binary_dir, day);

  // Load the shared library for the solution
  void *handle = dlopen(lib_path, RTLD_NOW);
  if (!handle) {
    fprintf(stderr, "Failed to load solution for Day %d: %s\n", day, dlerror());
    free(aoc_input);
    return EXIT_FAILURE;
  }

  // Load the part1 and part2 functions
  part_func part1 = (part_func)dlsym(handle, "part1");
  part_func part2 = (part_func)dlsym(handle, "part2");

  if (!part1 || !part2) {
    fprintf(stderr, "Failed to load functions from Day %d: %s\n", day,
            dlerror());
    dlclose(handle);
    free(aoc_input);
    return EXIT_FAILURE;
  }

  // Run part1 and part2
  printf("Part 1: %d\n", part1(aoc_input));
  printf("Part 2: %d\n", part2(aoc_input));

  // Clean up
  dlclose(handle);
  free(aoc_input);

  return EXIT_SUCCESS;
}
