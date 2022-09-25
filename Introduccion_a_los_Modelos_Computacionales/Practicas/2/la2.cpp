//============================================================================
// Introducción a los Modelos Computacionales
// Name        : practica1.cpp
// Author      : Pedro A. Gutiérrez
// Version     :
// Copyright   : Universidad de Córdoba
//============================================================================


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <ctime>    // To obtain current time time()
#include <cstdlib>  // To establish the seed srand() and generate pseudorandom numbers rand()
#include <string.h>
#include <math.h>
#include <float.h> // For DBL_MAX

#include "MultilayerPerceptron.h"


using namespace imc;
using namespace std;


int main(int argc, char **argv) {
	// Process the command line
    bool Tflag = 0, tflag = 0, wflag = 0, pflag = 0, iflag = 0, lflag = 0, hflag = 0, eflag = 0, mflag = 0, vflag = 0, dflag = 0, oflag = 0, fflag = 0, sflag = 0;
    char *Tvalue = NULL, *tvalue = NULL, *wvalue = NULL;
    int c;
    int ivalue = 1000, lvalue = 1, hvalue = 4, fvalue = 0;
    double evalue = 0.7, mvalue = 1, vvalue = 0.0, dvalue = 1.0;
    bool ovalue = 0, svalue = 0;

    opterr = 0;

    // a: Option that requires an argument
    // a:: The argument required is optional
    while ((c = getopt(argc, argv, "T:t:i:l:h:e:m:v:w:d:f:sop")) != -1)
    {

        // The parameters needed for using the optional prediction mode of Kaggle have been included.
        // You should add the rest of parameters needed for the lab assignment.
        switch(c){

            //fichero de test
            case 'T':
                Tflag = true;
                Tvalue = optarg;
                break;

            //fichero de entrenamiento
            case 't':
                tflag = true;
                tvalue = optarg;
                break;

            //nº de iteraciones de bucle externo (default = 1000)
            case 'i':
                iflag = true;
                ivalue = atoi(optarg);
                break;

            //nº de capas ocultas (default = 1)
            case 'l':
                lflag = true;
                lvalue = atoi(optarg);
                break;
            
            //nº de neuronas en capas ocultas
            case 'h':
                hflag = true;
                hvalue = atoi(optarg);
                break;
            
            //valor del parámetro eta (default = 0.7)
            case 'e':
                eflag = true;
                evalue = atof(optarg);
                break;

            //valor del parámetro mu (defalt = 1)
            case 'm':
                mflag = true;
                mvalue = atof(optarg);
                break;

            //ratio de patrones de entrenamiento a utilizar como patrones de validación (default = 0.0)
            case 'v':
                vflag = true;
                vvalue = atof(optarg);
                break;
            
            //valor del factor de decremento (default = 1)
            case 'd':
                dflag = true;
                dvalue = atof(optarg);
                break;
            
            //opcion que determina si se utilizará la version on-line (default -> off-line)
            case 'o':
                oflag = true;
                ovalue = 1;
                break;

            //indica la función de error utilizada durante el aprendizaje 0: MSE 1: entropía cruzada (default -> MSE)
            case 'f':
                fflag = true;
                fvalue = atoi(optarg);
                break;

            //indica si utilizaremos la función softmax en capa de salida (default: utilizar función sigmoide)
            case 's':
                sflag = true;
                svalue = 1;
                break;

            case 'w':
                wflag = true;
                wvalue = optarg;
                break;
            case 'p':
                pflag = true;
                break;
            case '?':
                if (optopt == 'T' || optopt == 'w' || optopt == 'p' || optopt == 't' || optopt == 'i' || optopt == 'l' || optopt == 'h' || optopt == 'e' || optopt == 'm' || optopt == 'v' || optopt == 'd' || optopt == 'o' || optopt == 'f' || optopt == 's')
                    fprintf (stderr, "La opción -%c requiere un argumento.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Opción desconocida `-%c'.\n", optopt);
                else
                    fprintf (stderr,
                             "Caracter de opción desconocido `\\x%x'.\n",
                             optopt);
                return EXIT_FAILURE;
            default:
                return EXIT_FAILURE;
        }
    }


    if (!pflag) {
        //////////////////////////////////
        // TRAINING AND EVALUATION MODE //
        //////////////////////////////////

        // Multilayer perceptron object
    	MultilayerPerceptron mlp;

        // Parameters of the mlp. For example, mlp.eta = value (done)

        mlp.eta = evalue;
        mlp.mu = mvalue;
        mlp.validationRatio = vvalue;
        mlp.decrementFactor = dvalue;
        mlp.online = ovalue;
        mlp.outputFunction = svalue; //0: sigmoide 1: softmax

    	// Type of error considered
    	int error = 0; // This should be completed (done)
        
        if (fflag == true && fvalue == 1){
            error = 1;
        }

    	// Maximum number of iterations
    	int maxIter = ivalue; // This should be completed (done)

        // Read training and test data: call to mlp.readData(...)
    	Dataset * trainDataset = mlp.readData(tvalue); // This should be corrected
    	Dataset * testDataset = mlp.readData(Tvalue); // This should be corrected
        //cout << "Train: Nº patrones -> "<<trainDataset->nOfPatterns<< " Nº entradas -> "<<trainDataset->nOfInputs<< " Nº salidas -> "<<trainDataset->nOfOutputs<< endl;
        //cout << "Test: Nº patrones -> "<<testDataset->nOfPatterns<< " Nº entradas -> "<<testDataset->nOfInputs<< " Nº salidas -> "<<testDataset->nOfOutputs<< endl;
        
        // Initialize topology vector
        int layers =lvalue;
        int *topology = new int[layers+2];

        //crearemos un vector topologia con el numero de neuronas que tendrá cada capa

        topology[0] = trainDataset->nOfInputs;
        for(int i=1; i<(layers+2-1); i++){
            topology[i] = hvalue;
        }
        topology[layers+2-1] = trainDataset->nOfOutputs;

        mlp.initialize(layers+2,topology);

		// Seed for random numbers
		int seeds[] = {1,2,3,4,5};
		double *trainErrors = new double[5];
		double *testErrors = new double[5];
		double *trainCCRs = new double[5];
		double *testCCRs = new double[5];
		double bestTestError = DBL_MAX;
		for(int i=0; i<5; i++){
			cout << "**********" << endl;
			cout << "SEED " << seeds[i] << endl;
			cout << "**********" << endl;
			srand(seeds[i]);
			mlp.runBackPropagation(trainDataset,testDataset,maxIter,&(trainErrors[i]),&(testErrors[i]),&(trainCCRs[i]),&(testCCRs[i]),error);
			cout << "We end!! => Final test CCR: " << testCCRs[i] << endl;

			// We save the weights every time we find a better model
			if(wflag && testErrors[i] <= bestTestError)
			{
				mlp.saveWeights(wvalue);
				bestTestError = testErrors[i];
			}
		}


		double trainAverageError = 0, trainStdError = 0;
		double testAverageError = 0, testStdError = 0;
		double trainAverageCCR = 0, trainStdCCR = 0;
		double testAverageCCR = 0, testStdCCR = 0;

        // Obtain training and test averages and standard deviations

        //Calculo de la media de los errores
        for(int i = 0; i<5; i++){

            trainAverageError += trainErrors[i];
            testAverageError += testErrors[i];
            trainAverageCCR += trainCCRs[i];
            testAverageCCR += testCCRs[i];

        }

        trainAverageError = trainAverageError / 5;
        testAverageError = testAverageError / 5;
        trainAverageCCR = trainAverageCCR / 5;
        testAverageCCR = testAverageCCR / 5;

        //Desviación típica

        for(int i=0; i<5; i++){

            trainStdError += (trainErrors[i] - trainAverageError)*(trainErrors[i] - trainAverageError);
            testStdError += (testErrors[i] - testAverageError)*(testErrors[i] - testAverageError);
            trainStdCCR += (trainCCRs[i] - trainAverageCCR)*(trainCCRs[i] - trainAverageCCR);
            testStdCCR += (testCCRs[i] - testAverageCCR)*(testCCRs[i] - testAverageCCR);

        }

        trainStdError = sqrt(trainStdError/5);
        testStdError = sqrt(testStdError/5);
        trainStdCCR = sqrt(trainStdCCR/5);
        testStdCCR = sqrt(testStdCCR/5);

		cout << "WE HAVE FINISHED WITH ALL THE SEEDS" << endl;

		cout << "FINAL REPORT" << endl;
		cout << "*************" << endl;
	    cout << "Train error (Mean +- SD): " << trainAverageError << " +- " << trainStdError << endl;
	    cout << "Test error (Mean +- SD): " << testAverageError << " +- " << testStdError << endl;
	    cout << "Train CCR (Mean +- SD): " << trainAverageCCR << " +- " << trainStdCCR << endl;
	    cout << "Test CCR (Mean +- SD): " << testAverageCCR << " +- " << testStdCCR << endl;
		return EXIT_SUCCESS;
    } else {

        //////////////////////////////
        // PREDICTION MODE (KAGGLE) //
        //////////////////////////////

        // You do not have to modify anything from here.
        
        // Multilayer perceptron object
        MultilayerPerceptron mlp;

        // Initializing the network with the topology vector
        if(!wflag || !mlp.readWeights(wvalue))
        {
            cerr << "Error while reading weights, we can not continue" << endl;
            exit(-1);
        }

        // Reading training and test data: call to mlp.readData(...)
        Dataset *testDataset;
        testDataset = mlp.readData(Tvalue);
        if(testDataset == NULL)
        {
            cerr << "The test file is not valid, we can not continue" << endl;
            exit(-1);
        }

        mlp.predict(testDataset);

        return EXIT_SUCCESS;

	}
}

