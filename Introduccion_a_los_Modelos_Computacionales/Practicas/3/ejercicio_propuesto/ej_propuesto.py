import pandas as pd
import numpy as np

from sklearn import neighbors
from sklearn import preprocessing
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.linear_model import LogisticRegression

def main():

    df = pd.read_csv('german.csv', delimiter='\s+', header=None)

    #print (df)

    dataset = df.to_numpy(dtype=np.float32)
    inputs = dataset[:,0:-1]
    outputs = dataset[:,inputs.shape[1]:]

    #print(inputs)
    #print('---------------------------------')
    #print(outputs)

    min_max_scaler = preprocessing.MinMaxScaler()
    inputs = min_max_scaler.fit_transform(inputs)
    
    #print (inputs)
    train_inputs = 0
    test_inputs = 0
    train_outputs = 0
    test_outputs = 0
    train_inputs, test_inputs, train_outputs, test_outputs = train_test_split(inputs, outputs, train_size=0.6, stratify= outputs, random_state=42)

    #print(len(train_inputs))
    #print('----------------------')
    #print(len(train_outputs))
    #print('----------------------')
    #print(len(test_inputs))
    #print('----------------------')
    #print(len(test_outputs))

    knn = KNeighborsClassifier(n_neighbors=8).fit(train_inputs, train_outputs.ravel())
    rl = LogisticRegression(random_state=42).fit(train_inputs, train_outputs.ravel())

    print(f"KNeighbors CCR value: {knn.score(test_inputs, test_outputs)*100}%")
    print(f"Logistic Regresion CCR value: {rl.score(test_inputs, test_outputs)*100}%")
if __name__ == "__main__":
    main()
