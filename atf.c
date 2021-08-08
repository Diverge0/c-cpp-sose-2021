#include "atf.h"
#include <stdio.h>
#include <stdlib.h>

#define INCR 8

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

int count_up(int* minIndex, int* currentIndex, int* maxIndex, int current){
  if(current == -1) {
    return 1;
  }
  if(currentIndex[current] < maxIndex[current]){
    currentIndex[current]++;
    return 0;
  } else{
    currentIndex[current] = minIndex[current];
    return count_up(minIndex, currentIndex, maxIndex, current-1);

  }
}

void generate_search_space(tp_t* parameters, int num_parameters,
                           search_space_t* search_space) {
  //malloc search space with initial capacity INCR
  search_space->capacity = INCR;
  search_space->size = 0;
  search_space->configurations = (configuration_t*)malloc(INCR * sizeof(configuration_t));

  int minIndex[num_parameters];
  int currentIndex[num_parameters];
  int maxIndex[num_parameters];
  for(int i=0; i<num_parameters;i++){
    minIndex[i] = parameters[i].min;
    currentIndex[i] = parameters[i].min;
    maxIndex[i] = parameters[i].max;
  }

  //check if configuration is valid
  int finished = 0;
  while(!finished){
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
      //print_configuration(currentIndex, num_parameters);

      tp_t** stored_parameters = malloc(num_parameters * sizeof(tp_t*));
      for(int i=0; i<num_parameters; i++){
        stored_parameters[i] = &parameters[i];
      }

      int* stored_values = malloc(num_parameters * sizeof(int));
      for(int i=0; i<num_parameters; i++){
        stored_values[i] = currentIndex[i];
      }

      //expand array for configurations
      configuration_t current_conf = {stored_parameters, stored_values, num_parameters};
      if(search_space->capacity <= search_space->size){
        search_space->configurations = realloc(search_space->configurations, ((search_space->capacity + INCR) * sizeof(configuration_t)));
        search_space->capacity += INCR;
        printf("foo");
      }

      search_space->configurations[search_space->size] = current_conf;
      search_space->size++;
    }

    //count up
    finished = count_up(minIndex, currentIndex, maxIndex, num_parameters-1);
  }
}
configuration_t get_config(search_space_t* search_space, int index) {
  return search_space->configurations[index];
}
void free_search_space(search_space_t* search_space) {
  for(int i=0; i<search_space->size; i++){
    free(search_space->configurations[i].parameters);
    free(search_space->configurations[i].values);
  }
  free(search_space->configurations);
}

void explore_search_space(search_space_t* search_space, cost_function_t cost_function,
                          SEARCH_STRATEGY search_strategy, ABORT_TYPE abort_type, int abort_value,
                          configuration_t* best_config, int* cost) {
  // Ergänzen Sie hier Ihre Lösung für Aufgabe 3
}
