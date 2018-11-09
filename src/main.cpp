#include "helper.h"

int main(){

    //converts the files into picture objects, determines character_frequencies of pixels being characters
    vector<Picture> test_pictures = MakePictureVector("data/testimages.txt", "data/testlabels.txt");
    vector<vector<vector<int>>> character_frequency = FrequencyOfCharacters(test_pictures);

    Model traning_model("data/trainingimages.txt", "data/traininglabels.txt");

    int number_correctly_predicted = 0;
    int total_numbers = 1000;

    //returns a 2D array, keeping track of correct and incorrect guesses
    vector<vector<double>> results(10, vector<double>(10));
    for(int i = 0; i < total_numbers; i++){

        int guess = GuessNumber(test_pictures[i], traning_model);
        int actual = test_pictures[i].actual_number;
        results[guess][actual]++;

        if(guess == actual){
            number_correctly_predicted++;
        }
    }

    //finds the total number of each number in the picture array
    vector<int> number_of_each(10);
    for(int i = 0; i < test_pictures.size(); i++){
        number_of_each[test_pictures[i].actual_number]++;
    }

    //calculates percent of correct and incorrect guesses
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            results[i][j] = results[i][j] / number_of_each[i];
        }
    }

    //prints out table displaying the percentages of each possible correct/incorrect guess
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(results[j][i] == 0){
                cout << 0.0 << "        ";
            } else {
                cout << printf("%.5f", results[j][i]) << " ";
            }

        }
        cout << "\n";
    }

    double percent_correct = (double) number_correctly_predicted / (double) total_numbers;
    cout << "Percentage: " << percent_correct << endl;

    Save("data/traning_model.txt", traning_model);
    Load("data/traning_model.txt");

}
