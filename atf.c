#include "atf.h"

#include <stdio.h>

void print_configuration(int* values, int num_values) {
  for (int i = 0; i < num_values; ++i) {
    printf("%5d", values[i]);
  }
  printf("\n");
}

tp_t create_tp(char* name, int min, int max, constraint_t constraint) {
  tp_t newtpt = {.name = name, .min = min, .max = max, .constraint = constraint};
  return newtpt;
}

//todo: add to header file
void count_up(int num_parameters, int* currentIndex, int* maxIndex, int current){
  if()
}

void generate_search_space(tp_t* parameters, int num_parameters,
                           search_space_t* search_space) {
  int currentIndex[num_parameters];
  int maxIndex[num_parameters];
  for(int i=0; i<num_parameters;i++){
    currentIndex[i] = parameters[i].min;
    maxIndex[i] = parameters[i].max;
  }

  //check if configuration is valid
  while(~~~){
    int isValid = 1;
    int const_param[10];

    //das geht bestimmt irgendwie schöner
    for(int i=0; i<num_parameters; i++){
      const_param[i] = currentIndex[i];
    }

    //test constraints
    for(int i=0; i<num_parameters; i++){
      if(parameters[i].constraint != NULL){
        if(!parameters[i].constraint(const_param[0], const_param[1], const_param[2], 
                                    const_param[3], const_param[4], const_param[5], 
                                    const_param[6], const_param[7], const_param[8], 
                                    const_param[9])){
          isValid = 0;
        }
        
      }
    }
    if(isValid){
      print_configuration(currentIndex, num_parameters);
    }

    //count up
    for(int i=num_parameters; i>=0; i--){
      if()
    }
  }
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
