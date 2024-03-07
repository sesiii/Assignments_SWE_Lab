import cv2
import numpy as np

# Read the image
image_path = 'a.PNG'  # Specify the path to your image
img = cv2.imread(image_path)

# Converting the image from BGR to RGB
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

# Calculating the mean of the RGB values for each pixel to get the grayscale image
X = np.mean(img_rgb, axis=-1).astype(np.uint8)

# Create a black rectangle on the image
cv2.rectangle(X, (40, 100), (70, 200), (0), thickness=-1)

# Display the image with the rectangle
cv2.imshow('Grayscale Image with Black Rectangle', X)
cv2.waitKey(0)  # Wait for a key press to close the window
cv2.destroyAllWindows()
