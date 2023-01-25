# -*- coding: utf-8 -*-
"""
Created on Wed Mar  2 11:14:37 2022

@author: Anis
"""
import keras,os
from keras.models import Sequential
from keras.layers import Dense, Conv2D, MaxPool2D , Flatten
from keras.preprocessing.image import ImageDataGenerator
import numpy as np
import tensorflow as tf  
 
# Display the version
print(tf.__version__)    
 
# other imports
import numpy as np
import matplotlib.pyplot as plt
from tensorflow.keras.layers import Input, Conv2D, Dense, Flatten, Dropout
from tensorflow.keras.layers import GlobalMaxPooling2D, MaxPooling2D
from tensorflow.keras.layers import BatchNormalization
from tensorflow.keras.models import Model

# Define the Keras TensorBoard callback.
from datetime import datetime
import matplotlib.pyplot as plt

#Fonction de compatibilité
def compatibility(L,g):
    size = L.shape[1]
    batch = L.shape[0]
    #L_vector = tf.reshape(L,[batch,size*size,-1]) #(batch,56*56,256)
    L_vector=tf.reshape(L, shape=[tf.shape(L)[0], size*size,L.shape[-1]])
    L_vector_T = tf.transpose(L_vector, (0, 2, 1))
    g_vector = tf.expand_dims(g,axis=2)
    score_vector = tf.reduce_sum(tf.multiply(L_vector_T,g_vector),1) #(batch,56*56)
    score = tf.nn.softmax(score_vector) #(batch,56*56)
    # attention map
    imgs = tf.expand_dims(score,axis=1 , name = 'p')  #(batch,1,56*56)
    #a_score = tf.expand_dims(score,axis=1) #(batch,1,56*56)
    gas = tf.multiply(L_vector_T, imgs)  # (batch,256,56*56)
    ga = tf.reduce_sum(gas,[2])
    print(ga.shape)
    print(imgs.shape)
    return ga,imgs

#our model takes the images dimensions and the number of classes as inputs in our case the inputs are (200,200,5)
def VGG(img_height, img_width,classes):

    input1 = Input(shape=(img_height, img_width, 3))  #the input is an rgb image of (200,200,3)
    #print(input1)
    
    conv1_1 = Conv2D(64, (3,3), padding="same", activation="relu", name = 'conv1_1')(input1)
    conv1_2 = Conv2D(64, (3,3),padding="same", activation="relu", name = 'conv1_2')(conv1_1)
    #model.add(MaxPool2D(pool_size=(2,2),strides=(2,2)))
    
    conv2_1 = Conv2D(filters=128, kernel_size=(3,3), padding="same", activation="relu", name = 'conv2_1')(conv1_2)
    conv2_2 = Conv2D(filters=128, kernel_size=(3,3), padding="same", activation="relu", name = 'conv2_2')(conv2_1)
    #model.add(MaxPool2D(pool_size=(2,2),strides=(2,2)))
    
    conv3_1 = Conv2D(filters=256, kernel_size=(3,3), padding="same", activation="relu", name = 'conv3_1')(conv2_2)
    conv3_2 = Conv2D(filters=256, kernel_size=(3,3), padding="same", activation="relu", name = 'conv3_2')(conv3_1)
    conv3_3 = Conv2D(filters=256, kernel_size=(3,3), padding="same", activation="relu", name = 'conv3_3')(conv3_2)
    pool3 = MaxPool2D(pool_size=(2,2),strides=(2,2), name = 'pool3')(conv3_3)
    
    conv4_1 = Conv2D(filters=512, kernel_size=(3,3), padding="same", activation="relu", name = 'conv4_1')(pool3)
    conv4_2 = Conv2D(filters=512, kernel_size=(3,3), padding="same", activation="relu", name = 'conv4_2')(conv4_1)
    conv4_3 = Conv2D(filters=512, kernel_size=(3,3), padding="same", activation="relu", name = 'conv4_3')(conv4_2)
    pool4 = MaxPool2D(pool_size=(2,2),strides=(2,2), name = 'pool4')(conv4_3)
    
    conv5_1 = Conv2D(filters=512, kernel_size=(3,3), padding="same", activation="relu", name = 'conv5_1')(pool4)
    conv5_2 = Conv2D(filters=512, kernel_size=(3,3), padding="same", activation="relu", name = 'conv5_2')(conv5_1)
    conv5_3 = Conv2D(filters=512, kernel_size=(3,3), padding="same", activation="relu", name   = 'conv5_3')(conv5_2)
    pool5 = MaxPool2D(pool_size=(2,2),strides=(2,2), name = 'pool5')(conv5_3)     
    
    conv6_1 = Conv2D(filters=512, kernel_size=(3,3), padding="same", activation="relu", name = 'conv6_1')(pool5)
    pool6 = MaxPool2D(pool_size=(2,2),strides=(2,2), name = 'pool6')(conv6_1)
    conv7_1 = Conv2D(filters=512, kernel_size=(3,3), padding="same", activation="relu", name = 'conv7_1')(pool6)
    pool7 = MaxPool2D(pool_size=(2,2),strides=(2,2), name = 'pool7')(conv7_1)
    
    f1 = Flatten(name = 'F_1')(pool7)
    d1 = Dense(units=((512)),activation="relu", name = 'D1')(f1)

    
    #compute local feature with global feature
    channel1 = conv3_3.shape[3]  #get the shape of the 7th conv layer
    #channel2 = conv4_3.shape[3]
    #channel3 = conv5_3.shape[3]
  
    g1 = Dense(units=((channel1)), name = 'D2')(d1)  #the last layer (D1) i passed through a dense layer to match the dimensions of the conv layers
    #g2 = Dense(units=((channel2)), name = 'D3')(d1)
    #g3 = Dense(units=((channel3)), name = 'D4')(d1)
  
    #Calculating the compatibility between the global feature vector g1 (with matching dimensions) and the 7th conv
    ga_1,p1 = compatibility(conv3_3, g1) #Calculating the compatibility between the global feature vector g1 (with matching dimensions) and the 7th conv
    #ga_2,p2 = compatibility(conv4_3, g2)
    #ga_3,p3 = compatibility(conv5_3, g3)
  
    #Concatenate the outputs of the attention model
    #ga_total = tf.concat([ga_1, ga_2, ga_3],axis = 1)
    
    #ga_total is then passed into a fully connected layer to classify the images

    logit = Dense(units=((classes)),activation="softmax", name = 'logit')(ga_1)
    
  

    model = Model(input1, logit)

    #model2 = Model(input1, [model.layers[50].output, model.layers[51].output, model.layers[52].output])
    

    return model,p1
