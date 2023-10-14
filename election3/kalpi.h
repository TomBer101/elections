#pragma once

namespace elections {

	class kalpi {

	private:
		struct box {
			int counter;
			int chairs;
		};

		struct chairs_remainders //needed for calculating the chairs for each party
		{
			int party;
			float remain;
		};

		int amount_of_votes; //total votes in this district
		box* _kalpi_arr; //array of parties (each index is party's serial number)
		int _kalpi_logSize;
		chairs_remainders* _remainders_arr;
		int _winnig_party_in_dist;


	public:
		kalpi();
		~kalpi();

		const box& get_party_kalpi_arr(int party) const { return _kalpi_arr[party]; }
		const int get_amount_of_votes() const { return amount_of_votes; }
		const chairs_remainders* get_remainders_arr(int dist) { return _remainders_arr; }
		const int get_kalpi_size() const { return _kalpi_logSize; }
		const int return_winnin_party_in_dist() const { return _winnig_party_in_dist; }

		void resizeBox(int partyLog);
		void addVote(int party);
		void calc_chairs(int _chairs);
		void bubbleSort(chairs_remainders* remainders);
		const int getWinParty();
	};
}




