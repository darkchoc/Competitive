// https://leetcode.com/discuss/interview-question/1581894/bookingcom-onsite-hotel-list

#include <bits/stdc++.h>
using namespace std;

typedef struct RoomDetails {
    int price;
    int availability;
    vector<string> features;
    RoomDetails(int p, int a, vector<string> features): price(p), availability(a), features(features) {};
    RoomDetails(): price(0), availability(0), features(vector<string> {}) {};
    void print(){
        cout << "Price: " << price << " rooms: " << availability; 
        if(features.size()==0){
            cout << " features: {}" << endl;
            return;
        } else 
            cout << " features: {";
        for(int i=0; i<features.size(); i++){
            cout << features[i];
            if(i != features.size()-1)
                cout << ", ";
            else
                cout << "}" << endl;
        } 
    }
} RoomDetails;

bool featuresPresent(vector<string> &roomFeatures, vector<string> &reqdFeatures){
    if(reqdFeatures.size()==0)
        return true;
    if(reqdFeatures.size() > roomFeatures.size())
        return false;
    set<string> roomFeatureSet (roomFeatures.begin(), roomFeatures.end());
    for(int i=0; i<reqdFeatures.size(); i++)
        if(roomFeatureSet.find(reqdFeatures[i])==roomFeatureSet.end())
            return false;
    return true;
}

vector<string> setIntersection (vector<string> &set1, vector<string> &set2){
    set<string> s1 (set1.begin(), set1.end());
    set<string> s2 (set2.begin(), set2.end());
    vector<string> intersection;
    for(set<string>::iterator it = s1.begin(); it!=s1.end(); it++){
        if(s2.find(*it)!=s2.end())
            intersection.push_back(*it);
    }
    return intersection;
}

void helper(map<int, vector<RoomDetails> > &possibleRooms, int current, vector<RoomDetails> &options, RoomDetails &aggregate, int &checkin, int &checkout){
    if(current == checkout){
        options.push_back(aggregate);
        return;
    }
    vector<RoomDetails> &optionsForThisDate = possibleRooms[current];
    for(int i=0; i<optionsForThisDate.size(); i++){
        if(current == checkin){
            aggregate.price = optionsForThisDate[i].price;
            aggregate.availability = optionsForThisDate[i].availability;
            aggregate.features = optionsForThisDate[i].features;
            helper(possibleRooms, current+1, options, aggregate, checkin, checkout);
        } else {
            aggregate.price += optionsForThisDate[i].price;
            int originalAvailability = aggregate.availability;
            aggregate.availability = min(aggregate.availability, optionsForThisDate[i].availability);
            vector<string> originalFeatures = aggregate.features;
            aggregate.features = setIntersection(aggregate.features, optionsForThisDate[i].features);
            helper(possibleRooms, current+1, options, aggregate, checkin, checkout);
            aggregate.price -= optionsForThisDate[i].price;
            aggregate.availability = originalAvailability;
            aggregate.features = originalFeatures;
        }
    }
}

vector<RoomDetails> returnPossibleOptions(int checkin, int checkout, vector<string> features, int rooms, map<int, vector<RoomDetails> > &roomData){
    vector<RoomDetails> options;
    map<int, vector<RoomDetails> > possibleRooms;

    int current = checkin;
    while(current < checkout){
        vector<RoomDetails> &todaysRooms = roomData[current];
        for(int i=0; i<todaysRooms.size(); i++){
            if(todaysRooms[i].availability >= rooms && featuresPresent(todaysRooms[i].features, features))
                possibleRooms[current].push_back(todaysRooms[i]);
        }
        if(possibleRooms[current].size()==0)
            return options;
        current++;
    }

    RoomDetails aggregate;
    helper(possibleRooms, checkin, options, aggregate, checkin, checkout);
    return options;
}

int main(){
    map<int, vector<RoomDetails> > roomData;
    roomData[176] = {RoomDetails(120, 5, {"breakfast", "refundable"})};
    roomData[177] = {RoomDetails(130, 1, {"breakfast"}), RoomDetails(140, 3, {"breakfast", "refundable", "wifi"})};
    roomData[178] = {RoomDetails(130, 2, {"breakfast"}), RoomDetails(140, 10, {"breakfast", "refundable", "wifi"})};

    vector<RoomDetails> options = returnPossibleOptions(176, 178, {"breakfast"}, 1, roomData); //checkin, checkout, features, rooms
    for(int i=0; i<options.size(); i++){
        options[i].print();
    }
}