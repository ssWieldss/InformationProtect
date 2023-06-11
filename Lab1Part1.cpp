#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>
#include <iostream> 
#include <fstream> 
#include <iomanip>
#include <conio.h>

std::ifstream::pos_type fileSize(std::string filename) 
{
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}

std::vector<std::pair<unsigned char, int>> count_freq() {

	std::ifstream file ("Lab1Part1.docx", std::ios_base::in | std::ios_base::binary);

	file.seekg(0, std::ios::end);
	size_t n = file.tellg();
	file.seekg(0, std::ios::beg);
	
	unsigned char* temp_char = new unsigned char[n];

	std::vector<std::pair<unsigned char, int>> result_vector;

	
	file.read((char*)temp_char, n);

	for (size_t i = 0; i < n; i++)
	{
		//std::cout << std::hex << (size_t)temp_char[i] << std::endl;
		result_vector.push_back(std::make_pair(temp_char[i], 0));
	}

	for (int i = 0; i < result_vector.size(); i++){
		for (int j = 0; j < result_vector.size(); j++) {
			if (result_vector[i].first == result_vector[j].first && i != j)
				result_vector[i].second = result_vector[i].second + 1;
		}
	}

	return result_vector;
}

int main() {

    SetConsoleOutputCP(1251);

	std::string filename = "Lab1Part1.docx";
	size_t bytes = fileSize(filename);
	std::cout << bytes << " bytes" << std::endl;

	std::vector<std::pair<unsigned char, int>> result = count_freq();

	for (size_t i = 0; i < bytes; i++)
	{
		std::cout << "byte - " << std::hex <<(size_t)result[i].first << " freq - " << std::dec << (double) result[i].second / bytes << std::endl;
	}

	return 0;
}