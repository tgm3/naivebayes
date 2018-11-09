#ifndef NAIVEBAYES_HELPER_H
#define NAIVEBAYES_HELPER_H

#include <vector>
#include <string>
#include <iostream>
#include "picture.h"
#include <cmath>
#include "model.h"

using namespace std;

vector<Picture> MakePictureVector(string image_file, string label_file);
vector<vector<vector<int>>> FrequencyOfCharacters(vector<Picture> pictures);
vector<vector<vector<double>>> ProbabilityOfBeingACharacter(vector<vector<vector<int>>> character_frequencies);
vector<int> OccurrencesOfNumber(vector<vector<vector<int>>> picture_frequencies);
int GuessNumber(Picture picture, Model algorithm);

#endif //NAIVEBAYES_HELPER_H
