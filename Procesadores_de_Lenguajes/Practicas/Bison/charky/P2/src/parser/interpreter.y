/*! 
  \file interpreter.y
  \brief Grammar file
*/

%{
#include <iostream>
#include <string>

/* pow */
#include <math.h>

/* Use for recovery of runtime errors */
#include <setjmp.h>
#include <signal.h>

/* Error recovery functions */
#include "../error/error.hpp"

/* Macros for the screen */
#include "../includes/macros.hpp"

/* IMPORTANT: this file must be before init.hpp */
#include "../ast/ast.hpp"

/* Table of symbol */
#include "../table/table.hpp"

#include "../table/numericVariable.hpp"

#include "../table/logicalVariable.hpp"

#include "../table/numericConstant.hpp"

#include "../table/logicalConstant.hpp"

#include "../table/builtinParameter1.hpp"

#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter2.hpp"

#include "../table/init.hpp"

/*! 
	\brief  Lexical or scanner function
	\return int
	\note   C++ requires that yylex returns an int value
	\sa     yyparser
*/
int yylex();

extern int lineNumber; //!< External line counter

extern bool interactiveMode; //!< Control the interactive mode of execution of the interpreter

extern int control; //!< External: to control the interactive mode in "if" and "while" sentences 

extern std::string progname; //!<  Program name

/*
	jhmp_buf
	This is an array type capable of storing the information of a calling environment to be restored later.
	This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
jmp_buf begin; //!<  It enables recovery of runtime errors 

extern lp::Table table; //!< Extern Table of Symbols

extern lp::AST *root; //!< External root of the abstract syntax tree AST

%}

/* In case of a syntactic error, more information is shown */
%error-verbose

/* Initial grammar symbol */
%start program

/* Data type YYSTYPE  */
%union {
  char * identifier;
  double number;  
  bool logic;
  lp::ExpNode *expNode;
  std::list<lp::ExpNode *>  *parameters;    // NOTE: #include<list> must be in interpreter.l, init.cpp, interpreter.cpp
  std::list<lp::Statement *> *stmts;
  std::list<lp::Value *> *switchValues;
  lp::Statement *st;
  lp::AST *prog;
}

/* Type of the non-terminal symbols */
%type <expNode> exp cond 

%type <parameters> listOfExp  restOfListOfExp

%type <stmts> stmtlist

%type <switchValues> listOfValues restOfListOfValues

%type <st> stmt asgn ask_for_key print read read_string if while block do_while for switch placecursor clear

%type <prog> program

/* Defined tokens */
/* Minimum precedence */
%token PLACECURSOR CLEAR

%token SEMICOLON TWO_POINTS

%token ASK_FOR_KEY PRINT READ READ_STRING IF THEN END_IF ELSE WHILE DO END_WHILE DO_WHILE UNTIL FOR FROM STEP END_FOR SWITCH VALUE DEFAULT END_SWITCH

%token LETFCURLYBRACKET RIGHTCURLYBRACKET

%right ASSIGNMENT

%token COMMA

%token <number> NUMBER

%token <identifier> STRING

%token <logic> BOOL

%token <identifier> VARIABLE UNDEFINED CONSTANT BUILTIN

/* Left associativity */

%left OR

%left AND

%nonassoc GREATER_OR_EQUAL LESS_OR_EQUAL GREATER_THAN LESS_THAN  EQUAL NOT_EQUAL

%left NOT

%left PLUS MINUS CONCATENATION

%left MULTIPLICATION DIVISION INTEGER_DIVISION MODULO 

%left LPAREN RPAREN

%nonassoc  UNARY

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
          }
;


