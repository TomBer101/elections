#pragma once
#include "citizen.h"

namespace elections
{

	class citizen_list
	{
	private:
		struct listnode
		{
			citizen* data;
			listnode* next;
		};

		int _size; // in all citizen it is size, in a district it is amount of potentail voters 

		listnode* head;
		listnode* tail;


	public:
		citizen_list();
		~citizen_list();

		citizen* add_to_list(const citizen& toAdd);
		bool add_to_list(const citizen* toAdd);
		
		int getSize() const { return _size; }

		void print_list()const;
		void add_delegators_to_arr(citizen** arr, int num, int& count)const; // new

		const citizen* get_citizen(const char* id)const;
		citizen* getCitizen(int idx) const;


	};


}