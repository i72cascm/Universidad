/*! 
  \file interpreter.cpp
  \brief Main program
*/

/*!
 \mainpage Flex and Bison: example 17
 \author   
 \date     2018 - 4 - 26
 \version  1.0
 \note Novelties
	+ AST: intermidiate code
	+ New statements: if, while, block
*/

// cout.precision
#include <iostream>

#include <stdio.h>
#include <string>

/* IMPORTANT: must be written before interpreter.tab.h */
#include "ast/ast.hpp"

#include "./parser/interpreter.tab.h"

#include "./includes/macros.hpp"

// Use for recovery of runtime errors 
#include <setjmp.h>
#include <signal.h>

// Error recovery functions 
#include "error/error.hpp"

#include "table/init.hpp" 
#include "table/table.hpp"  

int lineNumber = 1; //!< Line counter

bool interactiveMode; //!< Control the interactive mode of execution of the interpreter

int control = 0; //!< To control the interactive mode in "if" and "while" sentences 

extern FILE * yyin; //!< Standard input device for yylex() 
std::string progname; //!<  Program name

lp::AST *root; //!< Root of the abstract syntax tree AST

/*
    jmp_buf
    This is an array type capable of storing the information of a calling environment to be restored later.
    This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
extern jmp_buf begin; //!<  It enables recovery of runtime errors 

lp::Table table; //!< Table of Symbols

//! \name Main program

/*! 
  \brief  Main function
  \param  argc: number of command line parameters
  \param  argv: values of command line parameters
  \return int
  \note   C++ requires that main returns an int value
  \sa     yyparse, yylex
*/
int main(int argc, char *argv[])
{
	/* Option -t needed to debug */
  /* 1, on; 0, off */
	yydebug = 0; 
 
  if (argc == 2) 
  {
    yyin = fopen(argv[1],"r");

    if(yyin == NULL)
    {
      std::cerr << BIRED; 
      std::cerr << " Error --> The input file " << argv[1] << " does not exist" << std::endl;
      std::cerr << RESET;
      return -1;
    }

    std::string filename(argv[1]);

    int position = filename.find_last_of(".");;
    if(filename.substr(position+1) != "e")
    warning("The extension of the input file is not \'.e\'", argv[1]);

    interactiveMode = false;
  }
  else
  {
    interactiveMode = true;
  }

	progname = argv[0];

  /* Number of decimal places */ 
  std::cout.precision(7);

  /* 
    Table of symbols initialization 
    Must be written before the recovery sentence: setjmp
  */
  init(table);

  /* Sets a viable state to continue after a runtime error */
  setjmp(begin);

  /* The name of the function to handle floating-point errors is set */
  signal(SIGFPE,fpecatch);

  // Parser function
  yyparse();

  if (interactiveMode == false)
  {
    //root->print();  
    root->evaluate(); 
  }

  return 0;
}



