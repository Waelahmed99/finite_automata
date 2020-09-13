#include <iostream>
#include <map>

using namespace std;

char graph[1000][1000];

bool match(string pattern, int endState,  int pos = 0, int state1 = 1, int state2 = 2) {
    if (state1 == endState)
        return true;
    if (graph[state1][state2] == '-')
        state2++;
    if (state2 > endState)
        return false;

    if (pattern[pos] == graph[state1][state2])
        return match(pattern, endState, pos + 1, state2, state2 + 1);
    else
        return match(pattern, endState, pos, state1, state2 + 1);
}

int main() {
    cout << "Welcome to our Finite Automata string matching evaluation\n";
    int states;
    cout << "Enter number of states: "; cin >> states;
    cout << "Enter First state, second state, and the linking label character, for example:\n";
    cout << "1 2 a\nEnter 0 to end\n";
    int state1, state2;
    char ch;
    map<int, int> paths;
    map<int, int> to_path;
    // Initialize our graph with '-'.
    for (int i = 0; i <= states; i++) {
        for (int j = 0; j <= states; j++)
            graph[i][j] = '-';
    }

    /// Add input to [graph] 2d matrix.
    while (true) {
        cin >> state1;
        if (state1 == 0) break;
        paths[state1]++;
        cin >> state2 >> ch;
        to_path[state2]++;
        graph[state1][state2] = ch;
    }

    // Start state
    for (int i = 1; i <= states; i++) {
        if (!to_path[i]) {
            cout << "Start state: " << i << endl;
            break;
        }
    }

    // End state
    int endState = -1;
    for (int i = states; i >= 1; i++) {
        if (!paths[i]) {
            cout << "End state: " << i << endl;
            endState = i;
            break;
        }
    }

    string pattern;
    cout << "Enter the string pattern for matching: ";
    cin >> pattern;

    // look for pattern matching
    if (match(pattern, endState))
        cout << "String match " << endl;
    else
        cout << "String doesn't match the automata " << endl;


    // output the matrix form.
    cout << "   ";
    for (int i = 1; i <= states; i++)
        cout << i << "  ";
    cout << endl;

    for (int i = 1; i <= states; i++) {
        cout << i << "  ";
        for (int j = 1; j <= states; j++)
            cout << graph[i][j] << "  ";
        cout << endl;
    }
    return 0;
}
