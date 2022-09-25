import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn import svm
from sklearn import preprocessing
from sklearn.model_selection import train_test_split
from sklearn import model_selection
from sklearn.model_selection import StratifiedKFold

# Load the dataset
data = pd.read_csv('dataset3.csv',header=None)
X = data.iloc[:,:-1].values
y = data.iloc[:,-1].values

# K-fold split
skf = StratifiedKFold(n_splits=5)

# Cs, Gs and result inicialization
Cs = np.logspace(-5, 15, num=11, base=2)
Gs = np.logspace(-15, 3, num=9, base=2)

# Loop k-fold splits in search of the best 
results=np.zeros((len(Cs)*len(Gs),7))
i = 0
for train_index, test_index in skf.split(X, y):
    train_x = X[train_index]
    test_x = X[test_index]
   
    train_y = y[train_index]
    test_y = y[test_index]
    j = 0
    
    for c in Cs:
        for g in Gs:
            train = svm.SVC(kernel='rbf', C=c, gamma=g).fit(train_x, train_y)
            results[j,i]=train.score(test_x, test_y)
            j = j+1
    i= i+1

# Escogemos la mejor combinación de C y gamma
maxJ=0
maxmedia=np.mean(results[0,2:7])
for x in range(1, (len(Cs)*len(Gs))):
    media = np.mean(results[x,2:7])
    if media > maxmedia:
        maxmedia = media
        maxJ = x

# Ejecución y obtención del CCR
sol = svm.SVC(kernel='rbf', C=results[maxJ,0], gamma=results[maxJ,1])
train_x, test_x, train_y, test_y = train_test_split(X, y, stratify=y, test_size=0.25)
sol.fit(train_x, train_y)
print("CCR:")
print(sol.score(test_x, test_y))

