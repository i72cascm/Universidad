import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn import svm
from sklearn import preprocessing
from sklearn.model_selection import train_test_split

# Load the dataset
data = pd.read_csv('dataset3.csv',header=None)
X = data.iloc[:,:-1].values
y = data.iloc[:,-1].values

# Strandardize data and split
scaler = preprocessing.StandardScaler()
train_x = scaler.fit_transform(X,y)
train_x, test_x, train_y, test_y = train_test_split(train_x, y, train_size = 0.75, stratify = y, random_state= 5)


# Train the SVM model
svm_model = svm.SVC(kernel='rbf',C=200 ,gamma=0.2)
svm_model.fit(train_x, train_y)

# CCR
print("CCR:")
print(svm_model.score(test_x, test_y))

# Plot the points
plt.figure(1)
plt.clf()
plt.scatter(X[:, 0], X[:, 1], c=y, zorder=10, cmap=plt.cm.Paired)



# Plot the support vectors class regions, the separating hyperplane and the margins
plt.axis('tight')


# |->Plot support vectors
plt.scatter(svm_model.support_vectors_[:,0], svm_model.support_vectors_[:,1], 
            marker='+', s=100, zorder=10, cmap=plt.cm.Paired)


# |-> Extract the limits
x_min = X[:, 0].min()
x_max = X[:, 0].max()
y_min = X[:, 1].min()
y_max = X[:, 1].max()
# |-> Create a grid with all the points and then obtain the SVM 
#    score for all the points
XX, YY = np.mgrid[x_min:x_max:500j, y_min:y_max:500j]
Z = svm_model.decision_function(np.c_[XX.ravel(), YY.ravel()])
# |-> Plot the results in a countour
Z = Z.reshape(XX.shape)
plt.pcolormesh(XX, YY, Z > 0)
plt.contour(XX, YY, Z, colors=['k', 'k', 'k'], 
            linestyles=['--', '-', '--'], levels=[-1, 0, 1])



plt.xlabel('x1')
plt.ylabel('x2')



plt.show()
