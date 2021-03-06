// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_SMALLEST_SUBARRAY_COVERING_SET_H_
#define SOLUTIONS_SMALLEST_SUBARRAY_COVERING_SET_H_

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::pair;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

// @include
pair<int, int> FindSmallestSubarrayCoveringSet(
    const vector<string> &paragraph, const unordered_set<string> &keywords) {
  unordered_map<string, int> keywords_to_count;
  int left = 0, right = 0;
  pair<int, int> result(-1, -1);
  while (right < paragraph.size()) {
    // Keeps advancing right until it reaches end or keywords_to_count has
    // all keywords.
    while (right < paragraph.size() &&
           keywords_to_count.size() < keywords.size()) {
      if (keywords.find(paragraph[right]) != keywords.end()) {
        ++keywords_to_count[paragraph[right]];
      }
      ++right;
    }


    // Found all keywords.
    if (keywords_to_count.size() == keywords.size() &&
        ((result.first == -1 && result.second == -1) ||
         right - 1 - left < result.second - result.first)) {
      result = {left, right - 1};
    }

    // Keeps advancing left until it reaches end or keywords_to_count does not
    // have all keywords.
    while (left < right && keywords_to_count.size() == keywords.size()) {
      if (keywords.find(paragraph[left]) != keywords.end()) {
        auto keyword_count = keywords_to_count.find(paragraph[left]);
        --keyword_count->second;
        if (keyword_count->second == 0) {
          keywords_to_count.erase(keyword_count);
          if ((result.first == -1 && result.second == -1) ||
              right - 1 - left < result.second - result.first) {
            result = {left, right - 1};
          }
        }
      }
      ++left;
    }
  }
  return result;
}
// @exclude
#endif  // SOLUTIONS_SMALLEST_SUBARRAY_COVERING_SET_H_
