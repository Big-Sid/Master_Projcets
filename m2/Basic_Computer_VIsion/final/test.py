import cv2 as cv
import numpy as np
import sys

sys.path.append("c:/Users/rougon/Notebooks")
from OpenCV_Image_Utilities import *  # Provides routine overlay_uchar_image()

##
## Global Variables
##

# - Camera video stream
isGrayCamera = False

# - Gaussian smoothing
trackbarStdDeviation_name = "10*StdDev"
trackbarStdDeviation_max_value = 75  # Trackbar max value
trackbarStdDeviation_min_value = 1  # Trackbar min value
trackbarStdDeviation_value = 1  # Trackbar value
trackbarStdDeviation_stepsize = 0.1  # Quantization step
sigma_default_value = 1.0  # Gaussian kernel std deviation default value

# - Contrast map (Sobel gradient kernel)
SobelKernelSize = 3  # Sobel gradient kernel size
useL2NormForContrast = True  # Vector norm for contrast

# - Contrast norm
trackbarContrastNorm_name = "L2 norm"
trackbarContrastNorm_max_value = 1  # Trackbar max value
trackbarContrastNorm_value = 1  # Trackbar value
useL2NormForContrast_default_value = True

# - Upper threshold
trackbarUpperThreshold_name = "Upper"
trackbarUpperThreshold_max_value = 255  # Trackbar max value
trackbarUpperThreshold_value = 128  # Trackbar value
upperThreshold_default_value = 128.0

# - % of upper threshold, defining lower threshold
trackbarUpperThresholdRatio_name = "% Upper"
trackbarUpperThresholdRatio_max_value = 100  # Trackbar max value
trackbarUpperThresholdRatio_value = 100  # Trackbar value
upperThresholdRatio_default_value = 100.0

# Edge map overlay
edge_color = 255
edge_color3 = (0, 0, 255)


##
## IMAGE PIPELINE COMPONENTS
##

#
# Graphical User Interface
#
def create_GUI():
    # Windows
    global window_in_name  # Displays original image
    global window_settings_name  # GUI
    global window_out_name  # Displays edge map
    global window_overlay_name  # Displays edge map onto original image

    window_name_prefix = 'OpenCV Demo |  Edge detection > '

    # Create windows
    # - for edge map overlay
    window_out_name = window_name_prefix + "Detected edges"
    cv.namedWindow(window_out_name, cv.WINDOW_AUTOSIZE)

    # - for hyperparameter settings
    window_settings_name = window_name_prefix + 'Settings'
    cv.namedWindow(window_settings_name, cv.WINDOW_AUTOSIZE)

    # - for edge map overlay
    window_out_name = window_name_prefix + "Detected edges"
    cv.namedWindow(window_out_name, cv.WINDOW_AUTOSIZE)

    # Create trackbars
    # - for Gaussian kernel std deviation
    cv.createTrackbar(trackbarStdDeviation_name, window_settings_name, 0,
                      trackbarStdDeviation_max_value, process_display_callback)
    cv.setTrackbarMin(trackbarStdDeviation_name, window_settings_name,
                      trackbarStdDeviation_min_value)

    # - for upper hysteresis threshold
    cv.createTrackbar(trackbarUpperThreshold_name, window_settings_name, 0,
                      trackbarUpperThreshold_max_value, process_display_callback)

    # - for % of upper threshold defining lower hysteris threshold
    cv.createTrackbar(trackbarUpperThresholdRatio_name, window_settings_name, 0,
                      trackbarUpperThresholdRatio_max_value, process_display_callback)

    # Set trackbar default positions
    # - for Gaussian kernel std deviation
    trackbarStdDeviation_value = (int)(sigma_default_value / trackbarStdDeviation_stepsize)
    cv.setTrackbarPos(trackbarStdDeviation_name, window_settings_name,
                      trackbarStdDeviation_value)

    # - for upper hysteresis threshold
    trackbarUpperThreshold_value = (int)(upperThreshold_default_value)
    cv.setTrackbarPos(trackbarUpperThreshold_name, window_settings_name,
                      trackbarUpperThreshold_value)

    # - for % of upper threshold defining lower hysteris threshold
    trackbarUpperThresholdRatio_value = (int)(upperThresholdRatio_default_value);
    cv.setTrackbarPos(trackbarUpperThresholdRatio_name, window_settings_name,
                      trackbarUpperThresholdRatio_value)


