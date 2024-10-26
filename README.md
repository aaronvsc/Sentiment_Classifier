# Twitter Sentiment Classifier

### Authors: Aaron Santa Cruz

## Project Overview
This project implements a sentiment classifier for tweets, leveraging a custom string class and a large dataset to predict sentiment in text. Using dynamic memory allocation, this classifier parses tweets, processes words, and applies a trained sentiment model to categorize tweet sentiments. The project covers core techniques in natural language processing, including stopword removal, word tokenization, and stemming, to optimize classification accuracy.

## Objectives
- **DSString Class**: Implement a `DSString` class with dynamic memory allocation for efficient string management.
- **Tweet Parsing**: Parse and tokenize meaningful words from tweets to enable analysis.
- **Sentiment Classifier**: Train a classifier using labeled data to identify tweet sentiments as positive or negative.
- **Model Evaluation**: Calculate classification accuracy and identify misclassified tweets.
- **Classification Optimization**: Implement techniques like stopword removal and stemming to improve classifier accuracy.

## Learning Objectives
This project provides an opportunity to:
- Practice debugging and detect memory leaks.
- Use STL containers, including vectors and maps.
- Analyze and optimize runtime complexity.
- Design, implement, and test a sentiment classification system.

## The Data
The original dataset is sourced from Kaggle: [Sentiment140 Dataset](https://www.kaggle.com/kazanova/sentiment140). For more information, see the research paper: *Go, A., Bhayani, R. and Huang, L., 2009. Twitter sentiment classification using distant supervision. CS224N Project Report, Stanford, 1(2009), p.12.*

The dataset consists of 1.6 million tweets and is formatted as a comma-separated-values (CSV) file containing the following fields for each tweet:
- Sentiment value (0 = negative, 4 = positive),
- Tweet ID,
- Date of tweet,
- Query status (ignored in this project),
- Twitter username,
- Text of the tweet.

### Testing Data Format
The testing dataset consists of two files:
1. **Tweet data**: A CSV file similar to the training data, but without a sentiment column.
2. **Sentiment labels**: A CSV file containing tweet IDs and their corresponding sentiment labels for testing accuracy.

## Running the Program: Training and Testing
The program requires five command-line arguments:
1. **Training Dataset** - Path to the CSV file with labeled tweets.
2. **Testing Dataset** - Path to the CSV file of unlabeled tweets.
3. **Testing Sentiment Labels** - Path to the CSV file with actual sentiment labels for the testing set.
4. **Classifier Results** - Output file for classifier predictions.
5. **Classifier Accuracy** - Output file for accuracy metrics and misclassified tweets.

### Example Command
Execute the program from the build directory:
```shell
./sentiment data/train_dataset_20k.csv data/test_dataset_10k.csv data/test_dataset_sentiment_10k.csv results.csv accuracy.txt