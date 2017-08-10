import os
import cv2

class Converter():

    def __init__(self, imgw, imgh, outfile, imgdir, counter, arraylist, arraytype, inverse):
        self._imgw = imgw
        self._imgh = imgh
        self._outfile = outfile
        self._img_dir = imgdir
        self._array_count = counter
        self._array_list = arraylist
        self._array_type = arraytype
        self._inverse_img = inverse

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
                    val = self._inverse_img
                else:
                    val = not self._inverse_img
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
            return self._array_type.lower() + "_" + self._array_count
        else:
            return self._array_type.lower() + "_" + name

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

def generateArray(imgw, imgh, outfile, imgdir, counter, arraytype, inverse):
    array_name = "const char *" + arraytype.lower() + "_list[] = { \n    "
    cvt = Converter(imgw, imgh, outfile, imgdir, counter, array_name, arraytype, inverse)
    cvt.executeConvertion()

if __name__ == "__main__":
    # generate weather icons array from image
    outfile = ".\\src\\icon.h"
    img_dir = os.path.abspath(".") + "\\icon"
    generateArray(64, 64, outfile, img_dir, 0, "ICON", False)
    
    # generate chinese characters array from image
    outfile = ".\\src\\character.h"
    img_dir = os.path.abspath(".") + "\\character"
    generateArray(64, 32, outfile, img_dir, 0, "CHARACTER", True)

    # generate number array from image
    outfile = ".\\src\\number.h"
    img_dir = os.path.abspath(".") + "\\number"
    generateArray(8, 16, outfile, img_dir, 0, "NUMBER", True)

        # generate symbol array from image
    outfile = ".\\src\\symbol.h"
    img_dir = os.path.abspath(".") + "\\symbol"
    generateArray(16, 16, outfile, img_dir, 0, "SYMBOL", True)