import cv2
import numpy as np

# Read the image
image_path = 'b.png'  # Specify the path to your image
img = cv2.imread(image_path)

# Define the filter (kernel)
kernel = np.array([[-1, -1, -1],
                   [ 0,  1,  0],
                   [ 1,  1,  1]])

# Apply the filter to the image using cv2.filter2D
filtered_img = cv2.filter2D(img, -1, kernel)

# Display the original and filtered images
cv2.imshow('Original Image', img)
cv2.imshow('Filtered Image', filtered_img)
cv2.waitKey(0)
cv2.destroyAllWindows()
