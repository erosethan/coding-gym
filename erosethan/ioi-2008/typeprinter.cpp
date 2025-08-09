#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  int n;
  cin >> n;

  string longest_word;
  vector<pair<int, string>> words(n);
  for (auto& [_, word] : words) {
    cin >> word;
    if (longest_word.size() < word.size()) longest_word = word;
  }

  auto ComputeCommonPrefix = [](const string& lhs, const string& rhs) {
    int common_prefix = 0;
    while (common_prefix < lhs.size() && common_prefix < rhs.size() &&
           lhs[common_prefix] == rhs[common_prefix])
      ++common_prefix;
    return common_prefix;
  };

  for (auto& [common_prefix, word] : words)
    common_prefix = ComputeCommonPrefix(word, longest_word);
  sort(words.begin(), words.end());

  string commands = words[0].second + 'P';
  for (int i = 1; i < n; ++i) {
    int common_prefix =
        ComputeCommonPrefix(words[i - 1].second, words[i].second);
    commands += string(words[i - 1].second.size() - common_prefix, '-') +
                words[i].second.substr(common_prefix) + 'P';
  }

  cout << commands.size() << '\n';
  for (char c : commands) cout << c << '\n';
}
