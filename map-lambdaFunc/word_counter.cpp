#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

map<string, int> getNumberOfWords(string file)
{
  string word;
  map<string, int> wordsFromText;
  ifstream inputFile;

  inputFile.open(file);
  while(inputFile >> word){
    if((word.at(0) == '(' && word.at(word.size() - 1) == ')') || (word.at(0) == '"' && word.at(word.size() - 1) == '"') || (word.at(0) == '[' && word.at(word.size() - 1) == ']'))
      {
	word.erase(0, 1);
	word.resize(word.size() - 1);
      }
    else if(word.at(word.size() - 1) == '.' || word.at(word.size() - 1) == ',' || word.at(word.size() - 1) == ')' || word.at(word.size() - 1) == '"' || word.at(word.size() - 1) == ':' || word.at(word.size() - 1) == ';' || word.at(word.size() - 1) == '!' || word.at(word.size() - 1) == '?')
      word.resize(word.size() - 1);
    else if(word.at(0) == '(' || word.at(0) == '"')
      word.erase(0, 1);
    wordsFromText[word]++;
  }
  inputFile.close();

  return wordsFromText;
}

void sortVecFunction(vector< pair<string, int> > & vec)
{
   auto sortFunc = [](pair<string, int> w1, pair<string, int> w2)
    {
      return w1.second < w2.second;
    };

   sort(vec.begin(), vec.end(), sortFunc);
}

int main()
{
  ofstream out;
  out.open("output.txt");

  map<string, int> wordsFreq = getNumberOfWords("input.txt");
  vector< pair<string, int> > wordsVec(wordsFreq.begin(),wordsFreq.end());

  sortVecFunction(wordsVec);

  for_each(wordsVec.begin(), wordsVec.end(), [&out](pair<string, int> word) mutable
	   {
	     //cout << word.first << " was found " << word.second << " times. " << endl;

	     out << "'" << word.first << "' was found " << word.second << " times." << endl;
	   });
  cout << "Finished!" << endl;
  out.close();
  return 0;
}
