#include "election_round.h"
#include "general.h"
using namespace elections;

int main()
{
	election_round round(DAY, MONTH, YEAR);
	int choice;

	cout << "HELLO!" << endl;
	printMenuOptions();
	cin >> choice;

	while (choice != EXIT)
	{
		switch (choice)
		{
		case 1:
		{
			districtInput(round);
			break;
		}

		case 2:
		{
			citizenInput(round);
			break;
		}
		case 3:
		{
			partyInput(round);
			break;
		}
		case 4:
		{
			citizenAsDelegate(round);
			break;
		}
		case (5):
		{
			round.showAllDistrict();
			break;
		}
		case (6):
		{
			round.showAllCitizen();
			break;
		}
		case (7):
		{
			round.showAllParties();
			break;
		}
		case (8):
		{
			vote(round);
			break;
		}
		case (9):
		{
			round.showResults();
			break;
		}
		}

		cout << "--------------------------------------------------------------------------------------\n" << endl;
		printMenuOptions();
		cin >> choice;
	}


	return 1;
}