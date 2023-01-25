# -*- coding: utf-8 -*-
"""
Created on Thu Mar 10 11:33:45 2022

@author: Anis
"""

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


#Blood smear Dataset


#load the dataset

#Specify the fold we are working on
fold = 'fold0'

batch_size = 5

train_generator,validation_generator = load_data(batch_size = batch_size,  fold = fold)

#load the model

m,_ = VGG(400,400,5)




#Training


m.compile(loss='sparse_categorical_crossentropy',
                optimizer=tf.keras.optimizers.Adam(learning_rate=0.00001),
                metrics=['acc']) 

#Save the best weights according to the validation accuracy

filepath = '/home/admin/Bureau/poids/my_best_model_one_attention_map{}.hdf5'.format(fold)  #path for saving the weights
checkpoint = ModelCheckpoint(filepath=filepath, 
                             monitor='val_acc',
                             verbose=1, 
                             save_best_only=True,
                             save_weights_only = True,
                             mode='max')

#save model performance in a csv file
filename='/home/admin/Bureau/log.csv'
history_logger=tf.keras.callbacks.CSVLogger(filename, separator=",", append=True)

#Train the model
history = m.fit_generator(
      train_generator,
      steps_per_epoch = train_generator.samples // batch_size,
      validation_data = validation_generator, 
      validation_steps = validation_generator.samples // batch_size,
      epochs = 50, callbacks=[checkpoint, history_logger])

#load the best weights
#m.load_weights('/home/admin_all/Bureau/Projet_long/weights/my_best_model_{}.hdf5'.format(fold))

#set a second model with Conv7, Conv11 and Conv13 as outputs to see the impact of the attention
#m2 = Model(m.layers[0].input , [m.layers[50].output, m.layers[51].output, m.layers[52].output])


#load images and theire labels of a certain batch
#x_batch, y_batch = next(train_generator)

#print(x_batch.shape)


#plot the attention maps
#attention_map(m2, x_batch, 0)




