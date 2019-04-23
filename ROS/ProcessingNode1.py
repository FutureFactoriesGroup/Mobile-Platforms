#!/usr/bin/env python
# license removed for brevity
import rospy
import time
import sys
import serial
from std_msgs.msg import String
import math
import numpy as np

rospy.init_node('ProcessingNode1', anonymous=True)
pub = rospy.Publisher('/process', String, queue_size=10)
time.sleep(2)

def callback(data):
	global pub


rospy.Subscriber('/process', String, callback)
try:
	rospy.spin()

except rospy.ROSInterruptException:
    pass
