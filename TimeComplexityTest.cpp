#include<iostream>
#include<chrono>

using namespace std;
using namespace chrono;

int slow(int n) {
    if(n < 2)return n;
    return slow(n - 1) + slow(n - 2);
}

int fast(int n) {
    int *tmp = new int[n+5];
	tmp[1] = tmp[2] = 1;
	for(int i = 3; i <= n; i++) {
		tmp[i] = tmp[i-1] + tmp[i-2];
		tmp[i] %= 1000000000;
	}
	n = tmp[n];
	delete[] tmp;
	return n;
}

int main() {
    for(int i = 30; i <= 55; i++) {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        slow(i);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        fast(i);
        high_resolution_clock::time_point t3 = high_resolution_clock::now();
        duration<double> timeSpent = duration_cast<duration<double>>(t2 - t1);
        cout << i << " " << timeSpent.count() << " ";
        timeSpent = duration_cast<duration<double>>(t3 - t2);
        cout << timeSpent.count() << endl;
    }
    return 0;
}