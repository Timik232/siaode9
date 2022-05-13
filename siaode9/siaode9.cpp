// siaode9.cpp : 
//Поиск по бору	|| Регистрация малого предприятия: номер лицензии -строковое значение из цифр и букв, название, учредитель
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
struct business
{
	string license;
	string name;
	string founder;
	business(string license, string name, string founder) :name(name), license(license), founder(founder) {};
};
void print(vector <business> strings, int n) //вывод элементов таблицы
{
	cout << setw(10) << "license" << setw(10) << "name" << setw(10) << "founder" << endl;
	if (n == 0)
	{
		for (int i = 0; i < strings.size(); i++)
			cout << setw(10) << strings[i].license << setw(10) << strings[i].name << setw(10) << strings[i].founder << endl;
	}
	else cout << setw(10) << strings[n].license << setw(10) << strings[n].name << setw(10) << strings[n].founder << endl;
}
void rand_val(vector <business> &strings, int n)
{
	for (int i = 0; i < n; i++)
	{
		string name = "";
		string founder = "";
		string license = "";
		for (int j = 0; j < 4; j++) //генерация имени
			name += (char)(rand() % 26 + 97);
		for (int j = 0; j < 6; j++) //генерация имени
			founder += (char)(rand() % 26 + 97);
		for (int j = 0; j < 4; j++) //генерация имени
			license += (char)(rand() % 26 + 97);
		for (int j = 0; j < 3; j++) //генерация имени
			license += to_string(rand() % 10);
		business B(license, name, founder);
		strings.push_back(B);
	}
}
void lin_find(vector <business> strings, string lic) //линейный поиск, "грубый"
{
	bool flag = false;
	for (int i = 0; i < strings.size(); i++)
		if (strings[i].license == lic)
		{
			flag = true;
			print(strings, i);
		}
	if (!flag)
		cout << "Key not found \n";
}
void barrier_find(vector <business> strings, string lic) //поиск с барьером
{
	string last = strings[strings.size() - 1].license; //Сохраним прежний элемент массива
	strings[strings.size() - 1].license = lic; //Гарантируем, что value есть в массиве
	//Есть гарантия того, что элемент есть в массиве, значит индекс можно не проверять
	int i = 0;
	while (strings[i].license != lic) i++;
	strings[strings.size() - 1].license = last; //Восстанавливаем последний элемент
	if (i != (strings.size() - 1) || lic == last) //Не уткнулись в барьер или последний элемент был искомым
	{
		print(strings, i);
	}
	else cout << "Key not found\n";
}
void bor_find(vector <business> strings, string lic)
{

}
int main()
{
	int n = 10000; //переменная, отвечающая за количество элементов, которые будут сгенерированы
	srand(time(0));
	vector <business> strings;
	rand_val(strings, n);
	//print(strings,0); //вывод сгенерированной таблицы
	cout << "find " << strings[8000].license << endl;
	unsigned int start_time = clock();
	lin_find(strings, strings[8000].license); 
	unsigned int end_time = clock();
	cout << "Time of linear find: " << end_time - start_time << endl;
	start_time = clock();
	barrier_find(strings, strings[8000].license);
	end_time = clock();
	cout << "Time of barrier find: " << end_time - start_time << endl;
	start_time = clock();
	bor_find(strings, strings[8000].license);
	end_time = clock();
	cout << "Time of bor find: " << end_time - start_time << endl;
}
