#include<bits/stdc++.h>
using namespace std;

bool can_abhimanyu_cross_chakravyuha(int p, int a, int b, vector<int>& k) {
    // Define DP array as a 3D vector
    vector<vector<vector<int>>> dp(p + 1, vector<vector<int>>(a + 1, vector<int>(k.size(), -1)));

    // Base case initialization
    for (int i = 0; i <= a; ++i) {
        for (int j = 0; j <= b; ++j) {
            dp[0][i][j] = true; // If Abhimanyu's power is 0, he can always cross
        }
    }

    // Iterate through all possible states
    for (int power = 1; power <= p; ++power) {
        for (int skips = 0; skips <= a; ++skips) {
            for (int index = 0; index < k.size(); ++index) {
                // Handle regenerating enemies at k3 and k7
                if (index == 3 && k[2] > 0) {
                    k[2] /= 2;
                }
                if (index == 7 && k[6] > 0) {
                    k[6] /= 2;
                }

                // Check if Abhimanyu is battling in the 4th or 8th circle
                if ((index == 3 && k[2] > 0) || (index == 7 && k[6] > 0)) {
                    int additional_attack = (index == 4) ? k[2] : k[6];
                    if (power < additional_attack) {
                        dp[power][skips][index] = false; // Abhimanyu loses if power drops below zero
                    } else {
                        power -= additional_attack; // Reduce power by the regenerating enemy's attack
                    }
                }

                // Option 1: Battle the current enemy if possible
                if (power >= k[index]) {
                    if (dp[power - k[index]][skips][index + 1]) {
                        dp[power][skips][index] = true;
                    }
                }

                // Option 2: Skip the current enemy if skips are available
                if (skips > 0) {
                    if (dp[power][skips - 1][index + 1]) {
                        dp[power][skips][index] = true;
                    }
                }

                // Option 3: Recharge and battle the current enemy if recharges are available
                if (b > 0) {
                    if (dp[p][a][index + 1]) {
                        dp[power][skips][index] = true;
                    }
                }

                // If none of the options work, Abhimanyu loses
                if (dp[power][skips][index] == -1) {
                    dp[power][skips][index] = false;
                }
            }
        }
    }

    return dp[p][a][0];
}

int main() {
    vector<int> k1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    vector<int> k2 = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    // Example test runs
    cout << (can_abhimanyu_cross_chakravyuha(20, 2, 1, k1) ? "True" : "False") << std::endl;  // Expected outcome: True or False
    cout << (can_abhimanyu_cross_chakravyuha(5, 3, 2, k2) ? "True" : "False") << std::endl;   // Expected outcome: True or False

    return 0;
}