#pragma once
#include <memory>
#include <string>
#include <fstream>
#include <unordered_map>

#define CHAR_SEPARATOR '-'
//fps
//res
//volume
//shaders
//controls
//read from file

namespace msf {

class Settings {
public:
	Settings(std::initializer_list<std::pair<const std::string, int>> vals);
	Settings(std::string loadPath_);
	Settings(const Settings& settings);
	Settings();
	~Settings();

	int getField(const std::string& key);
	void setField(const std::string& key, int val);

	//
	std::string serialize();
	static Settings unserialize(const std::string& in_);

	bool save(std::string filePath);
	bool load(std::string filePath);
	
private:
	std::unordered_map<std::string, int> fields;
};
}