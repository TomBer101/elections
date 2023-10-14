#include "general.h"
#include <iostream>
using namespace std;

namespace elections
{
	void printMenuOptions()
	{
		cout << endl;
		cout << "Please enter your choice: " << endl;
		cout << "1- Add a new district (enter district name, and number of deligators)" << endl;
		cout << "2- Add a new citizen (enter name, id, year of birth and district num)" << endl;
		cout << "3- Add a new party (enter name, and id of the candidate to the government)" << endl;
		cout << "4- Add a citizen as a delegator of party (enter name, party number and district)" << endl;
		cout << "5- Show all districts" << endl;
		cout << "6- Show all citizens" << endl;
		cout << "7- Show all parties" << endl;
		cout << "8- Add vote: please enter id and party number:" << endl;
		cout << "9- Show elections results" << endl;
		cout << "10- exit" << endl;
		cout << endl;
	}

	void districtInput(election_round& round)
	{
		int delegates, i = 0;
		char name[MAX_SIZE];

		cout << "Please enter ditrict name: " << endl;
		cin.ignore();
		cin.getline(name, MAX_SIZE);

		cout << "Please enter number of delegates in the district: " << endl;
		cin >> delegates;

		if (!round.addDistrict(name, delegates))
			cout << "District name already exist!" << endl;
	}

	void citizenInput(election_round& round)
	{
		int year, dist;
		char id[10];
		char name[MAX_SIZE];

		cout << "Plesse enter name: " << endl;
		cin.ignore();
		cin.get(name, MAX_SIZE);

		cout << "Please enter id: " << endl;
		cin >> id;

		cout << "Please enter year of birth: " << endl;
		cin >> year;
		cout << "Please enter district number: " << endl;
		cin >> dist;

		if (!round.addCitizen(name, id, year, dist))
			cout << "Citzen id already exist!" << endl;
	}

	void partyInput(election_round& round)
	{
		char name[MAX_SIZE];
		char candidate_id[10];
		int res, i = 0;

		cin.ignore();
		cout << "Plesse enter party name: " << endl;
		cin >> name;

		cout << "Plesse enter candidate's id: " << endl;
		cin >> candidate_id;

		res = round.addParty(name, candidate_id);
		if (res == 0)
			cout << "Party name already exist!" << endl;
		else if (res == 1)
			cout << "Candidate is not a citizen!" << endl;
		else if (res == 2)
			cout << "Candidnate already has a part!" << endl;
		else if (res == 3)
			cout << "Candidnate is a minor citizen!" << endl;
	}

	void citizenAsDelegate(election_round& round)
	{
		int party, dist, i = 0, res;
		char id[10];

		cout << "Please enter party number: " << endl;
		cin >> party;

		cout << "Please enter district number: " << endl;
		cin >> dist;

		cout << "Please enter id: " << endl;
		cin >> id;

		res = round.addDeligate(id, party, dist);
		if (res == 0)
			cout << "Citizen already takes part!" << endl;
		else if (res == 1)
			cout << "Candidnate is a minor citizen!" << endl;
		else if (res == 2)
			cout << "District does not exist!" << endl;
		else if (res == 5) { cout << " Citizen does not exist." << endl; }
		else if (res == 3)
			cout << "Party does not exist!" << endl;
	}

	void vote(election_round& round)
	{
		int party, i = 0;
		char id[10];

		cout << "Please enter party number: " << endl;
		cin >> party;

		cout << "Please enter id: " << endl;
		cin >> id;

		int res;
		res = round.addVote(id, party); //NEW_OFEK
		if (res == 0)
			cout << "Citizen does not exsit!" << endl;
		else if (res == 1)
			cout << "Citizen already voted!" << endl;
		else if (res == 2)
			cout << "Party does not exsit!" << endl;
		else if (res == 3)
			cout << "Party does not has delegates in cisiten's district!" << endl;
	}

	void showResults(election_round& round)
	{
		round.showResults();
	}

	void show_all_district(election_round& round)
	{
		round.showAllDistrict();
	}

	void show_all_citizen(election_round& round)
	{
		round.showAllCitizen();
	}

	void show_all_parties(election_round& round)
	{
		round.showAllParties();
	}

}