stmtlist: /* Empty: epsilon rule */
          { 
            // create an empty list of statements
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
                (*it)->print(); 
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
 

stmt: SEMICOLON /* Empty statement: ";" */
      {
        // Create a new empty statement node
        $$ = new lp::EmptyStmt(); 
      }
	  | asgn SEMICOLON
      {
        // Default action
        // $$ = $1;
      }
	  | ask_for_key SEMICOLON {}
    | print SEMICOLON {}
    | read SEMICOLON {}
	  | read_string SEMICOLON {}
	  | if SEMICOLON {}
	  | while SEMICOLON {}
	  | do_while SEMICOLON {}
	  | for SEMICOLON {}
    | switch SEMICOLON {}
	  | block {}
	  | placecursor SEMICOLON {}
	  | clear SEMICOLON	{}
;


block: LETFCURLYBRACKET stmtlist RIGHTCURLYBRACKET  
      {
        $$ = new lp::BlockStmt($2); 
      }
;


controlSymbol: /* Empty: Epsilon rule*/
              {
                // To control the interactive mode in "if" and "while" sentences
                control++;
              }
;


if: IF controlSymbol cond THEN stmtlist END_IF
    {
      // Create a new if statement node
      $$ = new lp::IfStmt($3, $5);
        
      // To control the interactive mode
      control--;
  	}
	| IF controlSymbol cond stmtlist END_IF
    {
		  execerror("Syntax error: missing ENTONCES symbol of if statement", "si cond ENTONCES ..");
    }
	| IF controlSymbol cond THEN stmtlist ELSE stmtlist END_IF
	  {
      $$ = new lp::IfStmt($3, $5, $7);
      control--;
	  }
	| IF controlSymbol cond stmtlist ELSE stmtlist END_IF
    {
		  execerror("Syntax error: missing ENTONCES symbol of if statement", "si cond ENTONCES ..");
	  }
;


while: WHILE controlSymbol cond DO stmtlist END_WHILE 
      {
        $$ = new lp::WhileStmt($3, $5);
        control--;
      }
		| WHILE controlSymbol cond stmtlist END_WHILE 
      {
        execerror("Syntax error: missing HACER symbol of while statement", "mientras cond HACER ..");
      }
;


do_while: DO_WHILE controlSymbol stmtlist UNTIL cond
          {
            $$ = new lp::DoWhileStmt($5, $3);
            control--;
    	    }
		    | DO_WHILE controlSymbol stmtlist cond
          {
            execerror("Syntax error: missing HASTA symbol of do while statement", "repetir stmtlist HASTA cond ..");
          }
;


for: FOR controlSymbol VARIABLE FROM exp UNTIL exp STEP exp DO stmtlist END_FOR
    {
      $$ = new lp::ForStmt($3, $5, $7, $9, $11);
      control--;
    }
	| FOR controlSymbol VARIABLE FROM exp UNTIL exp DO stmtlist END_FOR
    {
      $$ = new lp::ForStmt($3, $5, $7, $9);
      control--;
    }
	| FOR controlSymbol CONSTANT FROM exp UNTIL exp STEP exp DO stmtlist END_FOR
    {
      execerror("Semantic error in for statement: it is not allowed to modify a constant ", $3);
    }
	| FOR controlSymbol CONSTANT FROM exp UNTIL exp DO stmtlist END_FOR
    {
      execerror("Semantic error in for statement: it is not allowed to modify a constant ", $3);
    }
	| FOR controlSymbol VARIABLE exp UNTIL exp STEP exp DO stmtlist END_FOR
    {
      execerror("Syntax error: missing DESDE symbol of for statement", "para id DESDE ..");
    }
	| FOR controlSymbol VARIABLE FROM exp STEP exp DO stmtlist END_FOR
    {
      execerror("Syntax error: missing HASTA symbol of for statement", "para id DESDE exp HASTA ..");
    }
	| FOR controlSymbol VARIABLE FROM exp UNTIL exp STEP exp stmtlist END_FOR
    {
      execerror("Syntax error: missing HACER symbol of for statement", "para id DESDE exp HASTA exp PASO exp HACER ..");
    }
	| FOR controlSymbol VARIABLE exp UNTIL exp DO stmtlist END_FOR
    {
      execerror("Syntax error: missing DESDE symbol of for statement", "para id DESDE ..");
    }
	| FOR controlSymbol VARIABLE FROM exp DO stmtlist END_FOR
    {
      execerror("Syntax error: missing HASTA symbol of for statement", "para id DESDE exp HASTA ..");
    }
	| FOR controlSymbol VARIABLE FROM exp UNTIL exp stmtlist END_FOR
    {
      execerror("Syntax error: missing HACER symbol of for statement", "para id DESDE exp HASTA exp HACER ..");
    }
	| FOR controlSymbol VARIABLE FROM UNTIL exp STEP exp DO stmtlist END_FOR
    {
      execerror("Syntax error: missing from EXP argument of for statement", "para id desde EXP ..");
    }
	| FOR controlSymbol VARIABLE FROM exp UNTIL STEP exp DO stmtlist END_FOR
    {
      execerror("Syntax error: missing until EXP argument of for statement", "para id desde exp hasta EXP ..");
    }
	| FOR controlSymbol VARIABLE FROM UNTIL exp DO stmtlist END_FOR
    {
      execerror("Syntax error: missing from EXP argument of for statement", "para id desde EXP ..");
    }
	| FOR controlSymbol VARIABLE FROM exp UNTIL DO stmtlist END_FOR
    {
      execerror("Syntax error: missing until EXP argument of for statement", "para id desde exp hasta EXP ..");
    }
;


switch: SWITCH controlSymbol LPAREN exp RPAREN listOfValues DEFAULT TWO_POINTS stmtlist END_SWITCH
        {
          $$ = new lp::SwitchStmt($4, $6, $9);
          control --;
        }
;


listOfValues: VALUE NUMBER TWO_POINTS stmtlist restOfListOfValues
              {
                $$ = $5;
                lp::ExpNode *e = new lp::NumberNode($2);
                lp::Value *v = new lp::Value(e, $4);
                $$->push_front(v);
              }
            | VALUE STRING TWO_POINTS stmtlist restOfListOfValues
              {
                $$ = $5;
                lp::ExpNode *e = new lp::StringNode($2);
                lp::Value *v = new lp::Value(e, $4);
                $$->push_front(v);
              }
;


restOfListOfValues: /*Empty: Epsilon rule*/
                    {
                      $$ = new std::list<lp::Value *>(); 
                    }
                  | VALUE NUMBER TWO_POINTS stmtlist restOfListOfValues
                    {
                      $$ = $5;
                      lp::ExpNode *e = new lp::NumberNode($2);
                      lp::Value *v = new lp::Value(e, $4);
                      $$->push_front(v);
                    }
                  | VALUE STRING TWO_POINTS stmtlist restOfListOfValues
                    {
                      $$ = $5;
                      lp::ExpNode *e = new lp::StringNode($2);
                      lp::Value *v = new lp::Value(e, $4);
                      $$->push_front(v);
                    }
;


cond: LPAREN exp RPAREN
      { 
        $$ = $2;
      }
;


asgn: VARIABLE ASSIGNMENT exp	
      { 
        $$ = new lp::AssignmentStmt($1, $3);
      }
	  |  VARIABLE ASSIGNMENT asgn 
      {
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


ask_for_key: ASK_FOR_KEY LPAREN exp RPAREN
            {
              $$ = new lp::AskForKeyStmt($3);
            }
			    | ASK_FOR_KEY LPAREN RPAREN
            {
              $$ = new lp::AskForKeyStmt(new lp::StringNode("Pulsa INTRO para continuar"));
            }
;


print: PRINT exp 
      {
        $$ = new lp::PrintStmt($2);
      }
;	


read: READ LPAREN VARIABLE RPAREN  
      {
        $$ = new lp::ReadStmt($3);
      }
	  | READ LPAREN CONSTANT RPAREN  
      {   
        execerror("Semantic error in \"read statement\": it is not allowed to modify a constant ",$3);
      }
;


placecursor: PLACECURSOR LPAREN exp COMMA exp RPAREN 
            {
              $$ = new lp::PlaceStmt($3, $5);
            }
;

clear: CLEAR
      {
        $$ = new lp::ClearStmt();
      }
;

read_string: READ_STRING LPAREN VARIABLE RPAREN  
            {
              $$ = new lp::ReadStmtString($3);
            }
          | READ_STRING LPAREN CONSTANT RPAREN  
            {   
              execerror("Semantic error in \"read string statement\": it is not allowed to modify a constant ",$3);
            }
;


exp: NUMBER 
    { $$ = new lp::NumberNode($1); }
	|	STRING 
    { $$ = new lp::StringNode($1); }
	| exp PLUS exp 
    { $$ = new lp::PlusNode($1, $3); }
	| exp MINUS exp
    { $$ = new lp::MinusNode($1, $3); }
	|	exp MULTIPLICATION exp 
		{ $$ = new lp::MultiplicationNode($1, $3); }
	| exp DIVISION exp 
    { $$ = new lp::DivisionNode($1, $3); }
	| exp INTEGER_DIVISION exp
		{ $$ = new lp::IntegerDivisionNode($1, $3); }
  | exp CONCATENATION exp 
    { $$ = new lp::ConcatenationNode($1, $3); }
	| LPAREN exp RPAREN
    { $$ = $2; }
  | PLUS exp %prec UNARY
		{ $$ = new lp::UnaryPlusNode($2); }
	|	MINUS exp %prec UNARY
		{ $$ = new lp::UnaryMinusNode($2); }
	|	exp MODULO exp 
		{ $$ = new lp::ModuloNode($1, $3); }
	|	exp POWER exp 
    { $$ = new lp::PowerNode($1, $3); }
	| VARIABLE
		{ $$ = new lp::VariableNode($1); }
	| CONSTANT
		{ $$ = new lp::ConstantNode($1); }
  | exp GREATER_THAN exp
	 	{ $$ = new lp::GreaterThanNode($1,$3); }
	| exp GREATER_OR_EQUAL exp 
	 	{ $$ = new lp::GreaterOrEqualNode($1,$3); }
	| exp LESS_THAN exp 	
	 	{ $$ = new lp::LessThanNode($1,$3); }
	| exp LESS_OR_EQUAL exp 
	 	{ $$ = new lp::LessOrEqualNode($1,$3); }
	| exp EQUAL exp 	
	 	{ $$ = new lp::EqualNode($1,$3); }
  | exp NOT_EQUAL exp 	
	 	{ $$ = new lp::NotEqualNode($1,$3); }
  | exp AND exp 
	 	{ $$ = new lp::AndNode($1,$3); }
  | exp OR exp 
	 	{ $$ = new lp::OrNode($1,$3); }
  | NOT exp 
	 	{ $$ = new lp::NotNode($2); }
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
;


listOfExp: /* Empty list of numeric expressions */
          {
            $$ = new std::list<lp::ExpNode *>(); 
          }
	      | exp restOfListOfExp
          {
            $$ = $2;
            $$->push_front($1);
          }
;


restOfListOfExp: /* Empty list of numeric expressions */
                {
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
