#include "citizen_list.h"

namespace elections
{
	elections::citizen_list::citizen_list() :
		_size(0), head(nullptr), tail(nullptr)
	{}

	elections::citizen_list::~citizen_list()
	{
		while (head != nullptr)
		{
			listnode* tmp = head;
			head = head->next;
			delete tmp;
		}
	}

	citizen* elections::citizen_list::add_to_list(const citizen& toAdd)
	{
		/* we will add a person to the tail of the list.
		* I have also added bool* can_vote : if = true, we will also add
		*the citizen adress to the correct district list.
		* citizin* loc will hold that citizen adress, to pass to the other list.
		*/
		citizen* person = new citizen(toAdd); // using copy ctor
		listnode* new_citizen = new listnode;

		new_citizen->data = person;
		new_citizen->next = nullptr;

		if (head == nullptr)
		{
			head = tail = new_citizen;
		}
		else
		{
			tail->next = new_citizen;
			tail = tail->next;
		}
		_size++;

		return person;
	}

	bool citizen_list::add_to_list(const citizen* toAdd)
	{
		listnode* new_node = new listnode;
		new_node->data = const_cast<citizen*>(toAdd);
		new_node->next = nullptr;

		if (head == nullptr)
			head = tail = new_node;
		else
		{
			tail->next = new_node;
			tail = tail->next;
		}

		this->_size++;
		return true;
	}

	void citizen_list::print_list() const
	{
		listnode* tmp = head;

		while (tmp != nullptr)
		{
			cout << *tmp->data << endl;
			tmp = tmp->next;
		}
	}

	void citizen_list::add_delegators_to_arr(citizen** arr, int num, int& count) const
	{
		listnode* tmp = head;
		int idx = 0;

		while (tmp != nullptr && idx < num)
		{
			arr[count] = tmp->data;
			idx++;
			count++;
			tmp = tmp->next;
		}
	}

	const citizen* citizen_list::get_citizen(const char* id) const
	{
		listnode* tmp = head;

		while (tmp != nullptr)
		{
			if (*tmp->data == id) // compares ID
			{
				break;
			}
			tmp = tmp->next;
		}
		if (tmp != nullptr) // in case person was faound
			return tmp->data;
		return nullptr;
	}

	citizen* citizen_list::getCitizen(int idx) const 
	{
		listnode* temp = head;
		int index = 0;

		while (head != nullptr && index < _size)
		{
			if (idx == index)
				return temp->data;
			else
			{
				temp = temp->next;
				index++;
			}
		}
		
	}


}



