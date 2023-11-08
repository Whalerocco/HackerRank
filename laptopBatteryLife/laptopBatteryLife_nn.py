# https://www.hackerrank.com/challenges/battery/problem

# !/bin/python3

import math
import os
import random
import re
import sys
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import tensorflow as tf
import copy

def get_xy(dataframe, y_label, x_labels=None):
    dataframe = copy.deepcopy(dataframe)
    if x_labels is None:
        X = dataframe[[c for c in dataframe.columns if c!=y_label]].values # Take all the columns' values
    else: # Labels are passed into the function
        if len(x_labels) == 1:
            X = dataframe[x_labels[0]].values.reshape(-1, 1) # Reshape to make it 2D, since only one column
        else:
            X = dataframe[x_labels].values
    y = dataframe[y_label].values.reshape(-1, 1) # reshape to be able to stack with the X matrix
    data = np.hstack((X,y))

    return data, X, y

def plot_loss(history):

    plt.plot(history.history['loss'], label='loss')
    plt.plot(history.history['val_loss'], label='val_loss')
    plt.xlabel('Epoch') # An epoch is a training cycle
    plt.ylabel('MSE')
    plt.legend()
    plt.grid(True)
    plt.show()

def plot_scatter(X_train, y_train):
    plt.scatter(X_train, y_train, label='Data', color='blue')
    x = tf.linspace(0, 12, 100)
    plt.plot(x, nn_model.predict(np.array(x).reshape(-1,1)), label='Fit', color='red', linewidth=3) # Change model to NN model, otherwise keep the same
    plt.legend()
    plt.title("Predicted ChargeTime")
    plt.ylabel("ChargeTime")
    plt.xlabel("BatteryTime")
    plt.show()

if __name__ == '__main__':
    timeCharged = float(input().strip())

    df = pd.read_csv("trainingdata.txt", sep=",")

    labels = ["ChargeTime", "BatteryTime"]
    df.columns = labels

    # plt.scatter(df["ChargeTime"], df["BatteryTime"])
    # plt.title("Battery Time")
    # plt.ylabel("BatteryTime")
    # plt.xlabel("ChargeTime")
    # plt.show()

    train, valid, test = np.split(df.sample(frac=1), [int(0.7*len(df)), int(0.85*len(df))])

    _, X_train, y_train = get_xy(train, "BatteryTime", x_labels = ["ChargeTime"]) # train just using the temperature
    _, X_valid, y_valid = get_xy(valid, "BatteryTime", x_labels = ["ChargeTime"]) # train just using the temperature
    _, X_test, y_test = get_xy(test, "BatteryTime", x_labels = ["ChargeTime"]) # train just using the temperature

    normalizer = tf.keras.layers.Normalization(input_shape=(1,), axis=None)
    normalizer.adapt(X_train.reshape(-1,1))

    nn_model = tf.keras.Sequential([ # Use a real neural network
        normalizer, # Normalizes the data 
        tf.keras.layers.Dense(32, activation='relu'),
        tf.keras.layers.Dense(32, activation='relu'),
        tf.keras.layers.Dense(1, activation='relu') # Output layer ->
    ])
    nn_model.compile(optimizer=tf.keras.optimizers.Adam(learning_rate=0.001), loss='mean_squared_error')

    history = nn_model.fit(
        X_train, y_train,
        validation_data=(X_valid, y_valid),
        verbose=0, epochs=300
    )

    # plot_scatter(X_train, y_train)
    # plot_loss(history)

    x_input = pd.DataFrame(np.array([timeCharged]))
    y_pred = nn_model.predict(x_input)
    print(y_pred)

























