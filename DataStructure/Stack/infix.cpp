/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    Daniel Guzman
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stack.h"     // for STACK
using namespace std;

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string & infix)
{
   string postfix;
   Stack<char> op;
   bool addOperators = false;
   char token = '\0';
    
   postfix += ' ';
for (int i = 0; i < infix.length(); ++i)
{
    switch (infix[i])
  {
    case '+':
    if (infix[i + 1] != ' ')
    {
     for (int k = i; k < infix.length(); ++k)
    {
     if (infix[k] == '+')
    {
    token = infix[--k];
    break;
    }
  }
}
    case '-':
    case '/':
    case '*':
    postfix += ' ';
    op.push(infix[i]);
    break;
    case '^':
    addOperators = true;
    op.push(infix[i]);
    postfix += ' ';
                
if (infix[++i] == ' ')
{
    i++;
    postfix += infix[i];
}
else
    postfix += infix[i];
break;
    case ')':
     addOperators = true;
    break;
    default:
    if (infix[i] != ' ' && infix[i] != '(')
          postfix += infix[i];
}
        
if (addOperators || infix[i] == token || i == infix.length() - 1)
{
    addOperators = false;
    token = 'q';
    
    for (int i = op.size(); i > 0; --i)
        {
            postfix += ' ';
            postfix += op.top();
            op.pop();
         }
    }
}
    
    return postfix;

}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix: " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   string assembly;

   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
      
}
