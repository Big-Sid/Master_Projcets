# -*- coding: utf-8 -*-
"""
Created on Wed Mar  2 12:17:05 2022

@author: Anis

This Library is used for loading the dataset using a dataloader
"""

import keras
from tensorflow.keras.preprocessing.image import ImageDataGenerator

#the fuction takes the batch_size and the fold number as inputs

def load_data(batch_size ,  fold):
    train_data_dir = '/media/admin/Données/WBC_data/fold0/training' #the traing dataset directory
    val_data_dir = '/media/admin/Données/WBC_data/fold0/testing' #the testing dataset directory
    #the image dimensions
    img_height = 400
    img_width = 400
    train_datagen = ImageDataGenerator(rescale=1./255,horizontal_flip=(True),vertical_flip=(True),) # normalise the images
    val_datagen = ImageDataGenerator(rescale=1./255)

    train_generator = train_datagen.flow_from_directory(train_data_dir, 
                            target_size=(img_height, img_width),
                            batch_size=batch_size,
                            class_mode='sparse',
                            subset='training') # set as training data

    validation_generator = val_datagen.flow_from_directory( 
        val_data_dir, 
        target_size=(img_height, img_width),
        batch_size=batch_size,
        class_mode='sparse') # set as validation data
    
    
    return train_generator, validation_generator
