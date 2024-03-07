import cv2
import numpy as np

# Reading the image
image_path = 'a.png'  # Path to the image

# Reading the image in BGR format ( in color)
img = cv2.imread(image_path, cv2.IMREAD_COLOR)

# Displaying the image in a window called "Image"
cv2.imshow('Image', img)

# Wait till any key is pressed
cv2.waitKey(0)

# Closing all OpenCV windows
cv2.destroyAllWindows()

# Converting the BGR format into RGB format for matplotlib.pylot
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

# Storing the image now in a 3-D numpy array (X)
X = img_rgb

