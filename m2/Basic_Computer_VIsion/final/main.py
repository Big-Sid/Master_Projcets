import cv2 as cv
import numpy as np
import sys
from OpenCV_Image_Utilities import *       # Provides routine overlay_uchar_image()
import time

# - KeyPoints
trackbarKeyPoints_name = "KeyPoints"
trackbarKeyPoints_max_value = 1  # Trackbar max value
trackbarKeyPoints_value = 0  # Trackbar value
trackbarKeyPoints_default_value = 0

# - Matches
trackbarMatches_name = "Matches"
trackbarMatches_max_value = 1  # Trackbar max value
trackbarMatches_value = 0  # Trackbar value
trackbarMatches_default_value = 0

# - Opacity
trackbarOpacity_name = "Opacity"
trackbarOpacity_max_value = 10  # Trackbar max value
trackbarOpacity_min_value = 0  # Trackbar min value
trackbarOpacity_default_value = 5
trackbarOpacity_value = 5  # Trackbar value

# - Camera video stream
isGrayCamera = False

def overlay_image(base, map_target, out):

    '''
    nrows, ncols, nchannels = np.shape(base)
    out = base.copy()
    for j in range(nrows):
        for i in range(ncols):
            if map_target[j,i][0]>0:
                out[j,i][0] = map_target[j,i][0]
                out[j,i][1] = map_target[j,i][1]
                out[j,i][2] = map_target[j,i][2]
    return out
    '''
    dst = cv.addWeighted(base,0.7, map_target,Opacity,0)
    return dst

def create_GUI():
    global window_out_name
    global window_settings_name
    window_name_prefix = 'OpenCV Demo |  Marker-based augmented reality > '


    #For Window
    window_out_name = window_name_prefix + "Demo"
    cv.namedWindow(window_out_name, cv.WINDOW_AUTOSIZE)

    #For Setting
    window_settings_name = window_name_prefix + 'Settings'
    cv.namedWindow(window_settings_name, cv.WINDOW_AUTOSIZE)

    # Create trackbars
    # - for Opacity Value
    cv.createTrackbar(trackbarOpacity_name, window_settings_name, 0,
                      trackbarOpacity_max_value, process_display_callback)
    cv.setTrackbarMin(trackbarOpacity_name, window_settings_name,
                      trackbarOpacity_min_value)

    # - for Keypoints
    cv.createTrackbar(trackbarKeyPoints_name, window_settings_name, 0,
                      trackbarKeyPoints_max_value, process_display_callback)

    # - for Matches
    cv.createTrackbar(trackbarMatches_name, window_settings_name, 0,
                      trackbarMatches_max_value, process_display_callback)


    # Set trackbar default positions
    # - for Opacity Value
    trackbarOpacity_value =trackbarOpacity_default_value
    cv.setTrackbarPos(trackbarOpacity_name, window_settings_name,
                      trackbarOpacity_value)
    # - for Keypoints
    trackbarKeyPoints_value =trackbarKeyPoints_default_value
    cv.setTrackbarPos(trackbarKeyPoints_name, window_settings_name,
                      trackbarKeyPoints_value)

    # - for Matches
    trackbarMatches_value =trackbarMatches_default_value
    cv.setTrackbarPos(trackbarMatches_name, window_settings_name,
                      trackbarMatches_value)

