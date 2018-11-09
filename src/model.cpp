#include <fstream>
#include "model.h"
#include "helper.h"

/*
 * model constructor
 * @param image_file the path to the file containing the images of the numbers
 * @param label_file the path to the file containing the list of the actual value of the numbers
 * @return an algorithm object
 */
Model::Model(string image_file, string label_file) {
    character_frequencies = FrequencyOfCharacters(MakePictureVector(image_file, label_file));
    chance_of_pixel_being_character = ProbabilityOfBeingACharacter(character_frequencies);
}

//helper functions used by the load a save functions

istream &operator>>(istream &in, Model &model) {
    for (int i = 0; i < model.chance_of_pixel_being_character.size(); i++) {
        for (int j = 0; j < model.chance_of_pixel_being_character[0].size(); j++) {
            for (int k = 0; k < model.chance_of_pixel_being_character[0][0].size(); k++) {
                in >> model.chance_of_pixel_being_character[i][j][k];
            }
        }
    }
    for (int i = 0; i < model.character_frequencies.size(); i++) {
        for (int j = 0; j < model.character_frequencies[0].size(); j++) {
            for (int k = 0; k < model.character_frequencies[0][0].size(); k++) {
                in >> model.character_frequencies[i][j][k];
            }
        }
    }
    return in;
}

ostream &operator<<(ostream &out, const Model &algorithm) {
    for (int i = 0; i < algorithm.chance_of_pixel_being_character.size(); i++) {
        for (int j = 0; j < algorithm.chance_of_pixel_being_character[0].size(); j++) {
            for (int k = 0; k < algorithm.chance_of_pixel_being_character[0][0].size(); k++) {
                out << algorithm.chance_of_pixel_being_character[i][j][k];
            }
        }
    }
    for (int i = 0; i < algorithm.character_frequencies.size(); i++) {
        for (int j = 0; j < algorithm.character_frequencies[0].size(); j++) {
            for (int k = 0; k < algorithm.character_frequencies[0][0].size(); k++) {
                out << algorithm.character_frequencies[i][j][k];
            }
        }
    }
    return out;
}

//functions to load and save the algorithm to a file

void Save(string path, Model algorithm) {
    ofstream stream(path);
    stream << algorithm;
    stream.close();
}

Model Load(string path) {
    Model ex("", "");
    ifstream stream(path);
    stream >> ex;
    stream.close();
    return ex;
}
