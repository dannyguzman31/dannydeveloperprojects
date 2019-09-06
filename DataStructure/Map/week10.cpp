/**************************************************************************
* Program:
*    Assignment: MAP
*    Brother Ercanbrack, CS 235E
* Author:
*    Daniel Guzman
* Summary: 
*    You need to write a program that uses the STL Map to count the 
*    number of occurrences of palabras from a data file. The program must 
*    prompt the user for the filename. The array indexes will be the 
*    palabras and the value of each element of the array will be a count 
*    of the number of occurrences of that palabra.
***************************************************************************/
#include <iostream> // For STL Library
#include <fstream> // For Input and output files
#include <map>  // STL Map
#include <string> // For strings
#include <iomanip> // For setw(23)
using namespace std;

/***************************************************************************
 * Remove Function: 
 * Removes the punctuations except with the exception of the hyphen ('-')
 * Function - 
 * First: Checks if the palabra is an alphabet, to make it easier 
 * I used the "isalpha" function from STL which checks whether character 
 * is an alphabetic letter.
 * Second: Change CapLetters to lower by calling "toLower" function for STL
 ***************************************************************************/
void remove(string & palabra)
{
   string::iterator it = palabra.begin();
   
   while (it != palabra.end())
   {
   
      if (isalpha(*it))
      {
         *it = tolower(*it);
         it++;
      }
      else if ( (*it) == '-')
      {
         it++;
      }
      else
      {
         palabra.erase(it);
      }   
   }
}

/*********************************************************************************
 * MAIN - Gets input from one of the 3 input files. Counts the number of palabras
 * process and finds 100 of the most common palabras found and their frequencies
 ********************************************************************************/
int main(int argc, char* argv[])
{
   // Prompts for File name and gets file
   char* file;
   cout << "Enter filename: ";
   file = new char[100];
   cin >> file;

   ifstream fin(file);
   
   if (fin.fail())
   {
      cout << "The file '" << file << "' is not found on records! Try Again" << endl;
      return 0;    
   }

   /* ********************************************************************************
    * The array indexes will be the palabras and the value of each element of the array 
    * will be a count of the number of occurrences of that palabra. 
    *********************************************************************************/

   map < string, int, less < string > > i;
   
   string palabra;
   int npalabra = 0;
   while (fin >> palabra)
   {
      remove(palabra);

      if (i[palabra])
         i[palabra]++;
      else
         i[palabra] = 1;
         npalabra++;
   }

   cout << endl << "Number of words processed: " << npalabra << endl;
   cout << "100 most common words found and their frequencies:" << endl;

   // CREATE A MAP ...
   
   multimap < int, string, less < int > > contar;
   map < string, int > ::reverse_iterator iter;

   for (iter = i.rbegin(); iter != i.rend(); iter++)
   {
      contar.insert(pair < int, string > (iter->second,iter->first));
   }

   multimap < int, string > ::reverse_iterator it = contar.rbegin();
   
   for (int j = 0;j < 100; j++)
   {
      cout << setw(23) << it->second << " - " << it->first << endl;
      it++;
   }
   
   return 0;
}
