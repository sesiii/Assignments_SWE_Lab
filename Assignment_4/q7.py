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
Y = X.T

Z = np.dot(X,Y)

print("The matrix X is :- \n{}\nThe matrix Y is :-\n{}\nThe matrix Z is :-\n{}\n".format(X,Y,Z))
# cv2.imshow("Image Z", Z)
# cv2.waitKey(0)
# cv2.destroyAllWindows()
