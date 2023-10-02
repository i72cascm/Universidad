/*! 
  \file interpreter.l
  \brief Lexical or scanner file
*/


%{
/*********************/
/* cout */
#include <iostream>
/*********************/

/*********************/
/* atof */
#include <stdlib.h>
/*********************/

/* Macros for the screen */
#include "../includes/macros.hpp"

/*********************/
/* 
  AST class
  IMPORTANT: must be written before interpreter.tab.h
*/
#include "../ast/ast.hpp"
/*********************/

/*  interpreter.tab.h contains the numeric values of the tokens produced by the parser */
#include "interpreter.tab.h"

/********************/
#include "../error/error.hpp"
/********************/


/*********************************************/
/* Table of symbols */
#include "../table/table.hpp"

#include "../table/numericVariable.hpp"

extern lp::Table table; //!< External Table of Symbols
/*********************************************/

extern int lineNumber; //!< External line counter

/* uso de strdup */
#include <string.h>


%}


/*! \name REGULAR DEFINITIONS  */

DIGIT  [0-9] 

NUMBER {DIGIT}{DIGIT}*(\.{DIGIT}{DIGIT}*(([Ee][+\-]?)?{DIGIT}{DIGIT}*)?)?

LETTER [a-zA-Z]

IDENTIFIER  {LETTER}(_?({LETTER}|{DIGIT})+)*

ALPHA "'"([^']|"\\\'")*"'"


/* STATE  */
%x ERROR COMENTARIO_LINEAS_MULTIPLES COMENTARIO_LINEA_SIMPLE

/*! \name REGULAR EXPRESSIONS  */
%%

[ \t] 	{ ; }    /* skip white space and tabular */

\n      { 
			/* Line counter */
           	lineNumber++; 
        	/* return NEWLINE; */
        }

";"		{
			return SEMICOLON;
		}


","		{
			return COMMA;
		}

"-"		{ return MINUS;  }

"+"		{ return PLUS;   } 			

"*"	    { return MULTIPLICATION; } 	

"/"     { return DIVISION; } 		

"//"	{ return DIV_INT; }

"%"     { return MODULO; }			

"^"	    { return POWER; }			

"("     { return LPAREN; } 		

")"	    { return RPAREN; } 			

":=" 	{ return ASSIGNMENT; }		

"="		{ return EQUAL; }		

"<>"	{ return NOT_EQUAL; }		

">="	{ return GREATER_OR_EQUAL; }

"<="	{ return LESS_OR_EQUAL; }	

">"		{ return GREATER_THAN; }	

"<"		{ return LESS_THAN; }		

":"		{ return COLON; }

"["		{ return SQUARE_LEFT_BRACKET; }

"]"	 	{ return SQUARE_RIGHT_BRACKET; }

"||"	{ return CONCAT; }

{NUMBER}  {
					  
					  /* Conversion of type and sending of the numerical value to the parser */
					   yylval.number = atof(yytext); 

                       return NUMBER; 
                      }

(_{IDENTIFIER}|{IDENTIFIER}_) {
								warning("Lexical error: bad identifier.","identifier");
							  }


{IDENTIFIER}   		 {
						 
						 std::string identifier(yytext);
						  yylval.string =  strdup(yytext);

						 if (table.lookupSymbol(identifier) == false)
							{
								lp::NumericVariable *n = new lp::NumericVariable(identifier,VARIABLE,UNDEFINED,0.0);
								table.installSymbol(n);
								return VARIABLE;
							}
						else 
							{
								lp::Symbol	*s = table.getSymbol(identifier);
								return s->getToken();
							}
                     }


{ALPHA} {
			std::string yytextString(yytext);
				int strSize = yytextString.size();
				std::string stringWithoutQuotes = yytextString.substr(1, strSize-2);

				yylval.string =  strdup(stringWithoutQuotes.c_str()); 			 
				return ALPHA; 
}


<<EOF>> { /* The interpreter finishes when finds the end of file character */
		/*  PLACE(24,10);
	  	  std::cout <<  BICYAN;
	   	  std::cout <<  ">>>>>>> End of program <<<<<<<";
	 	  std::cout << std::endl;
	   	  std::cout << RESET;
		  PLACE(25,1);
		*/
	  	  return 0;
	}

#                                  {
                                        yymore();
                                        BEGIN(COMENTARIO_LINEA_SIMPLE);
                                    }


<COMENTARIO_LINEA_SIMPLE>[^\n]      {
                                        yymore();
                                    }

<COMENTARIO_LINEA_SIMPLE>\n         {
										lineNumber++;
                                        BEGIN(INITIAL);
                                    }


"<<"                                { 
                                        yymore();
                                        BEGIN(COMENTARIO_LINEAS_MULTIPLES);                                    
                                    }	


<COMENTARIO_LINEAS_MULTIPLES>\n		{
										lineNumber++;
										yymore();
									} 

<COMENTARIO_LINEAS_MULTIPLES>[^<<]  {
                                        yymore();
                                    }


<COMENTARIO_LINEAS_MULTIPLES>">>"   {
                                        BEGIN(INITIAL);
                                    }


.								{ 	
									/* Any other character */
									/* Change to error state */
									BEGIN(ERROR); 

									/* 
										The current value of yytext 
										will be concatenated with the next character
									*/
									yymore();  
								}

<ERROR>[^0-9+\-*/()\^% \t\n\;a-zA-Z=<>!&]	{ 
								  
								  /* 
									The current value of yytext 
									will be concatenated with the next character
								  */
									yymore(); 
								}

<ERROR>(.|\n)                { 
								
								/* Rewind one position */
								yyless(yyleng-1); 

								/* Display the error message */
								warning("Lexical error", yytext);

								/* Restore the initial state */
   								BEGIN(INITIAL);
							}
%%

