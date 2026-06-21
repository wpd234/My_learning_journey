#include <iostream>
using namespace std;
#include <string>

int main() {
  int n;
  cin >> n;
  string s;
  cin.ignore();
  getline(cin, s);
  for (int i = 0; i < s.size(); i++) {
    if (s[i] >= 'a' && s[i] <= 'z')
      s[i] = (s[i] - 'a' + 26 - n) % 26 + 'a';
    if (s[i] >= 'A' && s[i] <= 'Z')
      s[i] = (s[i] - 'A' + 26 - n) % 26 + 'A';
  }
  cout << s;
}