def initialize_stream():
    global cap
    global frame, frame_overlay, keypoint_frame_overlay
    global kp_image1
    global isGrayCamera
    global img1
    global kp1
    global des1
    global surf,akaze
    img1 = cv.imread("Phone_3.jpeg")  # Registered Image
    img1 = cv.resize(img1,(1280,720))
    surf = cv.xfeatures2d.SURF_create()
    sift = cv.xfeatures2d.SIFT_create()
    akaze = cv.AKAZE_create()

    kp1, des1 = akaze.detectAndCompute(img1, None)
    '''
        time_s2 = time.time()
        kp_sift , des_sift = sift.detectAndCompute(img1, None)
        time_t2 = time.time()
        print("SIFT took {:.5f}s".format(time_t2 - time_s2))

        time_s3 = time.time()
        kp_akaze, des_akaze = akaze.detectAndCompute(img1, None)
        time_t3 = time.time()
        print("AKAZE took {:.5f}s".format(time_t3-time_s3))
    '''

    kp_image1 = cv.drawKeypoints(img1, kp1, None,None,flags=cv.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
    # Open default camera
    cap = cv.VideoCapture(0)
    # Check if camera opening is successful
    if not cap.isOpened():
        sys.exit("! Cannot open default camera")
    # Get camera properties and initialize various variables
    # - Get frame dimensionsk
    ncols = (int)(cap.get(cv.CAP_PROP_FRAME_WIDTH))    #1280
    nrows = (int)(cap.get(cv.CAP_PROP_FRAME_HEIGHT))   #720
    # - Check for color camera
    status, frame = cap.read()  # Get frame
    if not status:
        sys.exit("! Cannot grab frame from default camera")
    if frame.ndim == 1:
        isGrayCamera = True
    else:
        isGrayCamera = False
    frame_overlay = np.empty((nrows, ncols, 3), dtype="uint8") # frame_overlay = (1280, 720, 3) augmented frame overlay
    keypoint_frame_overlay = np.empty((nrows, ncols, 3), dtype="uint8") #keypoints frame overlay
    matches_frame_overlay =  np.empty((nrows, ncols, 3), dtype="uint8") # matches frame overlay

def grab_preprocess():
    global frame, the_frame
    global kp_image2
    global des2
    global H
    global matches
    global img_obj
    # Get a new frame from camera
    status, frame = cap.read() #frame
    #SIFT
    #sift = cv.xfeatures2d.SIFT_create()
    the_frame = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
'''
    matcher = cv.BFMatcher()
    raw_matches = matcher.knnMatch(des1, des2, k=2)
    good_matches = []
    for m1, m2 in raw_matches:
        if m1.distance < ratio * m2.distance:
            good_matches.append([m1])

    if len(good_matches) > 4:
        ptsA = np.float32([kp1[m[0].queryIdx].pt for m in good_matches]).reshape(-1, 1, 2)
        ptsB = np.float32([kp2[m[0].trainIdx].pt for m in good_matches]).reshape(-1, 1, 2)
        ransacReprojThreshold = 5
        H, status = cv.findHomography(ptsA, ptsB, cv.RANSAC,ransacReprojThreshold)

    #matches = cv.drawMatchesKnn(img1, kp1, frame, kp2, good_matches, None, flags=2)
'''

def process_display():
    global im2, frame_overlay
    ratio = 0.7
    kp2, des2 = akaze.detectAndCompute(frame, None)
    matcher = cv.BFMatcher()
    raw_matches = matcher.knnMatch(des1, des2, k=2)
    good_matches = []
    for m1, m2 in raw_matches:
        if m1.distance < ratio * m2.distance:
            good_matches.append([m1])

    if key_1 == 1:
        kp_image2 = cv.drawKeypoints(frame, kp2, None,None,flags=cv.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
        hmerge = np.hstack((kp_image1,kp_image2 ))
        cv.imshow(window_out_name,hmerge)

    elif matches_1 == 1:
        matches = cv.drawMatchesKnn(img1, kp1, frame, kp2, good_matches, None, flags=2)
        cv.imshow(window_out_name,matches)
    else:
        if len(good_matches) > 4:
            ptsA = np.float32([kp1[m[0].queryIdx].pt for m in good_matches]).reshape(-1, 1, 2)
            ptsB = np.float32([kp2[m[0].trainIdx].pt for m in good_matches]).reshape(-1, 1, 2)
            ransacReprojThreshold = 5
            H, status = cv.findHomography(ptsA, ptsB, cv.RANSAC, ransacReprojThreshold)
            imgOut = cv.warpPerspective(img1, H, (frame.shape[1], frame.shape[0]))
            frame_overlay = overlay_image(frame, imgOut,frame_overlay)
            cv.imshow(window_out_name, frame_overlay)

def process_display_callback(value):
    global Opacity
    global key_1
    global matches_1
    global kp_image1
    # Get trackbars positions
    trackbarOpacity_value = cv.getTrackbarPos(trackbarOpacity_name, window_settings_name)
    trackbarKeyPoints_value = cv.getTrackbarPos(trackbarKeyPoints_name, window_settings_name)
    trackbarMatches_value = cv.getTrackbarPos(trackbarMatches_name, window_settings_name)

    # Set hyperparameter values from trackbars
    # - Opacity
    Opacity = (float)(trackbarOpacity_value/10)
    key_1 = trackbarKeyPoints_value
    matches_1 = trackbarMatches_value
    process_display()

def application():
    # Open camera & Get its features
    initialize_stream()
    # Grab & preprocess frame
    grab_preprocess()
    # GUI creation
    create_GUI()
    # Invoke callback routine to initialize and process
    process_display_callback(trackbarOpacity_value)
    # Process video stream
    while True:
        # Grab & preprocess frame
        grab_preprocess()
        # Processing & Visualization
        process_display()
        # Listen to next event
        if cv.waitKey(5) >= 0:
            break
    # Release camera
    cap.release()
    # Destroy windows
    cv.destroyAllWindows()


# Run application
application()