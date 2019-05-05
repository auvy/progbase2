#pragma once

#include <string>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <fstream>

using std::vector;
using std::string;

using namespace std;

using CsvRow = vector<string>;   // type name alias
using CsvTable = vector<CsvRow>; // type name alias

namespace Csv
{
    // parse csv, create & fill string table
    CsvTable createTableFromString(const string &csv_str);
    // return a string filled with csv from string table
    string createStringFromTable(const CsvTable &csv_table);
} // namespace Csv