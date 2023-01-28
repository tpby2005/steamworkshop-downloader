#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

int main() {
    std::vector<std::string> downloadList;
    std::fstream input;

    //check if steamcmd exists
    std::filesystem::path steamcmd { "C:\\steamcmd\\steamcmd.exe" };
    if (!std::filesystem::exists(steamcmd)) {
        std::cerr << "Please install steamcmd to 'C:\\steamcmd', https://developer.valvesoftware.com/wiki/SteamCMD#Downloading_SteamCMD";
        return -1;
    }

    //check if steamcmd has been initialized
    std::filesystem::path steamdll { "C:\\steamcmd\\steam.dll" };
    if (!std::filesystem::exists(steamdll)) {
        system("C:\\steamcmd\\steamcmd.exe +quit");
    }

    //add ids to vector
    input.open("input.txt", std::ios::in);
    if (input.is_open()) {
        std::string line;

        while (std::getline(input, line)) {
            downloadList.push_back(line);
        }
        input.close();
    }

    else {
        std::cerr << "Failed to open input.txt, does it exist?";
        return -1;
    }

    for (const std::string &i : downloadList) {
        std::string con = "C:\\steamcmd\\steamcmd.exe +login anonymous +workshop_download_item " + i + " +quit";

        system(con.c_str());
    }

    //move all to closer dir
    std::filesystem::remove_all("downloads");

    std::filesystem::copy(R"(C:\steamcmd\steamapps\workshop)", "downloads", std::filesystem::copy_options::recursive);

    return 0;
}