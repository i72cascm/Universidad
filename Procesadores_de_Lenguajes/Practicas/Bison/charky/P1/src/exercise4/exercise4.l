%{
    #include "exercise4.h"
%}

espacio     [ \t\n]
espacios    {espacio}+
letra       [a-zA-ZáéíóúÁÉÍÓÚ]
digito      [0-9]
identificador   {letra}(_?({letra}|{digito})+)*_?
numero      {digito}+(\.{digito}+)?(E[+\-]?{digito}+)?


%x ESTADO_COMENTARIO_VARIAS_LINEAS ESTADO_COMENTARIO_UNA_LINEA
%x ESTADO_CADENA
%x MAL_IDENTIFICADOR MAL_NUMERO

%%

{espacios}          ;

(?i:inicio)         { printf("\n Palabra reservada: %s --> token %d\n", yytext, INICIO); }

(?i:fin)            { printf("\n Palabra reservada: %s --> token %d\n", yytext, FIN); }

(?i:leer)           { printf("\n Palabra reservada: %s --> token %d\n", yytext, LEER); }

(?i:escribir)       { printf("\n Palabra reservada: %s --> token %d\n", yytext, ESCRIBIR); }

(?i:si)             { printf("\n Palabra reservada: %s --> token %d\n", yytext, SI); }

(?i:entonces)       { printf("\n Palabra reservada: %s --> token %d\n", yytext, ENTONCES); }

(?i:si_no)          { printf("\n Palabra reservada: %s --> token %d\n", yytext, SI_NO); }

(?i:fin_si)         { printf("\n Palabra reservada: %s --> token %d\n", yytext, FIN_SI); }

(?i:mientras)       { printf("\n Palabra reservada: %s --> token %d\n", yytext, MIENTRAS); }

(?i:hacer)          { printf("\n Palabra reservada: %s --> token %d\n", yytext, HACER); }

(?i:fin_mientras)   { printf("\n Palabra reservada: %s --> token %d\n", yytext, FIN_MIENTRAS); }

(?i:repetir)        { printf("\n Palabra reservada: %s --> token %d\n", yytext, REPETIR); }

(?i:hasta_que)      { printf("\n Palabra reservada: %s --> token %d\n", yytext, HASTA_QUE); }

(?i:para)           { printf("\n Palabra reservada: %s --> token %d\n", yytext, PARA); }

(?i:desde)          { printf("\n Palabra reservada: %s --> token %d\n", yytext, DESDE); }
    
(?i:hasta)          { printf("\n Palabra reservada: %s --> token %d\n", yytext, HASTA); }

(?i:paso)           { printf("\n Palabra reservada: %s --> token %d\n", yytext, PASO); }

(?i:fin_para)       { printf("\n Palabra reservada: %s --> token %d\n", yytext, FIN_PARA); }

:=          { printf("\n Operador de asignacion: %s --> token %d\n", yytext, ASIGNACION); }

\+          { printf("\n Operador aritmetico: %s --> token %d\n", yytext, SUMA); }

-           { printf("\n Operador aritmetico: %s --> token %d\n", yytext, RESTA); }

\*          { printf("\n Operador aritmetico: %s --> token %d\n", yytext, PRODUCTO); }

\/          { printf("\n Operador aritmetico: %s --> token %d\n", yytext, DIVISION); }

#mod        { printf("\n Operador aritmetico: %s --> token %d\n", yytext, MODULO); }

#div        { printf("\n Operador aritmetico: %s --> token %d\n", yytext, DIVISION_ENTERA); }

\*\*        { printf("\n Operador aritmetico: %s --> token %d\n", yytext, POTENCIA); }

\|\|        { printf("\n Concatenacion: %s --> token %d\n", yytext, CONCATENACION); }

"<"         { printf("\n Operador relacional: %s --> token %d\n", yytext, MENOR_QUE); }

"<="        { printf("\n Operador relacional: %s --> token %d\n", yytext, MENOR_IGUAL_QUE); }

">"         { printf("\n Operador relacional: %s --> token %d\n", yytext, MAYOR_QUE); }

