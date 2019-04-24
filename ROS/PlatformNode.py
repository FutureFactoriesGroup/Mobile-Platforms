#!/usr/bin/env python
# license removed for brevity
import rospy
import time
import sys
import serial
from std_msgs.msg import String
import math
import numpy as np

x = []
y = []
serialList = []
PtIndex = 0
pub = None
pathlength = 0
Command = ""
GoToZero = False
Target = 0
#Speed = 0
#PreviousTime = 0
#print("this is a test")
rospy.init_node('TransportNode', anonymous=True)
pub = rospy.Publisher('/PlatformError', String, queue_size=10)
time.sleep(2)
#pub.publish("Starting up")
#print("starting up")
try:
	serialList.append(serial.Serial('/dev/ttyACM0', 115200,timeout = 1))
	#pub.publish("Flag 1")
except:
	pass

try:
	serialList.append(serial.Serial('/dev/ttyACM1', 115200,timeout = 1))
	#pub.publish("Flag 2")
except:
	pass
#Arm = serial.Serial('/dev/ttyACM0',115200,timeout = 1)
time.sleep(2)
inputString = ""

Arm = None
arduino = None

for port in serialList:
	try:
		returnValue = port.read(15)
		#pub.publish("returnValue is: {}".format(returnValue))
		print(returnValue)
		if "arm" in returnValue:
			Arm = port
			pub.publish("Arm found")
			time.sleep(2)
			Arm.write("M2231 V0")
			Arm.write("G1 X85 Y151 Z16.5 F100\n")
		elif "pla" in returnValue:
			arduino = port
			pub.publish("Platform found")
	except serial.SerialException:
		pass

