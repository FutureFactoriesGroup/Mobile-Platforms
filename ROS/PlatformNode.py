#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import String

pub = rospy.Publisher('/PlatformError', String, queue_size=10)
rospy.init_node('TransportNode', anonymous=True)

def callback(data):
	rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)
	pub.publish(data.data)

def listener():

	# In ROS, nodes are uniquely named. If two nodes with the same
	# name are launched, the previous one is kicked off. The
	# anonymous=True flag means that rospy will choose a unique
	# name for our 'listener' node so that multiple listeners can
	# run simultaneously.
	rospy.init_node('TransportNode', anonymous=True)

	rospy.Subscriber("/transport", String, callback)

	# spin() simply keeps python from exiting until this node is stopped


if __name__ == '__main__':
    try:
		listener()
		rospy.spin()

    except rospy.ROSInterruptException:
        pass

# #!/usr/bin/env python
# import rospy
# import sys
# import time
# import serial
# from std_msgs.msg import String
#
# arduino = serial.Serial('/dev/ttyACM0', 9600,timeout = 1)
# time.sleep(2)
#
# # L = 3.4
# # W = 1.6
# i = 0
# PathSent = False
# path2 = ['<'+'P','047','100','100','200','200','300','300','400','400','500','500'+'>'+"\n"]
# pastring2 = ",".join(path)
# pub = rospy.Publisher('/PlatformError', String, queue_size=10)
#
# def convert(input,old_min,old_max,new_min,new_max):
# 	old_value =  input
# 	# take original values (-1 to 1) and map it to a new range between 100 and 355***
# 	new_value = ( ( old_value - old_min ) / (old_max - old_min) ) * (new_max - new_min) + new_min
# 	return(new_value)
#
# def serialprint(data):
# 	global PathSent
# 	message = str(data.data)
# 	pub.publish("I heard " + data.data)
# 	if message[4:7] == "022" and PathSent == True:
# 		info = message.split("(")
# 		message = info[1]
# 		message = (message[:-65]).split(",")
# 		NID = message[0]
# 		X  = message[1]
# 		Y  = message[2]
# 		a  = message[3]
#
# 		pos = ['<'+ NID,X,Y,a +'>']
# 		postring = ",".join(pos)
# 		print(postring)
# 		arduino.write(postring)
# 		rospy.loginfo(postring)
# 		pub.publish(postring)
#
# 	elif message[4:7] == "019":
# 		PathSent = True
# 		NID = 'P'
# 		Length = message[11:14]
# 		info = message.split("(")
# 		message = info[1]
# 		message = message[:-65].split(",")
# 		x = message[0]
# 		xy = ' '
# 		for i in range(1,x):
# 			xy += message[i]
# 		path = ['<'+ NID,Length,xy+'>']
# 		pa    # Create a publisher object
#     # It publishes String messages to the topic 'chatter'
#     pub = rospy.Publisher('PlatformError', String, queue_size = 10)
#     rospy.init_node('TransportNode', anonymous = True)
#     rate = rospy.Rate(10) # 10hz
#
#     while not rospy.is_shutdown():
#         hello_str = "hello world %s" % rospy.get_time()
#         rospy.loginfo(pastring2)
#         pub.publish(pastring2)
#         rate.sleep()
#
# if __name__ == '__main__':
#     try:
#         talker()
#     except rospy.ROSInterruptException:
#         pass
# string = ",".join(path)
# 		pub.publish(pasting)
# 		rospy.loginfo(postring)
# 		print(pastring)
# 		arduino.write(pastring)
#
#
# 	#print(postring)
# 	#arduino.write(postring)
# 	#print(pastring)
#         #arduino.write(pastring)
# 	#rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)
#
# #def listener():
#
# 	#rospy.spin()
#
# 	#rate = rospy.Rate(10)
#
# #if __name__ == '__main__':
# 	#listener()
# rospy.init_node('TransportNode' , anonymous=False,log_level = rospy.DEBUG)
# rospy.Subscriber("/transport", String, serialprint)
#
# rospy.spin()
# 	#rospy.init_node('TransportNode', anonymous=False)
