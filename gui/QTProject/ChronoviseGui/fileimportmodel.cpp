#include "fileimportmodel.h"

#include <iostream>
#include <iomanip>
#include <fstream>

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream;

FileImportModel::FileImportModel()
{
    this->input_file_name="";
}

void FileImportModel::set_input_file_name(string str)
{
    this->input_file_name=str;
}
string FileImportModel::get_input_file_name()
{
    return this->input_file_name;
}


int FileImportModel::count_num_line(string file_name)
{
    int num_lines=0;
    string tmp;
    ifstream my_file (file_name);
    if(my_file.is_open())
    {
        while(std::getline(my_file,tmp))
        {
            ++num_lines;
        }
    }
    my_file.close();
    return num_lines;
}

double FileImportModel::wcet_calc(string file_name)
{
    string filename(file_name);
    double number;
    double max=0;

    ifstream input_file(file_name);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }

    while (input_file >> number)
    {
        if(number>max)
        {
            max=number;
        }
    }
    cout << endl;
    input_file.close();

    return max;
}


