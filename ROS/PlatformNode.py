#!/usr/bin/env python
# license removed for brevity
import rospy
import time
import sys
import serial
from std_msgs.msg import String

#arduino = serial.Serial('/dev/ttyACM0', 9600,timeout = 1)
arduino = serial.Serial('/dev/ttyUSB0', 9600,timeout = 1)
time.sleep(2)

#pub = rospy.Publisher('/PlatformError', String, queue_size=10)
#rospy.init_node('TransportNode', anonymous=True)

i = 0
PathSent = False
Talksig = " "
def callback(data):
	#rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)
	global PathSent
	global Talksig
        message = str(data.data)

        if message[4:7] == "022" and PathSent == True:
                info = message.split("(")
                message = info[1]
                message = (message[:-65]).split(",")
                NID = message[0]
                X  = message[1]
                Y  = message[2]
                a  = message[3]

                pos = ['<'+ NID,X,Y,a +'>']
                postring = ",".join(pos)
                print(postring)
                arduino.write(postring)
		Talksig = postring
		rospy.loginfo(Talksig)
		talker(Talksig)

        elif message[4:7] == "019":
                PathSent = True
                NID = 'P'
                Length = message[11:14]
                info = message.split("(")
                message = info[1]
                message = message[:-65].split(",")
                x = message[0]
                xy = ' '
                
                for i in range(1,(int(x)*2)+1):
                        xy += message[i]

                path = ['<'+ NID,Length,xy+'>']
                pathstring = ",".join(path)
                print(pathstring)
		arduino.write(pathstring)
		Talksig = pathstring
		rospy.loginfo(Talksig)
		talker(Talksig)
def talker(data):
	#rospy.init_node('TransportNode', anonymous=True)
        pub = rospy.Publisher('/PlatformError', String, queue_size=10)
	rate = rospy.Rate(10)
	#while not rospy.is_shutdown():
	pub.publish(data)
        rate.sleep()


def listener():
	global Talksig
	rospy.init_node('TransportNode', anonymous=True)
	pub = rospy.Subscriber('/Transport', String, callback)
	#talker(Talksig)
	rospy.spin()

if __name__ == '__main__':
    try:
		listener()
		rospy.spin()

    except rospy.ROSInterruptException:
        pass

#!/usr/bin/env python
#import rospy
#import sys
#import time
#import serial
#from std_msgs.msg import String

#arduino = serial.Serial('/dev/ttyACM0', 9600,timeout = 1)
#arduino = serial.Serial('/dev/ttyUSB0', 9600,timeout = 1)
#time.sleep(2)

# L = 3.4
# W = 1.6
#i = 0
#PathSent = False
#path2 = ['<'+'P','047','100','100','200','200','300','300','400','400','500','500'+'>'+"\n"]
#pastring2 = ",".join(path)

#rospy.init_node('TransportNode', anonymous=True)
#pub = rospy.Publisher('/PlatformError', String, queue_size=10)
#r = rospy.Rate(10)

#def convert(input,old_min,old_max,new_min,new_max):
        # take original value rangeand map it to a new range
#        old_value =  input
#        new_value = ( ( old_value - old_min ) / (old_max - old_min) ) * (new_max - new_min) + new_min
#        return(new_value)

#def serialprint(data):
#        global PathSent
        
#        message = str(data.data)
        
#        if message[4:7] == "022" and PathSent == True:
#                info = message.split("(")
#                message = info[1]
#                message = (message[:-65]).split(",")
#                NID = message[0]
#                X  = message[1]
#                Y  = message[2]
#                a  = message[3]
                
#                pos = ['<'+ NID,X,Y,a +'>']
#                postring = ",".join(pos)
#                print(postring)
#                arduino.write(postring)
#                rospy.loginfo(postring)
	        #while not rospy.is_shutdown():
               	#	pub.publish(postring)
                #	r.sleep()


#        elif message[4:7] == "019":
#                PathSent = True
#                NID = 'P'
#                Length = message[11:14]
#                info = message.split("(")
#                message = info[1]
#                message = message[:-65].split(",")
#                x = message[0]
#                xy = ' '
                
#                for i in range(1,x):
#                        xy += message[i]
#                        
#                path = ['<'+ NID,Length,xy+'>']
#                pathstring = ",".join(path)
#                print(pathring)
#                arduino.write(pathstring)
#                rospy.loginfo(pathring)
	       # while not rospy.is_shutdown():
               # 	pub.publish(pathstring)
               # 	r.sleep()

        
#def listener():
	# In ROS, nodes are uniquely named. If two nodes with the same
	# name are launched, the previous one is kicked off. The
	# anonymous=True flag means that rospy will choose a unique
	# name for our 'listener' node so that multiple listeners can
	# run simultaneously.
#        rospy.init_node('TransportNode', anonymous=True)
#        rospy.Subscriber("/Transport", String, serialprint)
#	rospy.spin() #simply keeps python from exiting until this node is stopped

#if __name__ == '__main__':
#	try:
#		listener()
#        except rospy.ROSInterruptException:
#                pass
