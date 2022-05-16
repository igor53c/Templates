#include "Datum.h"

const int Datum::DEFAULT_TAG = 1;
const int Datum::DEFAULT_MONAT = 1;
const int Datum::DEFAULT_JAHR = 2000;

const int Datum::maxMonatstage[]{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

const string Datum::arrMonatsname[]{
	"", "Januar", "Februar", "März", "April", "Mai", "Juni",
	"Juli", "August", "September", "Oktober", "November", "Dezember"
};

Datum::Datum()
{
	tag = DEFAULT_TAG;
	monat = DEFAULT_MONAT;
	jahr = DEFAULT_JAHR;
}

Datum::Datum(const int tag, const int monat, const int jahr) : Datum()
{
	setDatum(tag, monat, jahr);
}

bool Datum::setDatum(const int tag, const int monat, const int jahr)
{
	bool retValue = false;

	if (checkDatum(tag, monat, jahr))
	{
		this->tag = tag;
		this->monat = monat;
		this->jahr = jahr;

		retValue = true;
	}

	return retValue;
}

bool Datum::setTag(const int value)
{
	return setDatum(value, monat, jahr);
}

int Datum::getTag() const
{
	return tag;
}

bool Datum::setMonat(const int value)
{
	return setDatum(tag, value, jahr);
}

int Datum::getMonat() const
{
	return monat;
}

bool Datum::setJahr(const int value)
{
	return setDatum(tag, monat, value);
}

int Datum::getJahr() const
{
	return jahr;
}

string Datum::toString() const
{
	char buffer[16];

	sprintf_s(buffer, "%02d.%02d.%d", tag, monat, jahr);

	return static_cast<string>(buffer);
}

string Datum::toLongString() const
{
	char buffer[32];

	sprintf_s(buffer, "%02d. %s %d", tag, arrMonatsname[monat].c_str(), jahr);

	return static_cast<string>(buffer);
}

bool Datum::addiereJahre(const int anzahl)
{
	bool retValue = false;

	if (checkJahr(jahr + anzahl))
	{
		jahr += anzahl;

		if (!checkDatum(tag, monat, jahr))
			retValue = setDatum(getMaxMonatstage(monat, jahr), monat, jahr);
	}

	return retValue;
}

bool Datum::addiereMonate(const int anzahl)
{
	bool retValue = true;

	int aktTag = tag;
	int aktMonat = monat;
	int aktJahr = jahr;

	int anzahlJahre = anzahl / 12;
	int anzahlMonate = anzahl % 12;

	if (!checkJahr(jahr + anzahlJahre))
	{
		return false;
	}

	jahr += anzahlJahre;

	monat += anzahlMonate;

	if (monat > 12)
	{
		jahr++;
		monat = monat % 12;
	}

	else if (monat < 1)
	{
		jahr--;
		monat = 12 + monat;
	}

	if (!checkJahr(jahr))
	{
		setDatum(aktTag, aktMonat, aktJahr);
		retValue = false;
	}

	else if (!checkDatum(tag, monat, jahr))
	{
		retValue = setDatum(getMaxMonatstage(monat, jahr), monat, jahr);
	}

	return retValue;
}

bool Datum::addiereTage(int anzahl)
{
	bool retValue = true;

	int aktTag = tag;
	int aktMonat = monat;
	int aktJahr = jahr;

	while (anzahl > 0)
	{
		if (tag + anzahl > getMaxMonatstage(monat, jahr))
		{
			anzahl -= (getMaxMonatstage(monat, jahr) - tag) + 1;

			monat++;
			if (monat > 12)
			{
				jahr++;
				monat = 1;
			}

			tag = 1;
		}
		else
		{
			tag += anzahl;

			anzahl = 0;
		}
	}

	while (anzahl < 0)
	{
		if (tag + anzahl < 1)
		{
			anzahl += tag;

			monat--;

			if (monat < 1)
			{
				monat = 12;
				jahr--;
			}

			tag = getMaxMonatstage(monat, jahr);
		}
		else
		{
			tag += anzahl;

			anzahl = 0;
		}
	}

	if (!checkDatum(tag, monat, jahr))
	{
		retValue = setDatum(aktTag, aktMonat, aktJahr);
		retValue = false;
	}

	return retValue;
}

bool Datum::istSchaltjahr(const int jahr)
{
	bool retValue = false;

	if ((jahr % 4 == 0 && jahr % 100 != 0) || (jahr % 400 == 0))
		retValue = true;

	return retValue;
}

bool Datum::checkDatum(const int tag, const int monat, const int jahr) const
{
	return (checkJahr(jahr) && checkMonat(monat) && checkTag(tag, monat, jahr));
}

bool Datum::checkJahr(const int jahr) const
{
	return (jahr > 1582);
}

bool Datum::checkMonat(const int monat) const
{
	return (monat >= 1 && monat <= 12);
}

bool Datum::checkTag(const int tag, const int monat, const int jahr) const
{
	return (tag >= 1 && tag <= getMaxMonatstage(monat, jahr));
}

int Datum::getMaxMonatstage(const int monat, const int jahr) const
{
	int retValue = maxMonatstage[monat];

	if (monat == 2)
		retValue += (istSchaltjahr(jahr)) ? 1 : 0;

	return retValue;
}

bool Datum::operator==(const Datum& that) const
{
	return jahr == that.getJahr() && monat == that.getMonat() && tag == that.getTag();
}

bool Datum::operator!=(const Datum& that) const
{
	return jahr != that.getJahr() || monat != that.getMonat() || tag != that.getTag();
}

bool Datum::operator<(const Datum& that) const
{
	if (jahr < that.getJahr())
		return true;

	if (jahr == that.getJahr())
	{
		if (monat < that.getMonat())
			return true;

		if (monat == that.getMonat() && tag < that.getTag())
			return true;
	}

	return  false;
}

bool Datum::operator>(const Datum& that) const
{
	if (jahr > that.getJahr())
		return true;

	if (jahr == that.getJahr())
	{
		if (monat > that.getMonat())
			return true;

		if (monat == that.getMonat() && tag > that.getTag())
			return true;
	}

	return false;
}

bool Datum::operator>=(const Datum& that) const
{
	return !(*this < that);
}

bool Datum::operator<=(const Datum& that) const
{
	return !(*this > that);
}

Datum Datum::operator+(const int value) const
{
	Datum retValue = *this;

	retValue.addiereTage(value);

	return retValue;
}

Datum Datum::operator-(const int value) const
{
	Datum retValue = *this;

	retValue.addiereTage(-value);

	return retValue;
}

Datum& Datum::operator+=(const int value)
{
	addiereTage(value);

	return *this;
}

Datum& Datum::operator-=(const int value)
{
	addiereTage(-value);

	return *this;
}

Datum& Datum::operator++()
{
	addiereTage(1);

	return *this;
}

Datum Datum::operator++(int)
{
	Datum temp = *this;

	addiereTage(1);

	return temp;
}

Datum& Datum::operator--()
{
	addiereTage(-1);

	return *this;
}

Datum Datum::operator--(int)
{
	Datum temp = *this;

	addiereTage(-1);

	return temp;
}
