/*********************************************************************
* File  : MultilayerPerceptron.cpp
* Date  : 2020
*********************************************************************/

#include "MultilayerPerceptron.h"

#include "util.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>  // To establish the seed srand() and generate pseudorandom numbers rand()
#include <limits>
#include <math.h>


using namespace imc;
using namespace std;
using namespace util;

// ------------------------------
// Obtain an integer random number in the range [Low,High] (done)
int randomInt(int Low, int High)
{
	int out = 0;
	out = Low + (rand() * (int)(High - Low) / RAND_MAX);
	return out;
}

// ------------------------------
// Obtain a real random number in the range [Low,High]
double randomDouble(double Low, double High)
{
	double f = (double)rand() / RAND_MAX;
	return Low + f * (High - Low);
}

// ------------------------------
// Constructor: Default values for all the parameters
MultilayerPerceptron::MultilayerPerceptron()
{
	eta = 0.7;
	mu = 1;
	validationRatio = 0.0;
	decrementFactor = 1;
	online = false;
	outputFunction = 0;
	nOfLayers = 1;
	layers = NULL;
}

// ------------------------------
// Allocate memory for the data structures
// nl is the number of layers and npl is a vetor containing the number of neurons in every layer
// Give values to Layer* layers
int MultilayerPerceptron::initialize(int nl, int npl[]) {

	layers = new Layer[nl]; //vector de nl de capacidad del tipo struct Layer 
	nOfLayers = nl; //nº de capas

	//comprobacion
	if(layers == NULL){
		cout << "Error en la creación del vector de estructuras de las capas." << endl;
		return -1;
	}

	//nº de neuronas de cada capa e inicializar el vector neuronas con dicho numero de neuronas (memoria reservada)
	for(int i = 0; i<nl; i++){
		layers[i].nOfNeurons = npl[i]; //nº de neuronas de esa capa (normalmente, todas las capas ocultas tendran el mismo numero y la capa de entrada y de salida seran diferentes, depende del vector topologia)
		layers[i].neurons = new Neuron[npl[i]]; // reserva de memoria del vector con nº de neuronas

		//comprobacion
		if(layers[i].neurons == NULL){
			cout << "Error al reservar memoria en neuronas." << endl;
			return -1;
		}

		for(int j = 0; j<layers[i].nOfNeurons; j++){ //recorrer neuronas de la capa i 
			if (i>0){

				//Para el caso de la funcion softmax ponemos a NULL los valores de las neuronas de la ultima capa
				if ((outputFunction == 1) && (i == nOfLayers-1) && (j == layers[i].nOfNeurons-1)){
					layers[i].neurons[j].w = NULL;
					layers[i].neurons[j].wCopy = NULL;
					layers[i].neurons[j].deltaW = NULL;
					layers[i].neurons[j].lastDeltaW = NULL;
				
				}else{

					//reserva memoria con el nº de neuronas de la capa anterior +1 (sesgo)
					layers[i].neurons[j].w = new double[layers[i-1].nOfNeurons +1];
					layers[i].neurons[j].wCopy = new double[layers[i-1].nOfNeurons +1];
					layers[i].neurons[j].deltaW = new double[layers[i-1].nOfNeurons +1];
					layers[i].neurons[j].lastDeltaW = new double[layers[i-1].nOfNeurons +1];
				}
			}
		}
	}
	return 0;
}


// ------------------------------
// DESTRUCTOR: free memory
MultilayerPerceptron::~MultilayerPerceptron() {
	cout<<endl;
	cout<<"Liberando memoria."<<endl;
	cout<<"--------------------------------------------"<<endl;
	freeMemory();
	cout<<"Memoria liberada con exito."<<endl;
}


// ------------------------------
// Free memory for the data structures
void MultilayerPerceptron::freeMemory() {
	delete[] layers; //free todas las capas 
	
}

