#!/usr/bin/env python

import sys

from naoqi import ALProxy
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
import matplotlib.pyplot as plt
from collections import deque
import os
import random

class Central:


    def __init__(self):
        # initialize class variables
        #self.motionProxy = ALProxy("ALMotion", "10.152.246.172", 9559)
       # self.joint_names = []
        #self.x=0
       # self.y=0
        #self.joint_angles = []
        #self.joint_velocities = []
        self.jointPub = 0
        # self.stiffness_shoulder = 0.0
        # self.stiffness_head = 0.9
        # self.stiffness_elbow = 0.9
       # self.Button_Number = 0  # indicates status of last button pressed
       # self.pNames = ["HeadYaw", "HeadPitch", "LShoulderPitch", "LShoulderRoll", "LElbowYaw", "LElbowRoll"]
        #self.pStiffnessLists = [[0.9], [0.9], [0.0], [0.0], [0.9], [0.9]]
        #self.pTimeLists = [[1.0], [1.0], [1.0], [1.0], [1.0], [1.0]]
       # self.motionProxy.stiffnessInterpolation(self.pNames, self.pStiffnessLists, self.pTimeLists)
        #self.path = os.path.dirname(__file__)
        #self.path = self.path + os.sep
        

        pass

    def main(self, robotIP):
        motionProxy = ALProxy("ALMotion",robotIP, 9559)
        try:
            postureProxy = ALProxy("ALRobotPosture", robotIP, 9559)
        except Exception, e:
            print "Could not create proxy to ALRobotPosture"
            print "Error was: ", e


        #postureProxy.goToPosture("StandInit", 1.0)
        #postureProxy.goToPosture("SitRelax", 1.0)
        #postureProxy.goToPosture("StandZero", 1.0)
        #postureProxy.goToPosture("LyingBelly", 1.0)
        #postureProxy.goToPosture("LyingBack", 1.0)
        postureProxy.goToPosture("Stand", 1.0)
        #postureProxy.goToPosture("Crouch", 1.0)
        #postureProxy.goToPosture("Sit", 1.0)
        #pNames = [ "RHipRoll",  "RAnkleRoll","RAnklePitch","LHipRoll","LHipPitch", "LAnkleRoll","LAnklePitch", "LKneePitch"]
        #pStiffnessLists = [[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0], [0.0]]
        #pTimeLists = [[1.0], [1.0],[1.0],[1.0],[1.0],[1.0],[1.0], [1.0]]
        #motionProxy.stiffnessInterpolation(pNames, pStiffnessLists, pTimeLists)




    def joint_moveto(self, angle,joint): # controls joint movement
        joint_angles_to_set = JointAnglesWithSpeed()
        joint_angles_to_set.joint_names.append(joint) # each joint has a specific name, look into the joint_state topic or google
        joint_angles_to_set.joint_angles.append(angle) # the joint values have to be in the same order as the names!!
        joint_angles_to_set.relative = False # if true you can increment positions
        joint_angles_to_set.speed = 0.1 # keep this low if you can
        self.jointPub.publish(joint_angles_to_set)



if __name__ == "__main__":
    robotIp = "10.152.246.172"

    if len(sys.argv) <= 1:
        print "Usage python alrobotposture.py robotIP (optional default: 127.0.0.1)"
    else:
        robotIp = sys.argv[1]

    central_instance = Central()
    central_instance.main(robotIp)