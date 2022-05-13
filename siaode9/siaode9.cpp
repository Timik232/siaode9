// siaode9.cpp : 
//Поиск по бору	|| Регистрация малого предприятия: номер лицензии -строковое значение из цифр и букв, название, учредитель
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
const int N = 100;  //переменная, отвечающая за количество элементов, которые будут сгенерированы
struct business
{
	string license;
	string name;
	string founder;
	business(string license, string name, string founder) :name(name), license(license), founder(founder) {};
};
struct node 
{
	node* next[36];     //Массив указателей на следующие вершины
						//next[i] - указатель на следующую вершину, соответствующую символу ('a' + i)
						//(используются только строчные латинские буквы и цифры)

	int strings;        //Количество строк, заканчивающихся в этой вершине.
	business* end_b;
	node()
	{
		for (int i = 0; i < 36; i++) 
		{   //изначально заполняем next нулевыми указателями,
			next[i] = nullptr;           //так как следующие вершины ещё не созданы
		}

		strings = 0;
		end_b = nullptr;
	}
};
node* root = new node();     //корневая вершина бора, соответствующая пустой строке.

void add(const string& s, business* end_b) 
{
	node* cur_v = root;     //текущая вершина

	for (int i = 0; i < s.length(); i++) 
	{
		char c = s[i];

		if (cur_v->next[c - 'a'] == nullptr)
		{
			cur_v->next[c - 'a'] = new node();
		}
		else if (cur_v->next[c - '0'] == nullptr)
		{
			cur_v->next[c - '0'] = new node();
		}
		cur_v = cur_v->next[c - 'a'];
		
	}
	cur_v->end_b = end_b;
	cur_v->strings++;
}
bool has(const string& s) //проверка, есть ли элемент в графе
{
	node* cur_v = root;

	for (int i = 0; i < s.length(); i++) 
	{
		cur_v = cur_v->next[s[i] - 'a'];
		if (cur_v == nullptr) 
		{
			return false;
		}
	}
	return cur_v->strings > 0;
}

void write(node* v = root) //вывести
{
	string cur_str = "";

	for (int i = 0; i < v->strings; i++) 
	{
		cout << cur_str << endl;
	}

	for (int i = 0; i < 26; i++) 
	{
		if (v->next[i] != nullptr) 
		{
			cur_str.push_back('a' + i);
			write(v->next[i]);
			cur_str.pop_back();
		}
	}
}
void bor_find(vector <business> strings, string lic)
{
	node* cur_v = root;
	bool flag = true;
	for (int i = 0; i < lic.length(); i++)
	{
		if (i<5)
			cur_v = cur_v->next[lic[i] - 'a'];
		else if (i>4)
			cur_v = cur_v->next[lic[i] - '0'];
		if (cur_v != nullptr)
		{
			continue;
		}
		else
		{
			flag = false;
			cout << "Key not found\n";
			break;
		}
	}
	if (flag)
		cout << cur_v->end_b->license << " " << cur_v->end_b->name << " " << cur_v->end_b->founder;
}
/*struct bohr_v
{
	int next_vrtx[36], pat_num;
	bool flag;
};

bohr_v make_bohr_vrtx() //создание корня
{
	bohr_v v;
	//(255)=(2^8-1)=(все единицы в каждом байте памяти)=(-1 в дополнительном коде целого 4-байтного числа int)
	memset(v.next_vrtx, 255, sizeof(v.next_vrtx));
	v.flag = false;
	return v;
}
void bohr_ini(vector <bohr_v> &bohr)  //инициализация бора
{
	//добавляем единственную вершину - корень
	bohr.push_back(make_bohr_vrtx());
}
void add_string_to_bohr(const string& s, vector <bohr_v> &bohr) //добавление элемента
{
	int num = 0; //начинаем с корня   
	for (int i = 0; i < s.length(); i++) 
	{
		char ch = s[i] - 'a'; //получаем номер в алфавите
		if (bohr[num].next_vrtx[ch] == -1) //-1 - признак отсутствия ребра
		{ 
			bohr.push_back(make_bohr_vrtx());
			bohr[num].next_vrtx[ch] = bohr.size() - 1;
		}
		num = bohr[num].next_vrtx[ch];
	}
	bohr[num].flag = true;
	pattern.push_back(s);
	bohr[num].pat_num = pattern.size() - 1;
}*/

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

int main()
{
	srand(time(0));
	vector <business> strings;
	rand_val(strings, N);
	//print(strings,0); //вывод сгенерированной таблицы
	cout << "find " << strings[80].license << endl;
	unsigned int start_time = clock();
	lin_find(strings, strings[80].license); 
	unsigned int end_time = clock();
	cout << "Time of linear find: " << end_time - start_time << endl;
	start_time = clock();
	barrier_find(strings, strings[80].license);
	end_time = clock();
	cout << "Time of barrier find: " << end_time - start_time << endl;
	//vector <node*> bohr;
	for (int i = 0; i < strings.size(); i++)
	{
		add(strings[i].license, strings[i]);
	}
	write();
	start_time = clock();
	//bor_find(strings, strings[8000].license);
	end_time = clock();
	cout << "Time of bor find: " << end_time - start_time << endl;
}
