#include <iostream>
#include <set>
#include <ctime>
#include <vector>
using namespace std;

const int N = 1200;

struct query {
	int personID;
	bool entering;
	int Time;
};

int number_of_guests, number_of_chairs;
vector<query> queries;

set<int> st;

void come(query current) {
	if (st.size() == number_of_chairs) return;
	cout << "Person with a ID number: " << current.personID << " entered at " << current.Time << "\n";
	if (st.size() == 0) cout << "Waking up a Cook! \n";
	st.insert(current.personID);
	cout << "Number of waiting customers is " << st.size() << endl << endl;
}

void leave(query current) {
	if (st.count(current.personID)) {
		cout << "Person with a ID number: " << current.personID << " left at " << current.Time << "\n";
		st.erase(current.personID);
		cout << "Number of waiting customers is " << st.size() << endl;
		if (st.empty()) cout << "Cook goes to sleep....Zzz\n\n";
	}
}


bool cmp (query A, query B) {
	if (A.Time == B.Time) return rand() % 2;
	return A.Time < B.Time;
}

int main () {
	srand(time(NULL));
	cin >> number_of_chairs;
	cin >> number_of_guests;
	int Q = number_of_guests;
	int start_time = 0, end_time, persons = 0;
	for (int id = 1; id <= Q; ++id) {
		query A, B;
		A.personID = id;
		A.entering = true;
		A.Time = start_time;
		B.personID = id;
		B.entering = false;
		B.Time = max (start_time + rand() % 10, end_time + rand() % 10);
		start_time += rand() % 10;
		end_time = B.Time;
		queries.push_back(A);
		queries.push_back(B);
	} 

	sort(queries.begin(), queries.end(), cmp);
	for (int i = 0; i < Q * 2; ++i) {
		if (queries[i].entering) come(queries[i]);
		else leave(queries[i]);
	}
	return 0;
}