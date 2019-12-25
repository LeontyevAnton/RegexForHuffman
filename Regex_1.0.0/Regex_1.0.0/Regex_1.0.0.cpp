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
	string line1, line2, line3, line4;
	vector<string>linesArray1, linesArray2, linesArray3, linesArray4;
	ifstream Huffman("binCodes.txt");
	if (Huffman.is_open())
	{
		while (getline(Huffman, line))
		{
			smatch h;
			stringstream test;
			
			line1 = line.substr(0, 8);
			line= line.substr(8);
			line2 = line.substr(0, 8);
			line = line.substr(8);
			line3 = line.substr(0, 8);
			line = line.substr(8);
			line4 = line;
			linesArray1.push_back(line1);
			linesArray2.push_back(line2);
			linesArray3.push_back(line3);
			linesArray4.push_back(line4);
		}
	}
	
	ofstream fout;
	fout.open("testBench.txt");
	for (int i = 0; i < linesArray1.size(); i++)
	{
		string one = "liter_0 <= \"" + linesArray1[i] + "\"; liter_1 <= \"" + linesArray2[i] + "\"; wait for 10 ns;";
		string two = "liter_0 <= \"" + linesArray3[i] + "\"; liter_1 <= \"" + linesArray4[i] + "\"; wait for 10 ns;";
		fout << one << endl;
		fout << two << endl;
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
