#ifndef ESTADISTICAVECTOR_H
#define ESTADISTICAVECTOR_H

void reservaVector(int **vector,int n);
void leeVector(int *vec, int n);
void imprimeVector(int *vec,int n);
void doMedia(int *vec, int n, float *media);
void doVarianza(int *vec,int n,float media,float *varianza);
void doDt(float varianza,float *dt);
void imprimeResultados(float media, float varianza, float dt);

#endif