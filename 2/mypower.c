#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Check if the string is a number
int is_number(char *str) {
  char *endptr;
  strtod(str, &endptr);
  return endptr != str;
}

// Check if the arguments are correct
int is_correct_args(int args, char *argv[]) {
  return (args == 2 && is_number(argv[1]))
      || (args == 3 && is_number(argv[1]) && is_number(argv[2]));
}

int main(int args, char *argv[]) {
  // Check if the arguments are correct
  if (!is_correct_args(args, argv)) {
    puts("Usage: mypower num [num]");
    return 1;
  }

  // Calculate the power
  if (args == 2) {
    double argv1_d = atof(argv[1]);
    printf("%f\n", pow(argv1_d, 2.0));
  }
  else if (args == 3) {
    double argv1 = atof(argv[1]);
    double argv2 = atof(argv[2]);
    printf("%f\n", pow(argv1, argv2));
  }

  return 0;
}
