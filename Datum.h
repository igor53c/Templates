#pragma once

#include <iostream>

using namespace std;

class Datum
{
public:

	Datum();
	Datum(const int, const int, const int);

	bool setDatum(const int, const int, const int);

	bool setTag(const int);
	int getTag() const;
	bool setMonat(const int);
	int getMonat() const;
	bool setJahr(const int);
	int getJahr() const;

	virtual string toString() const;
	virtual string toLongString() const;

	bool addiereJahre(const int);
	bool addiereMonate(const int);
	bool addiereTage(int);

	static bool istSchaltjahr(const int);

	bool operator==(const Datum&) const;
	bool operator!=(const Datum&) const;
	bool operator<(const Datum&) const;
	bool operator>(const Datum&) const;
	bool operator>=(const Datum&) const;
	bool operator<=(const Datum&) const;

	Datum operator+(const int) const;
	Datum operator-(const int) const;

	Datum& operator+=(const int);
	Datum& operator-=(const int);

	Datum& operator++();
	Datum operator++(int);
	
	Datum& operator--();
	Datum operator--(int);

private:

	int tag, monat, jahr;

	static const int DEFAULT_TAG, DEFAULT_MONAT, DEFAULT_JAHR;

	static const int maxMonatstage[];
	static const string arrMonatsname[];

	bool checkDatum(const int, const int, const int) const;
	bool checkJahr(const int) const;
	bool checkMonat(const int) const;
	bool checkTag(const int, const int, const int) const;

	int getMaxMonatstage(const int, const int) const;

};