// ------------------------------
// Fill all the weights (w) with random numbers between -1 and +1
void MultilayerPerceptron::randomWeights() {

	for(int i = 1;i<nOfLayers;i++){ //recorre capas
		for(int j = 0;j<layers[i].nOfNeurons;j++){ //recorrer neuronas de la capa
			for(int k = 0; k<layers[i-1].nOfNeurons+1;k++){ //neuronas de la capa anterior + sesgo
				if(layers[i].neurons[j].w != NULL){
					layers[i].neurons[j].w[k] = randomDouble(-1,1); //rellenar w con funcion randomDouble
					//cout<<layers[i].neurons[j].w[k]<<endl;
				}
			}
		}
	}

}

// ------------------------------
// Feed the input neurons of the network with a vector passed as an argument
void MultilayerPerceptron::feedInputs(double* input) {

	//recorremos la primera capa (capa de entrada) y la rellenamos con el vector de input pasado como argumento
	for(int i=0; i<layers[0].nOfNeurons; i++){
		layers[0].neurons[i].out = input[i];
	}

}

// ------------------------------
// Get the outputs predicted by the network (out vector of the output layer) and save them in the vector passed as an argument
void MultilayerPerceptron::getOutputs(double* output){

	for(int i=0; i<layers[nOfLayers-1].nOfNeurons;i++){ //neuronas de la ultima capa (output layer)
		output[i] = layers[nOfLayers-1].neurons[i].out; //obtenemos sus salidas al vector
	}
}

// ------------------------------
// Make a copy of all the weights (copy w in wCopy)
void MultilayerPerceptron::copyWeights() {

	for (int i = 1; i<nOfLayers; i++){
		for (int j = 0; j<layers[i].nOfNeurons; j++){
			for(int k = 0; k<layers[i-1].nOfNeurons+1;k++){
				if(layers[i].neurons[j].w != NULL){
					layers[i].neurons[j].wCopy[k] = layers[i].neurons[j].w[k];
				}
			}
		}
	}

}

// ------------------------------
// Restore a copy of all the weights (copy wCopy in w)
void MultilayerPerceptron::restoreWeights() {
	for (int i = 1; i<nOfLayers; i++){
		for (int j = 0; j<layers[i].nOfNeurons; j++){
			for(int k = 0; k<layers[i-1].nOfNeurons+1;k++){
				if(layers[i].neurons[j].w != NULL){
					layers[i].neurons[j].w[k] = layers[i].neurons[j].wCopy[k];
				}
			}
		}
	}

}

// ------------------------------
// Calculate and propagate the outputs of the neurons, from the first layer until the last one -->-->
void MultilayerPerceptron::forwardPropagate() {

	

	if (outputFunction == 1){ //tipo softmax

		double net = 0.0;

		for(int i = 1; i<nOfLayers; i++){ //recorremos las capas
			double denominador = 0.0; //Sumatoria del denominador de la función softmax
			double sumatorio = 0.0; //Auxiliar para obtener la sumatoria del denominador

			if(i == nOfLayers-1){ //En el caso de que estemos en la última capa
				for(int j=0; j<layers[i].nOfNeurons; j++){ //Recorremos las neuronas de la ultima capa
					if(layers[nOfLayers-1].neurons[j].w!=NULL){ 
						sumatorio = 0.0;
						sumatorio = layers[nOfLayers-1].neurons[j].w[0];
						for(int k = 1; k<layers[nOfLayers-2].nOfNeurons+1; k++){
							sumatorio = sumatorio + layers[nOfLayers-1].neurons[j].w[k] * layers[nOfLayers-2].neurons[k-1].out;
						}
						denominador = denominador + exp(sumatorio);
					}
				}
			}

			for(int j = 0; j<layers[i].nOfNeurons;j++){
				if(layers[i].neurons[j].w!=NULL){
					net = 0.0;
					
					for(int k=1; k<layers[i-1].nOfNeurons+1; k++){ //recorremos capa anterior + sesgo
						net += layers[i].neurons[j].w[k]*layers[i-1].neurons[k-1].out; //sumatorio pesos*salida
					}

					net += layers[i].neurons[j].w[0]; //sesgo
				}else{
					net = 0.0;
				}
				
				if((i==nOfLayers-1) ){ //Solo si estamos en la ultima capa
					layers[i].neurons[j].out = exp(net)/(1+(denominador));			
				} else { //Resto de neuronas
					layers[i].neurons[j].out = 1.0/(1+exp(-(net)));
				}

			}
		}

	}else{ //tipo sigmoide

		double net = 0.0;

		for(int i=1; i<nOfLayers; i++){ //recorremos las capas
			for(int j=0;j<layers[i].nOfNeurons; j++){ //recorremos las neuronas en las capas
				if(layers[i].neurons[j].w!=NULL){
					net = 0.0;
					for(int k=1; k<layers[i-1].nOfNeurons+1; k++){ //recorremos capa anterior + sesgo
						net += layers[i].neurons[j].w[k]*layers[i-1].neurons[k-1].out; //sumatorio pesos*salida
					}
					net += layers[i].neurons[j].w[0]; //sesgo
				}else{
					net = 0.0;
				}
				layers[i].neurons[j].out = 1.0/(1 + exp(-net)); //actualización del out (fun. sigmoide(net))
			}
		}
	}
}

