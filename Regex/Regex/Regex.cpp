// Regex.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <regex>
#include <iostream>
#include <fstream>
#include <bitset>
#include <sstream>
#include <vector>

using namespace std;
//liter_0 <= "00000100"; liter_1 <= "00000001"; wait for 10 ns;
int main(uint_fast16_t argc, char* argv[])
{
	int StreamNumber = 1;
	

	setlocale(LC_ALL, "Russian");

	if ((argc == 1) || (strcmp(argv[1], "-i") == 0)) {
		cout << endl << endl;
		cout << ">>------------------   Информационная панель  ------------------<<" << endl;
		cout << ">>Формат запуска программы:                                     <<" << endl;
		cout << ">>      <progName>.exe  -param_1 -param_2 ...    <<" << endl;
		cout << ">>  -i     |  Информация о параметрах                           <<" << endl;
		cout << ">>  -s     |  Количество потоков                                <<" << endl;
		cout << ">>  -o     |  Создать файл с именами входных файлов             <<" << endl;
		cout << ">>--------------------------------------------------------------<<" << endl;
		cout << endl;
		return 0;
	}
	//for()
	//cin<<
	
	

	for (uint_fast16_t i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-s") == 0) {
			if (argv[i + 1][0] != '-')
				sscanf_s(argv[i + 1], "%d", &StreamNumber);
		}
		if (strcmp(argv[i], "-o") == 0) {
			ofstream inputFiles;
			cout << "Создан файл \"inputFiles.txt\". Введите в нем название загружаемых файлов, по одному файлу в строке и перезапустите программу :)" << endl;
			inputFiles.open("inputFiles.txt");
			inputFiles.close();
			return 0;
		}
	}


	
	vector<string> name;
	

	string line;
	ifstream inputFiles("inputFiles.txt");
	if (inputFiles.is_open())
	{
		while (getline(inputFiles, line)) {
			name.resize(name.size()+1);
			name.back() = line;
		}

	}
	inputFiles.close();
	
	
	ofstream tout,fout;
	tout.open("MEM.coe");
	fout.open("TestBench.txt");
	
	tout << "MEMORY_INITIALIZATION_RADIX=2;\nMEMORY_INITIALIZATION_VECTOR = \n";
	for (int r = 0; r < name.size(); r++) {
		
		string line;
		vector<string>linesArray;
		vector<vector<string>>linesArrayArr;
		linesArrayArr.resize(StreamNumber);
		ifstream Huffman(name[r]);
		if (Huffman.is_open())
		{
			cout << "Файл " + name[r] + " обработан" << endl;
			int i = 0;
			while (getline(Huffman, line))
			{

				smatch h;
				line = regex_replace(line, regex(" "), "");
				stringstream test;
				test << hex << line;
				unsigned int test1;
				test >> test1;
				bitset<8>bits(test1);
				linesArrayArr[i % StreamNumber].push_back(bits.to_string());

				i++;
			}
		}
		else {
			cout<< "\tФайл " + name[r] + " не обнаружен!" << endl;
		}
		Huffman.close();
		name[r] = name[r].substr(0, name[r].size() - 4);
		
		string testBench;
		

		for (int j = 1; j < linesArrayArr.size(); j++) {
			if (linesArrayArr[0].size() > linesArrayArr[j].size()) {
				linesArrayArr[j].push_back("00000000");
			}
		}
		for (int i = 0; i < linesArrayArr[0].size(); i++) {

			testBench = "";
			for (int j = 0; j < linesArrayArr.size(); j++)
				testBench += "liter_0(" + to_string(j) + ") <= \"" + linesArrayArr[j][i] + "; ";
			testBench += "wait for 10 ns;";
			fout << testBench << endl;

		}
	
		string mems;

		for (int j = 0; j < linesArrayArr[0].size(); j++) {
			mems = "";
			for (int i = 0; i < StreamNumber; i++) {
				mems += linesArrayArr[i][j];
			}

			//
		//}
			if(r==name.size()-1 && j== linesArrayArr[0].size()-1)
				mems += ";";
			else {
					mems += ",\n";
			}
			tout << mems;
			//cout << j << endl;
		}
	}
	fout.close();
	tout.close();
}
