#include "stdafx.h"
#include "Settings.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>

namespace msf {
Settings::Settings(std::initializer_list<std::pair<const std::string&, int>> vals)	{
	for (auto& pair : vals) {
		fields.insert(pair);
	}
}
	Settings::Settings(std::string loadPath_) {
	load(loadPath_);
}

	Settings::Settings() : fields{} {}

Settings::~Settings() {}

int Settings::getField(const std::string & key) {
	return fields[key];
}

void Settings::setField(const std::string & key, int val) {
	fields[key] = val;
}

std::string Settings::serialize() {
	std::stringstream data;
	for (const std::pair<const std::string&, int>& field : fields) {
		data << field.first << CHAR_SEPARATOR << field.second << "\n";
	}
	return data.str();
}

Settings Settings::unserialize(const std::string & in_)	{
	std::stringstream in{};
	in.str(in_);
	std::vector<std::string> lines;
	for (std::string line; std::getline(in, line, '\n');) {
		lines.push_back(line);
	}
	std::vector <std::pair<std::string, int> > fields_;
	for (std::string line : lines) {
		int count{0};
		for (char c : line) {
			if (c == CHAR_SEPARATOR)
				count++;

		}
		if (count == 1) {
			std::stringstream lineStream{};
			lineStream.str(line);
			std::string id;
			std::string value;
			std::getline(lineStream, id, CHAR_SEPARATOR);
			std::getline(lineStream, value, CHAR_SEPARATOR);
			std::pair<std::string, int> splitLine{id, std::stoi(value)};
			fields_.push_back(splitLine);
		}

	}

	Settings set{};
	for (auto values : fields_) {
		set.fields.insert(values);
	}
	return set;
}

bool Settings::save(std::string filePath) {
	std::ofstream out;
	out.open(filePath);
	out << serialize();
	out.close();
	return true;
}

bool Settings::load(std::string filePath) {
	std::ifstream in;
	in.open(filePath);
	std::vector<std::string> lines;
	for (std::string line; in;) {
		in >> line;
		lines.push_back(line);
	}
	std::string concat;
	for (std::string line : lines) {
		concat += line + "\n";
	}
	*this = unserialize(concat);
	return true;
}
}