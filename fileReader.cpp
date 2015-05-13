//: Finger Exercise 1: TP
// Read tsv file and get:
// 1) Number of positive reviews
// 2) Number of negative reviews
// 3) Maximum, minimum and average lenght of reviews (number of characters)
// 4) Are all the reviews that contain the word "amazing" positive reviews?
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

#define P(EXP) cout << #EXP " = " << EXP << endl;

int main() {
	ifstream in("labeledTrainData.tsv");
	vector<string> reviews;
	vector<string> topWords;
	char delimiter = '\t';
	string s, token, target = "amazing";
	stringstream iss;
	int i, sentiment, negativeAmazing = 0;
	int positiveS = 0, negativeS = 0;
	bool positive = false, negative = false;
	map<string,int> words;	

	getline(in, s);
	while(getline(in, s)) {
		i = 1;
		iss << s;
		while(getline(iss, token, delimiter)) {
			if(i == 2) {
				stringstream ss(token);
				ss >> sentiment;
				if(sentiment) {
					positiveS++;
					positive = true;
					negative = false;
				} else {
					negativeS++;
					positive = false;
					negative = true;
				}
			}
			if(i == 3) {
				reviews.push_back(token);
				if(negative)
					negativeAmazing += token.find(target) != string::npos ? 1 : 0; 			
			}
			i++;
		}
		iss.clear();
	}

	int averageLength = 0, max = 0, min = 99999, reviewLength;
	for(int i = 0; i < reviews.size(); i++) {
		reviewLength = reviews[i].size();
		if(max < reviewLength)
			max = reviewLength;
		if(min > reviewLength)
			min = reviewLength;
		averageLength += reviewLength;	
		iss << reviews[i];
		while(getline(iss, token, ' ')) { 
			// get word appearances in review
			if(!words.count(token)) {
				words[token] = 1;
			} else {
				words[token]++;
			}
		}
	}

	// print word appearances
	for(map<string,int>::iterator it=words.begin(); it!=words.end(); it++) {
		cout << it->first << ": " <<  it->second << endl;
	}
	cout << words.size();
	averageLength /= reviews.size();
	P(positiveS);
	P(negativeS);
	P(averageLength);
	P(max);
	P(min);
	P(negativeAmazing);
} ///:~
