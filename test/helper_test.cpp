#include "../src/helper.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("MakePictureVectorTest"){
    vector<Picture> test_images = MakePictureVector("../data/trainingimages.txt", "../data/traininglabels.txt");
    REQUIRE(test_images.size() == 5000);
}

TEST_CASE("MakeTrainingPictureVectorTest"){
    vector<Picture> test_images = MakePictureVector("../data/trainingimages.txt", "../data/traininglabels.txt");
    REQUIRE(test_images.size() == 1000);
}

TEST_CASE("FrequencyOfNotBeingCharactersTest"){
    vector<Picture> pictures = MakePictureVector("../data/trainingimages.txt", "../data/traininglabels.txt");
    REQUIRE(FrequencyOfCharacters(pictures)[0][0][0] == 479);
}

TEST_CASE("FrequencyOfBeingCharactersTest"){
    vector<Picture> pictures = MakePictureVector("../data/trainingimages.txt", "../data/traininglabels.txt");
    REQUIRE(FrequencyOfCharacters(pictures)[0][0][1] == 0);
}

TEST_CASE("ProbabilityOfBeingACharacterTest"){
    vector<Picture> pictures = MakePictureVector("../data/trainingimages.txt", "../data/traininglabels.txt");
    REQUIRE(ProbabilityOfBeingACharacter(FrequencyOfCharacters(pictures))[0][0][0] == Approx(-.0102775828));
}

TEST_CASE("GuessNumberTest"){
    vector<Picture> test_pictures = MakePictureVector("../data/trainingimages.txt", "../data/traininglabels.txt");
    Model algorithm("../data/testimages.txt", "../data/testlabels.txt");
    REQUIRE(GuessNumber(test_pictures[1], algorithm) == 0);
}

TEST_CASE("GuessSecondNumberTest"){
    vector<Picture> test_pictures = MakePictureVector("../data/trainingimages.txt", "../data/traininglabels.txt");
    Model algorithm("../data/testimages.txt", "../data/testlabels.txt");
    REQUIRE(GuessNumber(test_pictures[2], algorithm) == 2);
}

TEST_CASE("SaveTest"){
    vector<Picture> test_pictures = MakePictureVector("../data/trainingimages.txt", "../data/traininglabels.txt");
    Model algorithm("../data/testimages.txt", "../data/testlabels.txt");
    Save("data/algorithm.txt", algorithm);
    REQUIRE(Load("data/algorithm.txt").character_frequencies.size() == algorithm.character_frequencies.size());
}
