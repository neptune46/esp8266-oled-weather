import cv2

imgw = 64
imgh = 64

# Read a grayscale image
im_gray = cv2.imread('100.png', 0)

# Convert grayscale image to binary
(thresh, im_bw) = cv2.threshold(im_gray, 128, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)

# Resize image
im_resize = cv2.resize(im_bw, (imgw, imgh)) 

cv2.imshow("resize", im_resize)
cv2.waitKey(0)

# Save to disk
cv2.imwrite('bw_image.png', im_resize)

outstr = ""
bitcount = 0
bytecount = 0
data = 0

with open("array.txt", "w") as text_file:
    for i in range(imgh):
        for j in range(imgw):
            if im_resize[i][j] == 255:
                val = 0
            else:
                val = 1
            data = data | val << bitcount
            bitcount = bitcount + 1
            if bitcount == 8:
                bitcount = 0
                outstr = outstr + "{0:#0{1}x}".format(data, 4) + ", "
                data = 0
                bytecount = bytecount + 1
                if bytecount == 16:
                    outstr = outstr + "\n"
                    bytecount = 0     
    text_file.write("%s" % outstr)