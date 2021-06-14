#include "BIT_VM_Tool.h"

void Help();

void Split_String(std::string& input, std::vector<std::string>& substr, const char delimiter);

std::string get_timestamp();

bool Update_Required(std::filesystem::path Project_Path, std::vector<std::string> &Uncommited);

bool Compare_File_Contents(std::filesystem::path File_1, std::filesystem::path File_2);