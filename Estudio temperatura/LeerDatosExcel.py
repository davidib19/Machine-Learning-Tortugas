import pandas as pd
import datetime
import os
import matplotlib.pyplot as plt
import matplotlib.dates as mdates


def toDatetime(string_datetime):
    if isinstance(string_datetime, str):
        lista = string_datetime.split(" ")
        if len(lista[0].split('/')[2]) == 4:
            string_datetime = datetime.datetime.strptime(string_datetime, '%m/%d/%Y %I:%M:%S %p')
        else:
            string_datetime = datetime.datetime.strptime(string_datetime, '%m/%d/%y %I:%M:%S %p')
    else:
        string_datetime = string_datetime.replace(month=string_datetime.day, day=string_datetime.month)
    return string_datetime


def ReadData(path):
    df = pd.read_excel(path, converters={'Date Time, GMT-03:00':toDatetime})
    return df


def grafica_temp(df):
    x = mdates.date2num(df['Date Time, GMT-03:00'])
    fig, ax = plt.subplots()
    fig.autofmt_xdate()
    ax.plot_date(x, df.iloc[:, 3], '-')
    plt.show()


DATA_PATH = os.path.join(os.getcwd(), "Datos")
for document in os.listdir(DATA_PATH):
    grafica_temp(ReadData(os.path.join(DATA_PATH, document)))
