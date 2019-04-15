#!/usr/bin/env python

import time
import rospy
from std_msgs.msg import String

def talker():
	pub = rospy.Publisher('transport', String, queue_size = 10)
	rospy.init_node('talker',anonymous=True)
	rate = rospy.Rate(10)
	time.sleep(10)
	x = 0
	while not rospy.is_shutdown():
		while x != 1:
			hello_str = "3141019043(5,100,100,200,200,300,300,400,400,500,500)50f400162348e76cee08f538c8ab59f460bee702ff7e06df6da23510774d8502"
			rospy.loginfo(hello_str)
                	pub.publish(hello_str)
                	rate.sleep()
			x = 1
		hello_str = "3141022017(1,2736,1258,312)50f400162348e76cee08f538c8ab59f460bee702ff7e06df6da23510774d8502"
		rospy.loginfo(hello_str)
		pub.publish(hello_str)
		rate.sleep()

if __name__ == '__main__':
	try:
		talker()
	except rospy.ROSInterruptException:
		pass
