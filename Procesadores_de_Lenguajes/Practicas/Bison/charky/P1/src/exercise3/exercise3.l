%{
    void movePiece(char piece);
    void getPieceByLetter(char piece, char* pieceLetter);
%}

digit [0-9]
number {digit}+(E[+\-]?{digit}+)?
row [1-8]
column [a-h]
king R
queen D
bishop A
knight C
rook T
square {column}{row}
piece [RDACT]

/* AUTOMATON STATES */
%x WHITE_MOVE WHITE_PIECE_MOVE WHITE_AMBIGUOUS_MOVE WHITE_PAWN_MOVE WHITE_HAS_MOVED WHITE_CHECKS WHITE_CHECKMATES
%x BLACK_MOVE BLACK_PIECE_MOVE BLACK_AMBIGUOUS_MOVE BLACK_PAWN_MOVE BLACK_HAS_MOVED BLACK_CHECKS BLACK_CHECKMATES


%%

{number}\.              {
                            BEGIN(WHITE_MOVE);

                            int movement = 0;

                            sscanf(yytext, "%d", &movement);
                            printf("MOVEMENT %d\n", movement);
                            printf("\tWHITE: ");
                        }

<WHITE_MOVE>{piece}     {
                            BEGIN(WHITE_PIECE_MOVE);
                            movePiece(yytext[0]);
                        }

<WHITE_PIECE_MOVE>({row}|{column})  {
                                        BEGIN(WHITE_AMBIGUOUS_MOVE);

                                        /*ASCII: 1-8 --> 49-56
                                                 a-h --> 97-104 */
                                        
                                        char rowOrColumn[7];

                                        if(yytext[0] < 57)
                                            strcpy(rowOrColumn,"row");
                                        else strcpy(rowOrColumn,"column");

                                        printf("of the %s %c ", rowOrColumn, yytext[0]);
                                    }

<WHITE_AMBIGUOUS_MOVE>x?{square}    {
                                        BEGIN(WHITE_HAS_MOVED);

                                        char destinationSquare[2];

                                        if(yytext[0] == 'x') {
                                            sscanf(yytext, "x%s", destinationSquare);
                                            printf("captures on %s", destinationSquare);
                                        } else {
                                            sscanf(yytext, "%s", destinationSquare);
                                            printf("moves to %s", destinationSquare);
                                        }
                                    }

<WHITE_PIECE_MOVE>x?{square}    {
                                    BEGIN(WHITE_HAS_MOVED);

                                    char destinationSquare[2];

                                    if(yytext[0] == 'x') {
                                        sscanf(yytext, "x%s", destinationSquare);
                                        printf("captures on %s", destinationSquare);
                                    } else {
                                        sscanf(yytext, "%s", destinationSquare);
                                        printf("moves to %s", destinationSquare);
                                    }
                                }


<WHITE_MOVE>{column}    {
                            BEGIN(WHITE_PAWN_MOVE);
                            yymore();
                        }

<WHITE_PAWN_MOVE>{row}  {
                            BEGIN(WHITE_HAS_MOVED);
                            printf("\tPawn moves to %s", yytext);
                        }

<WHITE_PAWN_MOVE>x{square}    {
                                    BEGIN(WHITE_HAS_MOVED);

                                    char pawnColumn = 0, capturedSquare[2];

                                    sscanf(yytext, "%cx%s", &pawnColumn, capturedSquare);

                                    printf("\tPawn on the column %c captures on %s", pawnColumn, capturedSquare);
                                }

<WHITE_PAWN_MOVE>{row}=[D|T|A|C]    {
                                        BEGIN(WHITE_HAS_MOVED);

                                        char pawnColumn = 0, promotedPiece = 0, pieceLetter[10];

                                        sscanf(yytext, "%c%*c=%c", &pawnColumn, &promotedPiece);

                                        getPieceByLetter(promotedPiece, pieceLetter);

                                        printf("\tPawn on the column %c promotes to %s", pawnColumn, pieceLetter);
                                    }

