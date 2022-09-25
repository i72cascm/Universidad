import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn import model_selection
import pandas as pd
from sklearn import svm
from sklearn import preprocessing
from sklearn.metrics import confusion_matrix


# Load the dataset
data = pd.read_csv('train_spam.csv',header=None)
train_x = data.iloc[:,:-1].values
train_y = data.iloc[:,-1].values
data = pd.read_csv('test_spam.csv',header=None)
test_x = data.iloc[:,:-1].values
test_y = data.iloc[:,-1].values



#Training model
svm_model = svm.SVC(kernel = 'rbf', C=0.1)


#fit 
svm_model.fit(train_x, train_y)

# CCR
print("CCR:")
print(svm_model.score(test_x, test_y))