PathSent = False
def callback(data):
	#rospy.loginfo(rospy.get_caller_id() + "Iarduino heard %s", data.data)
	global PathSent
	global pub
	global x
	global y
	global PtIndex
	global Speed
	global PreviousTime
	global pathlength
	global Command
	global GoToZero
	message = str(data.data)
	#pub.publish(data.data)
	if message.startswith("31"):
		if message[4:7] == "022" and PathSent == True:
			#StartTime = time.time()*1000
			#TimeStep = StartTime - PreviousTime
			#PreviousTime = StartTime
			#pub.publish("022")
			info = message.split("(")
			message = info[1]
			message = (message[:-65]).split(",")
			PosX = int(message[1])
			PosY = int(message[2])
			alpha = int(message[3])
			pub.publish("    ")
			# create complex next position
			nextPos = x[PtIndex]+y[PtIndex]*1j
			pub.publish("next pos:" + str(nextPos))
			# create complex current position
			currentPos = PosX+PosY*1j
			pub.publish("currentPos:" + str(currentPos))
			# create error vector --> this gives Xerr and Yerr
			currentPosError = nextPos-currentPos
			pub.publish("currentPosError:" + str(currentPosError))
			Xerr,Yerr = currentPosError.real,currentPosError.imag

			# take arg of error vector and subtract alpha
			desiredAlpha = np.angle(currentPosError)*100
			pub.publish("InitialDesiredAlpha: " + str(desiredAlpha))
			#remap desiredAlpha
			if(desiredAlpha<0):
				desiredAlpha =   (math.pi)*200.0 - abs(desiredAlpha)

			#desiredAlpha = (math.pi5)*200.0  - desiredAlpha

			alphaError = (desiredAlpha)-alpha #+ (2*math.pi)*100.0
			if(alphaError > (math.pi)*100.0):
				alphaError = alphaError - (math.pi)*200.0
			elif(alphaError < -(math.pi)*100.0):
				alphaError = alphaError + (math.pi)*200.0
			pub.publish("DesiredAlpha: " + str(desiredAlpha))

			DistanceErr = ((Xerr**2)+(Yerr**2))**0.5

			if(not GoToZero):
				if((DistanceErr > 15)):# and (PtIndex < pathlength-2)):	#in mm
					#if(alphaError > 5 or alphaError < -5): #In centi-rad
					if (alphaError > 5 and alphaError < 309):
						#rotate anticlockwise
						try:
							NewCommand = "15,1\n"
							pub.publish("15,1")
							if (NewCommand != Command):
								arduino.write(NewCommand) #(Speed CCW,Rotate)
								Command= NewCommand
						except:
							pass
					elif (alphaError < -5 and alphaError > -309):
						try:
							NewCommand = "-15,1\n"
							pub.publish("-15,1")
							if (NewCommand != Command):
								arduino.write(NewCommand) #(Speed CCW,Rotate)
								Command= NewCommand
						except:
							pass
					else:
						#Stop rotating
						try:
							NewCommand = "15,2\n"
							pub.publish("15,2")
							if (NewCommand != Command):
								arduino.write(NewCommand) #(Speed CCW,Rotate)
								Command= NewCommand
								#Speed = 0
						except:
							pass

				elif((DistanceErr < 15)):
					if(PtIndex == pathlength-1):
						GoToZero = True
					else:
						PtIndex += 1

			else: #Last Point - Go to zero angle
				if(alpha > (Target - 5) or alpha < -Target + 5):
					if (alpha > -Target + 5):
						#rotate anticlockwise
						try:
							NewCommand = "-15,1\n"
							pub.publish("-15,1")
							if (NewCommand != Command):
								arduino.write(NewCommand) #(Speed CCW,Rotate)
								Command= NewCommand
						except:
							pass
					elif (alpha < Target -5):
						try:
							NewCommand = "15,1\n"
							pub.publish("15,1")
							if (NewCommand != Command):
								arduino.write(NewCommand) #(Speed CCW,Rotate)
								Command= NewCommand
						except:
							pass
				# elif((DistanceErr < 10)):
				# 	try:
				# 		NewCommand = "10,2\n"
				# 		pub.publish("10,2")
				# 		if (NewCommand != Command):
				# 			arduino.write(NewCommand) #(Speed CCW,Rotate)
				# 			Command= NewCommand
							#Speed = 0
					except:
						pass
				else:
					PathSent = False
					try:
						arduino.write("0,0\n") #All stop
						pub.publish("0,0")
					except:
						pass


			ErrorVector = "(" + str(int(Xerr))+","+str(int(Yerr))+","+str(int(alphaError)) + ")"
			pub.publish(ErrorVector)
			# if arduino != None:
			# 	try:
			# 		arduino.write(ErrorVector)
			# 		#Display.write(ErrorVector)
			# 		#pass
			# 	except serial.SerialException:
			# 		pass
			# 	#pub.publish("No Serial")
			# 	#exit()


		elif message[4:7] == "019":
			pub.publish("019")
			info = message.split("(")
			message = info[1]
			message = message[:-65].split(",")
			pathlength = int(message[0])
			x = []
			y = []
			for i in range(pathlength):
				x.append(int(message[(2*i)+1]))
				y.append(int(message[(2*i)+2]))
			Target = int(message[:-1])
			PathSent = True
			GoToZero = False
			PtIndex = 0

		elif message[4:7] == "041":
			if Arm != None:
				pub.publish("041")
				info = message.split("(")
				message = info[1]
				message = message[:-1].split(",")
				x = int(message[0])
				y = int(message[1])
				z = int(message[2])
				Suction = int(message[3])
				try:
					print("G1 X" + str(x) + " Y" + str(y) + " Z" + str(z) +" F100\n")
					pub.publish("G1 X" + str(x) + " Y" + str(y) + " Z" + str(z) +" F100")
					Arm.write("G1 X" + str(x) + " Y" + str(y) + " Z" + str(z) +" F100\n")
					time.sleep(3)
					print("M2231 V"+str(Suction)+"\n")
					pub.publish("M2231 V"+str(Suction))
					Arm.write("M2231 V"+str(Suction)+"\n")
				except:
					pass

rospy.Subscriber('/transport', String, callback)
try:
	rospy.spin()

except rospy.ROSInterruptException:
    pass
