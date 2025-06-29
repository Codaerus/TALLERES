import cv2
import numpy as np  

image = cv2.imread("image.png",0)
kernel = np.ones((5,5),np.float32)
w,h = kernel.shape
kernel = kernel*(1/(w*h))

image_convoluted = cv2.filter2D(image,-1,kernel)

cv2.imshow("Imagen",image)
cv2.imshow("Imagen con la convolución ",image_convoluted)
cv2.waitKey()
