#include <stdio.h>

int main()
{
  char str[100];
  int currentState = 1; 

  printf("Enter a binary string (0/1): ");
  scanf("%s", str);

  printf("q1"); 

  for (int i = 0; str[i] != '\0'; i++)
  {
    char ch = str[i];

    switch (currentState)
    {
    case 1: 
      if (ch == '0')
      {
        currentState = 1;
      }
      else if (ch == '1')
      {
        currentState = 2;
      }
      break;

    case 2: 
      if (ch == '0')
      {
        currentState = 4;
      }
      else if (ch == '1')
      {
        currentState = 3;
      }
      break;

    case 3: 
      if (ch == '0')
      {
        currentState = 3;
      }
      else if (ch == '1')
      {
        currentState = 4;
      }
      break;

    case 4: 
      if (ch == '0')
      {
        currentState = 3;
      }
      else if (ch == '1')
      {
        currentState = 1;
      }
      break;
    }
    printf(" --> q%d", currentState);
  }

  
  if (currentState == 3 || currentState == 4)
  {
    printf("\nResult: ACCEPTED\n");
  }
  else
  {
    printf("\nResult: REJECTED\n");
  }

  return 0;
}
