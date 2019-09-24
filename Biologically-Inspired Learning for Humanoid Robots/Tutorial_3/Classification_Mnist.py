import numpy as np
import matplotlib.pyplot as plt
import keras
from keras.datasets import mnist
from collections import deque

#Team A 1: Adon Yazigi, 2: Shengzhi Wang, 3:Fan Wu, 4: Helene Obert

## Input the MNIST Data from keras
(train_images, train_labels), (test_images, test_labels) = mnist.load_data()
train_images = train_images[:60000]         # Use 60000 images (i.e. all of them) to training
train_labels = train_labels[:60000]

test_images = test_images[:10000]           # Use 10000 images (i.e. all of them) to test
test_labels = test_labels[:10000]

train_images = train_images.reshape((60000, 28 * 28))           # Reshape the training data
train_images = train_images.astype('float32') / 255             # Normalize the pixel values in the range from 0 to 1
train_images = train_images.T
test_images = test_images.reshape((10000, 28 * 28))             # Reshape the test data
test_images = test_images.astype('float32') / 255               # Normalize the pixel values in the range from 0 to 1
test_images = test_images.T

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
        grad = a[L]

        grad[y] -= 1
        grad = grad
                
        dCdz = { L: grad }
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
        error_deque = deque(maxlen=60000)
        error_plot = []

        for i in range(iter_num):
            sample_num = i % 60000
            x_img = x[:, sample_num]
            x_img = x_img.reshape(-1, 1)
            y_label = y[sample_num]
            dW, db = self.bp(x_img, y_label)  
            for l in range(1, self.L+1):
                self.W[l] = self.W[l] - l_rate*dW[l]
                self.b[l] = self.b[l] - l_rate*db[l]
            error = cross_entropy(x_img, y_label, self.output)
            error_deque.append(error)
            error_plot.append(np.mean(error_deque))
            if i % 100 == 0:
                print('\rIteration {}\tAverage Error: {:.2f}'.format(i, np.mean(error_deque))) 
        return error_plot

    def predict(self, x, y):
        sample_num = 10000
        y_label = []
        correct_num = 0
        for i in range(sample_num):
            x_img = x[:, i]
            x_img = x_img.reshape(-1, 1)
            a, _ = self.fp(x_img)
            a_out = a[self.L]
            y_pr = a_out.argmax(axis=0)
            if y_pr == y[i]:
                correct_num += 1
            else:
                pass
        return (correct_num/sample_num)



NN = NNet((784,100,100,10), sigmoid, d_sigmoid, softmax, d_indentity)       # The neural network is with 4 layers. The first input layer consists of 784 nodes, the first and second hidden layers consist of 100 nodes, and the output layer consists of 10 nodes. 
error_plot = NN.gd_learn(120000, 0.02, train_images, train_labels)          # 1. 150+150 hidden neurons, 120000 iterations, 0.02>>>>> 92.27%; 2. 100+100 hidden neurons, 120000 iterations, 0.02>>>>> 92.44% 3. 100+100 hidden neurons, 200000 iterations, 0.02>>>>> 93.00% 4. 100+100 hidden neurons, 300000 iterations, 0.02>>>>> 93.47%
accuracy = NN.predict(test_images, test_labels)
print('\rAccuracy: {:.2f}%'.format(accuracy * 100)) 

## Plot error 
fig = plt.figure()
ax = fig.add_subplot(111)
plt.plot(np.arange(1, len(error_plot)+1), error_plot)
plt.title('Training Error')
plt.ylabel('Error')
plt.xlabel('Training Iteration')
plt.show()