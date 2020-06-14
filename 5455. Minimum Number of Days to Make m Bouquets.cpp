//Runtime: 1744 ms, faster than 10.00% of C++ online submissions for Minimum Number of Days to Make m Bouquets.
//Memory Usage: 165.3 MB, less than 10.00% of C++ online submissions for Minimum Number of Days to Make m Bouquets.
class Solution {
public:
    bool check(vector<int>& bloomDay, int m, int k, int day){
        int start = 0, end = 0;
        
        for(int i = 0; i < bloomDay.size(); i++){
            if(bloomDay[i] <= day){
                if(start == -1 || end+1 != i){
                    //new window
                    start = end = i;
                }else if(end+1 == i){
                    //extend existing window
                    end++;
                }
                
                if(end-start+1 == k){
                    m--;
                    start = end = -1;
                }
                
                if(m == 0) return true;
            }
        }
        
        return false;
    };
    
    int minDays(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size();
        if(m*k > n) return -1;
        
        unordered_map<int, int> mcounter;
        for(int& day : bloomDay){
            mcounter[day] += 1;
        }
        
        vector<vector<int>> counter;
        for(auto it = mcounter.begin(); it != mcounter.end(); it++){
            counter.push_back({it->first, it->second});
        }
        
        //smaller day, larger count
        sort(counter.begin(), counter.end(), [](const vector<int>& v1, const vector<int>& v2){
            return (v1[0] == v2[0]) ? (v1[1] > v2[1]) : (v1[0] < v2[0]);
        });
        
        int left = -1, right = counter.size()-1, mid;
        int totalCount = 0;
        for(int i = 0; i < counter.size(); i++){
            totalCount += counter[i][1];
            if(totalCount >= m*k){
                left = i;
                break;
                // if(check(bloomDay, m, k, counter[i][0])){
                //     return counter[i][0];
                // }
            }
        }
        
        if(left == -1) return -1;
        
        //find left boundary
        while(left <= right){
            mid = left + (right-left)/2;
            if(check(bloomDay, m, k, counter[mid][0])){
                right = mid-1;
            }else{
                left = mid+1;
            }
        }
        
        return counter[left][0];
    }
};
