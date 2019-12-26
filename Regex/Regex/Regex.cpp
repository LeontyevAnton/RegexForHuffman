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
	for (uint_fast16_t i = 1; i < argc; i++){
		if (strcmp(argv[i], "-i") == 0){
			cout << endl << endl;
			cout << ">>--------------------------   Info   --------------------------<<" << endl;
			cout << ">>  -i     |  Информация о параметрах                           <<" << endl;
			cout << ">>  -s     |  Количество потоков                                <<" << endl;
			cout << ">>--------------------------------------------------------------<<" << endl;
			cout << endl;
			return 0;
		}
		
		if (strcmp(argv[i], "-s") == 0){
			if (argv[i + 1][0] != '-')
				sscanf_s(argv[i + 1], "%d", &StreamNumber);
		}
	}


	
	string line;
	vector<string>linesArray;
	vector<vector<string>>linesArrayArr;
	linesArrayArr.resize(StreamNumber);
	ifstream Huffman("StandartDataHEX.txt");
	if (Huffman.is_open())
	{
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
	ofstream fout;
	string testBench;
	fout.open("testBench.txt");
	
	for (int j = 1; j < linesArrayArr.size(); j++) {
		if (linesArrayArr[0].size() > linesArrayArr[j].size()) {
			linesArrayArr[j].push_back("00000000");
		}
	}
	for(int i=0;i<linesArrayArr[0].size();i++){
		
		testBench = "";
		for (int j = 0; j < linesArrayArr.size(); j++)
			testBench += "liter_" + to_string(j) + " <= \"" + linesArrayArr[j][i] + "; ";
		testBench+= "wait for 10 ns;";
		fout << testBench << endl;
		
	}
	fout.close();

	vector<string>mems;
	mems.resize(StreamNumber);
	for (int i = 0; i < StreamNumber; i++) {
		ofstream fout;
		fout.open("Mem_" + to_string(i) + ".coe");
		mems[i] += "MEMORY_INITIALIZATION_RADIX=2;\nMEMORY_INITIALIZATION_VECTOR = \n";
		for (int j = 0; j < linesArrayArr[0].size(); j++){
			mems[i] += linesArrayArr[i][j] + ";\n";
		}
		fout << mems[i];
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
