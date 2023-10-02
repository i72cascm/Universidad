/*! 
  \file interpreter.l
  \brief Lexical or scanner file
*/

%{

#include <iostream>
#include <stdlib.h>

/* Macros for the screen */
#include "../includes/macros.hpp"

#include "../ast/ast.hpp"

/* interpreter.tab.h contains the numeric values of the tokens produced by the parser */
#include "interpreter.tab.h"

#include "../error/error.hpp"

/* Table of symbols */
#include "../table/table.hpp"

#include "../table/numericVariable.hpp"

/* uso de strdup */
#include <string.h>

extern lp::Table table; //!< External Table of Symbols
extern int lineNumber; //!< External line counter

%}

/*! \name REGULAR DEFINITIONS  */

DIGIT  [0-9] 

LETTER [a-zA-ZáéíóúÁÉÍÓÚñÑ]

NUMBER {DIGIT}+(\.{DIGIT}+)?(e[+\-]?{DIGIT}+)?

IDENTIFIER  {LETTER}(_?({LETTER}|{DIGIT})+)*

STRING "'"([^']|"\\\'")*"'"

/* STATES */
%x ERROR
%x COMENTARIO_UNA_LINEA
%x COMENTARIO_VARIAS_LINEAS

/*! \name REGULAR EXPRESSIONS  */
%%
[ \t] 	{ ; }

\n      { lineNumber++; }

";"		{ return SEMICOLON; }

":"		{ return TWO_POINTS; }

","		{ return COMMA; }

"<<"    {
			BEGIN(COMENTARIO_VARIAS_LINEAS);
			yymore();
		}

<COMENTARIO_VARIAS_LINEAS>\n 	{
									lineNumber++;
									yymore();
								}

<COMENTARIO_VARIAS_LINEAS>[^<<] {
									yymore();
								}

<COMENTARIO_VARIAS_LINEAS>">>"  {
									BEGIN(INITIAL);
								}

@   {
		BEGIN(COMENTARIO_UNA_LINEA);
		yymore();
	}

<COMENTARIO_UNA_LINEA>[^\n] {
								yymore();
							}

<COMENTARIO_UNA_LINEA>\n    {
								lineNumber++;
								BEGIN(INITIAL);
							}

{NUMBER}  	{
				/* Conversion of type and sending of the numerical value to the parser */
				yylval.number = atof(yytext); 

				return NUMBER; 
			}

({NUMBER}{LETTER}|{LETTER}{NUMBER})	{
										warning("Lexical error, misspelled number",yytext);
									}

{STRING}	{
				std::string yytextString(yytext);
				int strSize = yytextString.size();
				std::string stringWithoutQuotes = yytextString.substr(1, strSize-2);

				yylval.identifier =  strdup(stringWithoutQuotes.c_str()); 			 
				return STRING; 
			}

(?i:{IDENTIFIER})   {
						std::string yytextString(yytext);

						for(int i=0; i<yytextString.size(); i++)
							yytextString.at(i) = toupper(yytextString[i]);

						std::string identifier(yytextString);

						/* 
							strdup() function returns a pointer to a new string 
							which  is a duplicate of the string yytext
						*/
						yylval.identifier =  strdup(yytextString.c_str()); 
	
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

({IDENTIFIER}_|_{IDENTIFIER}) 	{ 
									warning("Lexical error, misspelled identifier",yytext);
								}

"-"		{ return MINUS;  }
"+"		{ return PLUS;   }

"*"	    { return MULTIPLICATION; }
"/"     { return DIVISION; }

"#div"	{ return INTEGER_DIVISION; }

"("     { return LPAREN; }
")"	    { return RPAREN; }

"#mod"	{ return MODULO; }

"**"	{ return POWER; }

":=" 	{ return ASSIGNMENT; }

"||" 	{ return CONCATENATION; }

"="		{ return EQUAL; }

"<>"	{ return NOT_EQUAL; }

">="	{ return GREATER_OR_EQUAL; }

"<="	{ return LESS_OR_EQUAL; }

">"		{ return GREATER_THAN; }

"<"		{ return LESS_THAN; }

(?i:"#no")	{ return NOT; }
(?i:"#o")	{ return OR; }
(?i:"#y")	{ return AND; }

"{"		{ return LETFCURLYBRACKET; }
"}"		{ return RIGHTCURLYBRACKET; }

(?i:#borrar)	{ return CLEAR; } 
(?i:#lugar)		{ return PLACECURSOR; }

<<EOF>>	{ 
			/* The interpreter finishes when finds the end of file character (CTRL+D) */
			std::cout <<  BICYAN;
			std::cout <<  ">>>>>>> End of file <<<<<<<" << std::endl;
			std::cout << RESET;

			return 0;
		}

.	{ 	
		BEGIN(ERROR); 
		yymore();  
	}

<ERROR>[^0-9+\-*/()\^% \t\n\;a-zA-Z=<>!&]	{ yymore(); }

<ERROR>(.|\n)   { 
					/* 
						yyless(n):
						Retiene los primeros n caracteres de yytext y 
						devuelve el resto al dispositivo de lectura
					*/

					/* Rewind one position */
					yyless(yyleng-1); 

					warning("Lexical error, unrecognized symbol", yytext);

					BEGIN(INITIAL);
				}
%%
