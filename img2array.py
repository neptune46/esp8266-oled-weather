import os
import cv2

class Converter():

    def __init__(self, imgw, imgh, outfile, imgdir, counter, arraylist, arraytype):
        self._imgw = imgw
        self._imgh = imgh
        self._outfile = outfile
        self._img_dir = imgdir
        self._array_count = counter
        self._array_list = arraylist
        self._array_type = arraytype

    def img2Array(self, fileImg):
        # Read a grayscale image
        im_gray = cv2.imread(fileImg, 0)
        # Convert grayscale image to binary
        (thresh, im_bw) = cv2.threshold(im_gray, 128, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)
        # Resize image
        im_resize = cv2.resize(im_bw, (self._imgw, self._imgh)) 

        arraystr = "    "
        bitcount = 0
        bytecount = 0
        data = 0

        for i in range(self._imgh):
            for j in range(self._imgw):
                if im_resize[i][j] == 255:
                    val = 1
                else:
                    val = 0
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

    def getArrayName(self, imgfile):
        name = imgfile.split(".")[-2].split("\\")[-1]
        if name == "":
            return "array_" + self._array_count
        else:
            return "array_" + name

    def convertImg(self, imgfile):
        array_name = self.getArrayName(imgfile)
        struct_str = "const char " + array_name + "[] PROGMEM = { \n"
        struct_str = struct_str + self.img2Array(imgfile)
        struct_str = struct_str + "};\n"
        self._array_count = self._array_count + 1
        with open(self._outfile, "a") as text_file:
            text_file.write("%s" % struct_str)
        self._array_list = self._array_list + array_name + ", \n    "
        print "convert image file [" + imgfile + "] done..." 

    def writePrefix(self):
        prefix_str = "#define " + self._array_type + "_WIDTH " + str(self._imgw) + "\n"
        prefix_str += "#define " + self._array_type + "_HEIGHT " + str(self._imgh) + "\n"
        with open(self._outfile, "w") as text_file:
            text_file.write("%s" % prefix_str)

    def writeSuffix(self):
        array_name = self._array_type.lower() + "_list"
        array_num = self._array_type.lower() + "_num"
        self._array_list = self._array_list + "};\n"
        self._array_list = self._array_list + "int " + array_num + " = (sizeof(" + array_name + ") / sizeof(char *));\n"
        with open(self._outfile, "a") as text_file:
            text_file.write("%s" % self._array_list)

    def executeConvertion(self):
        print "start conversion ..."
        self.writePrefix()
        for imgfile in os.listdir(self._img_dir):
            self.convertImg(self._img_dir + "\\" + imgfile)
        self.writeSuffix()
        print "conversion done!\nconverted " + str(self._array_count) + " files"

def generateArray(imgw, imgh, outfile, imgdir, counter, arraylist, arraytype):
    cvt = Converter(imgw, imgh, outfile, imgdir, counter, arraylist, arraytype)
    cvt.executeConvertion()

if __name__ == "__main__":
    # generate weather icons from image
    outfile = ".\\src\\icon.h"
    img_dir = os.path.abspath(".") + "\\icon"
    array_list = "const char *icon_list[] = { \n    "
    generateArray(64, 64, outfile, img_dir, 0, array_list, "ICON")
    
    # generate chinese characters from image
    outfile = ".\\src\\character.h"
    img_dir = os.path.abspath(".") + "\\character"
    array_list = "const char *character_list[] = { \n    "
    generateArray(64, 32, outfile, img_dir, 0, array_list, "CHARACTER")