import cv2
import numpy as np

# Read the image
image_path = 'a.PNG'  # Specify the path to your image
img = cv2.imread(image_path)

# Converting the image from BGR to RGB
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

# Calculating the mean of the RGB values for each pixel to get the grayscale image
X = np.mean(img_rgb, axis=-1).astype(np.uint8)

Y = X.T

Z = np.dot(X,Y)

print("The matrix X is :- \n{}\nThe matrix Y is :-\n{}\nThe matrix Z is :-\n{}\n".format(X,Y,Z))

