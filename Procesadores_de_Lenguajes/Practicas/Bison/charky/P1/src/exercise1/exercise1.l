/* DECLARATIONS AREA */

/* Regular definitions */
digit [0-9]
letter [a-zA-Z]
identifier {letter}({letter}|{digit})*
integer {digit}+(E[+\-]?{digit}+)?
real {digit}+(\.{digit}+)?(E[+\-]?{digit}+)?

/* END OF DECLARATIONS AREA */

/* RULES AREA */
%%

{integer}               fprintf(yyout, "%.1f", (float)atoi(yytext));
{identifier}|{real}     fprintf(yyout, "%s", yytext);

%%
/* END OF RULES AREA */

/* AUXILIARY FUNCTIONS AREA */
int main(int argc, char* argv[])
{
    switch(argc)
    {
        case 2: yyin = fopen(argv[1],"r");
        
                if(yyin == NULL)
                {
                    printf("Error. Input file doesn't exist\n");
                    return -1;
                }

                break;

        case 3: yyin = fopen(argv[1],"r");
                yyout = fopen(argv[2], "r");

                if(yyin == NULL)
                {
                    printf("Error. Input file doesn't exist\n");
                    return -1;
                }

                if(yyout != NULL)
                {
                    printf("Error. Output file already exists\n");
                    fclose(yyout);
                    return -1;
                } else yyout = fopen(argv[2], "w");

                break;

        default: printf("Error. Arguments number must be 1 or 2\n");
                 return -1;
    }

    yylex();

    return 0;
}
/* END OF AUXILIARY FUNCTIONS AREA */