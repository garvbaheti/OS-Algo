
#include <iostream> 
#include <vector> 
#include <algorithm> 

using namespace std; 

const int P = 5; 
const int R = 3; 

void calculateNeed(int need[P][R], int maxm[P][R], 
				int allot[P][R]) 
{ 
	for (int i = 0 ; i < P ; i++) 
		for (int j = 0 ; j < R ; j++) 

			need[i][j] = maxm[i][j] - allot[i][j]; 
} 

bool isSafe(int processes[], int avail[], int maxm[][R], 
			int allot[][R]) 
{ 
	int need[P][R]; 

	calculateNeed(need, maxm, allot); 

	bool marked[P] = {0}; 

	vector<int> safeSeq; 

	int work[R]; 
	for (int i = 0; i < R ; i++) 
		work[i] = avail[i]; 

	int count = 0; 
	while (count < P) 
	{ 
		bool found = false; 
		for (int p = 0; p < P; p++) 
		{ 

			if (marked[p] == false) 
			{ 

				int j; 
				for (j = 0; j < R; j++) 
					if (need[p][j] > work[j]) 
						break; 

				if (j == R) 
				{ 

					for (int k = 0 ; k < R ; k++) 
						work[k] += allot[p][k]; 

					safeSeq.push_back(p); 

					marked[p] = true; 

					count++; 

					found = true; 
				} 
			} 
		} 

		if (found == false) 
		{ 
			cout << "System is not in safe state"; 
			return false; 
		} 
	} 

	cout << "System is in safe state.\nSafe"
		" sequence is: "; 
	for (auto it = safeSeq.begin(); it != safeSeq.end(); it++) 
		cout << 'P' << *it << ' '; 

	return true; 
} 

int main() 
{ 
	int processes[] = {0, 1, 2, 3, 4}; 

	int avail[] = {3, 3, 2}; 

	int maxm[][R] = {{7, 5, 3}, 
					{3, 2, 2}, 
					{9, 0, 2}, 
					{2, 2, 2}, 
					{4, 3, 3}}; 

	int allot[][R] = {{0, 1, 0}, 
					{2, 0, 0}, 
					{3, 0, 2}, 
					{2, 1, 1}, 
					{0, 0, 2}}; 

	isSafe(processes, avail, maxm, allot); 

	return 0; 
}

// Here's what the above class is doing:
// 1. process[], avail[], maxm[][] and allot[][] represents the processes, available resource instances, the max required resources and allocated resources need to compute the safe sequence.

// 2. count keeps track how many processes are scheduled.

// 3. marked[] records the processes that are already scheduled.

// 4. work is an array with the number of resources available. It is initially the available instance of resources.

// 5. Need matrix is calculated. Below is the illustration.
      
//           Need = Maxm – Allot 
// 6. The safe sequence is computed as:
// a) Specify the work = available and mark = false.
// b) Find index p such that marked[p] == false and need[p] <= work
// if no such process exists, go to step (f)
// else work = work + alloted
// mark == true, count++ 
// Add p to safe sequence.
// goto step (b)
// f) If count == n then stop, safe sequence has been found.
// 7. If all processes are completed, then safe sequence is found. Else not safe.*/

// END OF IMPLEMENTATION FOR CORRECTNESS CHECK
// OS Homework 2 done. See FCFS_v2
// See rest of hws via my Github repository: JayVora-CMPE
// Prints the safe sequence found.