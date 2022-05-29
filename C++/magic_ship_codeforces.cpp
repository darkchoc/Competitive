//Question: https://codeforces.com/problemset/problem/1117/C

#include <bits/stdc++.h>
using namespace std;

/*
Observation: If at all it is possible to reach, then if we can reach in d days, we can surely reach in d+1 days.
So the function is monotonic. 

Also, we can check what is the final displacement caused by wind. Let vertical displacement be v_wind, and horizontal displacement be h_wind. Let this point be x2, y2
Now, in the n days, we can go to any place within n manhattan distance of (x2, y2)

If we want to calculate for k days, we can simply check where will wind take us in k days. Let's say it is (x3, y3). Then we know we can go to any point within k manhattan distance from x3, y3. We can check if destination is within k distance from this point. 

To get x3,y3 : We can calculate displacement every day from 1 to n. Now for some day > n, say k, our displacement will be (k/n)*disp[n] + disp[k%n]. That is, after k/n cycles, we just add remainder displacement.

Also, how can we say that answer doesn't exist? 
We want that with every cycle of n days, we should reach at least 1 distance closer to destination. So max days that can be taken is manhattanDistance(source, destination) * n.
*/

typedef long long ll;

ll manhattanDistance(ll x, ll y, ll p, ll q){
    return abs(x-p) + abs(y-q);
}

bool possible(ll days, vector<pair<ll, ll> > &displacementOnDay, ll x, ll y, ll p, ll q, ll n){
    ll xDisplacement = (days/n)*displacementOnDay[n].first + displacementOnDay[days%n].first;
    ll yDisplacement = (days/n)*displacementOnDay[n].second + displacementOnDay[days%n].second;
    ll xAfterWind = x + xDisplacement;
    ll yAfterWind = y + yDisplacement;
    if(manhattanDistance(xAfterWind, yAfterWind, p, q) <= days)
        return true;
    return false;
}

ll minDays(int x, int y, int p, int q, string s){
    //we want to go from x,y to p,q and wind is repeating in pattern s
    ll n = (ll)s.length();
    map<char, pair<ll, ll> > disp;
    disp['U'] = make_pair(0, 1);
    disp['D'] = make_pair(0, -1);
    disp['L'] = make_pair(-1, 0);
    disp['R'] = make_pair(1, 0);
    vector<pair<ll, ll> > displacementOnDay (n+1);
    displacementOnDay[0] = make_pair(0,0);
    for(int i=0; i<n; i++){
        displacementOnDay[i+1] = displacementOnDay[i];
        displacementOnDay[i+1].first += disp[s[i]].first;
        displacementOnDay[i+1].second += disp[s[i]].second;
    }
    //now displacementOnDay[i] gives displacement of ship from 0,0 in i days (1 indexed).

    ll low = 0, high = manhattanDistance((ll)x, (ll)y, (ll)p, (ll)q)*n + (ll)100;
    while(low < high){
        ll mid = (low + high)/(ll)2; //bias it towards low
        if(possible(mid, displacementOnDay, (ll)x, (ll)y, (ll)p, (ll)q, (ll)n))
            high = mid;
        else
            low = mid+(ll)1;
    }
    if(high > manhattanDistance((ll)x, (ll)y, (ll)p, (ll)q)*n)
        return -1;
    return high;
}

int main(){
    //cout << minDays(0, 0, 4, 6, "UUU") << endl;
    //cout << minDays(0, 3, 0, 0, "UDD") << endl;
    //cout << minDays(0, 0, 0, 1, "L") << endl;
    int x, y, p, q;
    cin >> x >> y >> p >> q;
    int n;
    cin >> n;
    string s;
    cin >> s;
    cout << minDays(x, y, p, q, s);
}