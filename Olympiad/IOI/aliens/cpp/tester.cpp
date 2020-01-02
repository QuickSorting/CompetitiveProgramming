#include <bits/stdc++.h>

using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	system("g++ -std=c++11 -o aliens aliens.cpp grader.cpp");
	system("g++ -std=c++11 -o aliens2 aliens2.cpp grader.cpp");
	system("g++ -std=c++11 -o gen generator.cpp");

	int i = 0;
	while(true){
		cout << (++i) << endl;

		system("gen > input.txt");
		system("aliens < input.txt > output1.txt");
		system("aliens2 < input.txt > output2.txt");

		ifstream in1("output1.txt"), in2("output2.txt");
		string s1, s2;

		in1 >> s1;
		in2 >> s2;

		if(s1 != s2){
			cout << s1 << " " << s2 << "\n";
			return 0;
		}
	}
}