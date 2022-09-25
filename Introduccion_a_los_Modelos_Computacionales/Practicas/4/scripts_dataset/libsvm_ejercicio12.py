import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn import svm
from sklearn import preprocessing
from sklearn.model_selection import train_test_split
from sklearn import model_selection
import time

# Load the dataset
data = pd.read_csv('train_nomnist.csv',header=None)
train_x = data.iloc[:,:-1].values
train_y = data.iloc[:,-1].values
data = pd.read_csv('test_nomnist.csv',header=None)
test_x = data.iloc[:,:-1].values
test_y = data.iloc[:,-1].values

# inicio de programa
inicio = time.time()

# Strandardize data and split
scaler = preprocessing.StandardScaler()
train_x = scaler.fit_transform(train_x)
test_x = scaler.fit_transform(test_x)


# Train the SVM model
svm_model = svm.SVC(kernel='rbf')

# Grid-Search
Cs = np.logspace(-5, 15, num=11, base=2)
Gs = np.logspace(-15, 3, num=9, base=2)
sol = model_selection.GridSearchCV(estimator=svm_model, param_grid=dict(C=Cs,gamma=Gs), n_jobs=-1,cv=10)
sol.fit(train_x, train_y)

# fin de programa
fin = time.time()

# CCR
print("CCR:")
print(sol.score(test_x, test_y))
print("Tiempo empleado:")
print(fin-inicio)
