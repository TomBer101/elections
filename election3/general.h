#pragma once
#include "election_round.h"

namespace elections
{
#define EXIT 10
#define MAX_SIZE 100

#define DAY 25
#define MONTH 9
#define YEAR 2020

	void printMenuOptions();
	void districtInput(election_round& round); //user press 1
	void citizenInput(election_round& round); //user press 2
	void partyInput(election_round& round); //user press 3
	void citizenAsDelegate(election_round& round); //user press 4
	void show_all_district(election_round& round); //user press 5
	void show_all_citizen(election_round& round); //user press 6
	void show_all_parties(election_round& round); //user press 7
	void vote(election_round& round); //user press 8
	void showResults(election_round& round); //user predss 9
}