/*** control.l ***/

/*** Zona de las declaraciones o definiciones ***/
%{
   /* Descripción
    	El analizador léxico denominado automata.l permite simular el funcionaminento
        de un autómata finito determinista
    */
    
%}

/***** Definiciones regulares *****/
espacio [ \t]

/***** Estados del automata *****/
%x Q1 Q2 Q3 Q4 Q5


/***** Zona de reglas y funcion de automata *****/
%%



"e"{espacio}        {
                        yymore();
                        BEGIN(Q1);
                    }

<Q1>"a"{espacio}    {
                        yymore();
                        BEGIN(Q2);
                    }

<Q1>[^ a]           {
                        yymore();
                        printf("Error, la cadena %s no ha sido reconocida por el autómata.\n",yytext);
                        BEGIN(INITIAL);
                    }

<Q2>"r"{espacio}    {
                        yymore();
                        BEGIN(Q1);
                    }


<Q2>"d"{espacio}    {
                        yymore();
                        BEGIN(Q3);
                    }

<Q2>[^ dr]          {
                        yymore();
                        printf("Error, la cadena %s no ha sido reconocida por el autómata.\n",yytext);
                        BEGIN(INITIAL);
                    }
                    
<Q3>"r"{espacio}    {
                        yymore();
                        BEGIN(Q1);
                    }

<Q3>"i"{espacio}    {
                        yymore();
                        BEGIN(Q4);
                    }

<Q3>[^ ri]          {
                        yymore();
                        printf("Error, la cadena %s no ha sido reconocida por el autómata.\n",yytext);
                        BEGIN(INITIAL);
                    }

<Q4>"r"{espacio}    {
                        yymore();
                        BEGIN(Q1);
                    }

<Q4>"p"{espacio}    {
                        yymore();
                        BEGIN(Q5);
                    }

<Q4>[^ rp]          {
                        yymore();
                        printf("Error, la cadena %s no ha sido reconocida por el autómata.\n",yytext);
                        BEGIN(INITIAL);
                    }

<Q5>"r"{espacio}    {
                        yymore();
                        BEGIN(Q1);
                    }

<Q5>"f"             {
                        yymore();
                        printf("El autómata ha reconocido la cadena: %s\n",yytext);
                        BEGIN(INITIAL);
                    }

<Q5>[^ rp]          {
                        yymore();
                        printf("Error, la cadena %s no ha sido reconocida por el autómata.\n",yytext);
                        BEGIN(INITIAL);
                    }

             
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
   return 0;
}