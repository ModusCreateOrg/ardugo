#!/usr/bin/env python3

import serial
import time

#
#  File: test.py
#  Purpose: Entry point to the AdruGo test suite.
#  Author: Don Anderson
#

ser = serial.Serial(
  '/dev/cu.usbmodem1411',
  9600,
  timeout=5,
  rtscts=1
  )

#
# Send a single command
#
def send(cmd):
  rsp_list=[]
  ser.write(bytes(cmd, 'utf-8'))
  rsp = ser.readline().rstrip().decode();

  if(rsp != 'OK' and rsp != 'ERROR'):
    rsp_list.append(rsp)

  while(ser.inWaiting()):
    rsp = ser.readline().rstrip().decode();
    if(rsp != 'OK' and rsp != 'ERROR'):
      rsp_list.append(rsp)

  return rsp_list

#
# Send a list of commands
#
def send_list(list):
  rsp_list=[]
  for cmd in list:
    rsp_list.append(send(cmd))
  return rsp_list


print("-- Running Tests --")

print(send('clear-board'))
print(send('print-board'))
print(send('dump-board'))

rsp = send_list([
  'clear-board',
  'print-board',
  'dump-board',
  ])

print(rsp)