<WHITE_PAWN_MOVE>x{square}=[D|T|A|C]    {
                                            BEGIN(WHITE_HAS_MOVED);

                                            char pawnColumn = 0, capturedSquare[10], promotedPiece = 0, pieceLetter[10];

                                            sscanf(yytext, "%cx%2s=%c", &pawnColumn, capturedSquare, &promotedPiece);

                                            getPieceByLetter(promotedPiece, pieceLetter);

                                            printf("\tPawn on the column %c captures on %s and promotes to %s", pawnColumn, capturedSquare, pieceLetter);
                                        }

<WHITE_PAWN_MOVE>x{square}[ ]a\.p\.     {
                                            BEGIN(WHITE_HAS_MOVED);

                                            char pawnColumn = 0, capturedSquare[2];

                                            sscanf(yytext, "%cx%s", &pawnColumn, capturedSquare);

                                            printf("\tPawn on the column %c captures on %s in passant", pawnColumn, capturedSquare);
                                        }

<WHITE_MOVE>0-0         {
                            BEGIN(WHITE_HAS_MOVED);
                            printf("\tWhite castles on the kingside");
                        }

<WHITE_MOVE>0-0-0       {
                            BEGIN(WHITE_HAS_MOVED);
                            printf("\tWhite castles on the queenside");
                        }

<WHITE_HAS_MOVED>\+     {
                            BEGIN(WHITE_CHECKS);
                            printf(" and checks");
                        }

<WHITE_HAS_MOVED>(\+\+|#)       {
                                    BEGIN(WHITE_CHECKMATES);
                                    printf(" and checkmates\n");
                                }

<WHITE_CHECKMATES>[ ]1-0        {
                                    printf("\nThe match has finished. White wins by checkmate\n\n");
                                    return 0;
                                }

<WHITE_CHECKS>[ ]       {
                            BEGIN(BLACK_MOVE);
                            printf("\n\tBLACK: ");
                        }

<WHITE_HAS_MOVED>[ ]    {
                            BEGIN(BLACK_MOVE);
                            printf("\n\tBLACK: ");
                        }

<WHITE_HAS_MOVED>[ ]1-0     {
                                printf("\n\nThe match has finished. White wins by resignation\n\n");
                                return 0;
                            }

<WHITE_HAS_MOVED>[ ]0-1     {
                                printf("\n\nThe match has finished. Black wins by resignation\n\n");
                                return 0;
                            }

<WHITE_HAS_MOVED>[ ]1\/2-1\/2   {
                                    printf("\n\nThe match has finished. Draw.\n\n");
                                    return 0;
                                }

<BLACK_MOVE>{piece}     {
                            BEGIN(BLACK_PIECE_MOVE);
                            movePiece(yytext[0]);
                        }

<BLACK_PIECE_MOVE>({row}|{column})  {
                                        BEGIN(BLACK_AMBIGUOUS_MOVE);

                                        /*ASCII: 1-8 --> 49-56
                                                 a-h --> 97-104 */
                                        
                                        char rowOrColumn[7];

                                        if(yytext[0] < 57)
                                            strcpy(rowOrColumn,"row");
                                        else strcpy(rowOrColumn,"column");

                                        printf("of the %s %c ", rowOrColumn, yytext[0]);
                                    }

<BLACK_AMBIGUOUS_MOVE>x?{square}    {
                                        BEGIN(BLACK_HAS_MOVED);

                                        char destinationSquare[2];

                                        if(yytext[0] == 'x') {
                                            sscanf(yytext, "x%s", destinationSquare);
                                            printf("captures on %s", destinationSquare);
                                        } else {
                                            sscanf(yytext, "%s", destinationSquare);
                                            printf("moves to %s", destinationSquare);
                                        }
                                    }

<BLACK_PIECE_MOVE>x?{square}    {
                                    BEGIN(BLACK_HAS_MOVED);

                                    char destinationSquare[2];

                                    if(yytext[0] == 'x') {
                                        sscanf(yytext, "x%s", destinationSquare);
                                        printf("captures on %s", destinationSquare);
                                    } else {
                                        sscanf(yytext, "%s", destinationSquare);
                                        printf("moves to %s", destinationSquare);
                                    }
                                }


<BLACK_MOVE>{column}    {
                            BEGIN(BLACK_PAWN_MOVE);
                            yymore();
                        }

<BLACK_PAWN_MOVE>{row}  {
                            BEGIN(BLACK_HAS_MOVED);
                            printf("\tPawn moves to %s", yytext);
                        }

