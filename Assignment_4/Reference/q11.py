import cv2
import numpy as np

# Read the image
image_path = 'c.png'  # Specify the path to your image
img = cv2.imread(image_path)

# Converting the image from BGR to RGB
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

# Calculating the mean of the RGB values for each pixel to get the grayscale image
X = np.mean(img_rgb, axis=-1).astype(np.uint8)

# Binarize the image for each threshold
thresholds = [50, 70, 100, 150]
Z50 = (X > thresholds[0]).astype(np.uint8) * 255
Z70 = (X > thresholds[1]).astype(np.uint8) * 255
Z100 = (X > thresholds[2]).astype(np.uint8) * 255
Z150 = (X > thresholds[3]).astype(np.uint8) * 255

# Assuming you want to display these binarized images to verify the operation
# You can use OpenCV's imshow function in a loop for this purpose
cv2.imshow('Original Grayscale Image', X)
cv2.imshow('Binarized Image Z50', Z50)
cv2.imshow('Binarized Image Z70', Z70)
cv2.imshow('Binarized Image Z100', Z100)
cv2.imshow('Binarized Image Z150', Z150)
cv2.waitKey(0)  # Wait for a key press to close the windows
cv2.destroyAllWindows()
