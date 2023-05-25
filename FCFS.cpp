#include <iostream>
#include <stack>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <vector>
#include <string>
#include <time.h>
#include <chrono>
#include <array>
#include <random>
#include <ctime>
#include <numeric>
#include <iomanip>
#include <queue>
#include <map>
#include <unordered_map>
#include <cstring>
using namespace std;
 
void print(vector<int> arr, int tat[], int wait[], int n, int seek_count)
{
    cout << endl << "Total cylinder movement : " << seek_count << endl;
    cout << "Seek Sequence : ";
    for (int i = 0; i < arr.size(); i++) 
    {
        cout << arr[i] << " ";
    }
    float avg_wait = 0;
    float avg_tat = 0;
    cout << endl << endl;
    cout << "Waiting time : \n";
    cout << "Cylinder no." << "   " << "time(in ms)\n";
    for (int i = 0; i < n; i++) 
    {
        cout << arr[i] << "\t\t" << wait[i] << endl;
        avg_wait += wait[i];
    }
    avg_wait /= n;
    cout << endl;
    cout << "Average waiting time = " << avg_wait << endl;
    cout << endl;
    cout << "Turnaround time : \n";
    cout << "Cylinder no." << "   " << "time(in ms)\n";
    for (int i = 0; i < n; i++) 
    {
        cout << arr[i] << "\t\t" << tat[i] << endl;
        avg_tat += tat[i];
    }
    avg_tat /= n;
    cout << endl;
    cout << "Average Turnaround time = " << avg_tat << endl;
}

void FCFS(vector<pair<int,int> > arr, int head, int n)
{
    int seek_count = 0;
    int distance, cur_track;
    int time = 0;
    int wait[n];
    int tat[n];
    vector<int> seek_sequence(n,0);
    // assuming the  processing time of each request as 100ms and the time required for moving from cylinder i to i+1 is 1 ms
    for (int i = 0; i < n; i++) 
    {
        cur_track = arr[i].second;
        wait[i] = time - arr[i].first;
        time += 100;
        tat[i] = time - arr[i].first;
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
        seek_sequence[i] = arr[i].second;
        if (i != n - 1)
        {
            time += 1;
        }
    }
    print(seek_sequence, tat, wait, n, seek_count);
}

int main()
{
    int n;
    cout << "Enter the number of the cylinder requests : ";
    cin >> n;
    vector<pair<int,int> > req_arr;
    cout << "Enter the sequence of cylinder along with their arrival time\n";
    int a, b;
    for(int i = 0; i < n; i++)
    {
        cin >> a >> b;
        req_arr.push_back(make_pair(b,a));
    }
    int head;
    cout << "Enter the current head position of the disk : ";
    cin >> head;
    sort(req_arr.begin(), req_arr.end());
    FCFS(req_arr, head, n);
    return 0;
}