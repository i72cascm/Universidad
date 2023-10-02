/*! 
  \file interpreter.y
  \brief Grammar file
*/


%{
/*******************************************/
/* cout & string */
#include <iostream>
#include <string>
/*******************************************/

/*******************************************/
/* pow */
#include <math.h>
/*******************************************/

/*******************************************/
/* Use for recovery of runtime errors */
#include <setjmp.h>

#include <signal.h>
/*******************************************/

/* Error recovery functions */
#include "../error/error.hpp"

/* Macros for the screen */
#include "../includes/macros.hpp"


/*******************************************/
/* 
  AST class
  IMPORTANT: this file must be before init.hpp
*/
#include "../ast/ast.hpp"

/*******************************************/
/* Table of symbol */
#include "../table/table.hpp"
/*******************************************/

/*******************************************/
#include "../table/numericVariable.hpp"
/*******************************************/

#include "../table/logicalVariable.hpp"

/*******************************************/
#include "../table/numericConstant.hpp"
/*******************************************/

/*******************************************/
#include "../table/logicalConstant.hpp"
/*******************************************/

/*******************************************/
#include "../table/builtinParameter1.hpp"
/*******************************************/

/*******************************************/
#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter2.hpp"
/*******************************************/

/*******************************************/
#include "../table/init.hpp"
/*******************************************/

/*! 
	\brief  Lexical or scanner function
	\return int
	\note   C++ requires that yylex returns an int value
	\sa     yyparser
*/
int yylex();

/***********************************************************/
extern int lineNumber; //!< External line counter
extern bool interactiveMode; //!< Control the interactive mode of execution of the interpreter
extern int control; //!< External: to control the interactive mode in "if" and "while" sentences 
/***********************************************************/
extern std::string progname; //!<  Program name
/***********************************************************/

/*******************************************/
/*
 jhmp_buf
    This is an array type capable of storing the information of a calling environment to be restored later.
   This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
jmp_buf begin; //!<  It enables recovery of runtime errors 
/*******************************************/

/*******************************************/
extern lp::Table table; //!< Extern Table of Symbols

/*******************************************/
extern lp::AST *root; //!< External root of the abstract syntax tree AST

%}

/* In case of a syntactic error, more information is shown */
/* DEPRECATED */
/* %error-verbose */

/* ALTERNATIVA a %error-verbose */
%define parse.error verbose


/* Initial grammar symbol */
%start program

/*******************************************/
/* Data type YYSTYPE  */
%union {
  double number;
  char * string; 				 
  bool logic;						 
  lp::ExpNode *expNode;  			 
  std::list<lp::ExpNode *>  *parameters;    //#include<list> must be in interpreter.l, init.cpp, interpreter.cpp
  std::list<lp::Statement *> *stmts; 
  lp::Statement *st;				 
  lp::AST *prog;
  std::list<lp::Value *> *cases;					 
}
/*******************************************/

/* Type of the non-terminal symbols */
%type <expNode> exp cond 
/*******************************************/
%type <parameters> listOfExp  restOfListOfExp
/*******************************************/
%type <stmts> stmtlist
/*******************************************/
%type <st> stmt asgn print printString read readString if while repeat for clear case place
/*******************************************/
%type <cases> firstCase otherCases
/*******************************************/
%type <prog> program
/*******************************************/

/* Defined tokens */

/* Minimum precedence */

/*******************************************/
%token SEMICOLON COLON SQUARE_LEFT_BRACKET SQUARE_RIGHT_BRACKET
/*******************************************/
%token CLEARSCREEN
/*******************************************/
%token PRINT PRINTSTRING READ READSTRING IF ELSE THEN ENDIF WHILE DO ENDWHILE REPEAT UNTIL FOR FROM TO STEP ENDFOR CASE VALUE BREAK DEFAULT ENDCASE PLACE
/*******************************************/
%right ASSIGNMENT
/*******************************************/
%token COMMA
/*******************************************/
%token <number> NUMBER
/*******************************************/
/*******************************************/
%token <logic> BOOL
/*******************************************/
%token <string> VARIABLE UNDEFINED CONSTANT BUILTIN ALPHA 
/*******************************************/

