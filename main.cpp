//Author: Sarim Qureshi
//Publication Date: 1/26/2020

#include "Header.h"
#include <cstdio>
#include <cstring>
#include <cctype>

boolean debugMode = FALSE;

// Enumarated Type specifying all of the Tokens
enum TokenType
{
  ERROR,
  OPERATOR,
  VALUE,
  EOLN,
  QUIT,
  HELP,
  EOFILE
};

void printCommands()
{
  printf("The commands for this program are:\n\n");
  printf("q - to quit the program\n");
  printf("? - to list the accepted commands\n");
  printf("or any infix mathematical expression using operators of (), *, /, +, -\n");
}

// Class to hold the Token information
class Token
{
private:
  TokenType type;
  char op; // using '$' as undefined/error
  int val; // using -999 as undefined/error

public:
  // Default to initialize to the ERROR TokenType
  Token()
  {
    type = ERROR;
    op = '$';
    val = -999;
  }

  // Initialize to a specific TokenType
  Token(TokenType t)
  {
    type = t;
    op = '$';
    val = -999;
  }

  // Set to a specific TokenType
  void setToType(TokenType t)
  {
    type = t;
    op = '$';
    val = -999;
  }

  // Set to a OPERATOR TokenType with specific operator value
  void setToOperator(char c)
  {
    type = OPERATOR;
    op = c;
    val = -999;
  }

  // Set to a VALUE TokenType with a specific numeric value
  void setToValue(int v)
  {
    type = VALUE;
    op = '$';
    val = v;
  }

  // return true if the Current Token is of the given TokenType
  bool equalsType(TokenType t)
  {
    if (type == t)
      return true;
    else
      return false;
  }

  // return true if the Current Token is of the OPERATOR TokenType
  //     and contains the given operator character
  bool equalsOperator(char c)
  {
    if (type == OPERATOR && op == c)
      return true;
    else
      return false;
  }

  // Return the Operator for the current Token
  //   verify the current Token is of the OPERATOR TokenType
  char getOperator()
  {
    if (type == OPERATOR)
      return op;
    else
      return '$'; // using $ to indicate an error value
  }

  // Return the Value for the current Token
  //   verify the current token is of the value TokenType
  int getValue()
  {
    if (type == VALUE)
      return val;
    else
      return -999; // using -999 to indicate an error value
  }
};

class TokenReader
{
private:
  char inputline[300]; // this assumes that all input lines are 300 characters or less in length
  bool needline;
  int pos;

public:
  // initialize the TokenReader class to read from Standard Input
  TokenReader()
  {
    // set to read from Standard Input
    inputline[0] = '\0';
    pos = 0;
    needline = true;
  }

  // Force the next getNextToken to read in a line of input
  void clearToEoln()
  {
    needline = true;
  }

  // Return the next Token from the input line
  Token getNextToken()
  {
    char *endCheck;

    //printf ("getToken %d, %d, %s\n", pos, needline, inputline);

    // get a new line of input from user
    if (needline)
    {
      endCheck = fgets(inputline, 300, stdin);

      if (endCheck == NULL)
      {
        printf("Error in reading");
        Token t(EOFILE);
        return t;
      }

      for (int i = 0; i < strlen(inputline); i++)
        if ('\n' == inputline[i])
          inputline[i] = ' ';
      strcat(inputline, " "); // add a space at end to help deal with digit calculation
      needline = false;
      pos = 0;
    }

    // skip over any white space characters in the beginning of the input
    while (pos < strlen(inputline) && isspace(inputline[pos]))
    {
      pos++;
    }

    // check for the end of the current line of input
    if (pos >= strlen(inputline))
    { // at end of line
      needline = true;
      Token t(EOLN);
      return t;
    }

    // Get the next character from the input line
    char ch = inputline[pos];
    pos++;

    // check if 'q' or 'Q' was entered ==> QUIT Token
    if ('q' == ch || 'Q' == ch)
    {
      return Token(QUIT);
    }

    // check if "?" was entered ==> HELP Token
    if ('?' == ch)
    {
      return Token(HELP);
    }

    // check for Operator values of: + - * / ( )  ==> OPERATOR Token
    if (('+' == ch) || ('-' == ch) || ('*' == ch) ||
        ('/' == ch) || ('(' == ch) || (')' == ch))
    {
      Token t;
      t.setToOperator(ch);
      return t;
    }

    // check for a number  ==> VALUE Token
    if (isdigit(ch))
    {
      int number = int(ch) - int('0'); // subtract ascii value of ch from ascii value of '0'
      ch = inputline[pos];
      pos++;
      while (isdigit(ch))
      {
        number = number * 10 + int(ch) - int('0');
        ch = inputline[pos];
        pos++;
      }
      pos--; // since number calcuation check one character after the last digit
      Token t;
      t.setToValue(number);
      return t;
    }

    // Input in not valid if code get to this part ==> ERROR Token
    return Token(ERROR);
  }
};

