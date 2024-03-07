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

# Plot the pixel intensity histogram of the grayscale image
plt.hist(X.ravel(), bins=256, color='gray')
plt.title('Pixel Intensity Histogram')
plt.xlabel('Pixel Intensity')
plt.ylabel('Frequency')
plt.show()