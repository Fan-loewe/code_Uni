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

#Team A 1: Adon Yazigi, 2: Shengzhi Wang, 3:Fan Wu, 4: Helene Obert

## ----------Some central part of the NAO robot---------- ##
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
            lower_red = np.array([0,15,50])#0,70,50
            upper_red = np.array([3,255,255])#10,255,255

            # Threshold the HSV image to get only blue colors
            mask = cv2.inRange(hsv, lower_red, upper_red)  
            mask = cv2.erode(mask, None, iterations=2)
            mask = cv2.dilate(mask, None, iterations=2) 

            # find contours in the mask and initialize the current
            contours,hierarchy = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
                cv2.CHAIN_APPROX_SIMPLE)
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

    def central_execute(self, NN):
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
         
            else:
                pass

            # When it deteced a blob, we use trained neural network to reach the blob. When no blob is detected, the shoulder will go back to home position
            if(float(self.x>0) and float(self.y>0)):
                self.pNamesShoulderL = ["LShoulderPitch", "LShoulderRoll"]
                self.pStiffnessListsShoulderL = [[0.9], [0.9]]
                self.pTimeListsShoulderL = [[1.0], [1.0]]
                self.motionProxy.stiffnessInterpolation(self.pNamesShoulderL, self.pStiffnessListsShoulderL, self.pTimeListsShoulderL)
                test_input=np.array([[self.x],[self.y]])
                test_input = (test_input - train_input_min.reshape(-1, 1)) / (train_input_max.reshape(-1, 1) - train_input_min.reshape(-1, 1))

                joint_angle_prediction = NN.predict(test_input)

                # Denormalization
                joint_angle_prediction = (train_output_max.reshape(-1, 1) - train_output_min.reshape(-1, 1)) * joint_angle_prediction + train_output_min.reshape(-1, 1)
                print(joint_angle_prediction[0], joint_angle_prediction[1])
                

                self.Shoulder_roll_L_moveto(joint_angle_prediction[1])
                self.Shoulder_pitch_L_moveto(joint_angle_prediction[0])

                rospy.sleep(2.0)
            
            else:
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

## ----------Some definitions of output functions and cost functions---------- ##
def indentity(x):
    return x

def d_indentity(x):
    return np.ones(x.shape)

def relu(x):
    return np.maximum(x, np.zeros(x.shape))

def d_relu(x):
    return (x>0).astype(float)

def sigmoid(x):
    return 1/(1+np.exp(-x))

def d_sigmoid(x):
    return sigmoid(x) * (1-sigmoid(x))

#cost MSE
def mse_cost(x_D, y_D, predict_f):
    y_predicted = predict_f(x_D)
    return np.mean(np.power(y_predicted-y_D, 2))

#cost Cross Entropy
def ce_cost(x_arr, y_arr, predict_f):    
    y_eq_0 = (y_arr==0).nonzero()[1]
    y_eq_1 = (y_arr==1).nonzero()[1]
    a = predict_f(x_arr)
    cost = np.sum( -np.log2(a[0][y_eq_1])) + np.sum( -np.log2(1-a[0][y_eq_0]))
    return cost

#cost Cross Entropy2
def cross_entropy(x, y, predict_f):
    """
    x is the training input ((28*28) x 1) = (784, 1)
    y is label (1 x 1)
    	Note that y is not one-hot encoded vector. 
    """
    p = predict_f(x)
    log_likelihood = -np.log(p[y])
    loss = np.sum(log_likelihood)
    return loss

def softmax(x):
    exp_x = np.exp(x - np.max(x, axis=0, keepdims=True))
    return exp_x / np.sum(exp_x, axis=0, keepdims=True)