/* No associativity */
%nonassoc GREATER_OR_EQUAL LESS_OR_EQUAL GREATER_THAN LESS_THAN  EQUAL NOT_EQUAL
/*******************************************/
%nonassoc  UNARY


/* Left associativity */

/*******************************************************/
%left CONCAT
/*******************************************/
%left OR
/*******************************************/
%left AND
/*******************************************/
%left NOT
/*******************************************************/
%left PLUS MINUS 
/*******************************************/
%left MULTIPLICATION DIVISION DIV_INT MODULO
/*******************************************/
%left LPAREN RPAREN
/*******************************************/

// Maximum precedence 
%right POWER


%%
 //! \name Grammar rules

program : stmtlist
		  { 
		    // Create a new AST
			$$ = new lp::AST($1); 

			// Assign the AST to the root
			root = $$; 

			// End of parsing
			//	return 1;
		  }
;

stmtlist:  /* empty: epsilon rule */
		  { 
			// create a empty list of statements
			$$ = new std::list<lp::Statement *>(); 
		  }  

        | stmtlist stmt 
		  { 
			// copy up the list and add the stmt to it
			$$ = $1;
			$$->push_back($2);

			// Control the interative mode of execution of the interpreter
			if (interactiveMode == true && control == 0)
 			{
				for(std::list<lp::Statement *>::iterator it = $$->begin(); 
						it != $$->end(); 
						it++)
				{
					(*it)->printAST();
					(*it)->evaluate();
					
				}

				// Delete the AST code, because it has already run in the interactive mode.
				$$->clear();
			}
		}

    | stmtlist error 
      { 
			 // just copy up the stmtlist when an error occurs
			 $$ = $1;

			 // The previous look-ahead token ought to be discarded with `yyclearin;'
			 yyclearin; 
       } 
;
 

stmt: SEMICOLON  /* Empty statement: ";" */
	  {
		// Create a new empty statement node
		$$ = new lp::EmptyStmt(); 
	  }
	| asgn  SEMICOLON
	  {}
	| print SEMICOLON
	  {}
	| printString SEMICOLON
	  {}
	| read SEMICOLON
	  {}
	| readString SEMICOLON
	  {}
	| if SEMICOLON
	  {}
	| while SEMICOLON
	  {}
	| repeat SEMICOLON
	  {}
	| clear SEMICOLON
	  {}
	| for SEMICOLON
	  {}
	| place SEMICOLON
	  {}
	| case SEMICOLON
	{}
;

controlSymbol:  /* Epsilon rule*/
		{
			// To control the interactive mode in "if" and "while" sentences
			control++;
		}
	;

while:  WHILE controlSymbol cond DO stmtlist ENDWHILE{
			// Create a new while statement node
			$$ = new lp::WhileStmt($3, $5);
			// To control the interactive mode
			control--;
    	}		
		
;

if: IF controlSymbol cond THEN stmtlist ENDIF{
      // Create a new if statement node
      $$ = new lp::IfStmt($3, $5);
      // To control the interactive mode
      control--;
  	}
	| IF controlSymbol cond stmtlist ENDIF{
		execerror("Syntax error: missing THEN symbol.", "IF controlSymbol cond THEN stmtlist ENDIF");
    }
	| IF controlSymbol cond THEN stmtlist ELSE stmtlist ENDIF{
      $$ = new lp::IfStmt($3, $5, $7);
      control--;
	  }
	| IF controlSymbol cond stmtlist ELSE stmtlist ENDIF{
		execerror("Syntax error: missing THEN symbol.", "IF controlSymbol cond THEN stmtlist ENDIF");
	}
	
;

