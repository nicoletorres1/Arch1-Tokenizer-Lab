#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

//TASK 1
//this is the first milestone in this project
//I will prompt the user to enter a string
//I will then print that string

size_t strlen(char* str)
{
  int i = 0;
  while (str[i] != '\0')
  {
    i++;
  }
  return i;
}

//since we can only use the 2 includes above this help method was created to help make a duplicate
//and return the pointer
char * strdup (char* toCopy)
{
  // printf("strdup(...): strlen(toCopy)=%d\n",strlen(toCopy));
  char * newStr = (char*) malloc((strlen(toCopy) + 1) * sizeof(char));
    
  for (int i = 0; i < strlen(toCopy); i++)
  {
    newStr[i] = toCopy[i];
  }
  
  newStr[strlen(toCopy)] = '\0';

  return newStr;
}

int main()
{
  char** strArr; //temporarily will store tokens for test
  int running = 1;
  char userInput[100]; //gives a max to characters accepted
  List * history = init_history(); 
  printf("Enter a string or command (!<number> for history of console input). Strings will be tokenized and printed.\n");
  
  while(running)
  {
    printf(">"); //as described in README file to start with > or $
    fgets(userInput, 100, stdin);
    //"Great carrots are orange\0\0"
    //"Harold\n\0"
    userInput[strlen(userInput)-1] = '\0';
    char * storeInput = strdup(userInput);
    //printf("storInput='%s'\n",storeInput);
    add_history(history, storeInput); 
    
    if (userInput[0] == '!')
    {
      int desiredId = atoi(userInput+1);
      char * retrieved = get_history(history, desiredId);
      if (retrieved == NULL)
      {
        printf("No history available for id %d.\n", desiredId);
      }
      else
      {
        printf("%d: '%s'\n",desiredId, retrieved);
      }
    }
	
    else
    {
        //  printf("The string: %s\n", userInput);
        // return 0; //exit status of application

        //test to tokenizer new string
        strArr = tokenize(userInput);
        printf("==TOKENIZED INPUT STRING==\n");
        print_tokens(strArr);
        printf("==========================\n");
        //  free_tokens(strArr);
    }
  }
  
}
