#include "citizen.h"

namespace elections
{
	void citizen::copyName(const char* src)
	{
		int size = strlen(src);
		_name = new char[size + 1];
		for (int i = 0; i < size; ++i)
		{
			_name[i] = src[i];
		}
		_name[size] = '\0';
	}

	citizen::citizen(const char* name, const char* id, int year, int dist) :
		_vote(false), _district(dist), _year_of_birth(year), has_a_part(false), city(nullptr)
	{
		for (int i = 0; i < 10; ++i)
		{
			_ID[i] = id[i];
		}

		copyName(name);
	}

	citizen::citizen(const citizen& other)
		: _district(other._district), _year_of_birth(other._year_of_birth), _vote(other._vote), has_a_part(false), city(other.city)
	{
		const char* src = other.getID();
		for (int i = 0; i < 10; ++i)
		{
			_ID[i] = src[i];
		}

		copyName(other.getName());
	}

	citizen::~citizen()
	{
		delete[] _name;
	}

	void citizen::set_vote_stat(bool vote)
	{
		if (_vote == false)
		{
			_vote = vote;
		}
	}

	void citizen::setCity(const district* new_city)
	{
		city =const_cast<district*>(new_city);
	}

	bool citizen::operator==(const char* ID) const
	{
		int res = strcmp(this->_ID, ID);
		if (res == 0)
			return true;
		return false;
	}

	ostream& operator<<(ostream& os, const citizen& person)
	{
		// name, ID, year, dist
		os << "name: " << person._name << " ID : " << person._ID << " year of burth: " << person._year_of_birth << " from district: " << person._district;
		return os;
	}

}

