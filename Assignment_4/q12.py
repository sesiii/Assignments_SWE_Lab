import cv2
import numpy as np

# Define the path to the image
image_path = 'c.png'

# Load the image
img = cv2.imread(image_path)

# Define the filter
kernel = np.array([[-1, -1, -1], [0,0 , 0], [1, 1, 1]])

# Apply the filter to the image
filtered_img = cv2.filter2D(img, -1, kernel)

# Display the filtered image
cv2.imshow('Filtered Image', filtered_img)
cv2.waitKey(0)
cv2.destroyAllWindows()