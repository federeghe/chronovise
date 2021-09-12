#ifndef FILEIMPORTMODEL_H
#define FILEIMPORTMODEL_H

#include <string>
using namespace std;

class FileImportModel
{
public:
    FileImportModel();
    void set_input_file_name(string str);
    string get_input_file_name();
    int count_num_line(string file_name);
    double wcet_calc(string file_name);

private:
    string input_file_name;
};

#endif // FILEIMPORTMODEL_H
