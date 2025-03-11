#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

pair<int, int> w[2 * 300000];
int M;

void build(const vector<int>& speeds) {
    M = speeds.size();
    for (int i = 0; i < M; i++) {
        w[M + i] = {speeds[i], i + 1};
    }
    for (int i = M - 1; i > 0; i--) {
        w[i] = max(w[2 * i], w[2 * i + 1]);
    }
}

void update(int pos, int new_speed) {
    int v = M + pos;
    w[v] = {new_speed, pos + 1};
    v /= 2;
    while (v > 0) {
        w[v] = max(w[2 * v], w[2 * v + 1]);
        v /= 2;
    }
}

pair<int, int> query(int a, int b) {
    int va = M + a, vb = M + b;
    pair<int, int> wyn = w[va];
    if (va != vb) wyn = max(wyn, w[vb]);

    while (va / 2 != vb / 2) {
        if (va % 2 == 0) wyn = max(wyn, w[va + 1]);
        if (vb % 2 == 1) wyn = max(wyn, w[vb - 1]);
        va /= 2;
        vb /= 2;
    }
    return wyn;
}

int main() {
    ios::sync_with_stdio(false);
    int n, k;
    cin >> n >> k;

    vector<int> speeds(n);
    for (int i = 0; i < n; ++i) {
        cin >> speeds[i];
    }

    build(speeds);
    vector <int> results;
    for (int i = 0; i < k; ++i) {
        int x;
        cin >> x;

        for (int j = 0; j < x; ++j) {
            int car, increase;
            cin >> car >> increase;
            car--;
            speeds[car] += increase;
            update(car, speeds[car]);
        }

        int a, b;
        cin >> a >> b;
        a--; b--;

        pair<int, int> result = query(a, b);
        results.push_back(result.second);
    }
    for(int i=0;i<results.size();i++){
        cout<<results[i]<<"\n";
    }

    return 0;
}

