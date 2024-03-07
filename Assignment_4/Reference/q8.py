import cv2
import numpy as np
import time

# Read the image
image_path = 'a.PNG'  # Specify the path to your image
img = cv2.imread(image_path)

# Converting the image from BGR to RGB
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

# Calculating the mean of the RGB values for each pixel to get the grayscale image
X = np.mean(img_rgb, axis=-1).astype(np.uint8)

# Storing the start time
start_time = time.time()

# Calculating Z the numpy way

Y = X.T

Z = np.dot(X,Y)

# End of numpy time
numpy_time = time.time()

# Priting the time required to calcute Z using numpy
print("The time to perform the multiplication using numpy is :- ", numpy_time - start_time, "s")

# Converting the nunmpy array X to a list X_list
X_list = X.tolist()

# Start time for matrix style multiplication
matrix_time = time.time()

Y_list = [list(row) for row in zip(*X_list)]

# Perform matrix multiplication between X_list and Y_list to get Z_list
# Initialize Z_list with the appropriate dimensions filled with zeros
Z_list = [[0 for _ in range(len(X_list))] for _ in range(len(X_list))]


# Populate Z_list with the results of the matrix multiplication
for i in range(len(X_list)):
    for j in range(len(X_list)):
        for k in range(len(Y_list[0])):
            Z_list[i][j] += X_list[i][k] * Y_list[k][j]

# End time for matrix style multiplication
end_time = time.time()

# Printing the caluclation time
print("The time taken ot multiply normally is :- ", end_time - matrix_time, "s")