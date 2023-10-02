/*** correo.l ***/

/*** Zona de las declaraciones o definiciones ***/
%{
   /* Descripción
    	El analizador léxico reconocerá direcciones de correo electrónico de estudiantes de la UCO
      llevará un contador con todos los correos introducidos y mostrará un mensaje de rror cuando
      no reconozca una dirección de correo correcta.
   */
   int contador = 0;
%}

/***** Definiciones regulares *****/
espacio       [ \t\n]
espacios      {espacio}+
letra         [a-zA-Z]
digito        [0-9]
identificador {letra}{digito}{2}{letra}{5}[@][u][c][o][.][e][s]

/***** Zona de las reglas *****/
%%

{identificador} contador++; 
[ ]+ ;
([a-zA-Z0-9.@]+) { printf("%s: ERROR, no es un correo de la uco.\n", yytext); }
.|\n ;

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
   printf("--------------------------------------------.\n");
   printf("%d direciones de correo correctas encontradas.\n", contador);
   return 0;
}