/* DECLARATIONS AREA */
%{

typedef struct fileInfo {
    int words;
    int numbers;
    int spaces;
    int tabs;
    int newLineCharacters;
    int commas;
    int dots;
} fileInfo;

static fileInfo info;

%}

digit [0-9]
letter [a-zA-ZáéíóúÁÉÍÓÚñÑ]
word ({letter}|{digit})*{letter}({letter}|{digit})*
number {digit}+(\.{digit}+)?(E[+\-]?{digit}+)?
/* END OF DECLARATIONS AREA */

/* RULES AREA */
%%
{word}      info.words++;
{number}    info.numbers++;
[ ]         info.spaces++;
\t          info.tabs++;
\n          info.newLineCharacters++;
,           info.commas++;
\.          info.dots++;
^#$         { printf("\nClosing lexical analyzer\n\n"); return 0; }
%%
/* END OF RULES AREA */


/* AUXILIARY FUNCTIONS AREA */
void initFileInfo(fileInfo* info);
void showFileInfo(char* filename, fileInfo* info);


int main(int argc, char* argv[])
{

    initFileInfo(&info);

    switch(argc)
    {
        case 2: yyin = fopen(argv[1],"r");
        
                if(yyin == NULL)
                {
                    printf("Error. Input file doesn't exist\n");
                    return -1;
                }
    }

    if(argc != 2)
        printf("Analyzing stdin. Enter '#' to finish\n\n");

    yylex();

    if(argc == 2)
        showFileInfo(argv[1], &info);
    else showFileInfo("stdin", &info);

    return 0;
}


void initFileInfo(fileInfo* info)
{
    info->words = 0;
    info->numbers = 0;
    info->spaces = 0;
    info->tabs = 0;
    info->newLineCharacters = 0;
    info->commas = 0;
    info->dots = 0;
}


void showFileInfo(char* filename, fileInfo* info)
{
    printf("%s contains:\n", filename);
    printf("\t%d words\n", info->words);
    printf("\t%d numbers\n", info->numbers);
    printf("\t%d spaces\n", info->spaces);
    printf("\t%d tabs\n", info->tabs);
    printf("\t%d newLineCharacters\n", info->newLineCharacters);
    printf("\t%d commas\n", info->commas);
    printf("\t%d dots\n", info->dots);
}
/* END OF AUXILIARY FUNCTIONS AREA */