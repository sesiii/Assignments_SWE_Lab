import cv2
import numpy as np
import time

# Define the path to the image
image_path = 'c.png'

# Load the image
img = cv2.imread(image_path)
print("Shape of original image array: ", img.shape)
print("Data type of original image array: ", img.dtype)

# Convert the image from BGR to RGB
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

# Compute the grayscale image by taking the mean of the RGB values
X = np.mean(img_rgb, axis=-1).astype(np.uint8)
print("Shape of grayscale image array (X): ", X.shape)
print("Data type of grayscale image array (X): ", X.dtype)

# Compute the transpose of X and the dot product of X and its transpose using NumPy
start_time = time.time()
Y = X.T
Z = np.dot(X, Y)
end_time = time.time()
print("Computation time with NumPy: ", end_time - start_time)

# Convert the numpy array X to a list
X_list = X.tolist()
print(X_list)

# Compute the transpose of X_list and the dot product of X_list and its transpose without using NumPy
start_time = time.time()
Y_list = list(map(list, zip(*X_list)))
print("Shape of transpose of X_list (Y_list): ", len(Y_list), "x", len(Y_list[0]))
print(Y_list)

Z_list = [[sum(a*b for a, b in zip(X_row, Y_col)) for Y_col in zip(*Y_list)] for X_row in X_list]
end_time = time.time()
print(Z_list)
print("Computation time without NumPy: ", end_time - start_time)