#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Apr 20 17:58:35 2022

@author: admin
"""
#ploting maps
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from keras import regularizers, optimizers
from keras.layers import Dense, Dropout, Input
from keras.models import Sequential, load_model
from keras.callbacks import ModelCheckpoint
from keras.datasets import boston_housing
from keras.losses import MeanSquaredError

import keras,os
from keras.layers import Dense, Conv2D, MaxPool2D , Flatten
from keras.preprocessing.image import ImageDataGenerator
import numpy as np
import tensorflow as tf  

import matplotlib.pyplot as plt
from tensorflow.keras.layers import Input, Conv2D, Dense, Flatten, Dropout
from tensorflow.keras.layers import GlobalMaxPooling2D, MaxPooling2D
from tensorflow.keras.layers import BatchNormalization
from tensorflow.keras.models import Model

from data import *
#from VGG_model import *
from Plots_2 import *
#from train1 import *
from VGG_model_2 import *


import matplotlib.cm as cm
from IPython.display import Image, display

fold = 'fold0'

batch_size = 5

train_generator,validation_generator = load_data(batch_size = batch_size,  fold = fold)

#load the model

m,p1 = VGG(400,400,5)

m.load_weights('/home/admin/Bureau/poids/my_best_model_one_attention_mapfold0.hdf5'.format(fold))
m2 = Model(m.layers[0].input , [p1])
for i in range(0,1000):
    x_batch, y_batch = next(train_generator)
    score1 = m2.predict(x_batch)
    predicted_class = tf.argmax(m.predict(x_batch))
    for j in range(0,5):
        if (int(y_batch[j]) == predicted_class[j].numpy()):
            reshape_score1 = score1[j,...].reshape(400,400)
            #reshape_score2 = score2[j,...].reshape(200,200)
            #reshape_score3 = score3[j,...].reshape(100,100)
            path = "/media/admin/Données/predicted/well/"+str(int(y_batch[j]))+"predictedas"+str(i)+str(j)+str(predicted_class[j].numpy())
            heatmap1 = cv2.resize(reshape_score1,(400,400))
            #heatmap2 = cv2.resize(reshape_score2,(400,400))
            #heatmap3 = cv2.resize(reshape_score3,(400,400))
            original = x_batch[j,...]

            fig1 = plt.figure(figsize = (10,10))
            plt.imshow(original)  #plot the original image
            plt.imshow(heatmap1, alpha=0.8)
            plt.colorbar()
            fig1.savefig(path+'heatmap1.jpg')
            '''fig2 = plt.figure(figsize = (10,10))
            plt.imshow(original)  #plot the original image
            plt.imshow(heatmap2*1000, alpha=0.8)
            plt.colorbar()
            fig2.savefig(path+'heatmap2.jpg')
            fig3 = plt.figure(figsize = (10,10))
            plt.imshow(original)  #plot the original image
            plt.imshow(heatmap3*1000, alpha=0.8)
            plt.colorbar()
            fig3.savefig(path+'heatmap3.jpg')'''

        else :
            path = "/media/admin/Données/predicted/bad/"+str(int(y_batch[j]))+"predictedas"+str(i)+str(j)+str(predicted_class[j].numpy())
            reshape_score1 = score1[j,...].reshape(400,400)
            #reshape_score2 = score2[j,...].reshape(200,200)
            #reshape_score3 = score3[j,...].reshape(100,100)
            heatmap1 = cv2.resize(reshape_score1,(400,400))        
            #heatmap2 = cv2.resize(reshape_score2,(400,400))
            #heatmap3 = cv2.resize(reshape_score3,(400,400))
            original = x_batch[j,...]
        
            fig4 = plt.figure(figsize = (10,10))
            plt.imshow(original)  #plot the original image
            plt.imshow(heatmap1*1000, alpha=0.8)
            plt.colorbar()
            fig4.savefig(path+'heatmap1.jpg')
            '''fig5 = plt.figure(figsize = (10,10))
            plt.imshow(original)  #plot the original image
            plt.imshow(heatmap2*1000, alpha=0.8)
            plt.colorbar()
            fig5.savefig(path+'heatmap2.jpg')
            fig6 = plt.figure(figsize = (10,10))
            plt.imshow(original)  #plot the original image
            plt.imshow(heatmap3*1000, alpha=0.8)
            plt.colorbar()
            fig6.savefig(path+'heatmap3.jpg')'''
        plt.close('all')

