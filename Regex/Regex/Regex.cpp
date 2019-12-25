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
int main()
{
	string line;
	vector<string>linesArray, linesArray1,linesArray2;
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
			if (i % 2 == 0)
				linesArray1.push_back(bits.to_string());
			else
				linesArray2.push_back(bits.to_string());
			i++;
		}
	}
	//vector<string>linesArray1(linesArray.begin(), linesArray.begin() + linesArray.size() / 2);
	//vector<string>linesArray2(linesArray.begin() + linesArray.size() / 2, linesArray.end());
	ofstream fout;
	cout << linesArray1.size() << "   " << linesArray2.size() << endl;
	fout.open("testBench.txt");
	for(int i=0;i<linesArray1.size();i++)
	{
		string one = "liter_0 <= \""+linesArray1[i]+"\"; liter_1 <= \""+linesArray2[i]+"\"; wait for 10 ns;";
		fout << one << endl;
	}
	fout.close();
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
