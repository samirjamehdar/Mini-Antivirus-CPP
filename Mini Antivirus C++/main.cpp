// Samir Jamehdar, samirjamehdar@hotmail.com
// Mathias Carlshjelm, mathias.c256400@gmail.com

#include "miniav.hpp"


int main(int argc, char** argv) 
{
    std::string folder_path;
    std::string virus_database_path = "signatures.db";


    /////// User Input Check ///////
    if (argc == 1){
        std::cout << "Please input folderpath and signaturepath, seperated by spacebar!" << std::endl;
        return 0;
    }
    else if (argc == 2) {
        folder_path = argv[1];
        DIR *folder_dir = opendir(folder_path.c_str());


        if (folder_dir == NULL){
            FILE *folder_check = fopen(folder_path.c_str(), "r");

            if (folder_check == NULL){
                std::cout << "No such file or directory. Try with an absolute path instead!" << std::endl;
                return 0;
            }
            else
            {
                std::vector<std::string> single_file;
                single_file.push_back(folder_path);

                std::vector<std::vector<std::string> > virus_meta = read_virus_database(virus_database_path);
                compare_log(virus_meta, single_file);
                return 0;
            }
        }
    } 
    else {
        folder_path = argv[1];
        virus_database_path = argv[2];

        DIR *folder_dir = opendir(folder_path.c_str());
        FILE *virus_file = fopen(virus_database_path.c_str(), "r");

        if (virus_file == NULL){
            std::cout << "No such signature file. Try with an absolute path instead!" << std::endl;
            return 0;
        }
        else if (folder_dir == NULL){
            // Nyligen tillagt
            FILE *folder_check = fopen(folder_path.c_str(), "r");

            if (folder_check == NULL){
                std::cout << "No such file or directory. Try with an absolute path instead!" << std::endl;
                return 0;
            }
            else
            {
                // Nyligen tillagt
                std::vector<std::string> single_file;
                single_file.push_back(folder_path);

                std::vector<std::vector<std::string> > virus_meta = read_virus_database(virus_database_path);
                compare_log(virus_meta, single_file);
                return 0;
            }
        }
    }

 

    // filepaths vector
    std::vector<std::string> file_paths = file_traversal(folder_path);

    // // 2d vector, vec1 innehåller virus namn, vec2 innehåller virus signatur.
    std::vector<std::vector<std::string> > virus_meta = read_virus_database(virus_database_path);

    compare_log(virus_meta, file_paths);
    
    return 0;
}
