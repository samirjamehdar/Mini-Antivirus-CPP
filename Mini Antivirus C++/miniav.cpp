// Samir Jamehdar, samirjamehdar@hotmail.com
// Mathias Carlshjelm, mathias.c256400@gmail.com

#include "miniav.hpp"


std::vector<std::string> file_traversal(std::string start_dir)
{
    /*
    Tar in en folderpath, och skannar mappen och dess undermappar.
    Alla filer som hittas läggs i en vektor som returneras.
    */


    std::string new_folder_path = "";
    std::vector<std::string> folder_paths;
    static std::vector<std::string> file_paths;

    DIR *folder = opendir(start_dir.c_str());
    dirent *read_folder;

    if (folder != NULL){
        while ((read_folder = readdir(folder)) != NULL){
            if (read_folder != NULL){
                std::string temp;
                temp = read_folder->d_name;


                if(temp.substr(0,2) == "..")
                {
                    temp.erase(0,2);
                }
                else if (temp[0] == '.')
                {
                    temp.erase(0,1);
                }
                
                if (temp != "")
                {
                    new_folder_path = start_dir + "/" + temp;

                    // nyligen tillagt för att lösa gömda filer.
                    std::string hidden = start_dir + "/." + temp;
                    folder_paths.push_back(hidden);

                    folder_paths.push_back(new_folder_path);
                }
            }
        }

        for(int i = 0; i < folder_paths.size(); i++)
        {
            file_paths = file_traversal(folder_paths[i]);
        }
        return file_paths;
    }

    else 
    {

        file_paths.push_back(start_dir);

        return file_paths;
    }

}

std::vector<std::vector<std::string> > read_virus_database(std::string signature_path)
{
    /* 
    Returnerar en dubbelvektor där första vektorn innehåller namnet på virusen
    och andra vektorn innehåller virussignaturen som har konverterats till ascii.
    */

    std::ifstream file(signature_path);

    std::vector<std::string> virus_signs;
    std::vector<std::string> virus_names;
    std::vector<std::vector<std::string> > virus_meta;

    std::string input;

    while(file >> input)
    {
        virus_signs.push_back(input);
    }

    for(int i = 0; i < virus_signs.size(); i++)
    {
        for(int j = 0; j <= virus_signs[i].length(); j++)
        {
            if(virus_signs[i][j] == '='){
                std::string virus_name = virus_signs[i].substr(0, j);
                virus_names.push_back(virus_name);
                virus_signs[i].erase (0, j+1);

                virus_signs[i] = hex_to_ascii(virus_signs[i], virus_name);
            }
        }
 
    }

    virus_meta.push_back(virus_names);
    virus_meta.push_back(virus_signs);

    return virus_meta;
}

std::string read_file_ascii(const std::string &file_name, const int &signature_length)
{
    //Tar in ett filpath, öppnar filen och returnerar en string med innehållet i ascii

    std::string file_str;
    char bytes;
    

    std::ifstream file(file_name, std::ios::in);

    while(file.get(bytes))
    {
        file_str.push_back(bytes);

        if(file_str.length() == signature_length)
        {
            break;
        }
    }
    
    return file_str;
}


std::string hex_to_ascii(const std::string &signature_str, const std::string &virus_name)
{
    /*
    Tar in en hexsignatur, gör om den till ascii och returnerar en string med innehållet.
    */

    std::string ascii_str;

    for(int i = 0; i < signature_str.length(); i++)
    {
        std::string temp_str;
        temp_str = signature_str[i];
        temp_str += signature_str[i + 1];

        try {
            const unsigned int byte = std::stoul(temp_str, nullptr, 16);
            ascii_str.push_back(char(byte));
        }
        catch(std::invalid_argument){
            static bool message_shown = false;
            if (message_shown == false){
                std::cout << virus_name << " signature is not hexadecimal. Please check the signature database" << std::endl;
                message_shown = true;
            }
        }
        i++;
    }

    return ascii_str;
}


void compare_log(std::vector<std::vector<std::string> > &virus_signs, std::vector<std::string> &file_paths)
{
    /*
    Tar in en dubbelvektor med virusnamn och virussignaturer i ascii och en vektor med filpaths.
    Funktionen jämför signaturerna och innehållet i filen, och om dessa två matchar så skriver en string till en loggfil
    */

    static std::string log_string = "";

    for (int i = 0; i < virus_signs[1].size(); i++)
    {

        for (int j = 0; j < file_paths.size(); j++)
        {
            std::string filename = file_paths[j];
            std::size_t found = filename.find_last_of("/");
            filename = filename.substr(found+1);

            int signature_length = virus_signs[1][i].length();

            if(virus_signs[1][i] == read_file_ascii(file_paths[j], signature_length))
            {
                log_string = log_string + "Filename: " + filename + "\nFilepath: " + 
                file_paths[j] + "\nis infected with " + virus_signs[0][i] + "\n\n";
            }
        }
    }
    write_log(log_string);
}

void write_log(std::string infected_file_string)
{
    if (infected_file_string == ""){
        infected_file_string = "No files are infected";
    } 
    std::ofstream log ("dv1620.log");

    log << infected_file_string;
    log.close();
}

