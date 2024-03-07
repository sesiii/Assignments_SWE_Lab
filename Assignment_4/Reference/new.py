import numpy as np
import matplotlib.pyplot as plt
import cv2

img = cv2.imread('image.jpg', cv2.IMREAD_COLOR)

cv2.imshow('image', img)


cv2.waitKey(0)

cv2.destroyAllWindows()