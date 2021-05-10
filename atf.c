#include "atf.h"

#include <stdio.h>

void print_configuration(int* values, int num_values) {
  for (int i = 0; i < num_values; ++i) {
    printf("%5d", values[i]);
  }
  printf("\n");
}

tp_t create_tp(char* name, int min, int max, constraint_t constraint) {
  // Ergänzen Sie hier Ihre Lösung für Aufgabe 1
}

void generate_search_space(tp_t* parameters, int num_parameters,
                           search_space_t* search_space) {
  // Ergänzen Sie hier Ihre Lösung für Aufgabe 1
}
configuration_t get_config(search_space_t* search_space, int index) {
  // Ergänzen Sie hier Ihre Lösung für Aufgabe 2
}
void free_search_space(search_space_t* search_space) {
  // Ergänzen Sie hier Ihre Lösung für Aufgabe 2
}

void explore_search_space(search_space_t* search_space, cost_function_t cost_function,
                          SEARCH_STRATEGY search_strategy, ABORT_TYPE abort_type, int abort_value,
                          configuration_t* best_config, int* cost) {
  // Ergänzen Sie hier Ihre Lösung für Aufgabe 3
}
