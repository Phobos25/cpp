/*
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.
*/

/*  The problem requires finding two numbers in the given vector that add up to a target value.

    By using an unordered map, we can efficiently store the elements of the vector along with their indices for quick access.

    The idea is to iterate through the vector and for each element, calculate the required number needed to reach the target value.

    We check if the required number is already present in the map. If it is, it means we have found a pair of numbers that add up to the target.

    If the required number is not found in the map, we store the current element and its index in the map.

    This way, as we iterate through the vector, we can quickly check if the required number for each element is present in the map.

    Once we find a pair of numbers that add up to the target, we return their indices.

    If we iterate through the entire vector without finding a solution, we return {-1, -1} to indicate that no valid pair of numbers was found.
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> twoSum(vector<int>& nums, int target){
  unordered_map <int, int> mp;
  vector <int> ans;
  for (int i =0; i< nums.size(); ++i){
    int required = target - nums[i];
    if (mp.find(required) != mp.end()){
      ans.push_back(i);
      ans.push_back(mp[required]);
      return ans;
    }
    mp[nums[i]] = i;
  }
  return {-1,-1};
}

int main(){  
  // vector<int> nums = {2,7,11,15};
  // int target = 9;
  // vector<int> nums = {3,2,4};
  // int target = 6;
  vector<int> nums = {3,3};
  int target = 6;

  vector<int> ans;
  ans = twoSum(nums, target);
  cout << ans[0] << ' ' <<ans[1] << endl;
  return 0;
}
