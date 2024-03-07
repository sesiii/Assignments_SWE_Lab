import cv2
import numpy as np
import time
import matplotlib.pyplot as plt

# Define the path to the image
image_path = 'c.png'

# Load the image
img = cv2.imread(image_path)

# Convert the image from BGR to RGB
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

# Compute the grayscale image by taking the mean of the RGB values
X = np.mean(img_rgb, axis=-1).astype(np.uint8)

# Draw a black rectangle on the grayscale image
cv2.rectangle(X, (40, 100), (70, 200), 0, -1)

# Display the grayscale image with the rectangle
cv2.imshow('Grayscale Image with Rectangle', X)
cv2.waitKey(0)
cv2.destroyAllWindows()

