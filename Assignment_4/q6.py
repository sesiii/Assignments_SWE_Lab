import cv2
import numpy as np

# Define the path to the image
image_path = 'c.png'

# Load the image
img = cv2.imread(image_path)

# Convert the image from BGR to RGB
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

# Compute the grayscale image by taking the mean of the RGB values
X= np.mean(img_rgb, axis=-1).astype(np.uint8)

# Display the grayscale image
cv2.imshow('Grayscale Image', X)

# Wait for a key press
cv2.waitKey(0)

# Close all OpenCV windows
cv2.destroyAllWindows()