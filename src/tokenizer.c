#include <stdio.h>
#include <stdlib.h>
#include "history.h"
#include "tokenizer.h"

/* Return true (non-zero) if c is a whitespace character
   ('\t' or ' ').
   Zero terminators are not printable (therefore false). */
int space_char(char c)
{
  return (c == '\t' || c == ' ' || c == '\0') ? 1 : 0;
}

/* Return true (non-zero) if c is a non-whitespace character
   ('\t' or ' ').
   Zero terminators are not printable (therefore false). */
int non_space_char(char c)
{
  return (c == '\t' || c == ' ' || c == '\0') ? 0 : 1;
}

/* Returns a pointer to the first character of the next
   space-separated word in a zero-terminated str. Return a zero pointer if
   str does not contain any words. */
char *word_start(char *str)
{
  /* Loops until end of input or until a non-space character is found. */
  while (*str) {
    if (non_space_char(*str))
      return str;
    else str++;
  }
  return str;
}

/* Returns a pointer terminator char following *word */
char *word_terminator(char *word)
{
  /* Loops until end of input or until a space character is found. */ 
  while (*word) {
    if (space_char(*word))
      return word;
    else word++;
  }
  return word;
}

/* Counts the number of words in the string argument. */
int count_words(char *str)
{
  int count = 0;
  
  /* Loop uses word_start to remove any leading spaces. If the
pointer has reached the end of the string, the if statment will
detect this and not allow word count to be incremented.
word_count is then utilized to move the pointer to the end of a
word or the end of the input. The loop will restart and continue
moving the pointer to count words or count will be returned.*/
  while (*str) {
    str = word_start(str);
    if (*str)
      count++;
    str = word_terminator(str);
  }
  return count;
}

/* Returns a freshly allocated new zero-terminated string
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len) {
  
  /* Dynamically allocating memory based on length of user
     input (determined in uimain.c). */
  char *cpy = malloc((len+1) * sizeof(char));
  char *ret = cpy;
  /* This while loop works by first copying the value from
     inStr to cpy then incrementing the pointer. It is not
     necessary to compare values against '\0' because the
     loop continues as long as it is true. */
  int count = 0;
  while (count < len && *inStr) {
    *cpy++ = *inStr++;
    count++;
  }
  return ret;
}

/* Returns a frshly allocated zero-terminated vector of freshly allocated
   space-separated tokens from zero-terminated str.

   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string"
     tokens[3] = 0
*/
char **tokenize(char* str) {
  /* Dynamically allocating space for each token */
  int num_tokens = count_words(str);
  char **tokens = malloc(sizeof(char*) * num_tokens + 1);

  /* Loop uses word_start and word_terminator to locate the first and last 
     characters of each token. copy_str is then utilized to copy the
     individual token and a pointer is set to its address.*/
  char *terminator;
  for (int i = 0; i < num_tokens; i++) {
    str = word_start(str);
    terminator = word_terminator(str);
    *(tokens + i) = copy_str(str, (terminator - str));
    str = terminator;
  }
  /* Loop began from zero, therefore the zero terminator must be placed at
     tokens + num_tokens. */
  *(tokens + num_tokens) = '\0';
  return tokens;
}

/* Prints all tokens*/
void print_tokens(char **tokens) {
  int count = 0;
  while (*tokens) {
    printf("token[%d] = %s\n", count, *tokens);
    count++;
    tokens++;
  }
  printf("token[%d] = 0\n", count);
}

/* Frees all tokens and the vector containing them. */
void free_tokens(char **tokens) {
  int count = 0;
  while (*tokens) {
    free(*tokens);
    tokens++;
    count++;
  }
  tokens -= count;
  free(tokens);
}
