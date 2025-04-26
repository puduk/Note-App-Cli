#include "sign_in.hpp"
#include <iostream>
#include "terminal.hpp"
#include <fstream>
#include "menu.hpp"

void sign_in(user &u) {

    std::cout << blue << "Username: \n";
    std::cin >> u.username;
    std::cout << blue << "Password: \n";
    std::cin >> u.password;
    std::cin.ignore();
    std::cin.clear();

    std::fstream checkuser("user.txt", std::ios::in);
    if (!checkuser.is_open()) {
        std::cerr << "We could not sign in:\n";
        exit(0);
    }

    std::string found_username;
    std::string found_password;
    bool loginsuccess = false;
    std::string line;

    while (std::getline(checkuser, line)) {
        if (line.find("Username: ") != std::string::npos) {
            found_username = line.substr(line.find(": ") + 2);
        } else if (line.find("Password: ") != std::string::npos) {
            found_password = line.substr(line.find(": ") + 2);
            if (found_username == u.username && found_password == u.password) {
                loginsuccess = true;
            }
        }
    }

    if (!loginsuccess) {
        std::cerr << "Wrong username or password!\n";
        exit(0);
    }

    std::fstream readnotes(u.username + ".txt", std::ios::in);
    if (!readnotes.is_open()) {
        std::cerr << "We could not sign in:\n";
        exit(0);
    }

    std::string notereader;
    while (std::getline(readnotes, notereader)) {
        std::cout << green << notereader << std::endl;
        menu(u);
    }
}
