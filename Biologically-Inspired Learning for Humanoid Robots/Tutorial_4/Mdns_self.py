import keras
import mdn
import numpy as np
import matplotlib.pyplot as plt
from collections import deque
import csv
import os
import random
import tensorflow as tf

os.environ['KMP_DUPLICATE_LIB_OK']='True'

np.random.seed(2)
tf.random.set_random_seed(1)

x_ph = tf.placeholder(dtype=tf.float32, shape=[None,2], name="x")           # Build input framework
y_ph = tf.placeholder(dtype=tf.float32, shape=[None,2], name="y")           # Build output framework

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

    out_pi, out_sigma, out_mu = tf.split(output, num_or_size_splits = [1,2,2], axis=-1)         # Split the first one to pi, second and third one to sigma, and last two to mu

    max_pi = tf.reduce_max(out_pi, 1, keep_dims=True)
    out_pi = tf.subtract(out_pi, max_pi)

    out_pi = tf.exp(out_pi)

    normalize_pi = tf.reciprocal(tf.reduce_sum(out_pi, 1, keep_dims=True))     # Normalize pi (actually is softmax calculation above until now, see http://blog.otoro.net/2015/11/24/mixture-density-networks-with-tensorflow/)
    out_pi = tf.multiply(normalize_pi, out_pi)

    out_sigma = tf.exp(out_sigma)           # Sigma is equal to the exponential function of out_sigma, see http://blog.otoro.net/2015/11/24/mixture-density-networks-with-tensorflow/

    return out_pi, out_sigma, out_mu

def tf_normal(y, mu, sigma):
    oneDivSqrtTwoPI = 1 / np.sqrt(2*np.pi) # normalisation factor for gaussian
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
    result = np.zeros_like(out_mu) 
    row_num = out_mu.shape[0]
    col_num = out_mu.shape[1]

    # sample
    for j in range(0, row_num):
        for i in range(0, col_num):
            result[j, i] = np.random.normal(out_mu[j, i], out_sigma[j, i])          # In our case, the mixture is one, so we can directly use mu and sigma to apply in np.random.normal distribution, in order to sample a value. 

    return result


# ----------- Read the training data ----------
# Read csv file
with open('samples.csv') as csv_file:           # Read the csv file
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

test_input = np.array([[21.40], [63.36]])
test_input = (test_input - train_input_min.reshape(-1, 1)) / (train_input_max.reshape(-1, 1) - train_input_min.reshape(-1, 1))
test_input = test_input.T

test_output_origin = np.array([[-0.236, -0.325, -0.316], [0.256, 0.072, -0.198]])

np.random.seed(2)

mse = []

# ----------- Build a MDN (Tensorflow)----------
N_MIXES = 1  # number of mixture components
OUTPUT_DIMS = 2  # number of real-values predicted by each mixture component
output = neural_network(x_ph)
out_pi, out_sigma, out_mu = get_mixture_coef(output)
lossfunc = get_lossfunc(out_pi, out_sigma, out_mu, y_ph)
train_op = tf.train.AdamOptimizer(learning_rate = 0.001).minimize(lossfunc)
# train_op = tf.train.RMSPropOptimizer(learning_rate = 0.001).minimize(lossfunc)


sess = tf.InteractiveSession()
sess.run(tf.initialize_all_variables())
saver = tf.train.Saver(max_to_keep=1)

NEPOCH = 10000
loss = np.zeros(NEPOCH) # store the training progress here.
for i in range(NEPOCH):
    sess.run(train_op,feed_dict={'x:0': training_input, 'y:0': training_output})            # Train the network by feeding it with inout data and output data
    loss[i] = sess.run(lossfunc, feed_dict={'x:0': training_input, 'y:0': training_output})
    if i == NEPOCH - 1:
        saver.save(sess, 'trained_network/save_net')

plt.figure(figsize=(10, 5))
plt.plot(np.arange(0, NEPOCH,1), loss[0:], 'r-')
plt.show()


# ----------- Test the network (tensorflow)----------
out_pi_test, out_sigma_test, out_mu_test = sess.run(get_mixture_coef(output), feed_dict={'x:0': test_input})
y_samples = generate_ensemble(out_mu_test, out_sigma_test)
y_samples = y_samples.T

# Denormalization
joint_angle_prediction = (train_output_max.reshape(-1, 1) - train_output_min.reshape(-1, 1)) * y_samples + train_output_min.reshape(-1, 1)
print(joint_angle_prediction[0, :], joint_angle_prediction[1, :])