// ------------------------------
// Obtain the output error (MSE) of the out vector of the output layer wrt a target vector and return it
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
double MultilayerPerceptron::obtainError(double* target, int errorFunction) {

	int size = 0;
	size = layers[nOfLayers-1].nOfNeurons; //neuronas capa salida
	double *predict = new double[size];
	getOutputs(predict); //vector outpus predecidos 

	if(errorFunction == 0){
		
		double mse = 0.0;
		for (int i = 0; i < size; ++i){
			mse += pow((predict[i]-target[i]), 2); //MSE
		}
		
		mse = mse/size;
		return mse;

	}else{

		double Centropy = 0.0;
		for (int i = 0; i < size; ++i){
			Centropy += (target[i]*log(predict[i])); //Entropia cruzada
		}

		Centropy = Centropy/size;
		return Centropy;

	}
	delete[] predict; //free predict
}


// ------------------------------
// Backpropagate the output error wrt a vector passed as an argument, from the last layer to the first one <--<--
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::backpropagateError(double* target, int errorFunction) {

	double sum = 0.0;

	if(outputFunction){ //Aplicando la función Softmax
		
		int aux = 0;
		for(int i=0; i<layers[nOfLayers-1].nOfNeurons;i++){
			
			sum = 0.0;
			for(int j=0; j<layers[nOfLayers-1].nOfNeurons;j++){
				
				if(j!=i){
					
					aux = 0;
				}else{
					
					aux = 1;
				}
				if(errorFunction){ //Cross Entropy

					sum += ((target[j] / layers[nOfLayers-1].neurons[j].out) * layers[nOfLayers-1].neurons[i].out * (aux - layers[nOfLayers-1].neurons[j].out));

				}else{ //MSE

					sum += ((target[j] - layers[nOfLayers-1].neurons[j].out) * layers[nOfLayers-1].neurons[i].out * (aux - layers[nOfLayers-1].neurons[j].out));

				}
			}
			
			layers[nOfLayers-1].neurons[i].delta = -sum;

		}

	}else{ //Caso en el aplicamos función sigmoide
		
		if(errorFunction){ //Cross Entropy

			for(int i=0 ; i<layers[nOfLayers-1].nOfNeurons; i++){ //Derivada de la entropia cruzada
	
				layers[nOfLayers-1].neurons[i].delta = (-1)*(target[i] / layers[nOfLayers-1].neurons[i].out)*(layers[nOfLayers-1].neurons[i].out*(1 - layers[nOfLayers-1].neurons[i].out)); 
			
			}

		}else{ //MSE

			for(int i=0;i<layers[nOfLayers-1].nOfNeurons;i++){ //Expresión de la derivada: calculo de delta para la capa de salida

				layers[nOfLayers-1].neurons[i].delta = (-2)*(target[i]-layers[nOfLayers-1].neurons[i].out)*(layers[nOfLayers-1].neurons[i].out*(1-layers[nOfLayers-1].neurons[i].out));
				
			}

		}

	}

	//recorremos las capas desde el	final al principio, actualizamos los deltas a partir del delta de la capa final

	for(int i=nOfLayers-2; i>=1; i--){
		for(int j=0; j<layers[i].nOfNeurons+1;j++){
			sum = 0.0;
			for(int k=0; k<layers[i+1].nOfNeurons; k++){
				if(layers[i+1].neurons[k].w != NULL){ 
					sum += layers[i+1].neurons[k].w[j+1]*layers[i+1].neurons[k].delta;
				}
			}
			layers[i].neurons[j].delta = sum*layers[i].neurons[j].out*(1-layers[i].neurons[j].out);
		}
	}

}

