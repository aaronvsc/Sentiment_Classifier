**Objective:** 

* Implement a class (DSString) that uses dynamic memory allocation and requires the implementation of the rule-of-three.
* Practice debugging and memory leak detection.
* Use of STL container (vectors, maps, etc.)
* Analyze the runtime complexity.
* Write a program with a command line interface.
* Design, implement, and test a small system.

## The Data
The original data was retrieved from Kaggle at https://www.kaggle.com/kazanova/sentiment140.
For more information, see  Go, A., Bhayani, R. and Huang, L., 2009. Twitter sentiment classification using distant supervision. CS224N Project Report, Stanford, 1(2009), p.12.

The training data file is formatted as a comma-separated-values (CSV) file containing a list of tweets, each one on a separate line.  Each line of the data files include the following fields:
* Sentiment value (negative = 0, positive = 4, numbers in between are not used),
* the tweet id,
* the date the tweet was posted
* Query status (you can ignore this column)
* the twitter username that posted the tweet
* the text of the tweet itself

The testing data set is broken into two files:
* A CSV file containing formatted just like the training data EXCEPT no Sentiment column
* A CSV file containing tweet ID and sentiment for the testing dataset (so you can compare your predictions of sentiment to the actually sentiment ground truth)


## Running your Program: Training and Testing
The program takes 5 cmd line arguements
1. training data set filename - the file with the training tweets
2. testing data set filename - tweets that your program will classify
3. testing data set sentiment filename - the file with the classifications for the testing tweet data
4. classifier results file name - see Output Files section below
5. classifier accuracy and errors file name - see Output Files section below

Example: In the build folder executing this command in the terminal should work.
```
./sentiment data/train_dataset_20k.csv data/test_dataset_10k.csv data/test_dataset_sentiment_10k.csv results.csv accuracy.txt
```


### Output Files
Program produces two output files. The first output file has the classifier's
results for all tweets in the testing dataset in the same format as the sentiment file:
```
4, 1467811596
...
```

The second file has the accuracy of the classifier. The remaining lines contain information related to which tweets the algorithm incorrectly classified, the ground turth, and the Tweet ID

Example of the testing data tweet classifications file:
```
0.500
4, 1, 2323232323
1, 3, 1132553423
...
```