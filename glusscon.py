import Adafruit_ADS1x15
import RPi.GPIO as GPIO
import time
import math
from time import sleep
from flask import Flask

app = Flask(__name__)
GPIO.setmode(GPIO.BCM)
GPIO.setup(25,GPIO.OUT)
GPIO.setup(24,GPIO.OUT)
GPIO.setup(23,GPIO.OUT)
GPIO.setup(22,GPIO.OUT)
adc = Adafruit_ADS1x15.ADS1115()

def actNameFromNumber(n):
  m = n % 6
  l = n / 6
  return ''.join([chr(ord('A')+l),chr(ord('0')+m)])


def setmuxsel(num):
  if num == 0:
    GPIO.output(25,GPIO.LOW)
    GPIO.output(24,GPIO.LOW)
    GPIO.output(23,GPIO.LOW)
    GPIO.output(22,GPIO.LOW)
  elif num == 1:
    GPIO.output(25,GPIO.LOW)
    GPIO.output(24,GPIO.LOW)
    GPIO.output(23,GPIO.LOW)
    GPIO.output(22,GPIO.HIGH)
  elif num == 2:
    GPIO.output(25,GPIO.LOW)
    GPIO.output(24,GPIO.LOW)
    GPIO.output(23,GPIO.HIGH)
    GPIO.output(22,GPIO.LOW)
  elif num == 3:
    GPIO.output(25,GPIO.LOW)
    GPIO.output(24,GPIO.LOW)
    GPIO.output(23,GPIO.HIGH)
    GPIO.output(22,GPIO.HIGH)
  elif num == 4:
    GPIO.output(25,GPIO.LOW)
    GPIO.output(24,GPIO.HIGH)
    GPIO.output(23,GPIO.LOW)
    GPIO.output(22,GPIO.LOW)
  elif num == 5:
    GPIO.output(25,GPIO.LOW)
    GPIO.output(24,GPIO.HIGH)
    GPIO.output(23,GPIO.LOW)
    GPIO.output(22,GPIO.HIGH)
  elif num == 6:
    GPIO.output(25,GPIO.LOW)
    GPIO.output(24,GPIO.HIGH)
    GPIO.output(23,GPIO.HIGH)
    GPIO.output(22,GPIO.LOW)
  elif num == 7:
    GPIO.output(25,GPIO.LOW)
    GPIO.output(24,GPIO.HIGH)
    GPIO.output(23,GPIO.HIGH)
    GPIO.output(22,GPIO.HIGH)  
  elif num == 8:
    GPIO.output(25,GPIO.HIGH)
    GPIO.output(24,GPIO.LOW)
    GPIO.output(23,GPIO.LOW)
    GPIO.output(22,GPIO.LOW)

@app.route("/")
# '''
# def getpotval():
#   result = "{"
#   setmuxsel(8)
#   result = result + "\"A8: " #%d\": " % (i)
#   result = result + str(int(math.floor(adc.read_adc(0,gain=2/3)/17)))
#   return result
# '''

@app.route("/")
def getpotval():
  result = "{"
  for i in range(0,9):
    #print result
    setmuxsel(i)
    # Because the current glusscon is physcially wired wrong,
    # I attempt to correct it in software here by swapping #1 and #2.
    if (i == 1):
        result = result + "\""+actNameFromNumber(2) +"\": "
    elif (i == 2):
        result = result + "\""+actNameFromNumber(1) +"\": "
    else:
        result = result + "\""+actNameFromNumber(i) +"\": "      
    result = result + str(int(math.floor(adc.read_adc(0,gain=2/3)/17))) 
    if i == 8:
      result = result + "\n"
    else:
      result = result + ",\n"
  return result + "}"

if __name__ == "__main__":
  app.run(host='0.0.0.0', port=80, debug=True)

  
