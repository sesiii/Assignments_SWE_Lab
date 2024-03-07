import cv2
import numpy as np
import matplotlib.pyplot as plt

# Read the image
image_path = 'a.png'  # Specify the path to your image
img = cv2.imread(image_path)

# Converting the image from BGR to RGB
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

# Calculating the mean of the RGB values for each pixel to get the grayscale image
X = np.mean(img_rgb, axis=-1).astype(np.uint8)

# Calculate the histogram of pixel intensities in the grayscale image
histogram, bin_edges = np.histogram(X, bins=256, range=(0, 256))

# Plot the histogram
plt.figure("Plot")
plt.title("Grayscale Histogram")
plt.xlabel("Pixel Intensity")
plt.ylabel("Pixel Count")
plt.xlim([0, 256])  # Ensure the x-axis covers the full range of pixel values
plt.plot(bin_edges[:-1], histogram)  # Plot the histogram
plt.show()
