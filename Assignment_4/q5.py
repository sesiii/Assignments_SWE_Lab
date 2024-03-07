import cv2
import numpy as np

# Define the image file path
img_file_path = 'c.png'

# Load the image in color (BGR format)
loaded_img = cv2.imread(img_file_path, cv2.IMREAD_COLOR)

# Show the loaded image in a window titled "Image Display"
cv2.imshow('Image Display', loaded_img)

# Pause the script until a key is pressed
cv2.waitKey(0)

# Close all windows created by OpenCV
cv2.destroyAllWindows()

# Convert the image from BGR to RGB format
img_in_rgb = cv2.cvtColor(loaded_img, cv2.COLOR_BGR2RGB)

# Save the RGB image in a 3D numpy array
img_array = img_in_rgb