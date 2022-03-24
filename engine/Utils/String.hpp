#pragma once

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

namespace mtEngine
{
  namespace String
  {
    using SplitMap = std::vector<std::string>;
    static SplitMap Split(const std::string &s, const std::string &delimiter = " ")
    {
      size_t pos_start = 0, pos_end, delim_len = delimiter.length();
      std::string token;
      SplitMap res;

      while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
      {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
      }

      res.push_back(s.substr(pos_start));
      return res;
    }

    static std::string &ltrim(std::string &s)
    {
      s.erase(s.begin(),
          std::find_if(
              s.begin(), s.end(), std::ptr_fun<int, int>(std::isgraph)));
      return s;
    }

    static std::string &rtrim(std::string &s)
    {
      s.erase(std::find_if(
                  s.rbegin(), s.rend(), std::ptr_fun<int, int>(std::isgraph))
                  .base(),
          s.end());
      return s;
    }

    static std::string &trim(std::string s) { return ltrim(rtrim(s)); }

    static std::string dump(std::vector<std::string> val)
    {
      if(val.size() == 0) return "";

      std::ostringstream ss;
      for(const auto i : val) {
        ss << " " << i;
      }

      return trim(ss.str());
    }
  } // namespace String
} // namespace mtEngine
