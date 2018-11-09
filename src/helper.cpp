#include <iostream>
#include <fstream>
#include "helper.h"

using namespace std;

/*
 * @param image_file string containing the path to the file containing the images of the numbers
 * @param label_file string containing the path to the file contating the list of actual numbers
 * @return a vetor of picture objects
 */
vector<Picture> MakePictureVector(string image_file, string label_file) {
    ifstream imagestream;
    ifstream labelstream;
    imagestream.open(image_file, ios::in);
    labelstream.open(label_file, ios::in);


    vector<Picture> all_pictures;

    if (imagestream.is_open() && labelstream.is_open()) {

        int label;

        //represents the "pixels" using true/false
        //true if there is a character and false if there isn't a character
        while (labelstream >> label) {
            vector<bool> individual_picture;
            for (int i = 0; i < 28; i++) {
                string each_line;
                getline(imagestream, each_line);
                for (int j = 0; j < each_line.length(); j++) {
                    individual_picture.push_back(each_line[j] != ' ');
                }
            }
            Picture picture(individual_picture, label);
            all_pictures.push_back(picture);
        }
    }

    return all_pictures;
}

/*
 * @param pictures the vector of picture objects
 * @return a 3D vector containing the total number of each numbers images that have
 *         a character at a specific "pixel" and the number that don't
 */
vector<vector<vector<int>>> FrequencyOfCharacters(vector<Picture> pictures){
    vector<vector<vector<int>>> character_frequencies(10, vector<vector<int>>(784, vector<int>(2)));
    for(int i = 0; i < pictures.size(); i++){

        int actual_number = pictures[i].actual_number;

        for(int j = 0; j < 784; j++){

            //if the pixel in the picture is not a character it adds one to the first index
            //of the third dimension of the array, otherwise it adds one to the second if there is a character
            bool character = pictures[i].pixel_array[j];

            if(character){
                character_frequencies[actual_number][j][1]++;
            } else {
                character_frequencies[actual_number][j][0]++;
            }
        }
    }

    return character_frequencies;
}

/*
 * @param character_frequencies the 3D vector containing the total number of each numbers images that have
 *        a character at a specific "pixel" and the number that don't
 * @return a 3D vector containing the probability of each of pixel in a numbers image being a character
 */
vector<vector<vector<double>>> ProbabilityOfBeingACharacter(vector<vector<vector<int>>> character_frequencies){
    double laplace = 1;

    vector<vector<vector<double>>> chance_of_pixel_being_character(10, vector<vector<double>>(784, vector<double>(2)));

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 784; j++){

            //implements naivebayes
            int number_of_label = character_frequencies[i][j][0] + character_frequencies[i][j][1];

            for(int k = 0; k < 2; k++){

                double probability = (laplace + character_frequencies[i][j][k]) /
                        (2 * laplace + number_of_label);
                chance_of_pixel_being_character[i][j][k] = log(probability);
            }
        }
    }

    return chance_of_pixel_being_character;
}

/*
 * @param picture_frequencies a 3D vector containing the total number of each numbers images that have
 *        a character at a specific "pixel" and the number that don't
 * @return a vector containing the amount of each number 0-9
 */
vector<int> OccurrencesOfNumber(vector<vector<vector<int>>> picture_frequencies){
    vector<int> occurrences_of_number(10);
    for(int i = 0; i < 10; i++){

        //adds the total amount of images with a character at the first index and the number without
        //to get the total number of each number
        occurrences_of_number[i] = picture_frequencies[i][0][0] + picture_frequencies[i][0][1];
    }

    return occurrences_of_number;
}

/*
 * @param picture the image whose value you are trying the determine
 * @param algorithm what is going to be determining the number
 * @return the algorithms guess at the number
 */
int GuessNumber(Picture picture, Model algorithm){
    vector<double> final_probabilities(10);

    for(int i = 0; i < 10; i++){
        double percent_chance = (double)(OccurrencesOfNumber(algorithm.character_frequencies)[i]) / 5000.0;
        final_probabilities[i] = log(percent_chance);
    }

    //algorithm finalizes the chance_of_pixel_being_character of the image being each number
    for(int i = 0; i < 784; i++){
        for(int j = 0; j < 10; j++){
            int index;
            if (picture.pixel_array[i]) {
                index = 1;
            } else {
                index = 0;
            }
            final_probabilities[j] += algorithm.chance_of_pixel_being_character[j][i][index];
        }
    }

    //runs through all the chance_of_pixel_being_character and returns the number with the largest
    double max_probability = final_probabilities[0];
    int most_likely_number = 0;
    for(int i = 0; i < 10; i++){
        if(final_probabilities[i] > max_probability){
            max_probability = final_probabilities[i];
            most_likely_number = i;
        }
    }
    return most_likely_number;
}