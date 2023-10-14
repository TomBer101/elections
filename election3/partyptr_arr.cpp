#include "partyptr_arr.h"

namespace elections
{
    void partyptr_arr::resize()
    {
        party** tmp = new party * [partyPhy * 2 + 1];

        for (int i = 0; i < partyLog; i++)
            tmp[i] = arr[i];

        delete[] arr;
        arr = tmp;
        this->partyPhy = partyPhy * 2 + 1;
    }

    partyptr_arr::partyptr_arr()
    {
        arr = nullptr;
    }

    partyptr_arr::~partyptr_arr()
    {
        for (int i = 0; i < partyLog; i++)
        {
            delete arr[i];
        }
        delete arr;
    }

    void partyptr_arr::add_party(const char* name, citizen* candi)
    {
        if (partyLog == partyPhy)
            resize();

        arr[partyLog] = new party(name, partyLog, candi);
        candi->setPart(true);
        partyLog++;
    }

    void partyptr_arr::add_citizen_as_deligator(int dist, int party, citizen* loc) // TODO : add checking
    {
        arr[party]->addDelegatoer(loc, dist);
    }

    party& partyptr_arr:: operator[](int ind) const
    {
        return *arr[ind];
    }

    void partyptr_arr::print_by_order() const
    {
        party** tmp = new party * [partyLog];

        for (int i = 0; i < partyLog; i++)
        {
            tmp[i] = arr[i];
        }

        QuickSort(tmp, 0, partyLog - 1);

        for (int j = 0; j < partyLog; j++)
        {
            cout << "Party: " << tmp[j]->getName() << "Head of the party: " << tmp[j]->getCndidate()->getName() << " ";
            cout << "Amount of electors: " << tmp[j]->getChairs() << "Amonut of votes: " << tmp[j]->getVotes() << endl;
        }

        delete[] tmp;
    }

    void partyptr_arr::QuickSort(party** tmp, int left, int right) const
    {
        int pivot;

        if (left < right)
        {
            pivot = partition(arr, left, right);
            QuickSort(arr, left, pivot - 1);
            QuickSort(arr, pivot + 1, right);
        }
    }

    int partyptr_arr::partition(party** arr, int left, int right) const
    {
        party* pivot = arr[left];
        party* tmp;
        int jump = 0;
        int start = left + 1;

        while (start < right)
        {
            if (arr[start]->getChairs() <= pivot->getChairs())
            {
                tmp = arr[start];
                arr[start] = arr[right];
                arr[right] = tmp;
                right--;
            }
            else
            {
                start++; jump++;
            }
        }
        tmp = arr[left];
        arr[left] = arr[jump];
        arr[jump] = tmp;
        return jump;
    }
}
