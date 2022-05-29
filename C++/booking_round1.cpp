/*
Problem Statement
Booking.com uses a 3rd party provider in order to convert from the user’s currency to the actual currency listed by the partner/hotel. For example, our user may use Euro while booking a hotel in GB, Booking.com will eventually pay in GBP to the partner.
Our currency conversion provider only has a few currency conversion options available.

We need to check if currency conversion is possible from the partner's currency to the currency mentioned by the user or not.

If the conversion is possible, we need to return the hotel price in the user’s currency. If the conversion is not possible, we need to return -1.

Booking also charges a service fee to the users for every exchange conversion. 
Booking calculates service fee by charging X(variable input) for every vendor side transaction.  

If Booking does K vendor transactions for user exchange then service fee will be X*K of user currency. Calculate total price of conversion for the user.
The service fee needs to be added to the price in the required currency.

Examples  
Sample Input 1 -
Vendor conversion table - 
1 EUR = 1.18 GBP
1 GBP =  1.35 USD
1 CAD =   2.89 AED

Hotel Price, P = 1000 
Transaction Fee, X = 0.75(in user currency)
Hotel Currency = EUR 
User Currency = USD

Output  - 
1594.5 

Sample Input 2 -
Vendor conversion table - 
1 EUR = 1.18 GBP
1 GBP =  1.35 USD
1 CAD =   2.89 AED

Hotel Price, P = 1000 
Transaction Fee, X = 0.75(in user currency)
Hotel Currency = CAD 
User Currency = USD

Output  - 
    (Not possible) -1
*/

#include <bits/stdc++.h>
using namespace std;

class CurrencyConverter {
    private:
        map<string, int> currencyToId;
        int numCurrencies = 0;
        int id = 0;
        vector<vector<double> > conversionMatrix;
        vector<vector<int> > hopMatrix;
    
        void generateIds(vector<pair<string, pair<string, double> > > &conversions){
            for(int i=0; i<conversions.size(); i++){
                string currency1 = conversions[i].first;
                string currency2 = conversions[i].second.first;
                if(currencyToId.find(currency1)==currencyToId.end()){
                    currencyToId[currency1] = id;
                    id++;
                } 
                if(currencyToId.find(currency2)==currencyToId.end()){
                    currencyToId[currency2] = id;
                    id++;
                }
            }
            numCurrencies = currencyToId.size();
        }
        
        void initializeConversionMatrixAndHopMatrix(vector<pair<string, pair<string, double> > > &conversions){
            conversionMatrix.resize(numCurrencies, vector<double> (numCurrencies, INT_MAX));
            hopMatrix.resize(numCurrencies, vector<int> (numCurrencies, INT_MAX));
            for(int i=0; i<conversions.size(); i++){
                string currency1 = conversions[i].first;
                string currency2 = conversions[i].second.first;
                int currency1Id = currencyToId[currency1];
                int currency2Id = currencyToId[currency2];
                double conversionRate = conversions[i].second.second;
                conversionMatrix[currency1Id][currency2Id] = conversionRate;
                conversionMatrix[currency2Id][currency1Id] = 1.0/conversionRate;
                hopMatrix[currency1Id][currency2Id] = 1;
                hopMatrix[currency2Id][currency1Id] = 1;
                //self conversion
                conversionMatrix[currency1Id][currency1Id] = 1.0;
                conversionMatrix[currency2Id][currency2Id] = 1.0;
                hopMatrix[currency1Id][currency1Id] = 0;
                hopMatrix[currency2Id][currency2Id] = 0;
            }
        }
        
        /*
        i-m
        m-j
        i-k
        k-j
        */
        
        void applyFloydWarshall(){
            for(int k=0; k<numCurrencies; k++){
                for(int i=0; i<numCurrencies; i++){
                    for(int j=0; j<numCurrencies; j++){
                        if(conversionMatrix[i][k]!=INT_MAX && conversionMatrix[k][j]!=INT_MAX && conversionMatrix[i][j]==INT_MAX){
                            conversionMatrix[i][j] = conversionMatrix[i][k] * conversionMatrix[k][j];
                        }
                        if(hopMatrix[i][k] != INT_MAX && hopMatrix[k][j] != INT_MAX){
                            if(hopMatrix[i][j] > hopMatrix[i][k] + hopMatrix[k][j])
                                hopMatrix[i][j] = hopMatrix[i][k] + hopMatrix[k][j];
                        }
                    }
                }
            }
        }
    
    public:
        CurrencyConverter (vector<pair<string, pair<string, double> > > &conversions){
            //{EUR, GBP, 1.18}, {GBP, USD, 1.35}
            generateIds(conversions);
            initializeConversionMatrixAndHopMatrix(conversions);
            applyFloydWarshall();
        }
        
        double findOutputCurrency(double hotelPrice, string hotelCurrency, string userCurrency, double transactionFee){
            if(currencyToId.find(hotelCurrency)==currencyToId.end() || currencyToId.find(userCurrency)==currencyToId.end()){
                return -1;
            }
            int hotelCurrencyId = currencyToId[hotelCurrency];
            int userCurrencyId = currencyToId[userCurrency];
            if(hopMatrix[hotelCurrencyId][userCurrencyId]==INT_MAX)
                return -1;
            double conversionRate = conversionMatrix[hotelCurrencyId][userCurrencyId];
            double preTransactionFeeOutput = hotelPrice * conversionRate;
            int numHops = hopMatrix[hotelCurrencyId][userCurrencyId];
            double totalTransactionFee = transactionFee*(double)numHops;
            double finalOutput = preTransactionFeeOutput + totalTransactionFee;
            return finalOutput;
        }
};


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    vector<pair<string, pair<string, double> > > conversions;
    conversions.push_back(make_pair("EUR", make_pair("GBP", 1.18)));
    conversions.push_back(make_pair("GBP", make_pair("USD", 1.35)));
    conversions.push_back(make_pair("CAD", make_pair("AED", 2.89)));
    CurrencyConverter *currencyConverter = new CurrencyConverter(conversions);
    cout << currencyConverter->findOutputCurrency(1000.0, "EUR", "USD", 0.75) << endl;
    cout << currencyConverter->findOutputCurrency(1000.0, "CAD", "USD", 0.75) << endl;
    
    return 0;
}