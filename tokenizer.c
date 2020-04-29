#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"



//will check if char is  a tab or space
int space_char(char c)
{
  if(c == '\t' || c == ' ')
    {
      return 1; //using 1 as my true
    }
  return 0; //false
}


//will check if char is a letter or not a space or tab
int non_space_char(char c)
{
  if(c != '\t' && c != ' ' && c != '\0' ) //zero terminators are not printable
    {
      return 1; //if char is not a tab or space it's true
    }
  return 0;
}

/* returns a pointer to the FIRST char of the NEXT space separated word*/
char *word_start(char *str)
{
  //traverse all the letters of the current word
  while(non_space_char(*str))
    {
      str++; //go to next letter
    }
  //traverse all the spaces and tabs
  while(space_char(*str))
    {
      str++;
    }
  // If we are at the end of the string (no more words), return NULL
  // to indicate that we have run out
  if (*str == '\0')
    {
      return NULL;
    }
  else
    {
      // Return the pointer to the next word
      // (str now points to the start of the next word due to above while loops)
      return str;
    }
}

//word end
char *word_end(char *str)
{
  while(non_space_char(*str)) //while a letter
    {
      str++;
    }
  if(*str == '\0') //if  string is empty
    {
      return NULL; //returns zero pointer if str does not contain any spaces chars
    }
  return str;
}
//count words

/*will count number of words in the string argument*/
int count_words(char *str)
{
  int count = 0;

  // Create a pointer to the beginning of the string
  char* tmp = str;

  // Skip to the first word (word_start does not work unless we have a pointer
  // to the first actual word)
  while(space_char(*tmp)) //while a tab or space
  {
    tmp++; // Iterate pointer to the next character
  }

  // While we have not run out of words (word_start returns NULL when it runs
  // out of words)
  while(tmp != NULL)
  {
    // Iterate the pointer to the next word
    tmp = word_start(tmp);
    // Increment the count
    count++;
  }
  return count;
}

/*-------  MILESTONE #3 ----------------*/
/*returns freshly allocated new zero term string
containing len chars from instr*/
char *copy_str(char *inStr, short len)
{
  char *new_str = (char*) malloc((len + 1)*sizeof(char));
  for(int i =0; i < len; i++){
    new_str[i] = inStr[i];
  }
  new_str[len] = '\0'; // last element is zero terminator
  return new_str;
}

// Tokenize takes in a string and returns an array of strings composed
// of each space-separated word in the input string
// input string = "Betty is great"
// output char ** = ["Betty", "is", "great", NULL]
char** tokenize(char* str)
{
  int count = count_words(str);
  // Create a char** (array of strings) with enough memory to hold a char* (string)
  // (separate string) for each individual word of the input string as well as a
  // NULL/0 char* pointer at the end to denote the end of the tokens array
  char** tokens = (char**) malloc((count + 1) * sizeof(char*));

  // Create a pointer to the beginning of the input string
  char* tmp = str;
  //start at beginning of the first word skip all spaces if words starts with spaces
  while(space_char(*tmp))
  {
    tmp++;
  }
  int i = 0;
  //while we are not out of words (not pointing to NULL)
  while(tmp != NULL)
    {
    //get the number of letters in the current world
    char* end_of_word = word_end(tmp);
    int word_len;
    // Use pointer arithmetic to compute # of letters of we didn't reach the end
    if(end_of_word != NULL)
    {
      // Subtract end position from the beginning of the word to get the # of letters
      word_len = end_of_word - tmp;
    }
    // Otherwise, need to manually create pointer to end of word
    // (Because we can't do pointer arithmetic on a NULL pointer)
    else
    {
     // Create pointer to beginning of word
     char* current_letter = tmp;
     // Iterate pointer to the end of the word manually
     while(non_space_char(*current_letter)) //non space is letters
     {
       current_letter++;
     }
     // Subtract end position from the beginning of the word to get the # of letters
     word_len = current_letter - tmp;
   }
    //create a copy of the word starting at this index (word_len character long)
    char* word = copy_str(tmp, word_len);
    //add the copy to tokens
    tokens[i] = word;
    //move to the next word
    tmp = word_start(tmp);
    i++;
   }
  // Set last token to be a NULL pointer to indicate the end of tokens
  tokens[count] = NULL;
  return tokens;
}

/* prints all tokens*/
// Take in an array of strings called tokens
void print_tokens(char** tokens)
{
  // We always need to print the left bracket
  printf("[");
  int i = 0;
  // Continue to iterate through tokens until we reach it's end indicator (NULL pointer)
  while(tokens[i] != NULL)
  {
    // Print the token and a newline
    printf("%s \n", tokens[i]); //special character to print string
    i++;
  }
  // We always need to print the right bracket
  printf("]");
}

//frees all word and vector containing them
void free_tokens(char** tokens)
{
  int i =0;
  // Continue to iterate through tokens until we reach it's end indicator (NULL pointer)
  while(tokens[i] != NULL)
  {
    free(tokens[i]); //frees each token/word
    i = i+1;
  }
  free(tokens); //frees whole vector
}