## ----------Class of Neural Network---------- ##
class NNet:
    """
    Object fields:
        layers = a tuple containing numbers of neurons in each layer, starting from the input layer
        
        L = depth of the NN
        
        act_hid   = activation function for neurons in the hidden layer
        d_act_hid = derivative of the activation function for neurons in the hidden layer
        act_out   = activation function for neuron(s) in the output layer
        d_act_out = derivative of the activation function for neuron(s) in the output layer        
        
        W = dictionary containing the W matrices for each layer. The keys are arranged such that the matrices 
            stored in the dictionary corresponds to the notation form the lecture. Ie, W[1] is the matrix which
            describes the connections between the layer 0 and layer 1. The matrix stored at W[1] is a numpy array
            with dimensions (number of neurons in the layer 1) x (number of neurons in the layer 0)          
        
        b = dictionary containing the b vectors for each layer. The indexing corresponds to the indexing from
            the lecture. See above. Eg, dimensions of b[1] (number of neurons in the layer 1) x  1   
    """
    def __init__(self, layers, act_hid, d_act_hid, act_out, d_act_out):
        self.layers = layers
        self.L = len(layers) - 1
        self.act_hid = act_hid
        self.d_act_hid = d_act_hid        
        self.act_out = act_out
        self.d_act_out = d_act_out        
        self.W, self.b = self.init_Wb()

        
    def init_Wb(self):
        """
        Initialize the matrices W[1],...,W[L] and the vectors b[1],...,b[L] with random numbers from gaussian
        distribution with 0-mean, and 1 variance.
        """
        W, b = {}, {}
        for i in range(1,self.L+1):
            W[i] = np.random.normal(0,1,(self.layers[i],self.layers[i-1]))
            b[i] = np.random.normal(0,1,(self.layers[i],1))
        return W, b
    
    def fp(self, x):
        """
        Forward propagation. Uses the current parameters W, b
        Inputs:
            x = np.array of size self.layers[0] x 1.
        Outputs:
            a = dictionary containing output of each layer of NN. Eg., a[1] should be np.array of size self.layers[1] x 1
                The indexing corresponds to the indexing from the lecture. E.g. a[0]=x because a[0] 

            z = dictionary containing input to each layer of NN. The indexing corresponds to the indexing
                from the lecture. E.g. z[1]=W[1].dot(a[0])+b[1].
        """
        a, z = {}, {}
        a[0] = x
        L = self.L
        for i in range(1,L):
            z[i] = np.dot(self.W[i], a[i-1]) + self.b[i]
            a[i] = self.act_hid(z[i])    
            
        z[L] = self.W[L].dot(a[L-1]) + self.b[L]    
        a[L] = self.act_out(z[L]) 
        return a,z    

    def bp(self, x, y):
        """
        Backpropagation. Uses the current parameters W, b
        Args:
            x = np.array of size self.layers[0] x 1 (contains one input vector from the training set)
            y = np.array of size self.layers[L] x 1 (contains one output vector from the training set)
        Returns:
            dW = dictionary corresponding to W, where each corresponding key contains a matrix of the 
                same size, eg, W[i].shape = dW[i].shape for all i. It contains the partial derivatives
                of the cost function with respect to each entry entry of W.
            db = dictionary corresponding to b, where each corresponding key contains a matrix of the 
                same size, eg, b[i].shape = bW[i].shape for all i. It contains the partial derivatives
                of the cost function with respect to each entry entry of b. 
            
        """
        a,z = self.fp(x)
        L = self.L
                
        dCdz = { L: 2 * (a[L] - y) }
        for l in range(L-1,0,-1):
            dCdz[l] = self.W[l+1].T.dot(dCdz[l+1]) * self.d_act_hid(z[l])
                
        db = {}
        for l in range(1,L+1):
            db[l] = np.sum(dCdz[l], axis=1).reshape((-1,1))
                
        dW = {}
        for l in range(1,L+1):
            dW[l] = dCdz[l].dot(a[l-1].T)
                            
        return dW, db
        
    def output(self, x):
        """
        Provides the output from the last layer of NN.
        """
        a_out = None
        a, _ = self.fp(x)
        a_out = a[self.L]
        return a_out

    def gd_learn(self, iter_num, l_rate, x, y):
        """
        Performs gradient descent learning.
        iter_num = nubmer of interations of GD
        l_rate = learning rate
        x = nparray with the training inputs
        y = nparray with the training outputs
        """
        error_deque = deque(maxlen=x.shape[1])
        error_plot = []

        for i in range(iter_num):
            sample_num = i % x.shape[1]
            x_img = x[:, sample_num]
            x_img = x_img.reshape(-1, 1)
            y_label = y[:, sample_num]
            y_label = y_label.reshape(-1, 1)
            dW, db = self.bp(x_img, y_label)  
            for l in range(1, self.L+1):
                self.W[l] = self.W[l] - l_rate*dW[l]
                self.b[l] = self.b[l] - l_rate*db[l]
            error = mse_cost(x_img, y_label, self.output)
            error_deque.append(error)
            error_plot.append(np.mean(error_deque))
            if i == 0:
                print('----------Training starting----------') 
            elif i == iter_num - 1:
                print('----------Training ended----------')
            else:
                pass 
        
        return error_plot

    def predict(self, x):
        x = x.reshape(-1, 1)
        a, _ = self.fp(x)
        a_out = a[self.L]
        return a_out




## ----------Main part starts from here---------- ##
if __name__=='__main__':


## Read the csv data
    with open('samples.csv') as csv_file:
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

    train_output_max = training_output.max(axis=1)
    train_output_min = training_output.min(axis=1)
    training_output = (training_output - train_output_min.reshape(-1, 1)) / (train_output_max.reshape(-1, 1) - train_output_min.reshape(-1, 1))


    NN = NNet((2,100,100,2), sigmoid, d_sigmoid, indentity, d_indentity)            # The neural network is with 4 layers. The first input layer consists of 784 nodes, the first and second hidden layers consist of 100 nodes, and the output layer consists of 10 nodes. 
    error_plot = NN.gd_learn(10000, 0.02, training_input, training_output)  


    # instantiate class and start loop function
    central_instance = Central()
    central_instance.central_execute(NN)






