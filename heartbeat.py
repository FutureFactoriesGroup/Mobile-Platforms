#!/usr/bin/env python

import rospy
from std_msgs.msg import String

def heartbeat():
        pub = rospy.Publisher('system', String, queue_size = 10)
        rospy.init_node('heartbeat',anonymous=True)
        rate = rospy.Rate(1)
        while not rospy.is_shutdown():
                beat = "X" 
                rospy.loginfo(beat)
                pub.publish(beat)
                rate.sleep()

if __name__ == '__main__':
        try:
                heartbeat()
        except rospy.ROSInterruptException:
                pass

