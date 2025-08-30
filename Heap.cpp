#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>
using namespace std;

// 1. Nearly sorted array (k)
vector<int> nearlySorted(vector<int> A, int n, int k)
{
    vector<int> ans;
    priority_queue<int, vector<int>, greater<int>> minH;

    int i = 0;
    while (i < k && i < n)
        minH.push(A[i]), i++;

    for (i; i < n; i++)
    {
        minH.push(A[i]);
        ans.push_back(minH.top());
        minH.pop();
    }

    while (!minH.empty())
    {
        ans.push_back(minH.top());
        minH.pop();
    }

    return ans;
}

// 2. Find K closest elements
class Solution
{
public:
    vector<int> findClosestElements(vector<int> &arr, int k, int x)
    {
        int n = arr.size();
        vector<int> ans;
        priority_queue<pair<int, int>> maxH;

        for (int i = 0; i < n; i++)
        {
            maxH.push({abs(x - arr[i]), arr[i]});
            while (maxH.size() > k)
                maxH.pop();
        }
        while (!maxH.empty())
            ans.push_back(maxH.top().second), maxH.pop();
        sort(ans.begin(), ans.end());
        return ans;
    }
};

//3. Meeting Room 3
#define pii pair<long,int>
class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& A) {
        sort(A.begin(), A.end()); // sort by start time
        vector<int> roomFreq(n, 0);

        priority_queue<int, vector<int>, greater<int>> freeRooms;
        for (int i = 0; i < n; i++) freeRooms.push(i);

        priority_queue<pii, vector<pii>, greater<pii>> busyRooms; // (endTime, roomIndex)

        for (auto &meeting : A) {
            long start = meeting[0];
            long end = meeting[1];
            long duration = end - start;

            // Free up rooms whose meetings ended before or at 'start'
            while (!busyRooms.empty() && busyRooms.top().first <= start) {
                freeRooms.push(busyRooms.top().second);
                busyRooms.pop();
            }

            if (freeRooms.empty()) {
                // No free room — wait for earliest ending meeting
                auto [endTime, roomIdx] = busyRooms.top();
                busyRooms.pop();
                start = endTime; // meeting starts when room gets free
                end = start + duration;
                freeRooms.push(roomIdx); // room becomes free now
            }

            // Assign the smallest indexed free room
            int roomIdx = freeRooms.top();
            freeRooms.pop();

            busyRooms.push({end, roomIdx});
            roomFreq[roomIdx]++;
        }

        // Find room with max frequency, tie-breaker: smaller index
        int ans = 0;
        for (int i = 1; i < n; i++) {
            if (roomFreq[i] > roomFreq[ans] ||
                (roomFreq[i] == roomFreq[ans] && i < ans)) {
                ans = i;
            }
        }
        return ans;
    }
};