#
# Video stream initialization
#
def initialize_stream():
    global cap
    global frame, frame_overlay
    global isGrayCamera

    # Open default camera
    cap = cv.VideoCapture(0)

    # Check if camera opening is successful
    if not cap.isOpened():
        sys.exit("! Cannot open default camera")

    # Get camera properties and initialize various variables
    # - Get frame dimensions
    ncols = (int)(cap.get(cv.CAP_PROP_FRAME_WIDTH))
    nrows = (int)(cap.get(cv.CAP_PROP_FRAME_WIDTH))

    # - Check for color camera
    status, frame = cap.read()  # Get frame
    if not status:
        sys.exit("! Cannot grab frame from default camera")
    if frame.ndim == 1:
        isGrayCamera = True
    else:
        isGrayCamera = False

    # Create edge map overlay BGR image
    frame_overlay = np.empty((nrows, ncols, 3), dtype="uint8")


#
# Input & Preprocessing
#
def grab_preprocess():
    global frame, the_frame

    # Get a new frame from camera
    status, frame = cap.read()

    # Convert image to graylevel if appropriate
    if isGrayCamera:
        the_frame = frame
    else:
        the_frame = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)


#
# Trackbar callback
#
def process_display_callback(value):
    global sigma  # Gaussian std deviation
    global upperThreshold  # Upper threshold
    global upperThresholdRatio  # % of upper threshold, defining lower threshold
    global lowerThreshold  # Lower threshold

    # Get trackbars positions
    trackbarStdDeviation_value = cv.getTrackbarPos(trackbarStdDeviation_name, window_settings_name)
    trackbarUpperThreshold_value = cv.getTrackbarPos(trackbarUpperThreshold_name, window_settings_name)
    trackbarUpperThresholdRatio_value = cv.getTrackbarPos(trackbarUpperThresholdRatio_name, window_settings_name)

    # Set hyperparameter values from trackbars
    sigma = (float)(trackbarStdDeviation_value) * trackbarStdDeviation_stepsize
    upperThreshold = (float)(trackbarUpperThreshold_value)
    upperThresholdRatio = (float)(trackbarUpperThresholdRatio_value)
    lowerThreshold = 0.01 * upperThreshold * upperThresholdRatio

    # Print hyperparameter summary
    if verbosity == True:
        print("Std Dev =", sigma, "| Ratio =", upperThresholdRatio, "| Upp =", upperThreshold, "| Low =",
              lowerThreshold)

    # Processing & Visualization
    process_display()


#
# Processing & Visualization
#
def process_display():
    global frame_out, frame_overlay

    # Preprocessing > Gaussian filtering
    # - Kernel size is set to 0, and is automatically estimated from sigma
    frame_out = cv.GaussianBlur(the_frame, (0, 0), sigma)

    # Gradient-based edge detection using the pipeline:
    #   Sobel contrast map > Non-Maximum Suppression > Hysteresis Threshold
    frame_out = cv.Canny(frame_out, lowerThreshold, upperThreshold, frame_out,
                         SobelKernelSize, useL2NormForContrast)


    # Overlay edge map on original image
    frame_overlay = overlay_uchar_image(frame, frame_out,
                                        edge_color, edge_color3, frame_overlay)

    # Display result
    cv.imshow(window_out_name, frame_out)


##
## MAIN ROUTINE
##

def application():
    # Open camera & Get its features
    initialize_stream()

    # Grab & preprocess frame
    grab_preprocess()

    # GUI creation
    create_GUI()

    # Invoke callback routine to initialize and process
    process_display_callback(trackbarStdDeviation_value)

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

# - Silent / Verbose mode
verbosity = True

# Run application
application()