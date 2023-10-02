/*** figura.l ***/

/*** Zona de las declaraciones o definiciones ***/
%{
   /* Descripción
    	El analizador léxico permite reconocer las siguientes figuras geomátricas:
      triángulo, cuadrado, círculo
      Nota: Una figura por línea de texto
   */
   int triangulo_ = 0;
   int cuadrado_ = 0;
   int circulo_ = 0;
%}

/***** Definiciones regulares *****/
digito        [0-9]
espacio       [ \t]
espacios      {espacio}+
coma          [,]
set           {digito}{coma}{digito}
punto         [(]{set}{espacio}{set}[)]
triangulo     ({punto}{espacio}){2}{punto}
cuadrado      {punto}{espacio}{punto}
circulo       {punto}{espacio}{set}

/***** Zona de las reglas *****/
%%
{triangulo}   triangulo_++;
{cuadrado}    cuadrado_++;
{circulo}     circulo_++;
[a-zA-Z0-9. @,()]+    { printf("%s: ERROR, no es una figura reconocida.\n", yytext); }  
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
   printf("%d triángulos.\n", triangulo_);
   printf("%d cuadrados.\n", cuadrado_);
   printf("%d círculo.\n", circulo_);
   return 0;
}