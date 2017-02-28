#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

bool pred(const pair<string, size_t> &a, const pair<string, size_t> &b)
{
	return a.second > b.second;
}

bool delChar(char c)
{
	switch (c)
	{
	case ',':
	case '.':
	case '!':
	case '?':
	case ':':
	case ';':
	case '-':
		return true;
	default:
		return false;
	}
}

int main()
{
	string path;
	string line;
	string word;
	map<string, size_t> word_count;

	cout << "Еnter the path to the file: " << endl;
	cin >> path;

	ifstream in(path);

	if (in.is_open()) {

		while (getline(in, line)) {
			//удаляем лишние символы
			line.erase(remove_if(line.begin(), line.end(), &delChar), line.end());
			//превращаем текст в нижний регистр и сортирует по алфавиту
			transform(line.begin(), line.end(), line.begin(), ::tolower);

			istringstream istr(line);

			while (istr >> word) {

				++word_count[word];
			}
		}

		in.close();

	}
	else {

		cout << "Unable to open file";

	}

	//создаем вектор из map'a
	vector<pair<string, size_t> > vec{ word_count.begin(), word_count.end() };

	//сортируем этот вектор по значению
	sort(vec.begin(), vec.end(), pred);

	for (const auto &p : vec) {

		cout << p.first << "\t" << p.second << endl;
	}

	system("pause");

	return 0;
}
