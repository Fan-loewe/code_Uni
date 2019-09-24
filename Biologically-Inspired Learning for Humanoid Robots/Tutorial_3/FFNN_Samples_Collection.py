#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from std_srvs.srv import Empty
from naoqi_bridge_msgs.msg import JointAnglesWithSpeed,Bumper,HeadTouch
from sensor_msgs.msg import Image,JointState
from cv_bridge import CvBridge, CvBridgeError
import cv2
import numpy as np
import argparse
from naoqi import ALProxy
import csv

#Team A 1: Adon Yazigi, 2: Shengzhi Wang, 3:Fan Wu, 4: Helene Obert

class Central:


    def __init__(self):
        # initialize class variables
        self.motionProxy = ALProxy("ALMotion", "10.152.246.172", 9559)
        self.joint_names = []
        self.x=0
        self.y=0
        self.joint_angles = []
        self.joint_velocities = []
        self.jointPub = 0
        # self.stiffness_shoulder = 0.0
        # self.stiffness_head = 0.9
        # self.stiffness_elbow = 0.9
        self.Button_Number = 0  # indicates status of last button pressed
        self.pNames = ["HeadYaw", "HeadPitch", "LShoulderPitch", "LShoulderRoll", "LElbowYaw", "LElbowRoll"]            # Initialize the stiffness
        self.pStiffnessLists = [[0.9], [0.9], [0.0], [0.0], [0.9], [0.9]]
        self.pTimeLists = [[1.0], [1.0], [1.0], [1.0], [1.0], [1.0]]
        self.motionProxy.stiffnessInterpolation(self.pNames, self.pStiffnessLists, self.pTimeLists)
        

        pass



    def key_cb(self,data):
        rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)

    def joints_cb(self,data):
        #rospy.loginfo("joint states "+str(data.name)+str(data.position))
        # store current joint information in class variables
        self.joint_names = data.name 
        self.joint_angles = data.position
        self.joint_velocities = data.velocity

        pass

    def bumper_cb(self,data):
        rospy.loginfo("bumper: "+str(data.bumper)+" state: "+str(data.state))
        if data.bumper == 0:
            self.stiffness = True
        elif data.bumper == 1:
            self.stiffness = False

    def touch_cb(self,data): # added part to save last button pressed
        rospy.loginfo("touch button: "+str(data.button)+" state: "+str(data.state))
        if (data.button == 1 and data.state==1):
            self.Button_Number = 1
   
            # self.set_stiffness(True) #to always return to normal position
        elif (data.button == 2 and data.state==1):
            self.Button_Number = 2
        elif (data.button == 3 and data.state==1):
            self.Button_Number = 3
        else:
            pass

    def image_cb(self,data):
        bridge_instance = CvBridge()
        try:
            cv_image = bridge_instance.imgmsg_to_cv2(data,"bgr8")
            img = cv_image.copy()
                        
            # Convert BGR to HSV
            hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
            
            # define range of blue color in HSV
            #lower_blue = np.array([0,15,50])#0,70,50
            #upper_blue = np.array([3,255,255])#10,255,255
            lower_red = np.array([0,15,50])#0,70,50
            upper_red = np.array([3,255,255])#10,255,255

            # Threshold the HSV image to get only blue colors
            mask = cv2.inRange(hsv, lower_red, upper_red)  
            mask = cv2.erode(mask, None, iterations=2)
            mask = cv2.dilate(mask, None, iterations=2) 

            # find contours in the mask and initialize the current
            # (x, y) center of the ball
            #ret,thresh = cv2.threshold(mask,127,255,0)
            contours,hierarchy = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
                cv2.CHAIN_APPROX_SIMPLE)
            #contours,hierarchy = cv2.findContours(thresh, 1, 2)
            cv2.drawContours(mask,contours,-1,(0,255,255),2)

            area=[]
            for i in range(len(contours)):
                area.append(cv2.contourArea(contours[i]))
            
            if len(area)>0:
                max_idx = np.argmax(area)
                if area[max_idx]<300 or area == []:
                    self.x=0
                    self.y=0

                else:
                    cv2.fillConvexPoly(mask,contours[max_idx],255)
                    #cv2.imshow('make window',mask)
                    cv2.waitKey(3)
                    M=cv2.moments(mask)
                    self.x, self.y= M['m10'] / M['m00'],  M['m01'] /  M['m00']
                    cv2.circle(img, (int(self.x),int(self.y)),5,(0,255,0),-1)
                    print ("Central Position:", self.x,self.y)
            else:
                self.x=0
                self.y=0

            # Bitwise-AND mask and original image


            res = cv2.bitwise_and(img,img, mask= mask)   

        except CvBridgeError as e:
            rospy.logerr(e)

        #cv2.imshow("image window",cv_image)
        cv2.imshow('frame',img)
        cv2.imshow('mask',mask)
        cv2.imshow('res',res)
        cv2.waitKey(3) # a small wait time is needed for the image to be displayed correctly

        return [self.x,self.y] 
        


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
    def Elbow_yaw_L_moveto(self,arm_angle): # controls left elbow movement
        joint_angles_to_set = JointAnglesWithSpeed()
        joint_angles_to_set.joint_names.append("LElbowYaw") # each joint has a specific name, look into the joint_state topic or google
        joint_angles_to_set.joint_angles.append(arm_angle) # the joint values have to be in the same order as the names!!
        joint_angles_to_set.relative = False # if true you can increment positions
        joint_angles_to_set.speed = 0.1 # keep this low if you can
        self.jointPub.publish(joint_angles_to_set)
    def Elbow_roll_L_moveto(self,angle): # controls left elbow movement
        joint_angles_to_set = JointAnglesWithSpeed()
        joint_angles_to_set.joint_names.append("LElbowRoll") # each joint has a specific name, look into the joint_state topic or google
        joint_angles_to_set.joint_angles.append(angle) # the joint values have to be in the same order as the names!!
        joint_angles_to_set.relative = False # if true you can increment positions
        joint_angles_to_set.speed = 0.1 # keep this low if you can
        self.jointPub.publish(joint_angles_to_set)

    def Shoulder_pitch_L_moveto(self,arm_angle): # controls left shoulder movement
        joint_angles_to_set = JointAnglesWithSpeed()
        joint_angles_to_set.joint_names.append("LShoulderPitch") # each joint has a specific name, look into the joint_state topic or google
        joint_angles_to_set.joint_angles.append(arm_angle) # the joint values have to be in the same order as the names!!
        joint_angles_to_set.relative = False # if true you can increment positions
        joint_angles_to_set.speed = 0.1 # keep this low if you can
        self.jointPub.publish(joint_angles_to_set)
    def Shoulder_roll_L_moveto(self,angle): # controls left shoulder movement
        joint_angles_to_set = JointAnglesWithSpeed()
        joint_angles_to_set.joint_names.append("LShoulderRoll") # each joint has a specific name, look into the joint_state topic or google
        joint_angles_to_set.joint_angles.append(angle) # the joint values have to be in the same order as the names!!
        joint_angles_to_set.relative = False # if true you can increment positions
        joint_angles_to_set.speed = 0.1 # keep this low if you can
        self.jointPub.publish(joint_angles_to_set)


    def Elbow_yaw_R_moveto(self,arm_angle): # controls right elbow movement
        joint_angles_to_set = JointAnglesWithSpeed()
        joint_angles_to_set.joint_names.append("RElbowYaw") # each joint has a specific name, look into the joint_state topic or google
        joint_angles_to_set.joint_angles.append(arm_angle) # the joint values have to be in the same order as the names!!
        joint_angles_to_set.relative = False # if true you can increment positions
        joint_angles_to_set.speed = 0.1 # keep this low if you can
        self.jointPub.publish(joint_angles_to_set)

    def set_head_angles(self,head_angle): ## controls head movement

        joint_angles_to_set = JointAnglesWithSpeed()
        joint_angles_to_set.joint_names.append("HeadYaw") # each joint has a specific name, look into the joint_state topic or google
        joint_angles_to_set.joint_angles.append(head_angle) # the joint values have to be in the same order as the names!!
        joint_angles_to_set.relative = False # if true you can increment positions
        joint_angles_to_set.speed = 0.1 # keep this low if you can
        self.jointPub.publish(joint_angles_to_set)
        joint_angles_to_set.joint_names.append("HeadPitch")
        joint_angles_to_set.joint_angles.append(head_angle)
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
        # self.set_stiffness(True) # don't let the robot stay enabled for too long, the motors will overheat!! (don't go for lunch or something)
        rospy.sleep(1.0)
        self.set_head_angles(0.5)
        #self.Elbow_roll_L_moveto(-1.5)
        #self.Elbow_yaw_L_moveto(0.1)
        rospy.sleep(3.0)
        self.Elbow_roll_L_moveto(-0.67)
        self.Elbow_yaw_L_moveto(0.0)
        self.set_head_angles(0.0)
        rospy.sleep(3.0)
        # self.set_stiffness(False) # always check that your robot is in a stable position before disabling the stiffness!!

        rate = rospy.Rate(10) # sets the sleep time to 10ms
        i=0
        a=0
        f= open("samples.txt","w+")
        while not rospy.is_shutdown():
            # self.set_stiffness(self.stiffness)

            if(self.Button_Number ==1): # button 2 pressed then save data

                if(a==0):
                    print(i)
                    f.write("%d \n" %i)
                    a=1
                    f.write("Lshoulderpitch = %f\n" % self.joint_angles[2])
                    f.write("Lshoulderroll = %f\n" % self.joint_angles[3])
                    f.write("Position node x = %f, " % self.x)
                    f.write("y = %f \n" %self.y)
                    with open('samples.csv', 'a') as samples:
                    #it is  'a' as 'append' : don't forget to delete the file if you want to change the data and not just to add to the previous ones!
                        samples_writer = csv.writer(samples)

                        samples_writer.writerow([i, self.joint_angles[2], self.joint_angles[3], self.x,self.y])
                    samples.close()
                    i+=1
                self.Button_Number = 0
               
               # pass
            
            else:
                pass

            a=0
            rate.sleep()
        f.close()
        

    # rospy.spin() just blocks the code from exiting, if you need to do any periodic tasks use the above loop
    # each Subscriber is handled in its own thread
    #rospy.spin()



if __name__=='__main__':
    # instantiate class and start loop function
    central_instance = Central()
    central_instance.central_execute()
    #self.Shoulder_roll_L_moveto(shoulder_L_roll_move)
    #self.Shoulder_pitch_L_moveto(shoulder_L_pitch_move)



