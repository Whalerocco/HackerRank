import numpy as np
import pandas as pd
from sklearn import linear_model as lm

def predict(time):
    df = pd.read_csv("trainingdata.txt", header=None, names=["ChargeTime", "BatteryTime"])
    x = df["ChargeTime"]
    y = df["BatteryTime"]
		# Notice that max value to y is 8.0
    x = np.array(x[y[y < 8.0].index], float)
    y = np.array( y[y < 8.0], float)
    model = lm.LinearRegression()
    model.fit(x.reshape(-1,1), y)
    return model.predict(pd.DataFrame(np.array([time])))

if __name__ == '__main__':
    timeCharged = float(input().strip())
		
    # Laptop's battery is full after 4h
    if timeCharged >= 4:
        print(8)
    else:
        print(round(predict(timeCharged)[0], 2))