// ------------------------------
// Accumulate the changes produced by one pattern and save them in deltaW
void MultilayerPerceptron::accumulateChange() {

	for(int i = 1;i<nOfLayers;i++){ //recorremos las capas
		for(int j = 0;j<layers[i].nOfNeurons;j++){ //recorremos las neuronas de la capa actual
			if(layers[i].neurons[j].deltaW != NULL){
				for(int k = 1;k<layers[i-1].nOfNeurons+1;k++){ //recorremos las neureonas de la capa anterior + sesgo
					layers[i].neurons[j].deltaW[k] += layers[i].neurons[j].delta * layers[i-1].neurons[k-1].out; //sumatorio delta*out -> deltaW
				}
				layers[i].neurons[j].deltaW[0] += layers[i].neurons[j].delta; //sesgo
			}
		}
	}
}

// ------------------------------
// Update the network weights, from the first layer to the last one
void MultilayerPerceptron::weightAdjustment() {

	if(online == true){ //en el caso de que estemos en el modo on-line

		double auxEta = 0.0;

		for (int i=1; i<nOfLayers; i++) { //recorrer capas
			auxEta = (pow(decrementFactor,-1*((nOfLayers-1)-i)))*eta; //ajuste de eta mediante el factor de decremento F por cada capa
			for (int j=0; j<layers[i].nOfNeurons; j++) { //recorrer neuronas de capa
				if(layers[i].neurons[j].w != NULL && layers[i].neurons[j].deltaW != NULL){
					for (int k=1; k<layers[i-1].nOfNeurons+1; k++) { //recorrer neuronas de capa anterior + sesgo
						layers[i].neurons[j].w[k] = layers[i].neurons[j].w[k]-auxEta*layers[i].neurons[j].deltaW[k]-mu*(auxEta*layers[i].neurons[j].lastDeltaW[k]); //update de peso (formula moodle)
					}
					layers[i].neurons[j].w[0]=layers[i].neurons[j].w[0]-auxEta*layers[i].neurons[j].deltaW[0]-mu*(auxEta*layers[i].neurons[j].lastDeltaW[0]); //update del sesgo 
				}
			}
		}

	}else{ //en el caso de que estemos en el modo off-line

		double auxEta = 0.0;

		for(int i = 1; i<nOfLayers; i++){
			auxEta = (pow(decrementFactor,-1*((nOfLayers-1)-i)))*eta; //ajuste de eta mediante el factor de decremento F por cada capa
			for(int j=0; j<layers[i].nOfNeurons; j++){
				if(layers[i].neurons[j].w != NULL && layers[i].neurons[j].deltaW != NULL){
					for(int k=1; k<layers[i-1].nOfNeurons+1;k++){
						layers[i].neurons[j].w[k] = layers[i].neurons[j].w[k] - ((auxEta*layers[i].neurons[j].deltaW[k])/nOfTrainingPatterns) - ((mu*(auxEta*layers[i].neurons[j].lastDeltaW[k]))/nOfTrainingPatterns);
					}
					layers[i].neurons[j].w[0] = layers[i].neurons[j].w[0] - ((auxEta*layers[i].neurons[j].deltaW[0])/nOfTrainingPatterns) - ((mu*(auxEta*layers[i].neurons[j].lastDeltaW[0]))/nOfTrainingPatterns);
				}
			}
		}
	}

}