">="        { printf("\n Operador relacional: %s --> token %d\n", yytext, MAYOR_IGUAL_QUE); }

"=="        { printf("\n Operador relacional: %s --> token %d\n", yytext, IGUAL); }

"<>"        { printf("\n Operador relacional: %s --> token %d\n", yytext, DISTINTO); }

#o          { 
                printf("\n Operador logico: %s --> token %d\n",
                        yytext,DISYUNCION_LOGICA); 
            }

#y          { 
                printf("\n Operador logico: %s --> token %d\n",
                        yytext,CONJUNCION_LOGICA);
            }

#no         { 
                printf("\n Operador logico: %s --> token %d\n",
                        yytext,NEGACION_LOGICA);
            }

;           { printf("\n Fin de Sentencia: %s --> token %d\n", yytext, FIN_SENTENCIA); }

"("         { printf("\n Parentesis izquierdo: %s --> token %d\n", yytext, PARENTESIS_IZQUIERDO); }

")"         { printf("\n Parentesis derecho: %s --> token %d\n", yytext, PARENTESIS_DERECHO); }

"<<"        {
                BEGIN(ESTADO_COMENTARIO_VARIAS_LINEAS);
                yymore();
            }

<ESTADO_COMENTARIO_VARIAS_LINEAS>[^<<]  {
                                            yymore();
                                        }

<ESTADO_COMENTARIO_VARIAS_LINEAS>"<<"   {
                                            printf("\n !! ERROR !!. No se pueden anidar comentarios:\n%s\n", yytext);
                                            return 0;
                                        }

<ESTADO_COMENTARIO_VARIAS_LINEAS>">>"   {
                                            printf("\n Comentario de varias lineas:\n%s\n --> token %d\n", yytext, COMENTARIO_VARIAS_LINEAS);
                                            BEGIN(INITIAL);
                                        }

!!          {
                BEGIN(ESTADO_COMENTARIO_UNA_LINEA);
                yymore();
            }

<ESTADO_COMENTARIO_UNA_LINEA>[^\n]  {
                                        yymore();
                                    }

<ESTADO_COMENTARIO_UNA_LINEA>!!     {
                                        printf("\n !! ERROR !!. No se pueden anidar comentarios: \n\t%s\n", yytext);
                                        return 0;
                                    }

<ESTADO_COMENTARIO_UNA_LINEA>\n     {
                                        printf("\n Comentario de una linea:\n\t%s --> token %d\n", yytext, COMENTARIO_UNA_LINEA);
                                        BEGIN(INITIAL);
                                    }

'           { 
                BEGIN(ESTADO_CADENA); 
            }

<ESTADO_CADENA>\\'    yymore();

<ESTADO_CADENA>[^']    yymore();

<ESTADO_CADENA>'   {
                        yytext[strlen(yytext)-1] = '\0';
                        printf("\n Cadena:\n\t%s\n --> token %d\n", yytext, CADENA);
                        BEGIN(INITIAL);
                    }

{identificador}     { 
                        printf("\n Identificador: %s --> token %d\n", yytext, IDENTIFICADOR);
                        BEGIN(INITIAL);
                    }

({identificador}_|_{identificador})[^ \t\n;]*   {
                                                    /*
                                                    printf("\n !! ERROR !!. Identificador mal escrito: '%s'\n",yytext);
                                                    BEGIN(INITIAL);
                                                    */
                                                }

{numero}            { printf("\n Numero: %s --> token %d\n", yytext, NUMERO); }

({numero}{letra})[^ \t\n;]* {
                                printf("\n !! ERROR !!. Numero mal escrito: '%s'\n",yytext);
                                BEGIN(INITIAL);
                            }

.           { printf("\n !! ERROR !!. El caracter %s no se reconoce\n", yytext); }

%%


int main(int argc, char* argv[])
{

    switch(argc)
    {
        case 2: yyin = fopen(argv[1],"r");
        
                if(yyin == NULL)
                {
                    printf("Error. El fichero de entrada no existe\n");
                    return -1;
                }
    }

    yylex();

    return 0;
}