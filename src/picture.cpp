#include "picture.h"

/*
 * picture constructor
 * @param picture_in vector of the "pixels", 784 long, true if there is a character, false if not
 * @param actual_number_in the actual number value of the picture
 * @return a picture object
 */
Picture::Picture(vector<bool> picture_in, int actual_number_in){
    actual_number = actual_number_in;
    pixel_array = picture_in;
}