// ------------------------------
// Print the network, i.e. all the weight matrices
void MultilayerPerceptron::printNetwork() {

	for(int i=1;i<nOfLayers;i++){
		cout<<"Layer: "<<i<<endl;
		cout<<"--------------"<<endl;
		for(int j=0; j<layers[i].nOfNeurons; j++){
			if(layers[i].neurons[j].w != NULL){
				for(int k=0; k<=layers[i-1].nOfNeurons+1;k++){
					cout<<layers[i].neurons[j].w[k]<<"###";
				}
				
				cout<<endl;
			}
		}
	}

}

// ------------------------------
// Perform an epoch: forward propagate the inputs, backpropagate the error and adjust the weights
// input is the input vector of the pattern and target is the desired output vector of the pattern
// The step of adjusting the weights must be performed only in the online case
// If the algorithm is offline, the weightAdjustment must be performed in the "train" function
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::performEpoch(double* input, double* target, int errorFunction) {
	//cout <<"flag1"<<endl;
	feedInputs(input);
	//cout <<"flag2"<<endl;
	forwardPropagate();
	//cout <<"flag3"<<endl;
	backpropagateError(target,errorFunction);
	//cout <<"flag4"<<endl;
	accumulateChange();
	//cout <<"flag5"<<endl;

}

// ------------------------------
// Read a dataset from a file name and return it
Dataset* MultilayerPerceptron::readData(const char *fileName) {
	ifstream myFile(fileName);    // Create an input stream

    if (!myFile.is_open()) {
       cout << "ERROR: I cannot open the file " << fileName << endl;
       return NULL;
    }

	Dataset * dataset = new Dataset;
	if(dataset==NULL)
		return NULL;

	string line;
	int i,j;


	if( myFile.good()) {
		getline(myFile,line);   // Read a line
		istringstream iss(line);
		iss >> dataset->nOfInputs;
		iss >> dataset->nOfOutputs;
		iss >> dataset->nOfPatterns;
	}
	dataset->inputs = new double*[dataset->nOfPatterns];
	dataset->outputs = new double*[dataset->nOfPatterns];

	for(i=0; i<dataset->nOfPatterns; i++){
		dataset->inputs[i] = new double[dataset->nOfInputs];
		dataset->outputs[i] = new double[dataset->nOfOutputs];
	}

	i=0;
	while ( myFile.good()) {
		getline(myFile,line);   // Read a line
		if (! line.empty()) {
			istringstream iss(line);
			for(j=0; j< dataset->nOfInputs; j++){
				double value;
				iss >> value;
				if(!iss)
					return NULL;
				dataset->inputs[i][j] = value;
			}
			for(j=0; j< dataset->nOfOutputs; j++){
				double value;
				iss >> value;
				if(!iss)
					return NULL;
				dataset->outputs[i][j] = value;
			}
			i++;
		}
	}

	myFile.close();

	return dataset;
}


