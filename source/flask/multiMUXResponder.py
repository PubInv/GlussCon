#!/usr/bin/python
import time
import serial
ser = serial.Serial('/dev/cu.usbmodem141401',115200,timeout=1)  # open serial port
import time
import math
from time import sleep
from flask import Flask
import sys

app = Flask(__name__)


@app.route("/")
def getpotval():
  ser.write(b'\n')
#  line = ser.readline()   # read a '\n' terminated line
  lines = ser.readlines()
  print >> sys.stderr, str(lines)
  result = ""
  result.join(lines)
  result = ''.join([str(x) for x in lines])
  print >> sys.stderr, result
  return result

if __name__ == "__main__":
  app.run(host='0.0.0.0', port=80, debug=True)
