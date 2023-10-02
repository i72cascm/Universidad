/*** analizadorlexico.l ***/

/*** Zona de las declaraciones o definiciones ***/
%{
   /* Descripción
    	Analizador léxico que permite reconocer los componentes
        léxicos de un programa escrito en pseudocódigo
    */
    #include "analizadorlexico.h"
%}

/***** Definiciones regulares *****/

espacio         [ \t\n]
letra           [a-zA-ZáéíóúÁÉÍÓÚ]
digito          [0-9]+(\.[0-9]+)?
identificador   {letra}(_?({letra}|{digito})+)*_?

/***** Estados del automata *****/
%x Q_CADENA Q_COMENTARIO_SIMPLE Q_COMENTARIO_MULTIPLE

/***** Zona de reglas y funcion de automata *****/
%%

"'"                       {
                            BEGIN(Q_CADENA);
                            yymore();
                        }

<Q_CADENA>\\'               {
                                yymore();
                            }


<Q_CADENA>'                 {
                                printf("TOKEN %d: Cadena de comillas simples detectada: %s \n",CADENA, yytext);
                                BEGIN(INITIAL);
                            }

<Q_CADENA>[^']              {
                                yymore();
                            }

"!!"                        {
                                yymore();
                                BEGIN(Q_COMENTARIO_SIMPLE);
                            }

<Q_COMENTARIO_SIMPLE>[^\n]  {
                                yymore();
                            }

<Q_COMENTARIO_SIMPLE>\n     {
                                yymore();
                                printf("TOKEN %d: Detectado comentario de una línea: %s",COMENTARIO_SIMPLE, yytext);
                                BEGIN(INITIAL);
                            }       

"<<"                        {
                                yymore();
                                BEGIN(Q_COMENTARIO_MULTIPLE);
                            }
                            
<Q_COMENTARIO_MULTIPLE>">>" {
                                yymore();
                                printf("TOKEN %d: Detectado comentario de más de una línea: %s\n",COMENTARIO_MULTIPLE, yytext);
                                BEGIN(INITIAL);
                            }

<Q_COMENTARIO_MULTIPLE>[^<<] {
                                yymore();
                                
                            }

":="                    { printf("TOKEN %d operador asignación: %s\n", ASIGNACION, yytext); }

"+"                     { printf("TOKEN %d operador aritmético: %s\n", SUMA, yytext); }
"++"                    { printf("TOKEN %d operador aritmético: %s\n", INCREMENTO, yytext); }
"-"                     { printf("TOKEN %d operador aritmético: %s\n", RESTA, yytext); }
"--"                    { printf("TOKEN %d operador aritmético: %s\n", DECREMENTO, yytext); }
"*"                     { printf("TOKEN %d operador aritmético: %s\n", PRODUCTO, yytext); }
"/"                     { printf("TOKEN %d operador aritmético: %s\n", DIVISION, yytext); }
"//"                    { printf("TOKEN %d operador aritmético: %s\n", DIVISION_ENTERA, yytext); }
"%"                     { printf("TOKEN %d operador aritmético: %s\n", MODULO, yytext); }
"^"                     { printf("TOKEN %d operador aritmético: %s\n", POTENCIA, yytext); }

"||"                    { printf("TOKEN %d operador alfanumérico: %s\n", CONCATENACION, yytext); }

"<"                     { printf("TOKEN %d operador relacional de números y cadenas: %s\n", MENOR_QUE, yytext); }
"<="                    { printf("TOKEN %d operador relacional de números y cadenas: %s\n", MENOR_IGUAL_QUE, yytext); }
">"                     { printf("TOKEN %d operador relacional de números y cadenas: %s\n", MAYOR_QUE, yytext); }
">="                    { printf("TOKEN %d operador relacional de números y cadenas: %s\n", MAYOR_IGUAL_QUE, yytext); }
"=="                    { printf("TOKEN %d operador relacional de números y cadenas: %s\n", IGUAL, yytext); }
"<>"                    { printf("TOKEN %d operador relacional de números y cadenas: %s\n", DISTINTO, yytext); }

"#o"                    { printf("TOKEN %d operadores lógicos: %s\n", DISYUNCION_LOGICA, yytext); }
"#y"                    { printf("TOKEN %d operadores lógicos: %s\n", CONJUNCION_LOGICA, yytext); }
"#no"                   { printf("TOKEN %d operadores lógicos: %s\n", NEGACION_LOGICA, yytext); }

(?i:inicio)                  { printf("TOKEN %d palabra reservada: %s\n", INICIO, yytext); }
(?i:fin)                     { printf("TOKEN %d palabra reservada: %s\n", FIN, yytext); }
(?i:leer)                    { printf("TOKEN %d palabra reservada: %s\n", LEER, yytext); }
(?i:escribir)                { printf("TOKEN %d palabra reservada: %s\n", ESCRIBIR, yytext); }                    
(?i:si)                      { printf("TOKEN %d palabra reservada: %s\n", SI, yytext); }
(?i:entonces)                { printf("TOKEN %d palabra reservada: %s\n", ENTONCES, yytext); }
(?i:si_no)                   { printf("TOKEN %d palabra reservada: %s\n", SI_NO, yytext); }
(?i:fin_si)                  { printf("TOKEN %d palabra reservada: %s\n", FIN_SI, yytext); }
(?i:mientras)                { printf("TOKEN %d palabra reservada: %s\n", MIENTRAS, yytext); }
(?i:hacer)                   { printf("TOKEN %d palabra reservada: %s\n", HACER, yytext); }
(?i:fin_mientras)            { printf("TOKEN %d palabra reservada: %s\n", FIN_MIENTRAS, yytext); }
(?i:repetir)                 { printf("TOKEN %d palabra reservada: %s\n", REPETIR, yytext); }
(?i:hasta_que)               { printf("TOKEN %d palabra reservada: %s\n", HASTA_QUE, yytext); }
(?i:para)                    { printf("TOKEN %d palabra reservada: %s\n", PARA, yytext); }
(?i:desde)                   { printf("TOKEN %d palabra reservada: %s\n", DESDE, yytext); }
(?i:hasta)                   { printf("TOKEN %d palabra reservada: %s\n", HASTA, yytext); }
(?i:paso)                    { printf("TOKEN %d palabra reservada: %s\n", PASO, yytext); }
(?i:fin_para)                { printf("TOKEN %d palabra reservada: %s\n", FIN_PARA, yytext); }

{identificador}         { printf("TOKEN %d identificador detectado: %s\n", IDENTIFICADOR, yytext); }
{digito}                { printf("TOKEN %d numero detectado: %s\n", NUMERO, yytext); }

";"                     { printf("TOKEN %d otros componentes léxicos: %s\n", FIN_SENTENCIA, yytext); }
"("                     { printf("TOKEN %d otros componentes léxicos: %s\n", PARENTESIS_IZQ, yytext); }
")"                     { printf("TOKEN %d otros componentes léxicos: %s\n", PARENTESIS_DRCH, yytext); }



{espacio}+              ;
.                       {printf("ERROR: %s no reconocido.\n",yytext);}


%%

/*** Zona de funciones auxiliares ***/

int main(int cantidad, char* palabras[]){
   switch(cantidad){

      case 2: 
         yyin = fopen(palabras[1],"r");
         if(yyin == NULL){
            printf("El fichero de entrada no existe.");
         }
         break;

      default:
         printf("Número de argumentos inválido, el número de argumentos para este programa es 2 (ejecutable y fichero de entrada).");
         return -1;
   }
   yylex();
   return 0;
}