for: FOR controlSymbol VARIABLE FROM exp TO exp DO stmtlist ENDFOR{
      $$ = new lp::ForStmt($3, $5, $7, $9);
      control--;
    }
	| FOR controlSymbol VARIABLE FROM exp TO exp STEP exp DO stmtlist ENDFOR{
      $$ = new lp::ForStmt($3, $5, $7, $9, $11);
      control--;
    }
	| FOR controlSymbol CONSTANT FROM exp TO exp STEP exp DO stmtlist ENDFOR{
      execerror("Semantic error in for statement: it is not allowed to modify a constant ", "FOR controlSymbol VARIABLE FROM exp TO exp STEP exp DO stmtlist ENDFOR");
    }
	| FOR controlSymbol CONSTANT FROM exp TO exp DO stmtlist ENDFOR{
      execerror("Semantic error in for statement: it is not allowed to modify a constant ", "FOR controlSymbol VARIABLE FROM exp TO exp STEP exp DO stmtlist ENDFOR");
    }
	| FOR controlSymbol VARIABLE exp TO exp STEP exp DO stmtlist ENDFOR{
      execerror("Syntax error: missing FROM symbol of for statement", "FOR controlSymbol VARIABLE FROM exp TO exp STEP exp DO stmtlist ENDFOR");
    }
	| FOR controlSymbol VARIABLE FROM exp STEP exp DO stmtlist ENDFOR{
      execerror("Syntax error: missing TO symbol of for statement", "FOR controlSymbol VARIABLE FROM exp TO exp STEP exp DO stmtlist ENDFOR");
    }
	| FOR controlSymbol VARIABLE FROM exp TO exp STEP exp stmtlist ENDFOR{
      execerror("Syntax error: missing DO symbol of for statement", "FOR controlSymbol VARIABLE FROM exp TO exp STEP exp DO stmtlist ENDFOR");
    }
	| FOR controlSymbol VARIABLE exp TO exp DO stmtlist ENDFOR{
      execerror("Syntax error: missing FROM symbol of for statement", "FOR controlSymbol VARIABLE FROM exp TO exp STEP exp DO stmtlist ENDFOR");
    }
	| FOR controlSymbol VARIABLE FROM exp DO stmtlist ENDFOR{
      execerror("Syntax error: missing TO symbol of for statement", "FOR controlSymbol VARIABLE FROM exp TO exp STEP exp DO stmtlist ENDFOR");
    }
	| FOR controlSymbol VARIABLE FROM exp TO exp stmtlist ENDFOR{
      execerror("Syntax error: missing DO symbol of for statement", "FOR controlSymbol VARIABLE FROM exp TO exp STEP exp DO stmtlist ENDFOR");
    }
	| FOR controlSymbol VARIABLE FROM exp TO STEP exp DO stmtlist ENDFOR{
      execerror("Syntax error: missing until EXP argument of for statement", "FOR controlSymbol VARIABLE FROM exp TO exp STEP exp DO stmtlist ENDFOR");
    }
	| FOR controlSymbol VARIABLE FROM exp TO DO stmtlist ENDFOR{
      execerror("Syntax error: missing until EXP argument of for statement", "FOR controlSymbol VARIABLE FROM exp TO exp STEP exp DO stmtlist ENDFOR");
    }
