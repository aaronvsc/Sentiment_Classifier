#include "SentimentClassifier.h"

int main(int argc, char** argv) {
    if (argc != 6) {
        std::cerr << "Incorrect number of arguements" << std::endl;
        return 1;  // Return error code 1
    }

    SentimentClassifier test;

    test.train(argv[1]);

    test.predict(argv[2], argv[4]);

    test.evaluate(argv[3], argv[4], argv[5]);

    return 0;
}