// ------------------------------
// Train the network for a dataset (one iteration of the external loop)
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::train(Dataset* trainDataset, int errorFunction) {

	

	if(online == true){
		
		//Para cada pattern llamamos a la funcion performEpoch para realizar los pasos de propagacion hacia adelante, propagar el error hacia atras, ...
		//en cada una de las iteraciones seteamos deltaw a 0 y ajustamos los pesos
		for(int pattern = 0; pattern<trainDataset->nOfPatterns; pattern++){
			
			//deltaw -> 0
			for(int i=1; i<nOfLayers; i++){
				for(int j=0; j<layers[i].nOfNeurons; j++){
					for(int k=0; k<layers[i-1].nOfNeurons+1; k++){
						if(layers[i].neurons[j].deltaW != NULL){
							layers[i].neurons[j].deltaW[k] = 0.0;
						}
					}
				}
			}
			
			//funcion de perform epoca
			performEpoch(trainDataset->inputs[pattern],trainDataset->outputs[pattern],errorFunction);
			
			//ajuste de peso
			weightAdjustment();
		}
		
	
	
	}else{
		
		//realiza lo mismo que la primera parte del if, pero con la diferencia de que seteamos los deltaw a 0 y ajustamos los pesos fuera del bucle (modo offline)

		for(int i=1; i<nOfLayers; i++){
			for(int j=0; j<layers[i].nOfNeurons; j++){
				for(int k=0; k<layers[i-1].nOfNeurons+1; k++){
					if(layers[i].neurons[j].deltaW != NULL){
						layers[i].neurons[j].deltaW[k] = 0.0;
					}
				}
			}
		}
		
		for(int i = 0; i<trainDataset->nOfPatterns; i++){
			performEpoch(trainDataset->inputs[i],trainDataset->outputs[i],errorFunction);
		}
		
		weightAdjustment();
	}

}

// ------------------------------
// Test the network with a dataset and return the error
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
double MultilayerPerceptron::test(Dataset* dataset, int errorFunction) {

	double error = 0.0;
	for(int i=0; i<dataset->nOfPatterns; i++){
		feedInputs(dataset->inputs[i]);
		forwardPropagate();
		error += obtainError(dataset->outputs[i], errorFunction);
	}

	if(errorFunction == 0){
		error = error / dataset->nOfPatterns;
	}else{
		error = -1 * (error / dataset->nOfPatterns);
	}

	return error;

}


// ------------------------------
// Test the network with a dataset and return the CCR
double MultilayerPerceptron::testClassification(Dataset* dataset) {

	double ccr = 0.0, auxsum = 0.0;

	int indiceSalida = 0;
	int indiceOut = 0;

	for(int i = 0; i<dataset->nOfPatterns; i++){
		
		indiceSalida = 0;
		indiceOut = 0;
		
		//propagacion de las entradas
		feedInputs(dataset->inputs[i]);
		forwardPropagate();

		//obtenemos las salidas
		double* out = new double[dataset->nOfOutputs];
		getOutputs(out);

		// Queremos saber la posicion de los patrones
		for(int j=1 ; j<dataset->nOfOutputs ; j++){
			// Busco el la posicion del valor mayor de la salida generada por la neurona
			if(out[indiceSalida] < out[j]){
				indiceSalida = j;
			}
			// Comprobamos la salida del dataset
			if(dataset->outputs[i][indiceOut] < dataset->outputs[i][j]){
				// Tomamos la posicion del mayor
				indiceOut = j;
			}
		}	

		// Cuando ambos indices coinciden, aumentamos 
		if(indiceSalida == indiceOut){
			auxsum++;
		}
	}

	// Calculo del CCR a partir de los patrones bien clasificados
	ccr = (100 * auxsum / (double)dataset->nOfPatterns);

	return ccr;

	

}


// ------------------------------
// Optional Kaggle: Obtain the predicted outputs for a dataset
void MultilayerPerceptron::predict(Dataset* dataset)
{
	int i;
	int j;
	int numSalidas = layers[nOfLayers-1].nOfNeurons;
	double * salidas = new double[numSalidas];
	
	cout << "Id,Category" << endl;
	
	for (i=0; i<dataset->nOfPatterns; i++){

		feedInputs(dataset->inputs[i]);
		forwardPropagate();
		getOutputs(salidas);

		int maxIndex = 0;
		for (j = 0; j < numSalidas; j++)
			if (salidas[j] >= salidas[maxIndex])
				maxIndex = j;
		
		cout << i << "," << maxIndex << endl;

	}
}



