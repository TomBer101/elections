#include "election_round.h"
#include <iostream>

using namespace std;

namespace elections
{
    election_round::election_round(int _day, int _month, int _year) :
        day(_day), month(_month), year(_year)
    {}

    election_round::~election_round()
    {}

    bool election_round::addDistrict(const char* name, int num)
    {
        if (findDist(name)) // if district's name is taken.
            return false;
        else
        {
            all_dist.add_dist(num, name);
            all_citizen.add_list_ptr();
            return true;
        }
    }

    bool election_round::addCitizen(const char* name, const char* ID, int year, int dist)
    {
        const citizen* tmp_citizen = findCitizen(ID);

        if (tmp_citizen != nullptr) // Citizen is already exists.
            return false;

        int dist_amount = all_dist.getNumOfDistricts();
        const district* dist_ptr = findDist(dist);

        if (dist<0 || dist>dist_amount || dist_amount == 0 || dist_ptr == nullptr) //check if district info is ok
            return false;

        citizen toAdd = citizen(name, ID, year, dist);
        toAdd.setCity(dist_ptr);
        citizen* loc = all_citizen.add_citizien(toAdd);

        if (this->year - toAdd.getYear() >= 18) //if citizen can vote (age over 18)
            all_dist[dist].add_citizen_to_voters(loc);
        return true;
    }

    int election_round::addParty(const char* name, const char* ID)
    {
        if (findParty(name))
            return 0; // the party already exists

        const citizen* tmp_candidate = findCitizen(ID); // checks if head of the party exsits
        if (tmp_candidate == nullptr)
            return 1;
        else if (tmp_candidate->getPart()) //check if candidate already has a part
            return 2;
        else if (year - tmp_candidate->getYear() < 18) //check if candidate is over 18
            return 3;

        citizen* tmp = const_cast<citizen*>(tmp_candidate);
        all_parties.add_party(name, tmp);
        for (int i = 0; i < all_dist.getNumOfDistricts(); i++)
        {
            int size = all_parties.getSize();
            all_dist[i].get_kalpi().resizeBox(size);
        }
        return 4;
    }

    int election_round::addDeligate(const char* ID, int party, int dist)
    {
        const citizen* delegator;
        delegator = findCitizen(ID);

        if (delegator == nullptr)
            return 5;

        if (delegator->getPart()) //check if delegator already has a part
            return 0;
        else if (year - delegator->getYear() < 18) //check if delegator is over 18
            return 1;
        else
        {
            if (!findDist(dist)) //checks if district exsit
                return 2;
            else if (!findParty(party)) //checks if party exsit
                return 3;
            else
            {
                all_parties.add_citizen_as_deligator(dist, party, const_cast<citizen*>(delegator));
                return 4;
            }
        }
    }

    void election_round::showAllDistrict() const
    {
        const int size = all_dist.getNumOfDistricts();

        for (int i = 0; i < size; i++)
        {
            cout << all_dist[i] << endl;
        }
    }

    void election_round::showAllCitizen() const
    {
        int size = all_citizen.getSize();

        for (int i = 0; i < size; i++)
        {
            all_citizen[i].print_list();
        }
    }

    void election_round::showAllParties() const
    {
        const int size = all_parties.getSize();

        for (int i = 0; i < size; i++)
        {
            cout << all_parties[i] << endl;
        }
    }

    int election_round::addVote(const char* id, int party_num)
    {
        const citizen* person = findCitizen(id);
        int dist;

        //check if the vote isn't legal:
        if (person == nullptr)
            return 0;
        else if (person->getVoteStat())
            return 1;
        else if (!findParty(party_num))
            return 2;
        else //otherwise
        {
            dist = person->getDist();
            party& tmp_party = all_parties[party_num];

            if (tmp_party.has_delegators(dist) == false)
                return 3;

            all_dist[dist].get_kalpi().addVote(party_num);
            const_cast<citizen*>(person)->set_vote_stat(true);
            return 4;
        }
    }

    bool election_round::findParty(const char* name)
    {
        int size = all_parties.getSize();
        bool flag = false;
        for (int i = 0; i < size && !flag; i++)
        {
            if (strcmp(all_parties[i].getName(), name) == 0)
                flag = true;
        }
        if (flag)
            return true;
        else
            return false; //if party hasn't found
    }

    bool election_round::findParty(const int serial_num)
    {
        int size = all_parties.getSize();
        bool flag = false;
        for (int i = 0; i < size && !flag; i++)
        {
            if (all_parties[i].getSerialNum() == serial_num)
                flag = true;
        }

        if (flag)
            return true;
        else
            return false; //if party hasn't found
    }

    const district* election_round::findDist(const int serial_num)
    {
        int size = all_dist.getNumOfDistricts();
        bool flag = false;
        for (int i = 0; i < size && !flag; i++)
        {
            if (all_dist[i].getSerialNum() == serial_num)
                return &all_dist[i];
        }

        return nullptr;
    }

    bool election_round::findDist(const char* name)
    {
        int size = all_dist.getNumOfDistricts();
        bool flag = false;
        for (int i = 0; i < size && !flag; i++)
        {
            if (strcmp(all_dist[i].getName(), name) == 0)
                flag = true;
        }

        if (flag)
            return true;
        else
            return false;
    }

    const citizen* election_round::findCitizen(const citizen& new_citizen)
    {
        return findCitizen(new_citizen.getID());
    }

    const citizen* election_round::findCitizen(const char* ID)
    {
        const citizen* res = nullptr;
        int size = all_citizen.getSize();

        for (int i = 0; i < size && res == nullptr; i++)
        {
            res = all_citizen[i].get_citizen(ID);
        }

        return res;
    }

    void election_round::showResults()
    {
        int distNum = all_dist.getNumOfDistricts();
        int partyNum = all_parties.getSize();
        int party;

        for (int i = 0; i < distNum; i++)
        {
            if (all_dist[i].get_amount_of_voters() != 0)
            {
                all_dist[i].calc_chairs_dist();
                if (!all_dist[i].set_delegators(all_parties))
                    return;
            }
        }

        for (int i = 0; i < distNum; i++) // loop checks all district
        {
            cout << all_dist[i] << endl; // prints dist num, name and amount of chairs. - FIX PRINT
            party = all_dist[i].get_kalpi().getWinParty();

            if (party == -1)
            {
                cout << "Non of the citizen in " << all_dist[i].getName() << "has voted yet. " << endl;
            }
            else
            {
                cout << " Winnig elector: " << all_parties[party].getCndidate()->getName() << endl;
                cout << all_dist[i].getVotersPrecent() << "% votings in the district. " << endl;
                all_parties[party].setChairs(all_dist[i].getChairs()); // add chairs to the winnig  party
                all_dist[i].show_delegators(all_parties);
            }
        }

        all_parties.print_by_order(); //print the candidates in sorted way by the amount of chairs they got (big to small)
    }

}