;


 
case: CASE controlSymbol LPAREN exp RPAREN firstCase SQUARE_LEFT_BRACKET DEFAULT COLON stmtlist SQUARE_RIGHT_BRACKET ENDCASE{
          $$ = new lp::CaseStmt($4, $6, $10);
          control --;
        }
		| CASE controlSymbol exp RPAREN firstCase SQUARE_LEFT_BRACKET DEFAULT COLON stmtlist SQUARE_RIGHT_BRACKET ENDCASE{
			execerror("Syntax error: missing LPAREN symbol.", "CASE controlSymbol LPAREN exp RPAREN firstCase SQUARE_LEFT_BRACKET DEFAULT COLON stmtlist SQUARE_RIGHT_BRACKET ENDCASE");
		}
		| CASE controlSymbol LPAREN exp firstCase SQUARE_LEFT_BRACKET DEFAULT COLON stmtlist SQUARE_RIGHT_BRACKET ENDCASE{
			execerror("Syntax error: missing RPAREN symbol.", "CASE controlSymbol LPAREN exp RPAREN firstCase SQUARE_LEFT_BRACKET DEFAULT COLON stmtlist SQUARE_RIGHT_BRACKET ENDCASE");
		}
		| CASE controlSymbol LPAREN exp RPAREN firstCase DEFAULT COLON stmtlist SQUARE_RIGHT_BRACKET ENDCASE{
			execerror("Syntax error: missing SQUARE_LEFT_BRACKET symbol.", "CASE controlSymbol LPAREN exp RPAREN firstCase SQUARE_LEFT_BRACKET DEFAULT COLON stmtlist SQUARE_RIGHT_BRACKET ENDCASE");
		}
		| CASE controlSymbol LPAREN exp RPAREN firstCase SQUARE_LEFT_BRACKET COLON stmtlist SQUARE_RIGHT_BRACKET ENDCASE{
			execerror("Syntax error: missing DEFAULT symbol.", "CASE controlSymbol LPAREN exp RPAREN firstCase SQUARE_LEFT_BRACKET DEFAULT COLON stmtlist SQUARE_RIGHT_BRACKET ENDCASE");
		}
		| CASE controlSymbol LPAREN exp RPAREN firstCase SQUARE_LEFT_BRACKET DEFAULT stmtlist SQUARE_RIGHT_BRACKET ENDCASE{
			execerror("Syntax error: missing COLON symbol.", "CASE controlSymbol LPAREN exp RPAREN firstCase SQUARE_LEFT_BRACKET DEFAULT COLON stmtlist SQUARE_RIGHT_BRACKET ENDCASE");
		}
		| CASE controlSymbol LPAREN exp RPAREN firstCase SQUARE_LEFT_BRACKET DEFAULT COLON stmtlist ENDCASE{
			execerror("Syntax error: missing SQUARE_RIGHT_BRACKET symbol.", "CASE controlSymbol LPAREN exp RPAREN firstCase SQUARE_LEFT_BRACKET DEFAULT COLON stmtlist SQUARE_RIGHT_BRACKET ENDCASE");
		}
		
;

firstCase: VALUE NUMBER COLON stmtlist BREAK otherCases{
			$$ = $6;
			lp::ExpNode *e = new lp::NumberNode($2);
			lp::Value *v = new lp::Value(e, $4);
			$$->push_front(v); 
		}
		| VALUE COLON stmtlist BREAK otherCases{
			execerror("Syntax error: missing NUMBER.", "VALUE NUMBER COLON stmtlist BREAK otherCases");
		}
		| VALUE NUMBER stmtlist BREAK otherCases{
			execerror("Syntax error: missing COLON symbol.", "VALUE NUMBER COLON stmtlist BREAK otherCases");
		}
		| VALUE NUMBER COLON stmtlist otherCases{
			execerror("Syntax error: missing BREAK symbol.", "VALUE NUMBER COLON stmtlist BREAK otherCases");
		}
;

otherCases: VALUE NUMBER COLON stmtlist BREAK otherCases{
			$$ = $6;
			lp::ExpNode *e = new lp::NumberNode($2);
            lp::Value *v = new lp::Value(e, $4);
            $$->push_front(v);
		}
		|	//epsilon
		{
			$$ = new std::list<lp::Value *>(); 
		}
		| VALUE COLON stmtlist BREAK otherCases{
			execerror("Syntax error: missing NUMBER.", "VALUE NUMBER COLON stmtlist BREAK otherCases");
		}
		| VALUE NUMBER stmtlist BREAK otherCases{
			execerror("Syntax error: missing COLON symbol.", "VALUE NUMBER COLON stmtlist BREAK otherCases");
		}
		| VALUE NUMBER COLON stmtlist otherCases{
			execerror("Syntax error: missing BREAK symbol.", "VALUE NUMBER COLON stmtlist BREAK otherCases");
		}
		
