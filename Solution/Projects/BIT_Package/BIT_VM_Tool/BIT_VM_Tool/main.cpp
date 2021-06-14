// BIT_VM_Tool.cpp : Defines the entry point for the application.
//

#include "BIT_Functions.h"

namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
	fs::path project_path, bit_path, version_path;
	std::string logs_path, data, folder_number, interim_path, log_entry;
	std::vector<std::string> substr, changes;
	const char  delimiter = ' ';
	std::ofstream logs_handle;
	std::ifstream print_handle;
	bool checkin_needed = true;
	if (argc > 1) {
		project_path = argv[1];
	}
	std::cout << "Working with: " << project_path << std::endl;

	if (project_path.string() != "" && fs::exists(project_path)) {
		static int version_number = 0;

		//First the .bit and checkins forlder is created if not already present.
		bit_path = project_path / ".bit" / "checkins";

		if (fs::create_directories(bit_path)) {
			std::cout << "Created .bit directory" << std::endl;
		}

		//The text file to store logs is created if not already present.
		logs_path = project_path.string() + "\\.bit" + "\\logs.txt";
		if (!fs::exists(project_path / ".bit" / "logs.txt")) {
			std::ofstream Log_File(logs_path);
			Log_File.close();
		}

		//Display the help information.
		Help();

		std::getline(std::cin, data);

		Split_String(data, substr, delimiter);

		//Check the neccessary options available based on the user input.
		if (substr[0] == "commit") {
			if (!fs::exists(bit_path / "1")) {
				version_number = 0;
			}
			else {
				if (Update_Required(project_path, changes)) {
					for (const fs::path& file_path : fs::directory_iterator(bit_path)) {
						version_number += 1;
					}
				}
				else {
					checkin_needed = false;
				}
			}

			if (checkin_needed) {

				version_path = bit_path / std::to_string(version_number + 1);

				if (fs::create_directory(version_path)) {
					std::cout << "check in created with version number: " << std::to_string(version_number + 1) << std::endl;

					for (const fs::path& copy_file_path : fs::directory_iterator(project_path)) {
						interim_path = copy_file_path.string();
						if (interim_path.find(".bit") == std::string::npos) {
							fs::copy_file(copy_file_path, (version_path / copy_file_path.filename()));
						}
					}
					log_entry = "Version: " + std::to_string(version_number + 1) + "  Message: " + substr[1] + "  Timestamp: " + get_timestamp() + '\n';
					logs_handle.open(logs_path, std::ios_base::app);
					logs_handle << log_entry;
					logs_handle.close();
				}
				else {
					std::cout << "Could not create checkin. Please check permissions" << std::endl;
				}
			}
			else {
				std::cout << "Checkin not required" << std::endl;
			}
		}
		else if (substr[0] == "list") {
			if (substr[1] == "versions") {
				if (fs::exists(bit_path / "1")) {
					print_handle.open(logs_path);
					if (!print_handle) {
						std::cout << "Error reading logs. Please make sure that log file is closed and try again." << std::endl;
						std::cout << "Error file: " << logs_path << std::endl;
					}
					else {
						while (getline(print_handle, log_entry)) {
							std::cout << log_entry << std::endl;
						}
					}
				}
				else {
					std::cout << "No checkins available" << std::endl;
				}
				print_handle.close();
			}
			else if (substr[1] == "changes") {
				if (Update_Required(project_path, changes)) {
					std::cout << "Altered files information: " << std::endl;
					for (int i = 0; i < changes.size(); i++) {
						std::cout << changes[i] << std::endl;
					}
				}
			}
			else {
				std::cout << "Unknown command" << std::endl;
			}
		}
		else if (substr[0] == "reset") {
			if (fs::exists(bit_path / substr[1])) {

				std::string interim_string;

				for (const fs::path& reset_src__file_path : fs::directory_iterator(project_path)) {
					interim_string = reset_src__file_path.string();
					if (interim_string.find(".bit") == std::string::npos) {
						fs::remove(reset_src__file_path);
					}
				}

				for (const fs::path& reset_file_path : fs::directory_iterator(bit_path / substr[1])) {

					fs::copy_file(reset_file_path, project_path / reset_file_path.filename().string());
				}

				std::cout << "Version checked out successfully." << std::endl;
			}
			else {
				std::cout << "Invalid version number. Use list versions option to get the available versions." << std::endl;
			}
		}
		else {
			std::cout << "Unknown command" << std::endl;
		}
	}
	else {
	std::cout << "Please enter valid project path." << std::endl;
}

	return 0;
}
