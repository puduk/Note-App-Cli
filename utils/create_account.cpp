#include "create_account.hpp"
#include "menu.hpp"
#include "terminal.hpp"
#include <iostream>
#include <fstream>
#include <string>


void create_account(user &u) {
    std::ofstream file("user.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Could not open file." << std::endl;
        return;
    }

    std::cout << blue << "Enter your username: ";
    std::cin >> u.username;
    std::cin.ignore();
    std::cin.clear();

    std::cout << blue << "Enter your password: ";
    std::cin >> u.password;
    std::cin.ignore();
    std::cin.clear();

    file << "Username: " << u.username << std::endl;
    file << "Password: " << u.password << std::endl;

    std::ofstream first_note_file(u.username + ".txt", std::ios::app);
    if (!first_note_file.is_open()) {
        std::cerr << "Could not create note file" << std::endl;
        return;
    }

    std::cout << green << "Add your first note:\n";
    std::getline(std::cin, *u.first_note_enter);
    u.first_note(*u.first_note_enter);
}
