#include<iostream>
#include<windows.h>
#include<vector>
#include <fstream> 
#include <string>
#include <bitset>

void take_byte_from_pixel(std::string file_name) {
	std::ifstream file(file_name, std::ios_base::in | std::ios_base::binary);

	file.seekg(0, std::ios::end);
	size_t n = file.tellg();
	file.seekg(0, std::ios::beg);

	char* temp_char = new char[n];

	file.read(temp_char, n);
	std::vector<std::pair<byte, byte>> bytes_vec;
	char temp_char2;
	int padding = 54;

	for (size_t i = 0; i < n; i++)
	{
		if (i >= 54) {
			temp_char2 = temp_char[i];
			bytes_vec.push_back(std::make_pair((temp_char2 >> 1) & 1u, (temp_char2 >> 0) & 1u));
		}
	}

	unsigned char temp_byte = 0;
	std::vector<char> result_char;

	for (size_t j = 0; j < bytes_vec.size() - 4; j += 4) {
		temp_byte |= (bytes_vec[j].first << 7);
		temp_byte |= (bytes_vec[j].second << 6);
		temp_byte |= (bytes_vec[j + 1].first << 5);
		temp_byte |= (bytes_vec[j + 1].second << 4);
		temp_byte |= (bytes_vec[j + 2].first << 3);
		temp_byte |= (bytes_vec[j + 2].second << 2);
		temp_byte |= (bytes_vec[j + 3].first << 1);
		temp_byte |= (bytes_vec[j + 3].second);

		if (temp_byte == 0xFF)
			break;

		result_char.push_back(temp_byte);
		temp_byte &= 0;
	}
	std::cout << "Decoded text from " << file_name << ": ";

	for (int i = 0; i < result_char.size(); i++)
		std::cout << result_char[i];

	std::cout << std::endl;

	delete[] temp_char;
	file.close();
}

void hide_byte_to_pixel(std::string file_name, std::string text) {

	std::ifstream file(file_name, std::ios_base::in | std::ios_base::binary);

	file.seekg(0, std::ios::end);
	size_t n = file.tellg();
	file.seekg(0, std::ios::beg);

	char* temp_char = new char[n];

	file.read(temp_char, n);
	std::vector<std::pair<byte, byte>> bytes_vec;
	char temp_char2;
	int padding = 54;

	unsigned char temp_byte = 0;
	std::vector<char> result_char;

	int text_index = 0;
	int file_index = 54;
	int temp_char_it = 0;

	text += (char)0xFF;

	while (text_index != text.size()) {

		temp_char_it = (char)text[text_index];

		temp_char[file_index] &= (0xFC);
		temp_char[file_index] |= (temp_char_it >> 6) & 0x3;

		file_index++;
		temp_char[file_index] &= (0xFC);
		temp_char[file_index] |= (temp_char_it >> 4) & 0x3;

		file_index++;
		temp_char[file_index] &= (0xFC);
		temp_char[file_index] |= (temp_char_it >> 2) & 0x3;

		file_index++;
		temp_char[file_index] &= (0xFC);
		temp_char[file_index] |= (temp_char_it) & 0x3;

		file_index++;
		text_index++;
	}
 
	std::ofstream file_new("Coded" + file_name, std::ios_base::out | std::ios_base::binary);
	file_new.write(temp_char, n);

	file_new.close();

	delete[] temp_char;

	file.close();
}

int main() {
	setlocale(LC_ALL, "en_US.UTF8");


	take_byte_from_pixel("3.bmp");
	hide_byte_to_pixel("3.bmp", "Hello everyone from third lab of information security!");
	take_byte_from_pixel("Coded3.bmp");

	return 0;
}