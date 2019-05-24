#include "csv.h"

CsvTable Csv::createTableFromString(const string & csv_str)
{
    int bracount = 0;
    string buf;

    const char * p = csv_str.c_str();

    CsvRow row;
    CsvTable table;
    while (1)
    {
        if (bracount == 0)
        {
            if (*p == '\"')
            {
                bracount = 1;
            }
            else
            {
                if (*p == '\n' || *p == '\0')
                {
                    row.push_back(buf);
                    table.push_back(row);
                    row.clear();
                    buf.clear();
                }
                else if(*p == ',')
                {
                    row.push_back(buf);
                    buf.clear();
                }
                else
                {
                    buf += *p;
                }
            }
        }
        else
        {
            if (*p == '\"')
            {
                if (*(p + 1) == '\"')
                {
                    buf += '\"';
                    p += 1;
                }
                else
                {
                    row.push_back(buf);
                    buf.clear();
                    if (*(p + 1) == ',')
                    {
                        p += 1;
                        bracount = 0;
                    }
                    else if(*(p + 1) == '\n' || *(p + 1) == '\0')
                    {
                        table.push_back(row);
                        row.clear();
                        p += 1;
                        bracount = 0;
                    }
                    else 
                    {
                        std::cerr << "CSV format error: invalid char" << std::endl;
                        abort();
                    }
                }
            }
            else
            {
                buf += *p;
            }
        }
        if (*p == '\0')
        {
            break;
        }
        p += 1;
    }


    return table;
}

string Csv::createStringFromTable(const CsvTable &csv_table)
{
    bool escape = false;

    string buf;
    string::size_type n = 0;

    std::string bracount;

    CsvRow row;

    for (int i = 0; i < csv_table.size(); i++)
    {
        row = csv_table.at(i);
        for (int j = 0; j < row.size(); j++)
        {
            n = 0;

            bracount.clear();
            std::string value = row.at(j);

            if((value.find(',') != string::npos || value.find('\n') != string::npos) && value.find('\"') == string::npos)
            {
                buf += "\"";
                buf += value;
                buf += "\"";
            }

            else if(value.find('\"') != string::npos)
            {
                buf += "\"";
                bracount = value;
                while(n != string::npos)
                {
                    if(n != 0)
                    {
                        bracount.insert(n, "\"");
                        n += 2;
                    }
                    n = value.find('\"', n);
                }
                buf += bracount;
                buf += "\"";
            }

            else
            {
                buf += value;
            }
            
            if (j != csv_table[i].size() - 1)
            {
                buf += ",";
            }
        }
        if (i != csv_table.size() - 1)
        {
            buf += "\n";
        }
    }
    return buf;
}





// CsvTable Csv::createTableFromString(const string & csv_str)
// {
//     CsvTable table;
//     const char *csvString = csv_str.c_str();

//     char buf[100];

//     for (int i = 0; i < 100; i++)
//     {
//         buf[i] = '\0';
//     }

//     //BUFFER TRACKER
//     int bufX = 0;

//     bool state = true;

//     string nonconst = csv_str;

//     string::iterator p = nonconst.begin();


//     CsvRow row;


//     int commacount = 0;


//     while (1)
//     {

//         if (state == true)
//         {
//             if (*p == '"')
//             {
//                 buf[bufX] = *p;
//                 bufX++;
//                 buf[bufX] = *p;
//                 bufX++;
//             }
//             else
//             {
//                 if(*p == ' ' || *p == ',' || *p == '\n')
//                 {
//                     if (*p == ' ')
//                     {
//                         for (int i = strlen(buf); i > 0; i--)
//                         {
//                             buf[i] = buf[i - 1];
//                         }
//                         buf[0] = '"';
//                         bufX++;
//                         buf[bufX] = *p;
//                         bufX++;
//                         state = false;
//                     }
//                     else if (*p == ',')
//                     {
//                         if(buf[0] == '\0')
//                         {
//                             buf[0] = '"';
//                             buf[1] = '"';
//                             buf[2] = '\0';

//                             row.push_back(buf);

//                             for (int i = 0; i < bufX + 1; i++)
//                             {
//                                 buf[i] = '\0';
//                             }

//                             commacount++;
//                             bufX = 0;
//                             p++;
//                             continue;
//                         }
//                         if (*(p + 1) == ' ' || *(p + 1) == '\n')
//                         {
//                             for (int i = strlen(buf); i > 0; i--)
//                             {
//                                 buf[i] = buf[i - 1];
//                             }
//                             buf[0] = '"';
//                             bufX++;
//                             buf[bufX] = *p;
//                             bufX++;
//                             state = false;

