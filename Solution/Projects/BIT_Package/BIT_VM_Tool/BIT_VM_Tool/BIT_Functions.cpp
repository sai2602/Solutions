#include "BIT_Functions.h"

/*
* Displays all the available options to the user
*/
void Help()
{
	std::cout << "Available options are: " << std::endl;
	std::cout << "--commit: This will save the current project files as a new version. Eg: commit \"my commit\"" << std::endl;
	std::cout << "--list versions: This will list all the previous versions commited. Syntax: list versions" << std::endl;
	std::cout << "--reset: reset the state of the working directory to specific version. Syntax: reset 1" << std::endl;
	std::cout << "--list changes: This will list the differences between project directory and latest checkin. Syntax: list changes" << std::endl;
	std::cout << "Choose your preferred operation" << std::endl;
	std::cout << std::endl;
}

/*
* This function splits the string based on the specified delimiter
*/
void Split_String(std::string& input, std::vector<std::string>& substr, const char delimiter)
{
	size_t start;
	size_t end = 0;

	while ((start = input.find_first_not_of(delimiter, end)) != std::string::npos)
	{
		end = input.find(delimiter, start);
		substr.push_back(input.substr(start, end - start));
	}
}

/*
* This functions gets the current timestamp which is then entered into the logs
*/
std::string get_timestamp()
{
	time_t     now = time(0);
	struct tm  timeinfo;
	char       stamp[80];
	timeinfo = *localtime(&now);

	strftime(stamp, sizeof(stamp), "%Y-%m-%d_%X", &timeinfo);

	return stamp;

}

/*
* This function actually checks if there is any difference from the current project files and latest checkins
* If there is any difference it returns true and saves all the changes info to a vector
*/
bool Update_Required(std::filesystem::path Project_Path, std::vector<std::string> &Uncommited)
{
	std::string file_path;
	int count = 0;
	std::filesystem::path last_checkin;
	std::vector<std::string> checkin_files, source_dir_files;
	bool not_found_flag;

	for (const std::filesystem::path& latest_checkin : std::filesystem::directory_iterator(Project_Path / ".bit" / "checkins")) {
		count += 1;
	}

	last_checkin = Project_Path / ".bit" / "checkins" / std::to_string(count);
	count = 0;

	for (const std::filesystem::path& latest_checkin : std::filesystem::directory_iterator(last_checkin)) {
		checkin_files.push_back(latest_checkin.filename().string());
	}
	
	for (const std::filesystem::path& project_files : std::filesystem::directory_iterator(Project_Path)) {
		file_path = project_files.string();
		if (file_path.find(".bit") == std::string::npos) {
			source_dir_files.push_back(project_files.filename().string());
		}
	}

	if (source_dir_files.size() > checkin_files.size()) {
		for (int i = 0; i < source_dir_files.size(); i++) {
			not_found_flag = true;
			for (int j = 0; j < checkin_files.size(); j++) {
				if (source_dir_files[i] == checkin_files[j]) {
					not_found_flag = false;
				}
			}
			if (not_found_flag) {
				Uncommited.push_back(source_dir_files[i]);
				source_dir_files.erase(source_dir_files.begin() + i);
			}
		}
	}
	else {
		for (int i = 0; i < checkin_files.size(); i++) {
			not_found_flag = true;
			for (int j = 0; j < source_dir_files.size(); j++) {
				if (source_dir_files[j] == checkin_files[i]) {
					not_found_flag = false;
				}
			}
			if (not_found_flag) {
				Uncommited.push_back(checkin_files[i]);
				checkin_files.erase(checkin_files.begin() + i);
			}
		}
	}

	if (source_dir_files.size() == checkin_files.size()) {
		std::filesystem::path path1, path2;
		for (int i = 0; i < source_dir_files.size(); i++) {
			path1 = Project_Path / source_dir_files[i];
			path2 = last_checkin / source_dir_files[i];
			if (!Compare_File_Contents(path1, path2)) {
				Uncommited.push_back(source_dir_files[i]);
			}
		}
	}
	else {
		std::cout << "Oops!!! Something went wrong" << std::endl;
		return false;
	}

	if (Uncommited.size() > 0) {
		return true;
	}
	
	return false;
}

/*
* This method compares two files line by line and returns true if they are same.
*/
bool Compare_File_Contents(std::filesystem::path File_1, std::filesystem::path File_2)
{
	std::ifstream File_1_Handle, File_2_Handle;
	File_1_Handle.open(File_1.string());
	File_2_Handle.open(File_2.string());
	std::string entry;
	std::vector<std::string> contents_1, contents_2;

	if (!File_1_Handle) {
		std::cout << "Error reading logs. Please make sure that log file is closed and try again." << std::endl;
		std::cout << "Error file: " << File_1 << std::endl;
	}
	else {
		while (getline(File_1_Handle, entry)) {
			contents_1.push_back(entry);
		}
	}

	if (!File_2_Handle) {
		std::cout << "Error reading logs. Please make sure that log file is closed and try again." << std::endl;
		std::cout << "Error file: " << File_2 << std::endl;
	}
	else {
		while (getline(File_2_Handle, entry)) {
			contents_2.push_back(entry);
		}
	}

	if (contents_1.size() != contents_2.size()) {
		return false;
	}
	else {
		for (int i = 0; i < contents_1.size(); i++) {
			if (contents_1[i] != contents_2[i]) {
				return false;
			}
		}
	}

	return true;
}
