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
// Constructor: Default values for all the parameters
MultilayerPerceptron::MultilayerPerceptron()
{
	nOfLayers = 1;
	layers = NULL;
	eta = 0.1;
	mu = 0.9;
	validationRatio = 0.2;
	decrementFactor = 1;
}

// ------------------------------
// Allocate memory for the data structures
// nl is the number of layers and npl is a vetor containing the number of neurons in every layer
// Give values to Layer* layers
int MultilayerPerceptron::initialize(int nl, int npl[]) {

	layers = new Layer[nl]; //vector capas con dicho nº de capas reservadas 
	nOfLayers = nl; //nº capas
	
	//comprobante de creacion
	if(layers == NULL){
		return -1;
	}

	

	//numero de neurones de cada capa e inicializar el vector neuronas con dicho numero de neuronas (memoria reservada)
	for (int i=0; i<nl; i++){
		
		layers[i].nOfNeurons = npl[i]; //nº de neuronas de esa capa
		layers[i].neurons = new Neuron[npl[i]]; //reserva de memoria del vector con nº de neuronas
	
		//comprobante
		if(layers[i].neurons == NULL){
			cout << "error reservando memoria"<< endl;
			return -1;
		}

		for(int j=0; j<layers[i].nOfNeurons; j++){ //recorrer neuronas de una capa
			if(i>0){
				//reserva memoria con el nº de neuronas de la capa anterior +1 (sesgo)
				layers[i].neurons[j].w = new double[layers[i-1].nOfNeurons +1];
				layers[i].neurons[j].wCopy = new double[layers[i-1].nOfNeurons +1];
				layers[i].neurons[j].deltaW = new double[layers[i-1].nOfNeurons +1];
				layers[i].neurons[j].lastDeltaW = new double[layers[i-1].nOfNeurons +1];
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
	delete[] layers[0].neurons; //free capa 0

	int i, j;
	//cout<<"flag 1 "<<endl;
	for (i = 0; i < nOfLayers; i++) {
		for (j = 0; j < layers[i].nOfNeurons; j++) { //free componentes de neurona
			//cout<<"flag 2 "<<endl;
			if(i>0){
				delete[] layers[i].neurons[j].lastDeltaW;
				delete[] layers[i].neurons[j].w;
				delete[] layers[i].neurons[j].deltaW;
				delete[] layers[i].neurons[j].wCopy;
			}
		}
		//cout<<"flag 3"<<endl;
	}
	delete[] layers; //free todas las capas 
	//cout<<"fkag 4"<<endl;
}


// ------------------------------
// Generate a random double from max and min
double randomDouble(double fMin, double fMax){
	double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);	
}

// ------------------------------
// Feel all the weights (w) with random numbers between -1 and +1
void MultilayerPerceptron::randomWeights() {
	int i, j, k;

	for(i=1;i<nOfLayers;i++){ //nº capas
		for(j=0;j<layers[i].nOfNeurons;j++){ //nº neuronas por capa
			for(k=0; k<layers[i-1].nOfNeurons+1;k++){ //neuronas de la capa anterior + sesgo
				layers[i].neurons[j].w[k] = randomDouble(-1,1); //rellenar w con funcion randomDouble
			}
		}
	}
}

// ------------------------------
// Feed the input neurons of the network with a vector passed as an argument
void MultilayerPerceptron::feedInputs(double* input) {
	for(int i=0;i<layers[0].nOfNeurons;i++){ //recorrer primera capa rellenando los out de las neuronas (salidas de las primeras neuronas que son los inputs a la capa oculta)
		layers[0].neurons[i].out = input[i];
	}
}

// ------------------------------
// Get the outputs predicted by the network (out vector the output layer) and save them in the vector passed as an argument
void MultilayerPerceptron::getOutputs(double* output)
{
	for(int i=0; i<layers[nOfLayers-1].nOfNeurons;i++){ //neuronas de la ultima capa (output layer)
		output[i] = layers[nOfLayers-1].neurons[i].out; //obtenemos sus salidas al vector
	}
}

// ------------------------------
// Make a copy of all the weights (copy w in wCopy)
void MultilayerPerceptron::copyWeights() {
	
	for(int i=1;i<nOfLayers;i++){//recorrer capas (la capa de entrada no)
		for(int j=0; j<layers[i].nOfNeurons; j++){ //en cada capa recorremos las neuronas 
			int nOfWeights = layers[i-1].nOfNeurons+1; //neuronas de la ultima capa + sesgo
			for(int k=0; k<nOfWeights;k++){
				layers[i].neurons[j].wCopy[k]=layers[i].neurons[j].w[k]; //copiamos los pesos de todas las neuronas
			}
		}
	}
}

// ------------------------------
// Restore a copy of all the weights (copy wCopy in w)
void MultilayerPerceptron::restoreWeights() {
	for(int i=1; i<nOfLayers; i++){ //recorrer capas (la capa de entrada no)
		for(int j=0; j<layers[i].nOfNeurons; j++){ //en cada capa recorremos las neuronas
			int nOfWeights = layers[i-1].nOfNeurons+1; //neuronas de la ultima capa + sesgo
			for(int k=0; k<nOfWeights; k++){ 
				layers[i].neurons[j].w[k]= layers[i].neurons[j].wCopy[k]; //restauramos de la copia los pesos de todas las neuronas
			}
		}
	}
}

// ------------------------------
// Calculate and propagate the outputs of the neurons, from the first layer until the last one -->-->
void MultilayerPerceptron::forwardPropagate() {

	for(int i=1; i<nOfLayers; i++){ //recorremos las capas
		for(int j=0;j<layers[i].nOfNeurons; j++){ //recorremos las neuronas en las capas
			double net = 0.0;
			for(int k=1; k<layers[i-1].nOfNeurons+1; k++){ //recorremos capa anterior + sesgo
				net += layers[i].neurons[j].w[k]*layers[i-1].neurons[k-1].out; //sumatorio pesos*salida
			}
			net += layers[i].neurons[j].w[0]; //sesgo
			layers[i].neurons[j].out = 1.0/(1 + exp(-net)); //actualización del out (fun. sigmoide(net))
		}
	}
}

// ------------------------------
// Obtain the output error (MSE) of the out vector of the output layer wrt a target vector and return it
double MultilayerPerceptron::obtainError(double* target) {
	
	int size = 0;
	double mse = 0.0;
	

	size = layers[nOfLayers-1].nOfNeurons; //neuronas capa salida
	double *predict = new double[size];
	getOutputs(predict); //vector outpus predecidos 

	for (int i = 0; i < size; ++i)
		mse += pow((predict[i]-target[i]), 2); //MSE

	delete[] predict; //free predict

	mse = mse/size;

	return mse;
}


// ------------------------------
// Backpropagate the output error wrt a vector passed as an argument, from the last layer to the first one <--<--
void MultilayerPerceptron::backpropagateError(double* target) {
	double out, aux;

	
	for(int i =0; i<layers[nOfLayers-1].nOfNeurons;i++){ //empezamos desde la ultima capa
		out = layers[nOfLayers-1].neurons[i].out;
		layers[nOfLayers-1].neurons[i].delta = -(target[i]-out)*out*(1-out); //calculamos delta de última capa
	}

	
	for(int i=nOfLayers-2;i>=1;i--){ //desde la penultima capa
		for(int j=0;j<layers[i].nOfNeurons;j++){ //recorremos neuronas 
			out = layers[i].neurons[j].out; 
			aux =0.0;
			for(int k=0; k<layers[i+1].nOfNeurons;k++){ //recorremos neuronas (capa siguiente)
				aux += layers[i+1].neurons[k].w[j+1]*layers[i+1].neurons[k].delta; //calculo de delta
			}
			layers[i].neurons[j].delta = aux*(1-out)*out; //set delta

		}
	}
}


// ------------------------------
// Accumulate the changes produced by one pattern and save them in deltaW
void MultilayerPerceptron::accumulateChange() {

	for(int i=1; i<nOfLayers; i++){ //recorrer capas
		for(int j=0; j<layers[i].nOfNeurons; j++){ //recorrer neuronas de la capa
			for(int k=1; k<layers[i-1].nOfNeurons+1; k++){ //recorrer neuronas de la capa anterior + sesgo
				layers[i].neurons[j].deltaW[k] += layers[i].neurons[j].delta*layers[i-1].neurons[k-1].out; //sumatorio delta*out -> deltaW
			}
			layers[i].neurons[j].deltaW[0] += layers[i].neurons[j].delta; //sesgo
		}
	}
}

// ------------------------------
// Update the network weights, from the first layer to the last one
void MultilayerPerceptron::weightAdjustment() {

	double auxEta = 0.0;

	for (int i=1; i<nOfLayers; i++) { //recorrer capas
		auxEta = (pow(decrementFactor,-1*((nOfLayers-1)-i)))*eta;
		//cout<<auxEta<<endl;
		for (int j=0; j<layers[i].nOfNeurons; j++) { //recorrer neuronas de capa
			for (int k=1; k<layers[i-1].nOfNeurons+1; k++) { //recorrer neuronas de capa anterior + sesgo
				layers[i].neurons[j].w[k] = layers[i].neurons[j].w[k]-auxEta*layers[i].neurons[j].deltaW[k]-mu*(auxEta*layers[i].neurons[j].lastDeltaW[k]); //update de peso (formula moodle)
			}
			layers[i].neurons[j].w[0]=layers[i].neurons[j].w[0]-auxEta*layers[i].neurons[j].deltaW[0]-mu*(auxEta*layers[i].neurons[j].lastDeltaW[0]); //update del sesgo 
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
			int nOfWeights = layers[i-1].nOfNeurons+1;
			for(int k=0; k<=nOfWeights;k++){
				cout<<layers[i].neurons[j].w[k]<<"###";
			}
			cout<<endl;
		}
	}
}

// ------------------------------
// Perform an epoch: forward propagate the inputs, backpropagate the error and adjust the weights
// input is the input vector of the pattern and target is the desired output vector of the pattern
void MultilayerPerceptron::performEpochOnline(double* input, double* target) {

	//esta funcion setea deltaW a 0 por si tiene valores basura
	for(int i=1; i<nOfLayers; i++){
		for(int j=0; j<layers[i].nOfNeurons; j++){
			int nOfWeights = layers[i-1].nOfNeurons+1;
			for(int k=0; k<nOfWeights; k++){
				layers[i].neurons[j].deltaW[k] = 0.0;
			}
		}
	}

	feedInputs(input);
	forwardPropagate();
	backpropagateError(target);
	accumulateChange();
	weightAdjustment();
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
// Perform an online training for a specific trainDataset
void MultilayerPerceptron::trainOnline(Dataset* trainDataset) {
	int i;
	for(i=0; i<trainDataset->nOfPatterns; i++){
		performEpochOnline(trainDataset->inputs[i], trainDataset->outputs[i]);
	}
}

// ------------------------------
// Test the network with a dataset and return the MSE
double MultilayerPerceptron::test(Dataset* testDataset) {
	double mse = 0.0;

	for(int i=0; i<testDataset->nOfPatterns; i++){
		feedInputs(testDataset->inputs[i]);
		forwardPropagate();
		mse += obtainError(testDataset->outputs[i]);
	}
	mse = mse / testDataset->nOfPatterns;
	//cout<<"Errores mse: "<<mse<<endl;
	return mse;
}


// Optional - KAGGLE
// Test the network with a dataset and return the MSE
// Your have to use the format from Kaggle: two columns (Id y predictied)
void MultilayerPerceptron::predict(Dataset* pDatosTest)
{
	int i;
	int j;
	int numSalidas = layers[nOfLayers-1].nOfNeurons;
	double * obtained = new double[numSalidas];
	
	cout << "Id,Predicted" << endl;
	
	for (i=0; i<pDatosTest->nOfPatterns; i++){

		feedInputs(pDatosTest->inputs[i]);
		forwardPropagate();
		getOutputs(obtained);
		
		cout << i;

		for (j = 0; j < numSalidas; j++)
			cout << "," << obtained[j];
		cout << endl;

	}
}

// ------------------------------
// Run the traning algorithm for a given number of epochs, using trainDataset
// Once finished, check the performance of the network in testDataset
// Both training and test MSEs should be obtained and stored in errorTrain and errorTest
void MultilayerPerceptron::runOnlineBackPropagation(Dataset * trainDataset, Dataset * pDatosTest, int maxiter, double *errorTrain, double *errorTest)
{
	int countTrain = 0;

	// Random assignment of weights (starting point)
	randomWeights();

	double minTrainError = 0; 
	int iterWithoutImproving;
	double testError = 0;
	
	double validationError = 1;
	double lastValidationError = 0;
	
	//variables dataset donde copiaremos trainDataset
	Dataset *newtrainDataset = new Dataset;
	Dataset *newtestDataset = new Dataset;
	
	// Generate validation data

	//-------------------------------------------------------------------------

	if(validationRatio>0 && validationRatio<1){ //copiamos en las nuevas variables los parametros del trainDataset
		newtestDataset->nOfInputs = trainDataset->nOfInputs;
		newtestDataset->nOfOutputs = trainDataset->nOfOutputs;
		newtestDataset->nOfPatterns = trainDataset->nOfPatterns*validationRatio;
		newtestDataset->inputs = new double*[newtestDataset->nOfPatterns];
		newtestDataset->outputs = new double*[newtestDataset->nOfPatterns];

		for (int i = 0; i < newtestDataset->nOfPatterns; i++) {
			newtestDataset->inputs[i] = new double[newtestDataset->nOfInputs];
			newtestDataset->outputs[i] = new double[newtestDataset->nOfOutputs];
		}

		newtrainDataset->nOfInputs = trainDataset->nOfInputs;
		newtrainDataset->nOfOutputs = trainDataset->nOfOutputs;
		newtrainDataset->nOfPatterns = trainDataset->nOfPatterns - newtestDataset->nOfPatterns;
		newtrainDataset->inputs = new double*[newtrainDataset->nOfPatterns];
		newtrainDataset->outputs = new double*[newtrainDataset->nOfPatterns];

		for (int i = 0; i < newtrainDataset->nOfPatterns; i++) {
			newtrainDataset->inputs[i] = new double[newtrainDataset->nOfInputs];
			newtrainDataset->outputs[i] = new double[newtrainDataset->nOfOutputs];
		}

		//----------------------------------------------------------------------

		int *randomVector = integerRandomVectoWithoutRepeating(0,trainDataset->nOfPatterns-1,trainDataset->nOfPatterns); //utilizamos la funcion de util.h para ayudarnos a partir el dataset
		
		//----------------------------------------------------------------------

		int index; //variable que sirve a la vez como señalizador de por donde nos hemos quedado

		//repartimos los patrones con randomVector
		for(index = 0; index < newtestDataset->nOfPatterns; index++) {
			newtestDataset->inputs[index] = trainDataset->inputs[randomVector[index]];
			newtestDataset->outputs[index] = trainDataset->outputs[randomVector[index]];
		}
		for (int j = 0; j < newtrainDataset->nOfPatterns; j++) {
			newtrainDataset->inputs[j] = trainDataset->inputs[randomVector[index]];
			newtrainDataset->outputs[j] = trainDataset->outputs[randomVector[index]];
			index++;

		//----------------------------------------------------------------------
		}
	}else{
		newtrainDataset = trainDataset; //no hacemos nada
	}


	// Learning
	do {

		trainOnline(newtrainDataset);
		double trainError = test(newtrainDataset);
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


		// Check validation stopping condition and force it
		// BE CAREFUL: in this case, we have to save the last validation error, not the minimum one
		// Apart from this, the way the stopping condition is checked is the same than that
		// applied for the training set

		if (validationRatio > 0 && validationRatio < 1) {
			validationError = test(newtestDataset);
			if(countTrain==0 || validationError < lastValidationError){ //guardamos el last validation error
				copyWeights();
				iterWithoutImproving = 0;
			}
			else if( (validationError-lastValidationError) < 0.00001) // si mejora continuamos
				iterWithoutImproving = 0;
			else
				iterWithoutImproving++; //si no mejora +1

			if(iterWithoutImproving==50){ //tras 50 iteraciones sin mejorar salimos y restauramos last validation error
				cout << "We exit because the validation is not improving!!"<< endl;
				restoreWeights();
				countTrain = maxiter;
			}
			lastValidationError = validationError;
		}

		countTrain++;
		cout << "Iteration " << countTrain << "\t Training error: " << trainError << "\t Validation error: " << validationError << endl;

	} while ( countTrain<maxiter );

	cout << "NETWORK WEIGHTS" << endl;
	cout << "===============" << endl;
	printNetwork();

	cout << "Desired output Vs Obtained output (test)" << endl;
	cout << "=========================================" << endl;
	for(int i=0; i<pDatosTest->nOfPatterns; i++){
		double* prediction = new double[pDatosTest->nOfOutputs];

		// Feed the inputs and propagate the values
		feedInputs(pDatosTest->inputs[i]);
		forwardPropagate();
		getOutputs(prediction);
		for(int j=0; j<pDatosTest->nOfOutputs; j++)
			cout << pDatosTest->outputs[i][j] << " -- " << prediction[j] << " ";
		cout << endl;
		delete[] prediction;

	}

	testError = test(pDatosTest);
	*errorTest=testError;
	*errorTrain=minTrainError;

}

// Optional Kaggle: Save the model weights in a textfile
bool MultilayerPerceptron::saveWeights(const char * archivo)
{
	// Object for writing the file
	ofstream f(archivo);

	if(!f.is_open())
		return false;

	// Write the number of layers and the number of layers in every layer
	f << nOfLayers;

	for(int i = 0; i < nOfLayers; i++)
		f << " " << layers[i].nOfNeurons;
	f << endl;

	// Write the weight matrix of every layer
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				f << layers[i].neurons[j].w[k] << " ";

	f.close();

	return true;

}


// Optional Kaggle: Load the model weights from a textfile
bool MultilayerPerceptron::readWeights(const char * archivo)
{
	// Object for reading a file
	ifstream f(archivo);

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
		f >> npl[i];

	// Initialize vectors and data structures
	initialize(nl, npl);

	// Read weights
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				f >> layers[i].neurons[j].w[k];

	f.close();
	delete[] npl;

	return true;
}
