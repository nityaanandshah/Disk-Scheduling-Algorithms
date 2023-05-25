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

int find(vector<pair<int,int> > arr, int n, int val) 
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i].second == val)
        {
            return i;
        }
    }
    return -1;
}

void fn(vector<pair<int,int> > arr, vector<int> seek_sequence, int n, int seek_count)
{
    int tat[n + 1];
    int wait[n + 1];
    int time = 0;
    for(int i = 0; i < seek_sequence.size(); i++)
    {
        // if(seek_sequence[i]==0) continue;
        int idx = find(arr, n, seek_sequence[i]);
        wait[i] = max(0, time - arr[idx].first);
        time += 100;
        tat[i] = (i==0) ? time : time - arr[idx].first;
        time += 1;
    }
    print(seek_sequence, tat, wait, n + 1, seek_count);
}

void CSCAN(vector<pair<int,int> > arr, int n, int head, int disk_size)
{
    int seek_count = 0;
    int distance, cur_track;
    vector<int> left, right;
    vector<int> seek_sequence;
    // appending end values which has to be visited before reversing the direction
    left.push_back(0);
    right.push_back(disk_size - 1);
    // tracks on the left of the head will be serviced when once the head comes back to the beginning (left end)
    for (int i = 0; i < n; i++) 
    {
        if (arr[i].second < head)
        {
            left.push_back(arr[i].second);
        }
        if (arr[i].second > head)
        {
            right.push_back(arr[i].second);
        }
    }
    // sorting left and right vectors
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    // first service the requests on the right side of the head
    for (int i = 0; i < right.size(); i++) 
    {
        cur_track = right[i];
        // appending current track to seek sequence
        seek_sequence.push_back(cur_track);
        // calculate absolute distance
        distance = abs(cur_track - head);
        // increase the total count
        seek_count += distance;
        // accessed track is now new head
        head = cur_track;
    }
    // once reached the right end jump to the beginning.
    head = 0;
    // adding seek count for head returning from 99 to 0
    seek_count += (disk_size - 1);
    // Now service the requests again which are left
    for (int i = 0; i < left.size(); i++) 
    {
        cur_track = left[i];
        // appending current track to seek sequence
        seek_sequence.push_back(cur_track);
        // calculate absolute distance
        distance = abs(cur_track - head);
        // increase the total count
        seek_count += distance;
        // accessed track is now the new head
        head = cur_track;
    }
    cout << "Seek Sequence is" << endl;
    fn(arr, seek_sequence, n, seek_count);
}
 
int main()
{
    int n;
    cout << "Enter the number of the cylinder requests : ";
    cin >> n;
    vector<pair<int,int> > req_arr;
    cout << "Enter the sequence of cylinder along with their arrival time\n";
    int a, b;
    for (int i = 0; i < n; i++)
    {
        cin >> a >> b;
        req_arr.push_back(make_pair(b,a));
    }
    int head;
    cout << "Enter the current head position of the disk : ";
    cin >> head;
    sort(req_arr.begin(), req_arr.end());
    int disk_size = 100;
    string direction = "left";
    CSCAN(req_arr, n, head, disk_size);
    return 0;
}