// ------------------------------
// Run the traning algorithm for a given number of epochs, using trainDataset
// Once finished, check the performance of the network in testDataset
// Both training and test MSEs should be obtained and stored in errorTrain and errorTest
// Both training and test CCRs should be obtained and stored in ccrTrain and ccrTest
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::runBackPropagation(Dataset * trainDataset, Dataset * testDataset, int maxiter, double *errorTrain, double *errorTest, double *ccrTrain, double *ccrTest, int errorFunction)
{
	int countTrain = 0;
	
	// Random assignment of weights (starting point)
	randomWeights();

	double minTrainError = 0;
	int iterWithoutImproving = 0;
	nOfTrainingPatterns = trainDataset->nOfPatterns;

	Dataset * validationDataset = NULL;
	double validationError = 0, previousValidationError = 0;
	int iterWithoutImprovingValidation = 0;

	//nuevos datasets para realizar la partición
	Dataset * newTrainDataset = new Dataset;
	Dataset * newTestDataset = new Dataset;

	
	// Generate validation data
	if(validationRatio > 0 && validationRatio < 1){

		

		//copiar variables al dataset nuevo
		newTestDataset->nOfInputs = testDataset->nOfInputs;
		newTestDataset->nOfOutputs = testDataset->nOfOutputs;
		newTestDataset->nOfPatterns = testDataset->nOfPatterns * validationRatio;

		//reservar memoria para inputs y outputs del nuevo dataset
		newTestDataset->inputs = new double*[newTestDataset->nOfPatterns];
		newTestDataset->outputs = new double*[newTestDataset->nOfPatterns];
		for(int i =0; i<newTestDataset->nOfPatterns;i++){
			newTestDataset->inputs[i] = new double[newTestDataset->nOfInputs];
			newTestDataset->outputs[i] = new double[newTestDataset->nOfOutputs];
		}

		

		//copiar variables al dataset nuevo
		newTrainDataset->nOfInputs = trainDataset->nOfInputs;
		newTrainDataset->nOfOutputs = trainDataset->nOfOutputs;
		newTrainDataset->nOfPatterns = trainDataset->nOfPatterns - newTestDataset->nOfPatterns;

		//reservar memoria para inputs y outputs del nuevo dataset
		newTrainDataset->inputs = new double*[newTrainDataset->nOfPatterns];
		newTrainDataset->outputs = new double*[newTrainDataset->nOfPatterns];
		for(int i = 0; i<newTrainDataset->nOfPatterns;i++){
			newTrainDataset->inputs[i] = new double[newTrainDataset->nOfInputs];
			newTrainDataset->outputs[i] = new double[newTrainDataset->nOfOutputs];
		}

		

		//funcion del util.h para ayudarnos a partir el dataset
		int *randomV = integerRandomVectorWithoutRepeating(0,trainDataset->nOfPatterns-1, trainDataset->nOfPatterns);



		//rellenar los nuevos datasets (a partir del dataset antiguo de train)
		
		int i; //declaramos aqui la i para que al rellenar el nuevo dataset de entrenamiento se continue por donde quedo al rellenar el nuevo dataset de test
		for(i = 0; i<newTestDataset->nOfPatterns; i++){
			newTestDataset->inputs[i] = trainDataset->inputs[randomV[i]];
			newTestDataset->outputs[i] = trainDataset->outputs[randomV[i]];
			//cout << "input: "<< newTestDataset->inputs[i][0] << endl;
			//cout << "input: "<< newTestDataset->inputs[i][1] << endl;
			//cout << "output: "<< newTestDataset->outputs[i][0] << endl;
			//cout << "output: "<< newTestDataset->outputs[i][1] << endl;
		}

		for(int j = 0;j<newTrainDataset->nOfPatterns;j++){
			newTrainDataset->inputs[j] = trainDataset->inputs[randomV[i]];
			newTrainDataset->outputs[j] = trainDataset->outputs[randomV[i]];
			//cout << "input: "<< newTrainDataset->inputs[j][0] << endl;
			//cout << "input: "<< newTrainDataset->inputs[j][1] << endl;
			//cout << "output: "<< newTrainDataset->outputs[j][0] << endl;
			//cout << "output: "<< newTrainDataset->outputs[j][1] << endl;
			i++;
		}
	}else{
		
		newTrainDataset = trainDataset;
		
	}

	// Learning
	do {
		
		train(newTrainDataset,errorFunction);
		
		double trainError = test(newTrainDataset,errorFunction);
		if(countTrain==0 || trainError < minTrainError){
			minTrainError = trainError;
			copyWeights();
			iterWithoutImproving = 0;
		}
		else if( (trainError-minTrainError) < 0.00001)
			iterWithoutImproving = 0;
		else
			iterWithoutImproving++;

		if(iterWithoutImproving==50){
			cout << "We exit because the training is not improving!!"<< endl;
			restoreWeights();
			countTrain = maxiter;
		}

		countTrain++;

		if(validationDataset!=NULL){
			if(previousValidationError==0)
				previousValidationError = 999999999.9999999999;
			else
				previousValidationError = validationError;
			validationError = test(validationDataset,errorFunction);
			if(validationError < previousValidationError)
				iterWithoutImprovingValidation = 0;
			else if((validationError-previousValidationError) < 0.00001)
				iterWithoutImprovingValidation = 0;
			else
				iterWithoutImprovingValidation++;
			if(iterWithoutImprovingValidation==50){
				cout << "We exit because validation is not improving!!"<< endl;
				restoreWeights();
				countTrain = maxiter;
			}
		}

		cout << "Iteration " << countTrain << "\t Training error: " << trainError << "\t Validation error: " << validationError << endl;
		
	} while ( countTrain<maxiter );
	
	if ( (iterWithoutImprovingValidation!=50) && (iterWithoutImproving!=50))
		restoreWeights();
		
	
	cout << "NETWORK WEIGHTS" << endl;
	cout << "===============" << endl;
	printNetwork();

	cout << "Desired output Vs Obtained output (test)" << endl;
	cout << "=========================================" << endl;
	for(int i=0; i<testDataset->nOfPatterns; i++){
		double* prediction = new double[testDataset->nOfOutputs];

		// Feed the inputs and propagate the values
		feedInputs(testDataset->inputs[i]);
		forwardPropagate();
		getOutputs(prediction);
		for(int j=0; j<testDataset->nOfOutputs; j++)
			cout << testDataset->outputs[i][j] << " -- " << prediction[j] << " ";
		cout << endl;
		delete[] prediction;

	}

	*errorTest=test(testDataset,errorFunction);;
	*errorTrain=minTrainError;
	*ccrTest = testClassification(testDataset);
	*ccrTrain = testClassification(trainDataset);

}

