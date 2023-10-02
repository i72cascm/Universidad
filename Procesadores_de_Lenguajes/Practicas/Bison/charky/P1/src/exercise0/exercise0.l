/* DECLARATIONS AREA */


    /* It can contains:
       - C code (delimited by {% %} )
       - Lex directives
       - Regular definitions  
    */


/* END OF DECLARATIONS AREA */


/* RULES AREA */
%%
.|\n        ECHO;
^#$         {printf("\nGoodbye!!\n"); return 0;}
%%
 /* END OF RULES AREA */


/* AUXILIARY FUNCTIONS AREA */

/* END OF AUXILIARY FUNCTIONS AREA */