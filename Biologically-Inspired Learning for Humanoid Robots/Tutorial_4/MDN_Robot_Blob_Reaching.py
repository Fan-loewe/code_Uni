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
import matplotlib.pyplot as plt
from collections import deque
import os
import random
import tensorflow as tf

os.environ['KMP_DUPLICATE_LIB_OK']='True'

path = os.path.dirname(__file__)
path = path + os.sep

np.random.seed(2)
tf.random.set_random_seed(1)

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
        self.pNames = ["HeadYaw", "HeadPitch", "LShoulderPitch", "LShoulderRoll", "LElbowYaw", "LElbowRoll"]
        self.pStiffnessLists = [[0.9], [0.9], [0.0], [0.0], [0.9], [0.9]]
        self.pTimeLists = [[1.0], [1.0], [1.0], [1.0], [1.0], [1.0]]
        self.motionProxy.stiffnessInterpolation(self.pNames, self.pStiffnessLists, self.pTimeLists)
        self.path = os.path.dirname(__file__)
        self.path = self.path + os.sep
        

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

    def central_execute(self, saver):
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
        f= open(self.path + "samples.txt","w+")
        while not rospy.is_shutdown():
            # self.set_stiffness(self.stiffness)

            if(self.Button_Number ==1): # button 2 pressed

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
         
            else:
                pass

            if(float(self.x>0) and float(self.y>0)):
                self.pNamesShoulderL = ["LShoulderPitch", "LShoulderRoll"]
                self.pStiffnessListsShoulderL = [[0.9], [0.9]]
                self.pTimeListsShoulderL = [[1.0], [1.0]]
                self.motionProxy.stiffnessInterpolation(self.pNamesShoulderL, self.pStiffnessListsShoulderL, self.pTimeListsShoulderL)
                test_input=np.array([[self.x],[self.y]])
                test_input = (test_input - train_input_min.reshape(-1, 1)) / (train_input_max.reshape(-1, 1) - train_input_min.reshape(-1, 1))      # Normalize input data
                test_input = test_input.T

                with tf.Session() as sess:          # Use trained network to predict shoulder positions
                    saver = tf.train.import_meta_graph(self.path + 'trained_network/save_net.meta')
                    saver.restore(sess, tf.train.latest_checkpoint(self.path + "trained_network/"))

                    # ----------- Prediction of network (tensorflow)----------
                    out_pi_test, out_sigma_test, out_mu_test = sess.run(get_mixture_coef(output), feed_dict={'x:0': test_input})
                    y_samples = generate_ensemble(out_mu_test, out_sigma_test)
                    y_samples = y_samples.T

                # Denormalization
                joint_angle_prediction = (train_output_max.reshape(-1, 1) - train_output_min.reshape(-1, 1)) * y_samples + train_output_min.reshape(-1, 1)
                

                self.Shoulder_roll_L_moveto(joint_angle_prediction[1])
                self.Shoulder_pitch_L_moveto(joint_angle_prediction[0])

                rospy.sleep(2.0)
            
            else:           # If nothing is detected, the arm goes back to home position
                self.Shoulder_roll_L_moveto(-0.263)
                self.Shoulder_pitch_L_moveto(0.684)
                rospy.sleep(2.0)
                self.pNamesShoulderL = ["LShoulderPitch", "LShoulderRoll"]
                self.pStiffnessListsShoulderL = [[0.0], [0.0]]
                self.pTimeListsShoulderL = [[1.0], [1.0]]
                self.motionProxy.stiffnessInterpolation(self.pNamesShoulderL, self.pStiffnessListsShoulderL, self.pTimeListsShoulderL)
                pass


            a=0
            rate.sleep()
        f.close()
        self.set_stiffness(False)
        

    # rospy.spin() just blocks the code from exiting, if you need to do any periodic tasks use the above loop
    # each Subscriber is handled in its own thread
    #rospy.spin()




# ----------- Define some functions ----------
def neural_network(X):
    """Network by using tensorflow (One input layer + 2 hidden layers + 1 output layer: Neuron number in each layer: 2 + 15 + 15 + 5)"""
    # 2 hidden layers with 15 hidden units in each layer
    K = 1       # Number of mixture
    net = tf.layers.dense(X, 15, activation=tf.nn.relu)
    net = tf.layers.dense(net, 15, activation=tf.nn.relu)
    output = tf.layers.dense(net, 5, activation=None)       #Output is 5 because 1 pi + 2 sigma + 2 mu
    return output

