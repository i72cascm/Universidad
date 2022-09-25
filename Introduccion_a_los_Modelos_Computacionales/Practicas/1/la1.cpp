//============================================================================
// Introduction to computational models
// Name        : la1.cpp
// Author      : Pedro A. Gutiérrez // Manuel Casas Castro (i72cascm)
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

#include "MultilayerPerceptron.h"


using namespace imc;
using namespace std;

int main(int argc, char **argv) {
    // Process arguments of the command line
    bool Tflag = 0, wflag = 0, pflag = 0, tflag = 0, iflag = 0, lflag = 0, hflag = 0, eflag = 0, mflag = 0, vflag = 0, dflag = 0;
    char *Tvalue = NULL, *wvalue = NULL, *tvalue = NULL;
    int c, ivalue = 0, lvalue = 0, hvalue = 0, dvalue = 0;
    double evalue = 0.0, mvalue = 0.0, vvalue = 0.0;


    opterr = 0;

    // a: Option that requires an argument
    // a:: The argument required is optional
    while ((c = getopt(argc, argv, "t:T:i:l:h:e:m:v:d:w:p")) != -1)
    {
        // The parameters needed for using the optional prediction mode of Kaggle have been included.
        // You should add the rest of parameters needed for the lab assignment.
        switch(c){
            
            //fichero entrenamiento
            case 't':
                tflag = true;
                tvalue = optarg;
                break;

            //fichero test
            case 'T':
                Tflag = true;
                Tvalue = optarg;
                break;

            //numero iteraciones del bucle externo (default=1000)
            case 'i':
                iflag = true;
                ivalue = atoi(optarg);
                break;

            //numero de capas ocultas (default=1)
            case 'l':
                lflag = true;
                lvalue = atoi(optarg);
                break;

            //numero de neuronas en cada capa oculta (default = 5)
            case 'h':
                hflag = true;
                hvalue = atoi(optarg);
                break;

            //valor de parametro eta (default = 0.1)
            case 'e':
                eflag = true;
                evalue = atof(optarg);
                break;

            //valor de parametro mu (default = 0.9)
            case 'm':
                mflag = true;
                mvalue = atof(optarg);
                break;

            //ratio de patrones de entrenamiento a utilizar como patrones de validacion (default = 0.0)
            case 'v':
                vflag = true;
                vvalue = atof(optarg);
                break;

            //valor del factor decremento a utilizar por cada una de las capas (default = 1)
            case 'd':
                dflag = true;
                dvalue = atoi(optarg);
                break;


            case 'w':
                wflag = true;
                wvalue = optarg;
                break;
            case 'p':
                pflag = true;
                break;
            case '?':
                if (optopt == 't' || optopt == 'T' || optopt == 'i' || optopt == 'l' || optopt == 'h' || optopt == 'e' || optopt == 'm' || optopt == 'v' || optopt == 'd' || optopt == 'w' || optopt == 'p')
                    fprintf (stderr, "The option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr,
                             "Unknown character `\\x%x'.\n",
                             optopt);
                return EXIT_FAILURE;
            default:
                return EXIT_FAILURE;
        }
    }

    if (tflag == false || Tflag == false){
        cout << "Ficheros train/test no han sido introducidos correctamente" << endl;
        return EXIT_FAILURE;
    }    

    if (!pflag) {
        //////////////////////////////////
        // TRAINING AND EVALUATION MODE //
        //////////////////////////////////

            


        // Multilayer perceptron object
    	MultilayerPerceptron mlp;

        // Parameters of the mlp. For example, mlp.eta = value;

        if(iflag == false){
            ivalue = 1000;
        }
        int iterations = ivalue;

        //////////////////////////////////////////////////////
        //////////////////////////////////////////////////////

        if(eflag == false){
            evalue = 0.1;
        }

        if(mflag == false){
            mvalue = 0.9;
        }

        if(vflag == false){
            vvalue = 0.0;
        }

        if(dflag == false){
            dvalue = 1;
        }

        mlp.eta = evalue;
        mlp.mu = mvalue;
        mlp.validationRatio = vvalue;
        mlp.decrementFactor = dvalue;

        // Read training and test data: call to mlp.readData(...) 
    	Dataset * trainDataset = mlp.readData(tvalue);
    	Dataset * testDataset = mlp.readData(Tvalue); 
        cout << "Datasets leidos train "<<trainDataset->nOfPatterns<< endl;
        cout << "Datasets leidos test "<<testDataset->nOfPatterns<< endl;


        // Initialize topology vector
        if(!lflag){
            lvalue = 1;
        }
    	int layers = lvalue;
    	int * topology = new int[lvalue+2];

        if(!hflag){
            hvalue = 5;
        }
        topology[0] = trainDataset->nOfInputs;
        for(int i=1; i<lvalue+1; i++){
            topology[i] = hvalue;
        }
        topology[lvalue+1] = trainDataset->nOfOutputs;
        //for (int i = 0;i<lvalue+2;i++){
        //    cout<<"Topologia nº: "<< i << " valor " << topology[i] <<endl;
        //}

        // Initialize the network using the topology vector
        mlp.initialize(layers+2,topology);

        

        // Seed for random numbers
        int seeds[] = {1,2,3,4,5};
        double *testErrors = new double[5];
        double *trainErrors = new double[5];
        double bestTestError = 1;
        for(int i=0; i<5; i++){
            cout << "**********" << endl;
            cout << "SEED " << seeds[i] << endl;
            cout << "**********" << endl;
            srand(seeds[i]);
            mlp.runOnlineBackPropagation(trainDataset,testDataset,iterations,&(trainErrors[i]),&(testErrors[i]));
            cout << "We end!! => Final test error: " << testErrors[i] << endl;

            // We save the weights every time we find a better model
            if(wflag && testErrors[i] <= bestTestError)
            {
                mlp.saveWeights(wvalue);
                bestTestError = testErrors[i];
            }
        }

        cout << "WE HAVE FINISHED WITH ALL THE SEEDS" << endl;

        double averageTestError = 0, stdTestError = 0;
        double averageTrainError = 0, stdTrainError = 0;
        
        // Obtain training and test averages and standard deviations

        for(int i=0; i<5; i++){
            averageTestError += testErrors[i];
            averageTrainError += trainErrors[i];
        }
        averageTestError = averageTestError/5;
        averageTrainError = averageTrainError/5;
        for(int i=0; i<5; i++){
            stdTestError += pow(testErrors[i] - averageTestError, 2);
            stdTrainError += pow(trainErrors[i] - averageTrainError, 2);
        }
        stdTestError = sqrt(stdTestError / 5);
        stdTrainError = sqrt(stdTrainError / 5);

        cout << "FINAL REPORT" << endl;
        cout << "************" << endl;
        cout << "Train error (Mean +- SD): " << averageTrainError << " +- " << stdTrainError << endl;
        cout << "Test error (Mean +- SD):          " << averageTestError << " +- " << stdTestError << endl;
        return EXIT_SUCCESS;
    }
    else {

        //////////////////////////////
        // PREDICTION MODE (KAGGLE) //
        //////////////////////////////
        
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