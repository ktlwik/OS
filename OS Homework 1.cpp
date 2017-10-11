/*
Name1  : Nurzhan Yergozhin
Email1 : nurzhan.yergozhin@gmail.com
Name2  : Loc Phan
Email2 : duyloc_1503@kaist.ac.kr

Input  : we give an input of number of chairs and number of guests. 
Output : All actions tracked when person enters or leaves restaurant and number of customers waiting at every moment.
Assumptions: 
		1. Cook will finish cooking after randomised time
		2. Number of chairs and number of guests will be fixed
		3. Process queries in FIFO (first in first out)
		
		
Algorithm :
  Depending on number of guests, we made # of guests multiplied by 2 queries. It's for each guest to enter and leave the kebap hourse.
  Then for each guests we are giving his id, entering time which is random number from 0 to 10 + the entering time of the earlier guest.
  Leaving time is random number from 0 to 10 + leaving time of the earlier guest. Then we add all these queries to the vector and sort them by time.
  We were trying to stimulate multithreading by generating random times for every query.
  We sorted all the queries by the time. So, we have to do all the queries from beginning to the end. 
  Our assumption was made to make queries behave as a threads, and the query which is being processed earlier
  means the query which acessed semaphore first(so, it's also random in our case). Only the timing is not random. 
 
*/
#include <iostream>
#include <set>
#include <ctime>
#include <vector>
using namespace std;

const int N = 1200;
/*
  I made a struct query, where every action will be tracked. 
   Firstly, I have to remember when the person enter or leaveas a room, which is tracked in Time. 
   Second, is the action : leaving or entering the kebab house.
   Third, is person ID to check which person enters and leaves.
 */
struct query {
	int personID;
	bool entering;
	int Time;
};

int number_of_guests, number_of_chairs;
vector<query> queries; // all the queries we have to process 
set<int> st; // to keep track of people, who are currently in kebap house. Following actions can be made : insert a new ID, delete an ID.
/*
	You can only enter kebap house if its not full.
*/
void come(query current) {
	if (st.size() == number_of_chairs) return;
	cout << "Person with a ID number: " << current.personID << " entered at " << current.Time << "\n";
	if (st.size() == 0) cout << "Waking up a Cook! \n";
	st.insert(current.personID);
	cout << "Number of waiting customers is " << st.size() << endl << endl;
}
/*
	You can leave kebap house only if u r present there.
*/
void leave(query current) {
	if (st.count(current.personID)) {
		cout << "Person with a ID number: " << current.personID << " left at " << current.Time << "\n";
		st.erase(current.personID);
		cout << "Number of waiting customers is " << st.size() << endl;
		if (st.empty()) cout << "Cook goes to sleep....Zzz\n\n";
	}
}
/*
	sort queries by increasing of time 
	if time of query A and query B is the same, then make a random behavior. 
*/

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
	/* 
	generate a random queries and push them to the list
	*/
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