/**************************************************************/
/*                                                            */
/*  The Code above this point should NOT need to be modified  */
/*  for this program.   If you feel you must modify the code  */
/*  below this point, you are probably trying to solve a      */
/*  more difficult problem that you are being asked to solve  */
/*                                                            */
/**************************************************************/

void processExpression(Token inputToken, TokenReader *tr);

int main(int argc, char *argv[])
{
  /***************************************************************/
  /* Add code for checking command line arguments for debug mode */
  for (int i = 0; i < argc; i++)
  {
    if (strcmp(argv[i], "-d") == 0)
      debugMode = TRUE;
  }

  Token inputToken;
  TokenReader tr;

  printf("Starting Expression Evaluation Program\n\n");
  printf("Enter Expression: ");

  inputToken = tr.getNextToken();

  while (inputToken.equalsType(QUIT) == FALSE)
  {
    /* check first Token on Line of input */
    if (inputToken.equalsType(HELP))
    {
      printCommands();
      tr.clearToEoln();
    }
    else if (inputToken.equalsType(ERROR))
    {
      printf("Invalid Input - For a list of valid commands, type ?\n");
      tr.clearToEoln();
    }
    else if (inputToken.equalsType(EOLN))
    {
      printf("Blank Line - Do Nothing\n");
      /* blank line - do nothing */
    }
    else
    {
      processExpression(inputToken, &tr);
    }

    printf("\nEnter Expression: ");
    inputToken = tr.getNextToken();
  }

  printf("Quitting Program\n");
  return 1;
}

int eval(int val1, char ops, int val2)
{
  if(ops == '+')
    return (val1 + val2);
  
  else if(ops == '-')
    return (val1 - val2);

  else if(ops == '*')
    return (val1 * val2);
  
  else if(ops == '/')
    return (val1 / val2);
  
  else
  {
    printf("ERROR: Invalid Operator");
    return -999;
  }
  
}

void popAndEval(charStack &charSta, intStack &intSta)
{
  char op = charSta.top();
  charSta.pop();

  int v2 = intSta.top();
  intSta.pop();

  int v1 = intSta.top();
  intSta.pop();

  int v3 = eval(v1, op, v2);
  intSta.push(v3);
}

void paranthesesPop(charStack &sta, char ops)
{
    charStack characters = charStack();

    while (sta.isEmpty() == FALSE)
    {
        if (sta.top() == ops)
            sta.pop();

        else
        {
            characters.push(sta.top());
            sta.pop();
        }
    }

    while (characters.isEmpty() == FALSE)
    {
        sta.push(characters.top());
        characters.pop();
    }
}

void processExpression(Token inputToken, TokenReader *tr)
{
  /**********************************************/
  /* Declare both stack head pointers here      */
  charStack characters;
  characters.init();

  intStack numbers;
  numbers.init();


  /* Loop until the expression reaches its End */
  while (inputToken.equalsType(EOLN) == false)
  {
    /* The expression contain a VALUE */
    if (inputToken.equalsType(VALUE))
    {
      /* make this a debugMode statement */
      if(debugMode == TRUE)
        printf("\n\nVal: %d, ", inputToken.getValue());

      // add code to perform this operation here
      numbers.push(inputToken.getValue());
    }

    /* The expression contains an OPERATOR */
    else if (inputToken.equalsType(OPERATOR))
    {
      /* make this a debugMode statement */
      if(debugMode == TRUE)
        printf("\n\nOP: %c, ", inputToken.getOperator());

      // add code to perform this operation here
      if(inputToken.getOperator() == '(')
        characters.push(inputToken.getOperator());

      else if(inputToken.getOperator() == '+' || inputToken.getOperator() == '-')
      {
        while ((characters.isEmpty() == FALSE) && (characters.top() == '+' || characters.top() == '-' ||
        characters.top() == '*' || characters.top() == '/'))
          popAndEval(characters, numbers);

        characters.push(inputToken.getOperator());
      }

      else if(inputToken.getOperator() == '*' || inputToken.getOperator() == '/')
      {
        while ((characters.isEmpty() == FALSE) && (characters.top() == '*' || characters.top() == '/'))
          popAndEval(characters, numbers);

        characters.push(inputToken.getOperator());
      }

      else if(inputToken.getOperator() == ')')
      {
        while ((characters.isEmpty() == FALSE) && (characters.top() != '('))
          popAndEval(characters, numbers);
        
        if(characters.isEmpty() == TRUE)
          printf("\n\nERROR: There are no characters!");
        
        else
          paranthesesPop(characters, '(');
      }
    }

    /* get next token from input */
    inputToken = tr->getNextToken();

    if(inputToken.equalsType(EOLN))
    {
      while(characters.isEmpty() == FALSE)
        popAndEval(characters, numbers); //to write

      printf("\n\nTop: %d", numbers.top());
      if(numbers.isEmpty() == TRUE)
        printf("\n\nERROR: The value stack is empty!");
    }
    
  }

  /* The expression has reached its end */

  // add code to perform this operation here

  while (characters.isEmpty() == FALSE)
    popAndEval(characters, numbers);
    
  printf("\n\nResult: %d", numbers.top());

  printf("\n");
}