// -------------------------
// Optional Kaggle: Save the model weights in a textfile
bool MultilayerPerceptron::saveWeights(const char * fileName)
{
	// Object for writing the file
	ofstream f(fileName);

	if(!f.is_open())
		return false;

	// Write the number of layers and the number of layers in every layer
	f << nOfLayers;

	for(int i = 0; i < nOfLayers; i++)
	{
		f << " " << layers[i].nOfNeurons;
	}
	f << " " << outputFunction;
	f << endl;

	// Write the weight matrix of every layer
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				if(layers[i].neurons[j].w!=NULL)
				    f << layers[i].neurons[j].w[k] << " ";

	f.close();

	return true;

}


// -----------------------
// Optional Kaggle: Load the model weights from a textfile
bool MultilayerPerceptron::readWeights(const char * fileName)
{
	// Object for reading a file
	ifstream f(fileName);

	if(!f.is_open())
		return false;

	// Number of layers and number of neurons in every layer
	int nl;
	int *npl;

	// Read number of layers
	f >> nl;

	npl = new int[nl];

	// Read number of neurons in every layer
	for(int i = 0; i < nl; i++)
	{
		f >> npl[i];
	}
	f >> outputFunction;

	// Initialize vectors and data structures
	initialize(nl, npl);

	// Read weights
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				if(!(outputFunction==1 && (i==(nOfLayers-1)) && (k==(layers[i].nOfNeurons-1))))
					f >> layers[i].neurons[j].w[k];

	f.close();
	delete[] npl;

	return true;
}