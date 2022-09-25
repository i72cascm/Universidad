    //Inicio
    cv::Ptr<cv::ml::Tipo> tipo
    tipo = cv::ml::Tipo::create();

    //KNearest
    knn-> setAlgorithmType(cv::ml::KNearest::BRUTE_FORCE); //Siempre igual
    knn-> setIsClassifier(true); //Siempre igual
    knn-> setDefaultK(knn_K); //Siempre igual

    //SVM
    svm->setKernel(cv::ml::SVM::LINEAR); //Siempre igual
    svm->setType(cv::ml::SVM::C_SVC); //Siempre igual
    svm->setC(svm_C);
    svm->setTermCriteria(termCriteria);
    svm->setGamma(svm_G);
    svm->setDegree(svm_D);

    //RTrees
    rtrees->setActiveVarCount(rtrees_V);
    //rtrees->setTermCriteria(TermCriteria);
    rtrees->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER, rtrees_T, rtrees_E));


    //TRAIN DATA SIEMPRE IGUAL
    cv::Ptr<cv::ml::TrainData> train_data = cv::ml::TrainData::create(patterns, cv::ml::SampleTypes::ROW_SAMPLE, labels);
    clf->train(train_data)