// Templates.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <bitset>

#include "Stack.h"
#include "Datum.h"

using namespace std;

void tauscheRef(int&, int&);

template <typename T> void tausche(T&, T&);
template <typename T> void bubbleSort(T[], const size_t);
template <typename T> void ausgabe(const T[], const size_t);
template <typename T> string toBinaryString(const T);

void integerStack();
void datumStack();

int main()
{
	locale::global(locale("German_germany"));

	int a = 5, b = 7;
	cout << "a: " << a << ", b: " << b << endl;

	tauscheRef(a, b);
	cout << "a: " << a << ", b: " << b << endl;
	cout << endl;

	int i1 = 42;
	int i2 = 99;

	cout << "i1: " << i1 << ", i2: " << i2 << endl;
	tausche<int>(i1, i2);
	cout << "i1: " << i1 << ", i2: " << i2 << endl;
	cout << endl;

	double d1 = 3.121592;
	double d2 = 2.718281;

	cout << "d1: " << d1 << ", d2: " << d2 << endl;
	tausche<double>(d1, d2);
	cout << "d1: " << d1 << ", d2: " << d2 << endl;
	cout << endl;

	string s1 = "Links";
	string s2 = "Rechts";

	cout << "s1: " << s1 << ", s2: " << s2 << endl;
	tausche<string>(s1, s2);
	cout << "s1: " << s1 << ", s2: " << s2 << endl;
	cout << endl;

	int lotto[]{ 42, 5, 38, 12, 21, 17 };
	bubbleSort<int>(lotto, size(lotto));
	ausgabe<int>(lotto, size(lotto));
	cout << endl;

	double dblArray[]{ 3.14, 9.88, 2.86, 42.0, 1.44 };
	bubbleSort<double>(dblArray, size(dblArray));
	ausgabe<double>(dblArray, size(dblArray));
	cout << endl;

	char charArray[]{ 'x', 'a', 'h', 'z', 'f' };
	bubbleSort<char>(charArray, size(charArray));
	ausgabe<char>(charArray, size(charArray));
	cout << endl;

	string stringArray[]{ "Hamster", "Zebra", "Katze", "Affe", "Hund" };
	bubbleSort<string>(stringArray, size(stringArray));
	ausgabe<string>(stringArray, size(stringArray));
	cout << endl;

	string binString;

	unsigned char usChar = 24;
	cout << "unsigned char: " << static_cast<int>(usChar) << endl;
	binString = toBinaryString<unsigned char>(usChar);
	cout << binString << ": " << binString.length() << " Bits" << endl;
	cout << endl;

	unsigned short usValue = 24;
	cout << "unsigned short: " << usValue << endl;
	binString = toBinaryString<unsigned short>(usValue);
	cout << binString << ": " << binString.length() << " Bits" << endl;
	cout << endl;

	unsigned long long ulValue = 24;
	cout << "unsigned long long: " << ulValue << endl;
	binString = toBinaryString<unsigned long long>(ulValue);
	cout << binString << ": " << binString.length() << " Bits" << endl;
	cout << endl;

	integerStack();

	datumStack();

	return EXIT_SUCCESS;
}

void tauscheRef(int& a, int& b)
{
	int temp = a;

	a = b;
	b = temp;
}

void integerStack()
{
	Stack<int> stapel;

	stapel.push(2);
	stapel.push(3);
	stapel.push(5);
	stapel.push(7);
	stapel.push(11);
	stapel.push(13);
	stapel.push(17);

	while (!stapel.isEmpty())
	{
		cout << stapel.pop() << endl;
	}

	cout << endl;

	Stack<int> stapel1(10);

	int i = 1;

	while (!stapel1.isFull())
	{
		stapel1.push(i++);
	}

	while (!stapel1.isEmpty())
	{
		cout << stapel1.pop() << endl;
	}

	cout << endl;

	Stack<int> stapel2 = Stack<int>(10);

	for (int i = 1; i <= 500; i++)
	{
		stapel2.push(i);
	}

	while (!stapel2.isEmpty())
	{
		cout << stapel2.pop() << endl;
	}

	cout << endl;
}

void datumStack()
{
	int aktJahr = 2022;

	Stack<Datum> stapel(5);

	Datum startDatum(1, 1, aktJahr);
	Datum endeDatum(31, 12, aktJahr);
	Datum aktDatum = startDatum;

	do
	{
		stapel.push(aktDatum);
		aktDatum.addiereTage(1);
	} while (aktDatum <= endeDatum);


	while (!stapel.isEmpty())
	{
		cout << stapel.pop().toString() << endl;
	}

	cout << endl;
}


template<typename T> void tausche(T& a, T& b)
{
	auto temp = a;

	a = b;
	b = temp;
}

template<typename T> void bubbleSort(T arr[], const size_t size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (arr[i] > arr[j])
				swap(arr[j], arr[i]);
		}
	}
}

template<typename T> void ausgabe(const T arr[], const size_t size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << ", ";

	cout << endl;
}

template<typename T> string toBinaryString(const T value)
{
	string binaryString;

	bitset<sizeof(value) * 8> bitSet(value);

	for (int i = 0; i < bitSet.size(); i++)
	{
		binaryString = (bitSet.test(i) ? "1" : "0") + binaryString;
	}

	return binaryString;
}