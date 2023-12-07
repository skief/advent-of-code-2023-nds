#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

constexpr char *test = (char*)
#include "../../inputs/day07.txt"
;

class Hand {
private:
    enum Card {
        TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, T, J, Q, K, A
    };

    enum Type {
        HIGH_CARD,
        ONE_PAIR,
        TWO_PAIR,
        THREE_KIND,
        FULL_HOUSE,
        FOUR_KIND,
        FIVE_KIND
    };

    Type value;

public:
    Card cards[5];
    int bid;

    void calcValue(bool jokers){
        map<Card, int> counts;
        for (auto card: cards){
            counts[card]++;
        }

        vector<int> c;
        int numJokers = 0;
        for (auto const& [key, val]: counts){
            if (key == J && jokers){
                numJokers = val;
            } else {
                c.emplace_back(val);
            }
        }
        if (!c.empty()){
            sort(c.begin(), c.end(), greater());
        }

        if (!jokers || numJokers == 0){
            if (c[0] == 5){
                value = FIVE_KIND;
            } else if (c[0] == 4) {
                value = FOUR_KIND;
            } else if (c[0] == 3 && c[1] == 2){
                value = FULL_HOUSE;
            } else if (c[0] == 3){
                value = THREE_KIND;
            } else if (c[0] == 2 && c[1] == 2){
                value = TWO_PAIR;
            } else if (c[0] == 2){
                value = ONE_PAIR;
            } else {
                value = HIGH_CARD;
            }
        } else {
            if (numJokers == 5 || c[0] + numJokers == 5){
                value = FIVE_KIND;
            } else if (c[0] + numJokers == 4){
                value = FOUR_KIND;
            } else if (c[0] + numJokers == 3 && c[1] == 2){
                value = FULL_HOUSE;
            } else if (c[0] + numJokers == 3){
                value = THREE_KIND;
            } else if (c[0] + numJokers == 2 && c[1] == 2){
                value = TWO_PAIR;
            } else if (c[0] + numJokers == 2){
                value = ONE_PAIR;
            }
        }
    }

    Hand(const string &cards, int bid): bid(bid){
        for (size_t i = 0; i < 5; i++){
            switch (cards[i]) {
                case 'A':
                    this->cards[i] = A;
                    break;
                case 'K':
                    this->cards[i] = K;
                    break;
                case 'Q':
                    this->cards[i] = Q;
                    break;
                case 'J':
                    this->cards[i] = J;
                    break;
                case 'T':
                    this->cards[i] = T;
                    break;
                case '9':
                    this->cards[i] = NINE;
                    break;
                case '8':
                    this->cards[i] = EIGHT;
                    break;
                case '7':
                    this->cards[i] = SEVEN;
                    break;
                case '6':
                    this->cards[i] = SIX;
                    break;
                case '5':
                    this->cards[i] = FIVE;
                    break;
                case '4':
                    this->cards[i] = FOUR;
                    break;
                case '3':
                    this->cards[i] = THREE;
                    break;
                case '2':
                    this->cards[i] = TWO;
                    break;
            }
        }
        calcValue(false);
    }

    bool operator < (const Hand &rhs) const{
        if (value < rhs.value){
            return true;
        }
        if (value > rhs.value){
            return false;
        }

        for (size_t i = 0; i < 5; i++){
            if (cards[i] > rhs.cards[i]){
                return false;
            } else if (cards[i] < rhs.cards[i]){
                return true;
            }
        }

        return false;
    }

    static bool lessWithJoker (const Hand &lhs, const Hand &rhs){
        if (lhs.value < rhs.value){
            return true;
        }
        if (lhs.value > rhs.value){
            return false;
        }

        for (size_t i = 0; i < 5; i++){
            int weightLeft = (lhs.cards[i] != J) ? lhs.cards[i] : -1;
            int weightRight = (rhs.cards[i] != J) ? rhs.cards[i] : -1;

            if (weightLeft > weightRight){
                return false;
            } else if (weightLeft < weightRight){
                return true;
            }
        }

        return false;
    }
};

int64_t part1(vector<Hand> hands){
    sort(hands.begin(), hands.end());
    int64_t res = 0;
    for (int i = 0; i < hands.size(); i++){
        res += (i + 1) * hands[i].bid;
    }

    return res;
}

int64_t part2(vector<Hand> hands){
    for (auto &hand: hands){
        hand.calcValue(true);
    }
    sort(hands.begin(), hands.end(), Hand::lessWithJoker);

    int64_t res = 0;
    for (int i = 0; i < hands.size(); i++){
        res += (i + 1) * hands[i].bid;
    }

    return res;
}

void solve(){
    stringstream input(test);

    string line;
    vector<Hand> hands;
    while(getline(input, line)){
        size_t sep = line.find(' ');
        hands.emplace_back(line.substr(0, sep), stoi(line.substr(sep + 1)));
    }

    cout << "Part 1: " << part1(hands) << endl;
    cout << "Part 2: " << part2(hands) << endl;
}
