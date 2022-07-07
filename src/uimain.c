#include <stdio.h>
#include <stdlib.h>
#include "history.h"
#include "tokenizer.h"

int main() {
  printf("Welcome to the string tokenizer! Please enter 'q' to quit, 'h' to display history or enter a string to be tokenized\n> ");
  List *history = init_history();

  while (1) {
    char sentence[100];
    char *ptr = sentence;
    int counter = 0;
    char c;
    while ((c = getchar()) != '\n' && counter < 99) {
      *(ptr + counter) = c;
      counter++;
    }
    *(ptr + counter) = '\0';
    if (sentence[0] == 'q' && sentence[1] == '\0') {
      free_history(history);
      break;
    }
    else if (sentence[0] == 'h' && sentence[1] == '\0') print_history(history);
    else {
      add_history(history, sentence);
      char **tokenVector = tokenize(ptr);
      print_tokens(tokenVector);
      free_tokens(tokenVector);
    }
    
    //    int len = 0;
    // char *tmp = userin;
    //while (*tmp != '\0') {
    //tmp++;
    //len++;
    //}
  }
  return 0;
}
