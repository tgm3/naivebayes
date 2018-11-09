//
// Created by thana on 3/12/2018.
//

#ifndef NAIVEBAYES_PICTURE2_H
#define NAIVEBAYES_PICTURE2_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Picture{
public:
    vector<bool> pixel_array;
    int actual_number;
    Picture(vector<bool> picture_in, int actual_number_in);
};
#endif //NAIVEBAYES_PICTURE_H

