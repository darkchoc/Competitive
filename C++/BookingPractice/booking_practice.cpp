//Question: https://leetcode.com/discuss/interview-question/1431676/bookingcom-award-top-k-hotels-oa-hackerrank

#include <bits/stdc++.h>
using namespace std;

vector<string> splitAndConvertToLowerCase(string &s){
    string word = "";
    int i = 0;
    vector<string> tokens;
    while(i<s.length()){
        if(s[i]=='.' || s[i]==',' || s[i]==' '){
            if(word.length())
                tokens.push_back(word);
            word = "";
        } else {
            word += (s[i]>='a' && s[i] <='z')?s[i]:(s[i]-'A'+'a');
        }
        i++;
    }
    if(word.length())
        tokens.push_back(word);
    return tokens;
}

int getScoreFromReview(set<string> &positiveWords, set<string> &negativeWords, vector<string> &tokens){
    int pos = 0, neg = 0;
    for(int i=0; i<tokens.size(); i++){
        if(positiveWords.find(tokens[i])!=positiveWords.end())
            pos++;
        else if(negativeWords.find(tokens[i])!=negativeWords.end())
            neg++;
    }
    return 3*pos - neg;
}


vector<int> getTopKHotels(string positiveString, string negativeString, int numHotels, vector<int> &hotelIds, int numReviews, vector<string> &reviews, int k){
    vector<string> positiveWordTokens = splitAndConvertToLowerCase(positiveString);
    vector<string> negativeWordTokens = splitAndConvertToLowerCase(negativeString);
    set<string> positiveWords (positiveWordTokens.begin(), positiveWordTokens.end());
    set<string> negativeWords (negativeWordTokens.begin(), negativeWordTokens.end());

    map<int, int> score;

    for(int i=0; i<hotelIds.size(); i++){
        int currentHotel = hotelIds[i];
        string currentReview = reviews[i];
        vector<string> reviewTokens = splitAndConvertToLowerCase(currentReview);
        int reviewScore = getScoreFromReview(positiveWords, negativeWords, reviewTokens);
        score[currentHotel] += reviewScore;
    }

    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > min_pq;
    for(map<int, int>::iterator it = score.begin(); it != score.end(); it++){
        if(min_pq.size() < k){
            min_pq.push(make_pair(it->second, it->first));
        } else {
            if(min_pq.top().first < it->second){
                min_pq.pop();
                min_pq.push(make_pair(it->second, it->first));
            } else if (min_pq.top().first == it->second){
                if(min_pq.top().second > it->first){
                    min_pq.pop();
                    min_pq.push(make_pair(it->second, it->first));
                }
            }
        }
    }

    vector<int> topKHotelIds;
    while(!min_pq.empty()){
        topKHotelIds.push_back(min_pq.top().second);
        min_pq.pop();
    }
    return topKHotelIds;
}

int main(){
    string positiveWords = "breakfast beach city center location metro view staff price";
    string negativeWords = "not";
    int numHotels = 5;
    vector<int> hotelIds = {1,2,1,1,2};
    int numReviews = 5;
    vector<string> reviews = {
        "This hotel has a nice view of the city center. The location is perfect.",
        "The breakfast is ok. Regarding location, it is quite far from city center but the price is cheap so it is worth.",
        "Location is excellent, 5 minutes from the city center. There is also a metro station very close to the hotel.",
        "They said I couldn’t take my dog and there were other guests with dogs! That is not fair.",
        "Very friendly staff and a good cost-benefit ratio. Its location is a bit far from the city center."
    };
    int k = 2;
    vector<int> topKHotels = getTopKHotels(positiveWords, negativeWords, numHotels, hotelIds, numReviews, reviews, k);
    for(int i=0; i<topKHotels.size(); i++)
        cout << topKHotels[i] << " ";
    cout << endl;
    return 0;
}