;

repeat: REPEAT controlSymbol stmtlist UNTIL cond{
			$$ = new lp::RepeatStmt($5, $3);
			control--;
		}
		| REPEAT controlSymbol stmtlist cond{
			execerror("Syntax error: missing UNTIL symbol of do while statement", "REPEAT stmtlist UNTIL cond");
		}
;

cond: 	LPAREN exp RPAREN
		{ 
			$$ = $2;
		}
;


asgn:   VARIABLE ASSIGNMENT exp 
		{ 
			// Create a new assignment node
			$$ = new lp::AssignmentStmt($1, $3);
		}

	|  VARIABLE ASSIGNMENT asgn 
		{ 
			// Create a new assignment node
			$$ = new lp::AssignmentStmt($1, (lp::AssignmentStmt *) $3);
		}


	| CONSTANT ASSIGNMENT exp 
		{   
 			execerror("Semantic error in assignment: it is not allowed to modify a constant ", $1);
		}

	| CONSTANT ASSIGNMENT asgn 
		{   
 			execerror("Semantic error in multiple assignment: it is not allowed to modify a constant ",$1);
		}
;

print:  PRINT LPAREN exp RPAREN
		{
			// Create a new print node
			 $$ = new lp::PrintStmt($3);
		}
;	

printString:  PRINTSTRING LPAREN exp RPAREN
		{
			// Create a new print node
			 $$ = new lp::PrintStmtString($3);
		}
;	


read:  READ LPAREN VARIABLE RPAREN  
		{
			// Create a new read node
			 $$ = new lp::ReadStmt($3);
		}

  	
	| READ LPAREN CONSTANT RPAREN  
		{   
 			execerror("Semantic error in \"read statement\": it is not allowed to modify a constant ",$3);
		}
;

readString:  READSTRING LPAREN VARIABLE RPAREN  
		{
			// Create a new read node
			 $$ = new lp::ReadStmtString($3);
		}

  	 
	| READSTRING LPAREN CONSTANT RPAREN  
		{   
 			execerror("Semantic error in \"read statement\": it is not allowed to modify a constant ",$3);
		}
;



clear: CLEARSCREEN
      {
        $$ = new lp::ClearStmt();
      }
;

place: PLACE LPAREN exp COMMA exp RPAREN 
            {
              $$ = new lp::PlaceStmt($3, $5);
            }
;


