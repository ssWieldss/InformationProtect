#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>
#include <iostream> 
#include <fstream> 
#include <iomanip>
#include <conio.h>
#include <string>

void getKey(std::vector<int>& key) {

	std::ifstream file("key.txt");
	int temp = 0;

	if (file.is_open())
	{
		while (file >> temp)
		{
			key.push_back(temp);
		}
	}
	file.close();
}


std::vector<unsigned char> code(std::string file_name, std::vector<int>& key) {

	std::ifstream file(file_name, std::ios_base::in | std::ios_base::binary);

	file.seekg(0, std::ios::end);
	size_t n = file.tellg();
	file.seekg(0, std::ios::beg);

	unsigned char* temp_char = new unsigned char[n];

	std::vector<unsigned char> result_vector;


	file.read((char*)temp_char, n);

	for (size_t i = 0; i < n; i++)
	{
		result_vector.push_back(temp_char[i]);
	}

	while (result_vector.size() % 5 != 0)
	{
		result_vector.push_back((unsigned char)"z");
	}
	
	unsigned char temp_char1[5];

	for (int i = 0; i < result_vector.size(); i += 5) {

		for (int j = 0; j < 5; j++) {
			temp_char1[j] = result_vector[i + j];
		}
		result_vector[i + 0] = temp_char[i + key[0]];
		result_vector[i + 1] = temp_char[i + key[1]];
		result_vector[i + 2] = temp_char[i + key[2]];
		result_vector[i + 3] = temp_char[i + key[3]];
		result_vector[i + 4] = temp_char[i + key[4]];
	}

	delete[] temp_char;
	return result_vector;
}

std::vector<unsigned char> encode(std::string file_name, std::vector<int>& key) {

	std::ifstream file(file_name, std::ios_base::in | std::ios_base::binary);

	file.seekg(0, std::ios::end);
	size_t n = file.tellg();
	file.seekg(0, std::ios::beg);

	char* temp_char = new char[n];
	char* te = new char;

	std::vector<unsigned char> result_vector;

	file.read((char*)temp_char, n);

	for (size_t i = 0; i < n; i++)
	{
		result_vector.push_back(temp_char[i]);
	}

	unsigned char temp_char1[5];

	for (int i = 0; i < result_vector.size(); i += 5) {

		for (int j = 0; j < 5; j++) {
			temp_char1[j] = result_vector[i + j];
		}
		result_vector[i + key[0]] = temp_char[i + 0];
		result_vector[i + key[1]] = temp_char[i + 1];
		result_vector[i + key[2]] = temp_char[i + 2];
		result_vector[i + key[3]] = temp_char[i + 3];
		result_vector[i + key[4]] = temp_char[i + 4];
	}

	delete[] temp_char;
	return result_vector;
}

void save_file(std::vector<unsigned char>& data, std::string extension, bool flag) {

	std::ofstream file_desc;

	if (flag) {
		file_desc.open("coded_file" + extension, std::ios_base::out | std::ios_base::binary);
	}
	else {
		file_desc.open("encoded_file" + extension, std::ios_base::out | std::ios_base::binary);
	}

	char* temp = new char;
	for (int i = 0; i < size(data); i++) {
		*temp = data[i];
		file_desc.write(temp, 1);
	}
	file_desc.close();
}

int main() {

	std::string file = "Lab1Part1.docx";
	std::string extension = file.substr(file.find_last_of("."));
	std::vector<unsigned char> result;
	std::vector<int> key;

	getKey(key);

	result = code(file, key);
	save_file(result, extension, 1);

	result = encode("coded_file" + extension, key);
	save_file(result, extension, 0);

	return 0;
}