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

void SCAN(vector<pair<int,int> > arr, int n, int head, int disk_size, string direction)
{
    int seek_count = 0;
    int distance, cur_track;
    vector<int> left, right;
    vector<int> seek_sequence;
    // appending end values which has to be visited before reversing the direction
    if (direction == "left")
    {
        left.push_back(0);
    }
    else if (direction == "right")
    {
        right.push_back(disk_size - 1);
    }
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
    // run the while loop two times, one by one scanning right and left of the head
    int run = 2;
    while (run--) 
    {
        if (direction == "left") 
        {
            for (int i = left.size() - 1; i >= 0; i--) 
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
            direction = "right";
        }
        else if (direction == "right") 
        {
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
                // head = cur_track;
            }
            direction = "left";
        }
    }
    fn(arr, seek_sequence, n, seek_count);
    // print(seek_sequence,tat,wait,n+1,seek_count);
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
    SCAN(req_arr, n, head, disk_size, direction);
    return 0;
}