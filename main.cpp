#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <map>
#include <utility>
#include <vector>

using namespace std;

int r, n;

bool isEmpty(char c[], int k){
    bool tmp = true;
    for (int x = 0; x < k; x++){
        if (c[x] != '\0'){
            tmp = false;
            break;
        }
    }
    return tmp;
}

int main()
{
    map<char, int> breedAndLevel;
    map<int, int> resourceAndLevel;
    vector<char> alive;

    cout << "plz input the amount of resources(R) and the amount of species(N): ";
    cin >> r >> n;
    char breed[n];
    char net[n+1][r];  // [2][_0_] -> res _1_, level 2
    memset(net, 0, sizeof net);
    for (int i = 0; i < n; i++){
        if (i < 26){
            breed[i] = 65 + i;
        }
        else {
            breed[i] = 97 + i - 26;
        }
        alive.push_back(breed[i]);
    }
    for (int i = 1; i <= r; i++){
        resourceAndLevel[i] = 0;
    }
    srand(time(NULL));

    while (true){
        int index = rand() % alive.size();
        cout << "picking " << alive.at(index);
        if (breedAndLevel.count(alive.at(index)) == 0){
            int res = rand() % r + 1;
            breedAndLevel[alive.at(index)] = ++resourceAndLevel[res];
            // the breed-(alive.at(index)) occupy the resource-(res-1), level-(resourceAndLevel[res])
            net[resourceAndLevel[res]][res-1] = alive.at(index);
            cout << " at " << res << endl;
        }
        else {
            vector<pair<int, int> > canEat_tmp;
            int count_tmp = 0;
            for (const auto i : resourceAndLevel){
                // count that how much resource can the creature eat
                if (breedAndLevel.at(alive.at(index)) > i.second){
                    canEat_tmp.push_back(i);
                    count_tmp++;
                }
            }
            if (count_tmp == 0){
                cout << endl << "\"" << alive.at(index) << "\" bye-bye" << endl;
                // the breed can't occupy resource anymore
                alive.erase(alive.begin() + index);
                if (alive.empty()){
                    // end
                    cout << "end." << endl;
                    break;
                }
                continue;
            }

            int _res = rand() % count_tmp;
            int res = canEat_tmp.at(_res).first;
            net[++resourceAndLevel[res]][res-1] = alive.at(index);
            cout << " at " << res << endl;
        }
    }

    for (int i = n; i >= 1; i--){
        if (isEmpty(net[i], r)){
            continue;
        }
        cout << "Level " << i << ":\t";
        for (int j = 0; j < r; j++){
            cout << "  " << (isalpha(net[i][j])? net[i][j] : '-') << "\t";
        } cout << endl;
    }
    cout << "Level 0:\t";
    for (int t = 1; t <= r; t++){
        cout << "res" << t << "\t";
    } cout << endl;

    return 0;
}
