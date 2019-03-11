#!/usr/bin/env python

import rospy
import sys
import time
import serial
from std_msgs.msg import String

arduino = serial.Serial('/dev/ttyACM0', 9600,timeout = 1)
time.sleep(2)

def serialprint(data):
	print(str(data.data))
	arduino.write(str(data.data))
	time.sleep(0.5)
	#rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)

def listener():
	rospy.init_node('listener' , anonymous=True)
	rospy.Subscriber("transport", String, serialprint)
	rospy.spin()

if __name__ == '__main__':
	listener()

#old_value1 = controls.get_axis(0)  # X-axis
#old_value2 = controls.get_axis(1)  # Y-axis
#old_value3 = controls.get_axis(3)  # Rudder

#old_min = -1
#old_max = 1
#new_min = 100
#new_max = 355
                                                # take original values (-1 to 1) and map it to a new range between 100 and 355***
#new_value1 = ( ( old_value1 - old_min ) / (old_max - old_min) ) * (new_max - new_min) + new_min
#new_value2 = ( ( old_value2 - old_min ) / (old_max - old_min) ) * (new_max - new_min) + new_min
#new_value3 = ( ( old_value3 - old_min ) / (old_max - old_min) ) * (new_max - new_min) + new_min

#a = str(int(round(new_value1)))   
#b = str(int(round(new_value2)))  # converts values from floats to integers and then to strings
#c = str(int(round(new_value3)))
#h = '000'
            
#control = ['<' + a,b,c,h + '>']    # save strings in a list
#cstring = ",".join(control)     # convert list to a single string with commas seperating values
                
#print(cstring)
#arduino.write(cstring)          # print string to shell and write data to arduino with a 0.1ms delay
#time.sleep(0.0001)
