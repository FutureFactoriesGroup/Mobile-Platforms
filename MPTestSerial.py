#!/usr/bin/env python

import sys
import time
import serial

arduino =  serial.Serial('COM6', 9600,timeout = 1) #connect to the arduino's serial port
time.sleep(2)

def convert(input_value,old_min,old_max,new_min,new_max): # take original values  and map it to a new range
        old_value   = input_value
        new_value = ( ( old_value - old_min ) / (old_max - old_min) ) * (new_max - new_min) + new_min
        return(new_value)
    
while 1:
    a = 'A'   
    b = '120' 
    c =  '130' 
    d = '140'
    e = '150'
    
    control = ['<' + a,b,c,d,e + '>']    # save strings in a list
    cstring = ",".join(control)     # convert list to a single string with commas seperating values
        
    print(cstring)
    arduino.write(cstring)          # print string to shell and write data to arduino with a 0.1ms delay
    time.sleep(0.5)
        
