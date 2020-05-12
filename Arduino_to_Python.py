#PYthon temperature sensor
#Author : Vuyani Daweti
#This code is designed to read Temperature values from the Serial monitor,these valuse are generated by an Arduino
#These values are then used to create a .csv file that contains all the temperature data for the day
#For this code to run accurately,The Arduino needs to be connected and the serial prot needs to on the right Port.
#In this code i used COM9 ( line )


import re
import serial
from tkinter import messagebox
from decimal import *
import csv
from datetime import datetime
import time


time1 = time.strftime("%Y%m%d-%H%M%S")  #take current time and make it a string
timeValue = list(time1)                 #Break the time to a list to make it YYY-MM-DD format
#print(timeValue)
#timeAdd = ''.join( timeValue[2:4])+ "-"+ ''.join(timeValue[4:6]) +'-'+ ''.join(timeValue[6:8]) # take the date only 
timeAdd = ''.join( timeValue[9:11])+ "H"+ ''.join(timeValue[11:13]) +'M'+ ''.join(timeValue[13:15])
#print(timeAdd)
port = "COM9"
ser = serial.Serial(port,9600) #the serial port 
value = 0
value1 = []
value2 = []
value3 = []
time2 = timeAdd +".csv" # Creating a .csv string to be used as a file name
file1 = open(time2,"w") # Create a file name with current time
c = csv.writer(file1)  #Set the file to be a csv(comma,separate,value) data type
c.writerow(["sep=,"])
c.writerow(["Tank Temperature(Celsius)","Element Input Temperature(Celsius)","Element Output Temperature(Celsius)"])

while 1 :
    value = ser.readline(40); #Reading the data from Arduino Serial monitor
    #print (value)
    #print(value)
    values = list(value) #Value is a byte it cannot be splitted unless we change it to its ASCII character numbers
    #print(len(values))
    
    value1.append([chr(values[0]),chr(values[1]),chr(values[2]),chr(values[3]),chr(values[4])]) # Using ASCII number to get the strings
    value2.append([chr(values[6]),chr(values[7]),chr(values[8]),chr(values[9]),chr(values[10])]) #Using ASCII number to get the string
    value3.append([chr(values[12]),chr(values[13]),chr(values[14]),chr(values[15]),chr(values[16])]) #Using ASCII number to get the string
    #print(value1)
    valueA= ''.join(value1[0])
    valueB = ''.join(value2[0])
    valueC = ''.join(value3[0])
    #print(valueA)
    valueA1 = Decimal(valueA) #Changing the strings to decimal values
    valueB1 = Decimal(valueB) #Changing the strings to decimal values
    valueC1 = Decimal(valueC) #Changing the strings to decimal values
    c.writerow([ valueA1,valueB1,valueC1]) # Writting the data to the created file
    #print(valueA1,',',valueB1,',',valueC1,sep='')
    if len(values) == 20:
        file1.close()
        print("Done")
        time.sleep(0.5)
        print("Create new")
        time1 = time.strftime("%Y%m%d-%H%M%S")  #take current time and make it a string
        timeValue = list(time1)                 #Break the time to a list to make it YYY-MM-DD format
        #print(timeValue)
        #timeAdd = ''.join( timeValue[2:4])+ "-"+ ''.join(timeValue[4:6]) +'-'+ ''.join(timeValue[6:8]) # take the date only 
        timeAdd = ''.join( timeValue[9:11])+ "H"+ ''.join(timeValue[11:13]) +'M'+ ''.join(timeValue[13:15])
        #print(timeAdd) 
        value = 0
        value1 = []
        value2 = []
        value3 = []
        time2 = timeAdd +".csv" # Creating a .csv string to be used as a file name
        file1 = open(time2,"w") # Create a file name with current time
        c = csv.writer(file1)  #Set the file to be a csv(comma,separate,value) data type
        c.writerow(["sep=,"])
        c.writerow(["Tank Temperature(Celsius)","Element Input Temperature(Celsius)","Element Output Temperature(Celsius)"])
    if len(values) == 21:
        print("ITs Here")
    else:
        value1 = []
        value2 = []
        value3 = []        
        continue