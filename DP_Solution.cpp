#include<bits/stdc++.h>
using namespace std;

bool can_abhimanyu_cross_chakravyuha_recursive(int p, int a, int b, vector<int>& k, int current_power, int index, vector<vector<vector<int>>>& dp) {
    // Base case: Successfully crossed all circles or insufficient power
    if (index >= k.size() || current_power <= 0) {
        return index >= k.size(); // True if all circles crossed, False otherwise
    }

    // Check if the result for the current subproblem is already computed
    if (dp[current_power][a][index] != -1) {
        return dp[current_power][a][index];
    }

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
        if (current_power < additional_attack) {
            return false; // Abhimanyu loses if power drops below zero
        }
        else{
            current_power -= additional_attack; // Reduce power by the regenerating enemy's attack
        }
    }

    // Option 1: Battle the current enemy if possible
    if (current_power >= k[index]) {
        if (can_abhimanyu_cross_chakravyuha_recursive(p, a, b, k, current_power - k[index], index + 1, dp)) {
            return dp[current_power][a][index] = true;
        }
    }

    // Option 2: Skip the current enemy if skips are available
    if (a > 0) {
        if (can_abhimanyu_cross_chakravyuha_recursive(p, a - 1, b, k, current_power, index + 1, dp)) {
            return dp[current_power][a][index] = true;
        }
    }

    // Option 3: Recharge and battle the current enemy if recharges are available
    if (b > 0) {
        if (can_abhimanyu_cross_chakravyuha_recursive(p, a, b - 1, k, p, index, dp)) {
            return dp[current_power][a][index] = true;
        }
    }

    // If none of the options work, Abhimanyu loses
    return dp[current_power][a][index] = false;
}
bool can_abhimanyu_cross_chakravyuha(int p, int a, int b, vector<int>& k) {
    // Define DP array as a 3D vector
    vector<vector<vector<int>>> dp(p + 1, vector<vector<int>>(a + 1, vector<int>(k.size(), -1)));
    return can_abhimanyu_cross_chakravyuha_recursive(p, a, b, k, p, 0, dp);
}

int main() {
    std::vector<int> k1 = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1};
    std::vector<int> k2 = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    // Example test runs
    std::cout << (can_abhimanyu_cross_chakravyuha(20, 2, 1, k1) ? "True" : "False") << std::endl;  // Expected outcome: True or False
    std::cout << (can_abhimanyu_cross_chakravyuha(5, 3, 2, k2) ? "True" : "False") << std::endl;   // Expected outcome: True or False

    return 0;
}