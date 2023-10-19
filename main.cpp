#include <cctype>
#include <climits>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <sstream>
using namespace std;

class Dictionary {
private:
  set<string> words; // the dictionary
public:
  Dictionary();
  bool is_word(string word);
};

void spellcheck();

int main() {
  char yn; // for yes/no response
  do {
    // prompts for and spellchecks a file
    do {
      spellcheck();
      // Ask if should spellcheck another file
      cout << "Spellcheck another file? (y/n): ";
      cin >> yn;
      yn = tolower(yn);
      cin.ignore(INT_MAX, '\n');
    } while (yn != 'y' && yn != 'n');
    // Continue spellchecking until N is entered
  } while (yn == 'y');
}

void spellcheck() {
  // Get file name and open file
  string fname;
  cout << "Enter file name: ";
  getline(cin, fname);
  ifstream f(fname);
  // Check for open success
  if (!f) {
    cout << "Could not open file " << fname << ".\n";
    return;
  }

  // Spellcheck the file
  static Dictionary d;
  string line;
  int line_number = 0;
  while (getline(f, line)) {
    line_number++;
    // cout << line_number << ": " << line << endl;
    // Read line word-by-word
    istringstream is(line);
    string word;
    while (is >> word) {
      if (ispunct(word.back()) && word.back() != '\'')
        word = word.substr(0, word.size() - 1);
      if (word.size() && !d.is_word(word))
        cout << line_number << ": " << word << endl;
    }
  }
}

Dictionary::Dictionary() {
  ifstream f("words.txt");
  string word;
  while (f >> word)
    words.insert(word);
}

bool Dictionary::is_word(string word) {
  // Convert the given word to lowercase
  for (char& ch: word)
    ch = tolower(ch);
  // Find the word in the set, return true if found
  return words.find(word) != words.end();
}