//                         }
//                         else if (*(p+1) != ' ' || *(p+1) != '\n')
//                         {
//                             buf[bufX] = '\0';

//                             row.push_back(buf);

//                             for (int i = 0; i < bufX + 1; i++)
//                             {
//                                 buf[i] = '\0';
//                             }
//                             commacount++;

//                             bufX = 0;
//                         }
//                     }
//                     else if(*p == '\n')
//                     {
//                         if (commacount == 5)
//                         {
//                             buf[bufX] = '\0';

//                             row.push_back(buf);

//                             for (int i = 0; i < bufX + 1; i++)
//                             {
//                                 buf[i] = '\0';
//                             }

//                             table.push_back(row);
//                             row.erase(row.begin(), row.end());

//                             commacount = 0;

//                             bufX = 0;
//                             p++;
//                             continue;
//                         }
//                         else
//                         {
//                             state = false;
//                             for (int i = strlen(buf); i > 0; i--)
//                             {
//                                 buf[i] = buf[i - 1];
//                             }
//                             buf[0] = '"';
//                             bufX++;
//                             buf[bufX] = *p;
//                             bufX++;
//                         }
//                     }
//                 }
//                 else
//                 {
//                     if (*p == '\0')
//                     {
//                         buf[bufX] = '\0';

//                         row.push_back(buf);

//                         for (int i = 0; i < bufX + 1; i++)
//                         {
//                             buf[i] = '\0';
//                         }

//                         table.push_back(row);
//                         row.erase(row.begin(),row.end());
                  
//                         bufX = 0;
//                     }
//                     else
//                     {
//                         buf[bufX] = *p;
//                         bufX += 1;
//                     }
//                 }
//             }
//         }
//         else if(state == false) // open brackets reading
//         {
//             if (*p == '"')
//             {
//                 buf[bufX] = *p;
//                 bufX++;
//                 buf[bufX] = *p;
//                 bufX++;
//             }
//             else
//             {
//                 if(*p == ' ' || *p == ',' || *p == '\n')
//                 {
//                     if (*p == ' ')
//                     {
//                         buf[bufX] = *p;
//                         bufX++;
//                     }
//                     else if (*p == ',')
//                     {
//                         if (*(p + 1) == ' ' || *(p + 1) == '\n')
//                         {
//                             buf[bufX] = *p;
//                             bufX++;
//                         }
//                         else
//                         {
//                             buf[bufX] = '"';
//                             bufX++;

//                             buf[bufX] = '\0';

//                             state = true;

//                             row.push_back(buf);

//                             for (int i = 0; i < bufX + 1; i++)
//                             {
//                                 buf[i] = '\0';
//                             }
//                             commacount++;
//                             //
//                             bufX = 0;
//                         }
//                     }
//                     else if (*p == '\n')
//                     {
//                         if (commacount == 5)
//                         {
//                             state = true;

//                             buf[bufX] = '"';
//                             bufX++;
//                             buf[bufX] = '\0';

//                             row.push_back(buf);

//                             for (int i = 0; i < bufX + 1; i++)
//                             {
//                                 buf[i] = '\0';
//                             }

//                             table.push_back(row);
//                             row.erase(row.begin(),row.end());

//                             commacount = 0;

//                             bufX = 0;
//                         }
//                         else
//                         {
//                             buf[bufX] = *p;
//                             bufX++;
//                         }
//                     }
//                 }
//                 else
//                 {
//                     if(*p == '\0')
//                     {
//                         buf[bufX] = '"';
//                         bufX++;
//                         buf[bufX] = '\0';

//                         row.push_back(buf);

//                         for (int i = 0; i < bufX + 1; i++)
//                         {
//                             buf[i] = '\0';
//                         }
                        
//                         table.push_back(row);
//                         row.erase(row.begin(),row.end());

//                         bufX = 0;
//                     }
//                     else
//                     {
//                         buf[bufX] = *p;
//                         bufX += 1;
//                     }
//                 }
//             }        
//         }

//         if (*p == '\0')
//         {
//             break;
//         }

//         p += 1;
//     }


//     return table;
// }



// string Csv::createStringFromTable(const CsvTable &csv_table)
// {
//     string to;

//     string::iterator it = to.end();

//     for(int i = 0; i < csv_table.size(); i++)
//     {
//         for(int j = 0; j < csv_table[i].size(); j++)
//         {
//             to+=csv_table[i][j];
//             if(j == csv_table[i].size() - 1)
//             {
//                 to+="\n";
//             }
//             else to+=',';

//         }
//     }
//     // it = to.end();
//     // it--;
//     // *it = '\0';
//     return to;
// }
