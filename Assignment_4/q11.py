import cv2
import numpy as np

# Define the path to the image
image_path = 'c.png'

# Load the image
img = cv2.imread(image_path)

# Convert the image from BGR to RGB
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

# Compute the grayscale image by taking the mean of the RGB values
X = np.mean(img_rgb, axis=-1).astype(np.uint8)

# Binarize the grayscale image with different thresholds
_, Z50 = cv2.threshold(X, 50, 255, cv2.THRESH_BINARY)
_, Z70 = cv2.threshold(X, 70, 255, cv2.THRESH_BINARY)
_, Z100 = cv2.threshold(X, 100, 255, cv2.THRESH_BINARY)
_, Z150 = cv2.threshold(X, 150, 255, cv2.THRESH_BINARY)

cv2.imshow('Binarized Image Z150', Z150)
cv2.imshow('Binarized Image Z100', Z100)
cv2.imshow('Binarized Image Z70', Z70)
cv2.imshow('Binarized Image Z50', Z50)
cv2.imshow('Original Grayscale Image', X)

cv2.waitKey(0)  # Wait for a key press to close the windows
cv2.destroyAllWindows()