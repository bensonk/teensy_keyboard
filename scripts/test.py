#!/usr/bin/env python
import serial, time
kb = serial.Serial("/dev/tty.RN42-9ADF-SPP", 115200)
time.sleep(5)
kb.write("This is pretty cool stuff.\nI hope you like it.\n")
