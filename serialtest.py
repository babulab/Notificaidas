#!/usr/bin/python

# Importamos la libreira de PySerial
import serial
import re
import numpy as np
import matplotlib.pyplot as plt
largo = 2000
x,y,z=np.zeros(largo),np.zeros(largo),np.zeros(largo)
# Abrimos el puerto del arduino a 9600
PuertoSerie = serial.Serial('COM4', 115200)
# Creamos un buble sin fin
j=0
while True:
  while (PuertoSerie.inWaiting()==0):
    pass
  # leemos hasta que encontarmos el final de linea
  sArduino = PuertoSerie.readline()
  leng = len(sArduino)
  sread = sArduino[0:leng-2]
  sread = str(sread)
  sread1 = sread[2:]
  sread2=sread1.split('\\t')
  # Mostramos el valor leido y eliminamos el salto de linea del final
  
  dR,dL,th = sread2
  lth = len(th)
  th = th[0:lth-1]

  dR = float(dR) # Convertimos los valores a número
  dL = float(dL) 
  th = int(th)

  #print (sread)
  #print (dR)
  #print (dL)
  #print (th)
  
  if j<largo:
      x[j]=dR
      y[j]=(dL)
      z[j]=(th)
      j=j+1
      print(j)
  else:
      print('asd')
      PuertoSerie.close()
      break