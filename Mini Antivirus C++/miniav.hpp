// Samir Jamehdar, samirjamehdar@hotmail.com
// Mathias Carlshjelm, mathias.c256400@gmail.com

#ifndef MINIAV_HPP
#define MINIAV_HPP

#include <string>
#include <vector>
#include <dirent.h>
#include <fstream>
#include <iostream>
// nyligen tillagt



//      File-dependent functions            //
std::vector<std::string> file_traversal(std::string path);
std::vector<std::vector<std::string> > read_virus_database(std::string signature_path);
std::string read_file_ascii(const std::string &filename, const int &signature_length);


std::string hex_to_ascii(const std::string &str, const std::string &virus_name);


void compare_log(std::vector<std::vector<std::string> > &virus_signs, std::vector<std::string> &filepaths);
void write_log(std::string infected_files);


#endif