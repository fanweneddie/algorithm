#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main() {
  vector<string> vec1, vec2;
  vec1.push_back("aa");
  vec1.push_back("bb");
  vec1.push_back("cc");
  vec2.push_back("dd");
  vec2.push_back("ee");
  vec2.push_back("ff");
  vector<string> vec(vec1.size() + vec2.size());
  merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), vec.begin());

  for (int j = 0; j < vec.size(); ++j) {
    cout << vec[j] << endl;
  }


}
