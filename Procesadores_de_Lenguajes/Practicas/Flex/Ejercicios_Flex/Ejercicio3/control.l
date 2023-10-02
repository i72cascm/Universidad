/*** control.l ***/

/*** Zona de las declaraciones o definiciones ***/
%{
   /* Descripción
    	El analizador léxico denominado control.l que recibe un
        fichero con el control de presencia de un trabajador y calcula
        - el número total de horas trabajadas
        - el número medio de horas trabajadas por día trabajado.
   */
   #include <stdbool.h>
   #include <stdio.h>
   #include <string.h> 

   bool comprobarDiaExiste(char* text_);
   bool comprobarHora(int horaIn_, int horaOut_, int minIn_, int minOut_);
   bool controlHora(int horaIn,int horaOut, int minIn, int minOut);
%}

%{
    int horaIn = 0;
    int horaOut = 0;
    int minIn = 0;
    int minOut = 0;
    int NRegistros = 0;
    float total = 0;
    float media = 0;
    float sumMins = 0;

%}

/***** Definiciones regulares *****/
digito     [0-9]
espacio    [ \t]
guion      [-]
dia_mes    {digito}{digito}
year       {digito}{4}
fecha      {dia_mes}{guion}{dia_mes}{guion}{year}
hora_minuto {digito}{digito}

/***** Estados del automata *****/
%x Q1 Q2 Q3 Q4


/***** Zona de reglas y funcion de automata *****/
%%


{fecha}{espacio}        {
                            
                            char fechatxt[10];
                            sscanf(yytext, "%s", fechatxt);

                            if (comprobarDiaExiste(fechatxt)){

                                BEGIN(Q1);

                            }else{
                                printf("Esta fecha no es válida: %s\n",yytext);
                                BEGIN(INITIAL);
                            }
                            
                        }

<Q1>{hora_minuto}:          {

                                sscanf(yytext, "%d", &horaIn);
                                BEGIN(Q2);
                            }

<Q2>{hora_minuto}{espacio}    {
                                sscanf(yytext, "%d", &minIn);
                                BEGIN(Q3);
                            }

<Q3>{hora_minuto}:          {
                                sscanf(yytext, "%d", &horaOut);
                                BEGIN(Q4);
                            }

<Q4>{hora_minuto}             {
                                 sscanf(yytext, "%d", &minOut);
                                 if (!comprobarHora(horaIn, horaOut, minIn, minOut)){
                                    
                                    BEGIN(INITIAL);

                                 }else{

                                    if(!controlHora(horaIn, horaOut, minIn, minOut)){
                                       
                                       BEGIN(INITIAL);

                                    }else{
                                       sumMins += ((horaOut*60)+minOut)-((horaIn*60)+minIn);
                                       NRegistros++;
                                       printf("¡Jornada registrada con éxito!\n");
                                       BEGIN(INITIAL);
                                    }
                                 } 
                              }
 


.|\n ;

%%

/*** Zona de funciones auxiliares ***/

bool controlHora(int horaIn,int horaOut, int minIn, int minOut){
    if(horaIn==horaOut){
        if(minIn<=minOut){
            return true;
        }else{
            printf("Error: Incompatibilidad de horas.\n");
            return false;
        }
    }else if(horaIn<horaOut){
        return true;
    }else{
        printf("Error: Incompatibilidad de horas.\n");
        return false;
    }
}

bool comprobarHora(int horaIn_, int horaOut_, int minIn_, int minOut_) {
    
    if (horaOut_ < 0 || horaOut_ >= 24 || minOut_ < 0 || minOut_ >= 60) {
        printf("Error: La hora es invalida: %d:%d\n", horaOut, minOut);
        return false;
    }
    
    if (horaIn_ < 0 || horaIn_ >= 24 || minIn_ < 0 || minIn_ >= 60) {
        printf("Error: La hora es invalida: %d:%d\n", horaIn, minIn);
        return false;
    }
   
    return true;
}

bool comprobarDiaExiste(char* text_){
    
    int dia_, mes_, year_;
    sscanf(text_, "%d", &dia_);
    /*printf("dia: %d\n",dia_);*/

    char mestxt[] = {text_[3], text_[4]};
    sscanf(mestxt, "%d", &mes_);
    /*printf("mes: %d\n",mes_);*/

    char yeartxt[] = {text_[6], text_[7], text_[8], text_[9]};
    sscanf(yeartxt, "%d", &year_);
    /*printf("year: %d\n",year_);*/

    if (mes_ >= 13 || mes_ == 0){
        return false;
    }else{
        switch(mes_){

            case 1 :
                if (dia_ == 0 || dia_ >= 32){
                    return false;
                }
                break;

            case 2 :
                if(year_%4 == 0){
                    if (dia_ == 0 || dia_ >= 30){
                        return false;
                    }
                    printf("Esta año es bisiesto: %d\n",year_);
                }else{
                    if (dia_ == 0 || dia_ >= 29){
                        return false;
                    }
                }
                break;

            case 3 :
                if (dia_ == 0 || dia_ >= 32){
                    return false;
                }
                break;

            case 4 :
                if (dia_ == 0 || dia_ >= 31){
                    return false;
                }
                break;

            case 5 :
                if (dia_ == 0 || dia_ >= 32){
                    return false;
                }
                break;

            case 6 :
                if (dia_ == 0 || dia_ >= 31){
                    return false;
                }
                break;

            case 7 :
                if (dia_ == 0 || dia_ >= 32){
                    return false;
                }
                break;

            case 8 :
                if (dia_ == 0 || dia_ >= 32){
                    return false;
                }
                break;

            case 9 :
                if (dia_ == 0 || dia_ >= 31){
                    return false;
                }
                break;

            case 10 :
                if (dia_ == 0 || dia_ >= 32){
                    return false;
                }
                break;

            case 11 :
                if (dia_ == 0 || dia_ >= 31){
                    return false;
                }
                break;

            case 12 :
                if (dia_ == 0 || dia_ >= 32){
                    return false;
                }
                break;

        }
    }
    

    return true;
}


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

    total = sumMins/60;
    media = total/NRegistros;
    printf("Total de horas: %f\n", total);
    printf("Media de horas al día entre todos los registros: %f\n", media);

    return 0;
}