exp:	NUMBER 
		{ 
			// Create a new number node
			$$ = new lp::NumberNode($1);
		}
	|	ALPHA 
    	{ 
			$$ = new lp::AlphaNode($1);
		}
		
	| 	exp PLUS exp 
		{ 
			// Create a new plus node
			 $$ = new lp::PlusNode($1, $3);
		 }

	| 	exp MINUS exp
      	{
			// Create a new minus node
			$$ = new lp::MinusNode($1, $3);
		}

	| 	exp MULTIPLICATION exp 
		{ 
			// Create a new multiplication node
			$$ = new lp::MultiplicationNode($1, $3);
		}

	| 	exp DIVISION exp
		{
		  // Create a new division node	
		  $$ = new lp::DivisionNode($1, $3);
	   }
	   

	| 	LPAREN exp RPAREN
       	{ 
		    // just copy up the expression node 
			$$ = $2;
		 }

  	| 	PLUS exp %prec UNARY
		{ 
		  // Create a new unary plus node	
  		  $$ = new lp::UnaryPlusNode($2);
		}

	| 	MINUS exp %prec UNARY
		{ 
		  // Create a new unary minus node	
  		  $$ = new lp::UnaryMinusNode($2);
		}

	|	exp MODULO exp 
		{
		  // Create a new modulo node	

		  $$ = new lp::ModuloNode($1, $3);
       }
	| 	exp DIV_INT exp 
	{ 
		// Create a new multiplication node
		$$ = new lp::DivIntNode($1, $3);
	}

	|	exp POWER exp 
     	{ 
		  // Create a new power node	
  		  $$ = new lp::PowerNode($1, $3);
		}

	 | VARIABLE
		{
		  // Create a new variable node	
		  $$ = new lp::VariableNode($1);
		}

	 | CONSTANT
		{
		  // Create a new constant node	
		  $$ = new lp::ConstantNode($1);

		}
	| exp CONCAT exp
	{
		// Create a new concat node	
		$$ = new lp::ConcatNode($1, $3);

	}

	| BUILTIN LPAREN listOfExp RPAREN
		{
			// Get the identifier in the table of symbols as Builtin
			lp::Builtin *f= (lp::Builtin *) table.getSymbol($1);

			// Check the number of parameters 
			if (f->getNParameters() ==  (int) $3->size())
			{
				switch(f->getNParameters())
				{
					case 0:
						{
							// Create a new Builtin Function with 0 parameters node	
							$$ = new lp::BuiltinFunctionNode_0($1);
						}
						break;

					case 1:
						{
							// Get the expression from the list of expressions
							lp::ExpNode *e = $3->front();

							// Create a new Builtin Function with 1 parameter node	
							$$ = new lp::BuiltinFunctionNode_1($1,e);
						}
						break;

					case 2:
						{
							// Get the expressions from the list of expressions
							lp::ExpNode *e1 = $3->front();
							$3->pop_front();
							lp::ExpNode *e2 = $3->front();

							// Create a new Builtin Function with 2 parameters node	
							$$ = new lp::BuiltinFunctionNode_2($1,e1,e2);
						}
						break;

					default:
				  			 execerror("Syntax error: too many parameters for function ", $1);
				} 
			}
			else
	  			 execerror("Syntax error: incompatible number of parameters for function", $1);
		}

	| exp GREATER_THAN exp
	 	{
		  // Create a new "greater than" node	
 			$$ = new lp::GreaterThanNode($1,$3);
		}

	| exp GREATER_OR_EQUAL exp 
	 	{
		  // Create a new "greater or equal" node	
 			$$ = new lp::GreaterOrEqualNode($1,$3);
		}

	| exp LESS_THAN exp 	
	 	{
		  // Create a new "less than" node	
 			$$ = new lp::LessThanNode($1,$3);
		}

	| exp LESS_OR_EQUAL exp 
	 	{
		  // Create a new "less or equal" node	
 			$$ = new lp::LessOrEqualNode($1,$3);
		}

	| exp EQUAL exp 	
	 	{
		  // Create a new "equal" node	
 			$$ = new lp::EqualNode($1,$3);
		}


    | exp NOT_EQUAL exp 	
	 	{
		  // Create a new "not equal" node	
 			$$ = new lp::NotEqualNode($1,$3);
		}

    | exp AND exp 
	 	{
		  // Create a new "logic and" node	
 			$$ = new lp::AndNode($1,$3);
		}

    | exp OR exp 
	 	{
		  // Create a new "logic or" node	
 			$$ = new lp::OrNode($1,$3);
		}

    | NOT exp 
	 	{
		  // Create a new "logic negation" node	
 			$$ = new lp::NotNode($2);
		}
;


listOfExp: 
			/* Empty list of numeric expressions */
			{
			    // Create a new list STL
				$$ = new std::list<lp::ExpNode *>(); 
			}

	|  exp restOfListOfExp
			{
				$$ = $2;

				// Insert the expression in the list of expressions
				$$->push_front($1);
			}
;

restOfListOfExp:
			/* Empty list of numeric expressions */
			{
			    // Create a new list STL
				$$ = new std::list<lp::ExpNode *>(); 
			}

		|	COMMA exp restOfListOfExp
			{
				// Get the list of expressions
				$$ = $3;

				// Insert the expression in the list of expressions
				$$->push_front($2);
			}
;

%%