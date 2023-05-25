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

void print(vector<int> arr, int tat[], int wait[], int n, int seek_count){
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

void calculatedifference(vector<pair<int,int> > arr, int head, int diff[][2], int n)
{
    for (int i = 0; i < n; i++)
    {
        diff[i][0] = abs(head - arr[i].second);
    }
}
 
int findMIN(int diff[][2], int n)
{
    int index = -1;
    int minimum = 1e9;
    for (int i = 0; i < n; i++)
    {
        if (!diff[i][1] && minimum > diff[i][0])
        {
            minimum = diff[i][0];
            index = i;
        }
    }
    return index;
}

void SSTF(int n, vector<pair<int,int> > arr, int head){
    if (n == 0)
    {
        return;
    }
    // Create array of objects of class node   
    int diff[n][2];
    for (int i = 0; i < n; i++)
    {
        diff[i][0] = 0;
        diff[i][1] = 0;
    }
    int time = 0;
    int wait[n];
    for (int i = 0; i < n; i++)
    {
        wait[i] = 0;
    }
    int tat[n];
    for (int i = 0; i < n; i++)
    {
        tat[i] = 0;
    } 
    // Count total number of seek operation  
    int seekcount = 0;
    // Stores sequence in which disk access is done
    // int seeksequence[n + 1] = {0};
    vector<int> seeksequence(n,0);
    for (int i = 0; i < n; i++)
    { 
        // seeksequence[i] = head;
        calculatedifference(arr, head, diff, n);
        int index = findMIN(diff, n);  
        diff[index][1] = 1;
        seekcount += diff[index][0];
        // Accessed track is now new head
        head = arr[index].second;
        seeksequence[i] = head;
        wait[i] = max(0, time - arr[index].first);
        time += 100;
        tat[i] = (i==0) ? time : time - arr[index].first;
        if(i != n - 1)
        {
            time+=1;
        }
    }
    print(seeksequence, tat, wait, n, seekcount);
}

int main()
{
    int n;
    cout << "Enter the number of the cylinder requests : ";
    cin >> n;
    vector<pair<int,int> > req_arr;
    cout << "Enter the sequence of cylinder along with their arrival time\n";
    int a, b;
    for(int i = 0; i < n; i++){
        cin >> a >> b;
        req_arr.push_back(make_pair(b,a));
    }
    int head;
    cout << "Enter the current head position of the disk : ";
    cin >> head;
    sort(req_arr.begin(), req_arr.end());
    SSTF(n,req_arr, head);
    return 0;
}