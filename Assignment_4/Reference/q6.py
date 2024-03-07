import cv2
import numpy as np

# Read the image
image_path = 'a.png'  # Specify the path to your image
img = cv2.imread(image_path)

# Converting the image from BGR to RGB
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

# Calculating the mean of the RGB values for each pixel to get the grayscale image
X = np.mean(img_rgb, axis=-1).astype(np.uint8)

# Since OpenCV's imshow expects a 2D array for a grayscale image, we can directly use X
cv2.imshow('Grayscale Image by Mean of RGB Values', X)

# Wait for a key press and then close all OpenCV windows
cv2.waitKey(0)
cv2.destroyAllWindows()
