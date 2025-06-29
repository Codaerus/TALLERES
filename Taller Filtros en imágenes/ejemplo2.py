import cv2
import numpy as np  

image = cv2.imread("image.png",0)

image_sobel_x = cv2.Sobel(image,cv2.CV_64F,1,0,3)
image_sobel_x_abs = cv2.convertScaleAbs(image_sobel_x)
image_sobel_y = cv2.Sobel(image,cv2.CV_64F,0,1,3)
image_sobel_y_abs = cv2.convertScaleAbs(image_sobel_y)

image_sobel = cv2.addWeighted(image_sobel_x_abs,1,image_sobel_y_abs,1,0)

cv2.imshow("Imagen",image)
cv2.imshow("Imagen con sobel ",image_sobel)
cv2.waitKey()