def get_mixture_coef(output):
    out_pi = tf.placeholder(dtype=tf.float32, shape=[None,1], name="mixparam")          # Build pi coefficient framework
    out_sigma = tf.placeholder(dtype=tf.float32, shape=[None,2], name="mixparam")       # Build sigma coefficient framework
    out_mu = tf.placeholder(dtype=tf.float32, shape=[None,2], name="mixparam")          # Build mu coefficient framework

    output = tf.reshape(output, [-1, (2 * 1 * 2) + 1])      # Set to (1,5) form

    out_pi, out_sigma, out_mu = tf.split(output, num_or_size_splits = [1,2,2], axis=-1)     # Split the first one to pi, second and third one to sigma, and last two to mu

    max_pi = tf.reduce_max(out_pi, 1, keep_dims=True)
    out_pi = tf.subtract(out_pi, max_pi)

    out_pi = tf.exp(out_pi)

    normalize_pi = tf.reciprocal(tf.reduce_sum(out_pi, 1, keep_dims=True))     # Normalize pi (actually is softmax calculation above until now, see http://blog.otoro.net/2015/11/24/mixture-density-networks-with-tensorflow/)
    out_pi = tf.multiply(normalize_pi, out_pi)

    out_sigma = tf.exp(out_sigma)           # Sigma is equal to the exponential function of out_sigma, see http://blog.otoro.net/2015/11/24/mixture-density-networks-with-tensorflow/

    return out_pi, out_sigma, out_mu

def tf_normal(y, mu, sigma):
    oneDivSqrtTwoPI = 1 / np.sqrt(2*np.pi) # normalisation factor for gaussian, not needed.
    result = tf.subtract(y, mu)
    result = tf.multiply(result,tf.reciprocal(sigma))
    result = -tf.square(result)/2           # Some calculation of gaussian distribution term which multiply with pi in the cost function (see http://blog.otoro.net/2015/11/24/mixture-density-networks-with-tensorflow/)
    return tf.multiply(tf.exp(result),tf.reciprocal(sigma))*oneDivSqrtTwoPI

def get_lossfunc(out_pi, out_sigma, out_mu, y):         # see http://blog.otoro.net/2015/11/24/mixture-density-networks-with-tensorflow/
    result = tf_normal(y, out_mu, out_sigma)
    result = tf.multiply(result, out_pi)
    result = tf.reduce_sum(result, 1, keep_dims=True)
    result = -tf.log(result)
    return tf.reduce_mean(result)

def generate_ensemble(out_mu, out_sigma):
    result = np.zeros_like(out_mu) # ixxx
    row_num = out_mu.shape[0]
    col_num = out_mu.shape[1]

    # sample
    for j in range(0, row_num):
        for i in range(0, col_num):
            result[j, i] = np.random.normal(out_mu[j, i], out_sigma[j, i])          # In our case, the mixture is one, so we can directly use mu and sigma to apply in np.random.normal distribution, in order to sample a value. 

    return result



if __name__=='__main__':



    with open(path + 'samples.csv') as csv_file:            # Read the csv file
        reader = csv.reader(csv_file, delimiter=',')
        tix=[]
        tiy=[]
        tox=[]
        toy=[]
        ti=[]
        to=[]
        for row in reader:
            x=row[1]
            tix=np.append(tix,x)
            y=row[2]
            tiy=np.append(tiy,y)
            bjx=row[3]
            tox=np.append(tox,bjx)
            bjy=row[4]
            toy=np.append(toy,bjy)
    training_output=[tix,tiy]
    training_input=[tox,toy]
    training_output= np.array(training_output,dtype=np.float)
    training_input= np.array(training_input,dtype=np.float)

    # Normalization
    train_input_max = training_input.max(axis=1)
    train_input_min = training_input.min(axis=1)
    training_input = (training_input - train_input_min.reshape(-1, 1)) / (train_input_max.reshape(-1, 1) - train_input_min.reshape(-1, 1))
    training_input = training_input.T

    train_output_max = training_output.max(axis=1)
    train_output_min = training_output.min(axis=1)
    training_output = (training_output - train_output_min.reshape(-1, 1)) / (train_output_max.reshape(-1, 1) - train_output_min.reshape(-1, 1))
    training_output = training_output.T


    # ----------Build the network framework----------
    x_ph = tf.placeholder(dtype=tf.float32, shape=[None,2], name="x")           # Build input framework
    y_ph = tf.placeholder(dtype=tf.float32, shape=[None,2], name="y")           # Build output framework

    # ----------- Build a MDN (Tensorflow)----------
    N_MIXES = 1  # number of mixture components
    OUTPUT_DIMS = 2  # number of real-values predicted by each mixture component
    output = neural_network(x_ph)
    out_pi, out_sigma, out_mu = get_mixture_coef(output)
    lossfunc = get_lossfunc(out_pi, out_sigma, out_mu, y_ph)
    train_op = tf.train.AdamOptimizer(learning_rate = 0.001).minimize(lossfunc)

    sess = tf.InteractiveSession()
    sess.run(tf.initialize_all_variables())
    saver = tf.train.Saver()


    # instantiate class and start loop function
    central_instance = Central()
    central_instance.central_execute(saver)






