#ifndef COLAS
#define COLAS
struct punto
{
  float x;
  float y;  	
};

struct cola
{
 struct punto p;
 struct cola *sig;
};


struct punto leerElemento();
void escribirElemento(struct punto p);
struct cola *nuevoElemento();
void insertarCola(struct cola **cabeza, struct punto p);
struct punto extraerCola(struct cola **cabeza);
int contiene(struct cola *cabeza);
int contarNodos(struct cola** cabeza);

#endif
