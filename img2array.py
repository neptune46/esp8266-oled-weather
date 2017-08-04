import cv2

imgw = 64
imgh = 64
outfile = ".\\src\\image.h"
array_count = 0
array_list = "const char *array_list[] = { "

def img2Array(fileImg):
    # Read a grayscale image
    im_gray = cv2.imread(fileImg, 0)
    # Convert grayscale image to binary
    (thresh, im_bw) = cv2.threshold(im_gray, 128, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)
    # Resize image
    im_resize = cv2.resize(im_bw, (imgw, imgh)) 

    arraystr = "    "
    bitcount = 0
    bytecount = 0
    data = 0

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
                arraystr = arraystr + "{0:#0{1}x}".format(data, 4) + ", "
                data = 0
                bytecount = bytecount + 1
                if bytecount == 16:
                    arraystr = arraystr + "\n" + "    "
                    bytecount = 0
    
    return arraystr

def getArrayName(imgfile):
    name = imgfile.split(".")[-2].split("\\")[-1]
    if name == "":
        return "array_" + array_count
    else:
        return "array_" + name
    
def convert(imgfile):
    array_name = getArrayName(imgfile)
    struct_str = "const char " + array_name + "[] PROGMEM = { \n"
    struct_str = struct_str + img2Array(imgfile)
    struct_str = struct_str + "};\n"
    global array_count
    array_count = array_count + 1
    with open(outfile, "a") as text_file:
        text_file.write("%s" % struct_str)
    global array_list
    array_list = array_list + array_name + ", "
    print "convert image file [" + imgfile + "] done..." 

def writePrefix():
    prefix_str = "#define IMG_WIDTH " + str(imgw) + "\n"
    prefix_str += "#define IMG_HEIGHT " + str(imgh) + "\n"
    with open(outfile, "w") as text_file:
        text_file.write("%s" % prefix_str)

def writeSuffix():
    global array_list
    array_list = array_list + "};\n"
    with open(outfile, "a") as text_file:
        text_file.write("%s" % array_list)

if __name__ == "__main__":
    writePrefix()

    imgfile = "..\\icon\\100.png"
    convert(imgfile)
    imgfile = "..\\icon\\101.png"
    convert(imgfile)
    imgfile = "..\\icon\\102.png"
    convert(imgfile)
    imgfile = "..\\icon\\103.png"
    convert(imgfile)
    imgfile = "..\\icon\\104.png"
    convert(imgfile)

    writeSuffix()