#ifndef NAIVEBAYES_ALGORITHM_H
#define NAIVEBAYES_ALGORITHM_H

#include <iostream>
#include <vector>
#include <string>
#include "picture.h"

using namespace std;

class Model{
public:
    vector<vector<vector<int>>> character_frequencies;
    vector<vector<vector<double>>> chance_of_pixel_being_character;
    Model(string image_file, string label_file);
};

istream& operator >> (istream& in, Model& model);
ostream& operator << (ostream& out, const Model& algorithm);
void Save(string path, Model algorithm);
Model Load(string path);

#endif //NAIVEBAYES_ALGORITHM_H