<BLACK_PAWN_MOVE>x{square}  {
                                BEGIN(BLACK_HAS_MOVED);

                                char pawnColumn = 0, capturedSquare[2];

                                sscanf(yytext, "%cx%s", &pawnColumn, capturedSquare);

                                printf("\tPawn on the column %c captures on %s", pawnColumn, capturedSquare);
                            }

<BLACK_PAWN_MOVE>{row}=[D|T|A|C]    {
                                        BEGIN(BLACK_HAS_MOVED);

                                        char pawnColumn = 0, promotedPiece = 0, pieceLetter[10];

                                        sscanf(yytext, "%c%*c=%c", &pawnColumn, &promotedPiece);

                                        getPieceByLetter(promotedPiece, pieceLetter);

                                        printf("\tPawn on the column %c promotes to %s", pawnColumn, pieceLetter);
                                    }

<BLACK_PAWN_MOVE>x{square}=[D|T|A|C]    {
                                            BEGIN(BLACK_HAS_MOVED);

                                            char pawnColumn = 0, capturedSquare[10], promotedPiece = 0, pieceLetter[10];

                                            sscanf(yytext, "%cx%2s=%c", &pawnColumn, capturedSquare, &promotedPiece);

                                            getPieceByLetter(promotedPiece, pieceLetter);

                                            printf("\tPawn on the column %c captures on %s and promotes to %s", pawnColumn, capturedSquare, pieceLetter);
                                        }

<BLACK_PAWN_MOVE>x{square}[ ]a\.p\.     {
                                            BEGIN(BLACK_HAS_MOVED);

                                            char pawnColumn = 0, capturedSquare[2];

                                            sscanf(yytext, "%cx%s", &pawnColumn, capturedSquare);

                                            printf("\tPawn on the column %c captures on %s en passant", pawnColumn, capturedSquare);
                                        }

<BLACK_MOVE>0-0         {
                            BEGIN(BLACK_HAS_MOVED);
                            printf("\tBlack castles on the kingside");
                        }

<BLACK_MOVE>0-0-0       {
                            BEGIN(BLACK_HAS_MOVED);
                            printf("\tBlack castles on the queenside");
                        }

<BLACK_HAS_MOVED>\+     {
                            BEGIN(BLACK_CHECKS);
                            printf(" and checks");
                        }

<BLACK_HAS_MOVED>(\+\+|#)       {
                                    BEGIN(BLACK_CHECKMATES);
                                    printf(" and checkmates\n");
                                }

<BLACK_CHECKMATES>[ ]0-1        {
                                    printf("\nThe match has finished. Black wins by checkmate\n\n");
                                    return 0;
                                }

<BLACK_CHECKS>[ ]       {
                            BEGIN(INITIAL);
                            printf("\n");
                        }

<BLACK_HAS_MOVED>[ ]    {
                            BEGIN(INITIAL);
                            printf("\n");
                        }

<BLACK_HAS_MOVED>[ ]1-0     {
                                printf("\n\nThe match has finished. White wins by resignation\n\n");
                                return 0;
                            }

<BLACK_HAS_MOVED>[ ]0-1     {
                                printf("\n\nThe match has finished. Black wins by resignation\n\n");
                                return 0;
                            }

<BLACK_HAS_MOVED>[ ]1\/2-1\/2   {
                                    printf("\n\nThe match has finished. Draw.\n\n");
                                    return 0;
                                }

%%


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

        default: printf("You must enter an input file!\n");
                 return -1;
    }

    printf("The match begins!!\n\n");
    yylex();

    return 0;
}


void movePiece(char piece) {
    char pieceLetter[10];
    getPieceByLetter(piece, pieceLetter);
    printf("\t%s ", pieceLetter);
}


void getPieceByLetter(char piece, char* pieceLetter) {
    switch(piece) {
        case 'R':
            strcpy(pieceLetter, "King");
            break;
        case 'D':
            strcpy(pieceLetter, "Queen");
            break;
        case 'T':
            strcpy(pieceLetter, "Rook");
            break;
        case 'A':
            strcpy(pieceLetter, "Bishop");
            break;
        case 'C':
            strcpy(pieceLetter, "Knight");
            break;
    }
}