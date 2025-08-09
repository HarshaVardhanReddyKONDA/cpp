#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <nlohmann/json.hpp> // JSON library

using json = nlohmann::json;
using namespace std;

struct Root {
    int x;
    string y_encoded;
    int base;
    long long y_decoded;
};

// Convert number in any base to decimal
long long convertToDecimal(const string &num, int base) {
    return stoll(num, nullptr, base);
}

// Function to calculate secret 'c' for y = a*x + c (linear example)
double calculateSecretC(const vector<Root> &roots) {
    if (roots.size() < 2) {
        cerr << "Not enough points to determine C" << endl;
        return 0;
    }
    double x1 = roots[0].x, y1 = roots[0].y_decoded;
    double x2 = roots[1].x, y2 = roots[1].y_decoded;

    double a = (y2 - y1) / (x2 - x1);
    double c = y1 - a * x1;
    return c;
}

int main() {
    // Step 1: Read JSON file
    ifstream file("testcases.json"); // your file name
    if (!file) {
        cerr << "Error: Could not open testcases.json" << endl;
        return 1;
    }

    json data;
    file >> data;

    vector<Root> roots;

    // Step 2: Parse JSON and decode
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (it.key() == "keys") continue; // skip the "keys" object

        Root r;
        r.x = stoi(it.key()); // convert key string to int
        r.base = stoi(it.value()["base"].get<string>());
        r.y_encoded = it.value()["value"].get<string>();
        r.y_decoded = convertToDecimal(r.y_encoded, r.base);
        roots.push_back(r);
    }

    // Step 3: Display decoded values
    cout << "Decoded Y values:\n";
    for (auto &r : roots) {
        cout << "x = " << r.x << ", y_encoded = " << r.y_encoded
             << " (base " << r.base << ") -> y_decoded = " << r.y_decoded << "\n";
    }

    // Step 4: Calculate secret C
    double secret_c = calculateSecretC(roots);
    cout << "\nSecret C = " << secret_c << endl;

    return 0;
}
