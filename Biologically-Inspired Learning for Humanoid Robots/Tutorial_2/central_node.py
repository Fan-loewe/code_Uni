#!/usr/bin/env python
#Team A 1: Adon Yazigi, 2: Shengzhi Wang, 3:Fan Wu, 4: Helene Obert

import rospy
from std_msgs.msg import String
from std_srvs.srv import Empty
from naoqi_bridge_msgs.msg import JointAnglesWithSpeed,Bumper,HeadTouch
from sensor_msgs.msg import Image,JointState
from cv_bridge import CvBridge, CvBridgeError
import cv2
import numpy as np


class Central:


    def __init__(self):							# initialize class variables      												
        self.joint_names = []
        self.joint_angles = []
        self.joint_velocities = []
        self.jointPub = 0
        self.stiffness = False
        self.Button_Number = 0  				# indicates status of last button pressed

        pass


    def key_cb(self,data):
        rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)

    def joints_cb(self,data):					        #rospy.loginfo("joint states "+str(data.name)+str(data.position))
        self.joint_names = data.name 					# store current joint information in class variables
        self.joint_angles = data.position
        self.joint_velocities = data.velocity

        pass

    def bumper_cb(self,data):
        rospy.loginfo("bumper: "+str(data.bumper)+" state: "+str(data.state))
        if data.bumper == 0:
            self.stiffness = True
        elif data.bumper == 1:
            self.stiffness = False

    def touch_cb(self,data): 							#for task 7: save last button pressed
        rospy.loginfo("touch button: "+str(data.button)+" state: "+str(data.state))
        if (data.button == 1):
            self.Button_Number = 1
            self.set_stiffness(True) 					#always return to home position
        elif (data.button == 2):
            self.Button_Number = 2
        elif (data.button == 3):
            self.Button_Number = 3
        else:
            pass

    def image_cb(self,data):							#task 9 			
        bridge_instance = CvBridge()
        try:
            cv_image = bridge_instance.imgmsg_to_cv2(data,"bgr8")
            img = cv_image.copy()                     
            hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)	# Convert BGR to HSV
            
            lower_red = np.array([0,70,50])		    # define range of red color in HSV
            upper_red = np.array([10,255,255])

            mask = cv2.inRange(hsv, lower_red, upper_red) # Threshold the HSV image to get only red colors
            mask = cv2.erode(mask, None, iterations=2)
            mask = cv2.dilate(mask, None, iterations=2) 

            contours,hierarchy = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
                cv2.CHAIN_APPROX_SIMPLE)					# find contours in the mask and initialize the current

            if len(contours) > 0:							#output the center only when the red bulb appears
                cnts = contours[0]
                center = None
                (x,y),radius = cv2.minEnclosingCircle(cnts)	# find the largest contour in the mask, then use it to compute the minimum enclosing circle
                center = (int(x),int(y))
                radius = int(radius)
                cv2.circle(img,center,radius,(0,255,0),2)
                print ("Central Position:", x,y)	# (x, y) center of the ball
            else:
                pass

            res = cv2.bitwise_and(img,img, mask= mask) 	# Bitwise-AND mask and original image

        except CvBridgeError as e:
            rospy.logerr(e)

        cv2.imshow('frame',img)
        #cv2.imshow('frame',hsv)                # Show the hsv video
        #cv2.imshow('frame',mask)               # Show the mask video
        #cv2.imshow('frame',res)                # Show the bitwise_and + original video
        cv2.waitKey(3) 									# a small wait time is needed for the image to be displayed correctly
        


    # sets the stiffness for all joints. can be refined to only toggle single joints, set values between [0,1] etc
    def set_stiffness(self,value):
        if value == True:
            service_name = '/body_stiffness/enable'
        elif value == False:
            service_name = '/body_stiffness/disable'
        try:
            stiffness_service = rospy.ServiceProxy(service_name,Empty)
            stiffness_service()
        except rospy.ServiceException, e:
            rospy.logerr(e)
    def arm_movement_l(self,arm_angle): # controls left elbow movement
        joint_angles_to_set = JointAnglesWithSpeed()
        joint_angles_to_set.joint_names.append("LElbowYaw") # each joint has a specific name, look into the joint_state topic or google
        joint_angles_to_set.joint_angles.append(arm_angle) # the joint values have to be in the same order as the names!!
        joint_angles_to_set.relative = False # if true you can increment positions
        joint_angles_to_set.speed = 0.1 # keep this low if you can
        self.jointPub.publish(joint_angles_to_set)
    def arm_movement_r(self,arm_angle): # controls right elbow movement
        joint_angles_to_set = JointAnglesWithSpeed()
        joint_angles_to_set.joint_names.append("RElbowYaw") # each joint has a specific name, look into the joint_state topic or google
        joint_angles_to_set.joint_angles.append(arm_angle) # the joint values have to be in the same order as the names!!
        joint_angles_to_set.relative = False # if true you can increment positions
        joint_angles_to_set.speed = 0.1 # keep this low if you can
        self.jointPub.publish(joint_angles_to_set)

    def set_joint_angles(self,head_angle): ## controls head movement

        joint_angles_to_set = JointAnglesWithSpeed()
        joint_angles_to_set.joint_names.append("HeadYaw") # each joint has a specific name, look into the joint_state topic or google
        joint_angles_to_set.joint_angles.append(head_angle) # the joint values have to be in the same order as the names!!
        joint_angles_to_set.relative = False # if true you can increment positions
        joint_angles_to_set.speed = 0.1 # keep this low if you can
        self.jointPub.publish(joint_angles_to_set)
        


    def central_execute(self):
        rospy.init_node('central_node',anonymous=True) #initilizes node, sets name

        # create several topic subscribers
        rospy.Subscriber("key", String, self.key_cb)
        rospy.Subscriber("joint_states",JointState,self.joints_cb)
        rospy.Subscriber("bumper",Bumper,self.bumper_cb)
        rospy.Subscriber("tactile_touch",HeadTouch,self.touch_cb)
        rospy.Subscriber("/nao_robot/camera/top/camera/image_raw",Image,self.image_cb)
        self.jointPub = rospy.Publisher("joint_angles",JointAnglesWithSpeed,queue_size=10)


        # test sequence to demonstrate setting joint angles
        self.set_stiffness(True) # don't let the robot stay enabled for too long, the motors will overheat!! (don't go for lunch or something)
        rospy.sleep(1.0)
        self.set_joint_angles(0.5)
        rospy.sleep(3.0)
        self.set_joint_angles(0.0)
        rospy.sleep(3.0)
        self.set_stiffness(False) # always check that your robot is in a stable position before disabling the stiffness!!

        rate = rospy.Rate(10) # sets the sleep time to 10ms
        while not rospy.is_shutdown():
            self.set_stiffness(self.stiffness)

            if(self.Button_Number ==2): # button 2 pressed
                self.stiffness = True
                self.set_stiffness(self.stiffness)
                self.arm_movement_l(-0.5) # move to home position)
                rospy.sleep(3.0)
                self.arm_movement_l(-2) #move to this angle
                rospy.sleep(3.0)
            elif(self.Button_Number ==1 ): # button 1 pressed
                self.arm_movement_l(-0.5)# move to home position
                rospy.sleep(3.0)
                self.stiffness = False
            elif(self.Button_Number == 3):# button 3 pressed
                self.stiffness = True
                self.set_stiffness(self.stiffness)
                self.arm_movement_l(-0.5)# move to home position
                self.arm_movement_r(0.5)# move to home position
                rospy.sleep(3.0)
                self.arm_movement_l(-2)#move to this angle
                self.arm_movement_r(2)#move to this angle
                rospy.sleep(3.0)
            else:
                pass
            rate.sleep()
     

    # rospy.spin() just blocks the code from exiting, if you need to do any periodic tasks use the above loop
    # each Subscriber is handled in its own thread
    #rospy.spin()



if __name__=='__main__':
    # instantiate class and start loop function
    central_instance = Central()
    central_instance.central_execute()



