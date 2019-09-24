#!/usr/bin/env python
# -*- coding: UTF-8 -*-
# from __future__ import unicode_literals
# import sys
# reload(sys)
# sys.setdefaultencoding("utf-8")
import rospy
from std_msgs.msg import String
from math import floor
from std_srvs.srv import Empty
from naoqi_bridge_msgs.msg import JointAnglesWithSpeed,Bumper,HeadTouch
from sensor_msgs.msg import Image,JointState
from cv_bridge import CvBridge, CvBridgeError
import cv2
import numpy as np
import argparse
from naoqi import ALProxy
import csv
import matplotlib.pyplot as plt
from collections import deque
import os
import random
import matplotlib


os.environ['KMP_DUPLICATE_LIB_OK']='True'

path = os.path.dirname(__file__)
path = path + os.sep

#np.random.seed(2)

#Team A 1: Adon Yazigi, 2: Shengzhi Wang, 3:Fan Wu, 4: Helene Obert

class Central:


    def __init__(self):
        # initialize class variables
        self.motionProxy = ALProxy("ALMotion", "10.152.246.172", 9559)
        self.postureProxy = ALProxy("ALRobotPosture", "10.152.246.172", 9559)
       # self.joint_names = []
        self.x=0
        self.y=0
      #  self.joint_angles = []
      #  self.joint_velocities = []
        self.jointPub = 0
        # self.stiffness_shoulder = 0.0
        # self.stiffness_head = 0.9
        # self.stiffness_elbow = 0.9
        self.Button_Number = 0  # indicates status of last button pressed
       # self.pNames = ["HeadYaw", "HeadPitch", "LShoulderPitch", "LShoulderRoll", "LElbowYaw", "LElbowRoll"]
       # self.pStiffnessLists = [[0.9], [0.9], [0.0], [0.0], [0.9], [0.9]]
       # self.pTimeLists = [[1.0], [1.0], [1.0], [1.0], [1.0], [1.0]]
       # self.motionProxy.stiffnessInterpolation(self.pNames, self.pStiffnessLists, self.pTimeLists)
       # self.path = os.path.dirname(__file__)
       # self.path = self.path + os.sep
        

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

            lower_red = np.array([0,100,100])#     0,100,100   160,100,160
            upper_red = np.array([10,255,255])#    10,255,255  180,255,255

            lower_orange = np.array([160,100,160])
            upper_orange = np.array([180,255,255])

            #0,15,50    to 3,255,255

            # Threshold the HSV image to get only blue colors
            mask = cv2.inRange(hsv, lower_red, upper_red)
            mask2 = cv2.inRange(hsv, lower_orange, upper_orange)
            mask = mask | mask2
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
                    #print ("Central Position:", self.x,self.y)
            else:
                self.x=0
                self.y=0



            res = cv2.bitwise_and(img,img, mask= mask)   

        except CvBridgeError as e:
            rospy.logerr(e)

        #cv2.imshow("image window",cv_image)
        cv2.imshow('frame',img)
        cv2.imshow('mask',mask)
        cv2.imshow('res',res)
        cv2.waitKey(3) # a small wait time is needed for the image to be displayed correctly

        return [self.x,self.y] 
               


    # sets the stiffness motionProxor all joints. can be refined to only toggle single joints, set values between [0,1] etc

    def joint_moveto(self, angle,joint,speed): # controls joint movement
        joint_angles_to_set = JointAnglesWithSpeed()
        joint_angles_to_set.joint_names.append(joint) # each joint has a specific name, look into the joint_state topic or google
        joint_angles_to_set.joint_angles.append(angle) # the joint values have to be in the same order as the names!!
        joint_angles_to_set.relative = False # if true you can increment positions
        joint_angles_to_set.speed = speed # keep this low if you can
        self.jointPub.publish(joint_angles_to_set)

    def kick_ready(self): # Kick ready position
        self.joint_moveto(0.538, "LHipRoll", 0.05)
        self.motionProxy.waitUntilMoveIsFinished()
        self.joint_moveto(0.911, "LKneePitch", 0.05)
        self.motionProxy.waitUntilMoveIsFinished()    
        self.joint_moveto(-0.288, "LHipPitch", 0.05)
        self.motionProxy.waitUntilMoveIsFinished()
        self.joint_moveto(0.637, "LShoulderRoll", 0.05)
        self.motionProxy.waitUntilMoveIsFinished()
        self.joint_moveto(0.216, "RHipRoll", 0.08)
        self.motionProxy.waitUntilMoveIsFinished()
        self.joint_moveto(-0.15, "RHipPitch", 0.08)
        self.motionProxy.waitUntilMoveIsFinished()
        self.joint_moveto(-0.405, "RAnkleRoll", 0.08)
        self.motionProxy.waitUntilMoveIsFinished()
        self.joint_moveto(0.178, "RAnklePitch", 0.08)
        self.motionProxy.waitUntilMoveIsFinished()
        self.joint_moveto(-0.362, "LAnklePitch", 0.05)
        self.motionProxy.waitUntilMoveIsFinished()
        self.joint_moveto(0.0, "HeadYaw", 0.08) #move head as well
        self.motionProxy.waitUntilMoveIsFinished()
        self.joint_moveto(0.0, "HeadPitch", 0.05)
        self.motionProxy.waitUntilMoveIsFinished()

    def kick(self): # Kick the ball
        self.joint_moveto(0.247, "LHipRoll", 1)
        self.motionProxy.waitUntilMoveIsFinished()
        self.joint_moveto(0.236, "LKneePitch", 1)
        self.motionProxy.waitUntilMoveIsFinished()     
        self.joint_moveto(-0.489, "LHipPitch", 1)
        self.motionProxy.waitUntilMoveIsFinished()
        self.joint_moveto(0.637, "LShoulderRoll", 1)
        self.motionProxy.waitUntilMoveIsFinished()
        self.joint_moveto(0.340, "LAnklePitch", 1)
        self.motionProxy.waitUntilMoveIsFinished()

    # ---------Definition of step function---------
    def step(self, action, state, state_index, pos):
        if action == 0 and state_index != pos*12:
            next_state = state - 0.1169949
            next_state_index = state_index - 1


        elif action == 1 and state_index != pos*12 + 11:
            next_state = state + 0.1169949
            next_state_index = state_index + 1

        else:
            next_state = state
            next_state_index = state_index

        return next_state, next_state_index

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
        self.postureProxy.goToPosture("Stand", 1.0)

        #rate = rospy.Rate(20) # sets the sleep time to 10ms

        # Set the robot to kick-ready position
        self.kick_ready()

        #self.joint_moveto(-0.087, "LAnkleRoll")

       # self.joint_moveto(-0.076, "RKneePitch")
        #self.joint_moveto(0.538, "LHipRoll")
       # self.joint_moveto(-0.237, "LKneePitch")
       # self.joint_moveto(0.200, "LHipPitch")
       # self.joint_moveto(0.116, "RHipRoll")
        #self.joint_moveto(0.085, "RHipPitch")
       # self.joint_moveto(0.084, "RAnkleRoll")
        #self.joint_moveto(0.067, "RAnklePitch")
        #self.joint_moveto(-0.092, "LAnklePitch")
       # self.joint_moveto(0.092, "LAnkleRoll")

        rate = rospy.sleep(10)

        #pNames = [ "LHipRoll","LHipPitch", "LAnkleRoll","LAnklePitch", "LKneePitch"]
        #pStiffnessLists = [[0.0],[0.0],[0.0],[0.0], [0.0]]
        #pTimeLists = [[1.0],[1.0],[1.0],[1.0], [1.0]]
        #self.motionProxy.stiffnessInterpolation(pNames, pStiffnessLists, pTimeLists)

        # Kick
        # self.joint_moveto(0.247, "LHipRoll", 1)
        # self.motionProxy.waitUntilMoveIsFinished()
        # self.joint_moveto(0.236, "LKneePitch", 1)
        # self.motionProxy.waitUntilMoveIsFinished()     
        # self.joint_moveto(-0.489, "LHipPitch", 1)
        # self.motionProxy.waitUntilMoveIsFinished()
        # self.joint_moveto(0.637, "LShoulderRoll", 1)
        # self.motionProxy.waitUntilMoveIsFinished()
        # self.joint_moveto(0.340, "LAnklePitch", 1)
        # self.motionProxy.waitUntilMoveIsFinished()

        # ------------Start with Scoring----------
        # ---------Initialization---------
        actions_name = ['in', 'out', 'kick']         # Definition of moves
        Pmove = np.zeros((3, 72, 72))            # Transition Probabilities of 3 actions (Because we have only 6(goalie)*12(hip angle) states)
        R = np.zeros((72, 3))            # Reward function (Because we have only 12 states, and in each state we can do three actions)
        visits = np.zeros((72, 3))       # Count the vistited times of state s in action a: vistis(s, a)
        state_memory = [5]                # Save the states which are already visited. By default it includes only the initial kick state, which is the fifth state
        n_episodes = 100
        max_state = 8
        accumulate_reward = 0
        scores_list = []
        gamma = 0.99
        goalie2bemoved = False
        moved_time = 0

        Q_table = np.loadtxt(path + 'Qtable.txt', dtype=float)     # Load the Q-table

        # ---------Definition of P matrixs---------
        for i in range(6):
            Pmove[0, i*12, i*12] = 1
            Pmove[0, i*12 + 1, i*12] = 1
            Pmove[0, i*12 + 2, i*12 + 1] = 1
            Pmove[0, i*12 + 3, i*12 + 2] = 1
            Pmove[0, i*12 + 4, i*12 + 3] = 1
            Pmove[0, i*12 + 5, i*12 + 4] = 1
            Pmove[0, i*12 + 6, i*12 + 5] = 1
            Pmove[0, i*12 + 7, i*12 + 6] = 1
            Pmove[0, i*12 + 8, i*12 + 7] = 1
            Pmove[0, i*12 + 9, i*12 + 8] = 1
            Pmove[0, i*12 + 10, i*12 + 9] = 1
            Pmove[0, i*12 + 11, i*12 + 10] = 1

            Pmove[1, i*12 + 11, i*12 + 11] = 1
            Pmove[1, i*12, i*12 + 1] = 1
            Pmove[1, i*12 + 1, i*12 + 2] = 1
            Pmove[1, i*12 + 2, i*12 + 3] = 1
            Pmove[1, i*12 + 3, i*12 + 4] = 1
            Pmove[1, i*12 + 4, i*12 + 5] = 1
            Pmove[1, i*12 + 5, i*12 + 6] = 1
            Pmove[1, i*12 + 6, i*12 + 7] = 1
            Pmove[1, i*12 + 7, i*12 + 8] = 1
            Pmove[1, i*12 + 8, i*12 + 9] = 1
            Pmove[1, i*12 + 9, i*12 + 10] = 1
            Pmove[1, i*12 + 10, i*12 + 11] = 1


        Pmove[2, :, :] = np.identity(72)
        
        # ---------Algorithm---------
        for i_episode in range(1, n_episodes+1):
            rate = rospy.sleep(10)
            #determine goalie position
            #position left x= 31
            #position right x= 176
            pos = (self.x - 31)/145 * 6
            pos = int(floor(pos))
            if (pos > 5):
                pos = 5
            elif (pos < 0):
                pos = 0 
            
            print("pos[0-5] = ", pos)
            print("Position node x = %f, " % self.x) # shows X position and used to calibrate the robot when we make it stand
            # calibrate at x = approx 80 for the left post (place goalie on left post)
            #print("Position node y = %f, " % self.y)
            


            # Set the robot to kick-ready position
            state = 0.538
            state_index = pos*12 + 8         #Begin from pos*12 (so actually is (pos*12 + 9)th state)
            done = False
            accumulate_reward_inLoop = 0
            self.kick_ready()
            rate = rospy.sleep(10)

            for t in range(max_state - 1):
                max_value = np.max(Q_table[state_index, :], axis=0)
                max_aindex = np.argwhere(Q_table[state_index, :] == max_value)
                action = int(max_aindex[np.random.randint(0, len(max_aindex))])
                next_state, next_state_index = self.step(action, state, state_index, pos)
                
                if action != 2:
                    self.joint_moveto(np.clip(next_state, -0.379472, 0.790477), "LHipRoll", 0.05)
                    print(state_index, action)
        

                else:
                    rate = rospy.sleep(5)
                    self.kick()
                    print(state_index, action)
                    rate = rospy.sleep(5)
                    done = True

                            

                state = next_state
                state_index = next_state_index
                if done:
                    break


        

    # rospy.spin() just blocks the code from exiting, if you need to do any periodic tasks use the above loop
    # each Subscriber is handled in its own thread
    #rospy.spin()








if __name__=='__main__':

    # instantiate class and start loop function
    central_instance = Central()
    central_instance.central_execute()