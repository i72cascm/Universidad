import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn import svm
from sklearn import preprocessing
from sklearn.model_selection import train_test_split
from sklearn import model_selection

# Load the dataset
data = pd.read_csv('dataset3.csv',header=None)
X = data.iloc[:,:-1].values
y = data.iloc[:,-1].values

# Strandardize data and split
scaler = preprocessing.StandardScaler()
train_x = scaler.fit_transform(X,y)
train_x, test_x, train_y, test_y = train_test_split(train_x, y, train_size = 0.75, stratify = y, random_state= 1)

# Train the SVM model
svm_model = svm.SVC(kernel='rbf')


# Grid-Search
Cs = np.logspace(-5, 15, num=11, base=2)
Gs = np.logspace(-15, 3, num=9, base=2)
sol = model_selection.GridSearchCV(estimator=svm_model, param_grid=dict(C=Cs,gamma=Gs), n_jobs=-1,cv=5)
sol.fit(train_x, train_y)

# CCR
print("CCR:")
print(sol.score(test_x, test_y))
