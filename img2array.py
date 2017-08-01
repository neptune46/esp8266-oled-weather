import cv2

# Read a grayscale image
im_gray = cv2.imread('100.png', 0)

# Convert grayscale image to binary
(thresh, im_bw) = cv2.threshold(im_gray, 128, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)

# Save to disk
cv2.imwrite('bw_image.png', im_bw)

with open("array.txt", "w") as text_file:
    for i in range(100):
        text_file.write("\n");
        for j in range(100):
            if im_bw[i][j] == 255:
                val = 0
            else:
                val = 1
            text_file.write("%s, " % val)

print "exit"