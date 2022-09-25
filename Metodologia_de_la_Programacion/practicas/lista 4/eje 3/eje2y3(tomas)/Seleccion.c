#include <stdio.h>
int main(){
	int menor;
	int auxiliar;
	int vector[]={0,5,1,4,2,6,9,0};
	printf("Metodo de ordenacion por seleccion.\n");
	
	for(int i = 0 ; i < 8; i++){ //atento a los bucles
		menor=i;
		for(int j=i+1; j<8; j++){ // mira como empieza este
			if(vector[j]<vector[menor]){
				menor=j;
			}
			
		}
		auxiliar=vector[menor];
			vector[menor]=vector[i];
			vector[i]=auxiliar;
	}

	printf("los elementos del vector ordenados son:\n");
	for(int i =0; i<8;i++){
		printf("v[%d]=%d\n",i,vector[i] );
	}

	return 0;
}