# -*- coding: utf-8 -*-
"""
Created on Wed Mar  2 12:01:27 2022

@author: Anis
"""
"""
Library for plotting the model architecture and the attention maps

"""

#!pip install pydot
#!pip install graphviz
#!pip install opencv-python


import keras,os
from keras.utils.vis_utils import plot_model
import pydot
#import graphviz
#import pydotplus
import matplotlib.pyplot as plt
import numpy as np

import cv2
#keras.utils.vis_utils.pydot = pydotplus


#Plot the model architecture and save the resulting image as a png file
def architecture(model):
    arch = plot_model(model, show_shapes=True, show_layer_names=True, to_file='model.png')
    return arch


#plotting the attention map
#the functions recieves the following inputs
#the model (with 3 outputs)
#the images of a batch represented by x
# the image number (img_n = {0,1,..., batch_size})
#The fold number (fold is a string that takes the following values {fold0, fold1,...,fold4})
def attention_map(model, x, img_n, fold):
    
    #get outputs of the second model (p1, p2, p3 reprensent the outputs of Conv7, Conv11, Conv13 respectively)
    p1, p2, p3 = model.predict(x)
    
    #reshape and extrapolate resulting vectors

    at7 = p1[img_n].reshape(200,200) #
    #at11 = np.resize(p2[0].reshape(16,16),(32, 32)) #
    at11 = p2[img_n].reshape(100,100)  #reshape the image from a 1D vector to a 2D vector
    at11 = cv2.resize(at11, dsize=(200, 200), interpolation=cv2.INTER_NEAREST)  #interpolate the resulting image to fit the original WBC image
    at13 = p3[img_n].reshape(50,50) #
    at13 = cv2.resize(at13, dsize=(200, 200), interpolation=cv2.INTER_NEAREST)
    
    #Ploting attention map

    #fig = figure.plt(figsize = (10, 10))
    #ax = fig.add_subplot(1, 1, 1, projection = )
    

    
    plt.figure(figsize = (10,10))
    plt.subplot(1,3,1)
    plt.imshow(x[img_n])  #plot the original image
    plt.imshow(at7, interpolation='NONE', alpha=0.8)  #plot the attention map of the 7th convolution layer
    #the attention maps is overlayed over the original image with a transparency of 0.8
    #background.paste(img, (0, 0), img)
    plt.title('sortie Attention model conv 7')
    

    plt.subplot(1,3,2)
    plt.imshow(x[img_n])
    plt.imshow(at11, alpha=0.8)
    plt.title('sortie Attention model conv 11')
    
    
    plt.subplot(1,3,3)
    plt.imshow(x[img_n])
    plt.imshow(at13, alpha=0.8)
    plt.title('sortie Attention model conv 13')
    
    #Save the attention maps as a png
    plt.savefig('/home/admin_all/Bureau/Projet_long/model_history/100_epochs/plot_{}.png'.format(fold))
    
    #return p1, p2, p3
    return at7, at11, at13
