# https://www.hackerrank.com/challenges/document-classification/problem

# !/bin/python3
import sys
import math
import os
import random
import re
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import nltk # natural language processing
from sklearn.preprocessing import MinMaxScaler, Normalizer 
from sklearn.feature_extraction.text import TfidfVectorizer # term frequency
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import MultinomialNB
import warnings
from nltk.tokenize import sent_tokenize #word_tokenize or sent_tokenize (best for longer texts)
from nltk.stem import PorterStemmer
from nltk.stem import WordNetLemmatizer
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import classification_report
from sklearn.metrics import confusion_matrix, accuracy_score, precision_score, recall_score, f1_score, roc_auc_score, roc_curve, precision_recall_curve
from sklearn.svm import SVC # Support vector classifier
from imblearn.over_sampling import RandomOverSampler

# Oversample the data to improve classification for classes with less items
def oversample_dataset(X, y):
    ros = RandomOverSampler()
    X_os,y_os = ros.fit_resample(X,y) # Take more of the class with fewer items until they have the same amount

    # Below is what we want to do - have to reshape y first to 2D
#     data = np.hstack((X, y)) # horisontal stack
    data = np.hstack((X_os, np.reshape(y_os, (-1, 1)))) # horisontal stack. (-1, 1) gets evaluated as (len(y), 1)

    return data, X_os, y_os

def trainModel(fileName, nrFeatures):
    with open(fileName, "r") as file1:
        content = file1.readlines()

    del content[0] # Remove numeber of lines from read data   

    stemmer = PorterStemmer() # Reduces the words to their base form

    lemmatizer = WordNetLemmatizer() # Reduces inflection from words - similar to stemming
    y = []
    X = []
    for line in content:
        y.append(int(line[0]))
        processed_line = sent_tokenize(line[2:]) # Tokenize the words. Other preprocesses include stop word removal, POS tagging and chunking
    #     processed_line = [stemmer.stem(i) for i in processed_line] # Takes long time, use if needed
        processed_line = [lemmatizer.lemmatize(i) for i in processed_line] 
        X.append(processed_line[0])

    df = pd.DataFrame(zip(X, y),
            columns =['Text', 'Class'])

    X_train, _, y_train, _ = train_test_split(df["Text"], df["Class"], test_size=0.0)

    # https://realpython.com/python-keras-text-classification/

    # Create features from the data
    tfidf = TfidfVectorizer(lowercase=False, max_features=nrFeatures)  # term frequency
    X_train_tfidf = tfidf.fit_transform(X_train).toarray()

    # Normalize the vectors
    norm_TFIDF = Normalizer(copy=False)
    X_norm_train_tfidf = norm_TFIDF.fit_transform(X_train_tfidf)
    # Over sample the data to improve the training. Before, there were 100 times more data of class 1 than class 5
    y_train = y_train.to_numpy()
    _, X_norm_train_tfidf_os, y_train_os = oversample_dataset(X_norm_train_tfidf,y_train)
    
    svm_model = SVC()
    svm_model.fit(X_norm_train_tfidf_os, y_train_os)
    
    return svm_model, tfidf


if __name__ == '__main__':
    nrFeatures = 150
    warnings.filterwarnings('ignore')

    # Read input from stdio
    input = sys.stdin.readline
    nrClassifications = int(input()) # first line says how many more lines there are
    ml_model, tfidf = trainModel("trainingdata.txt")

    stemmer = PorterStemmer() # Reduces the words to their base form
    lemmatizer = WordNetLemmatizer() # Reduces inflection from words - similar to stemming
    for i in range(nrClassifications):
        line = input()

        # ======== Process input text ======== #
        processed_line = sent_tokenize(line) # Tokenize the words. Other preprocesses include stop word removal, POS tagging and chunking
    #     processed_line = [stemmer.stem(i) for i in processed_line] # Takes long time, use if needed
        processed_line = [lemmatizer.lemmatize(i) for i in processed_line] 
    #         X.append(processed_line[0])
        X = processed_line

        # Create features from the data
        tfidf_in = TfidfVectorizer(lowercase=False, max_features=nrFeatures, stop_words ="english")  # term frequency, can remove stop words here
        X_ft_tfidf = tfidf_in.fit_transform(X).toarray()

        # Normalize the vectors
        norm_TFIDF = Normalizer(copy=False)
        X_ft_norm_tfidf = norm_TFIDF.fit_transform(X_ft_tfidf)

        # Create a vector of zeros with the same number of features as the model's training data
        X_norm_input_tfidf = np.zeros([1, nrFeatures])

        feature_names = tfidf.get_feature_names_out()
        feature_names_input = tfidf_in.get_feature_names_out()
        matched_feature_names = []

        # Check whether each feature in the input is in the trained features list
        for i in range(len(feature_names_input)):
            feat_input = feature_names_input[i]

            for j in range(len(feature_names)):
                feat = feature_names[j]

                if feat_input == feat:
                    X_norm_input_tfidf[0,j] = X_ft_norm_tfidf[0,i]
                    matched_feature_names.append(feat_input) # Can be used to show which features matched the training features
                    continue   # Skip to next 

        print(ml_model.predict(X_norm_input_tfidf)[0]) # "Class is: "
