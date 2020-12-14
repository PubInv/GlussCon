#!/usr/bin/python
import time
import serial
ser = serial.Serial('/dev/cu.usbmodem142401',115200,timeout=0.1)  # open serial port
import time
import math
from time import sleep
from flask import Flask
import sys
from flask_cors import CORS

app = Flask(__name__)

CORS(app)

@app.route("/")
def getpotval():
  ser.write(b'\n')
  start_time = time.time()
#  line = ser.readline()   # read a '\n' terminated line
  lines = ser.readlines()
  elapsed_time = time.time() - start_time
  print >> sys.stderr, str(elapsed_time)

#  print >> sys.stderr, str(lines)
  result = ""
  result.join(lines)
  result = ''.join([str(x) for x in lines])
#  print >> sys.stderr, result
  return result

if __name__ == "__main__":
  app.run(host='127.0.0.1', port=80, debug=True)
