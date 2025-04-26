#include "menu.hpp"
#include <iostream>
#include <limits>
#include "terminal.hpp"
#include "user.hpp"

void menu(user &u) {
    u.free_slot = u.capacity - u.current_size;
    std::cout << cyan << "---- MENU ----\n";
    std::cout << "1: ADD NOTE\n";
    std::cout << "2: REMOVE NOTE:\n";
    std::cout << "3: ADD PASSWORD NOTES:\n";
    std::cout << "4: REMOVE PASSWORD NOTES:\n";
    std::cout << "5: SHOWING NOTES:\n";
    std::cout << "6: SHOWING DELETED NOTES:\n";
    std::cout << "7: SHOWING PASSWORD NOTES:\n";
    std::cout << "8: SHOWING DELETED PASSWORD NOTES:\n";
    std::cout << "9: EXIT\n";
    std::cout << "----------------------------\n";
    std::cin >> u.menu_choice;

    if(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "You did not entered number!" << std::endl;
        menu(u);
    }

    switch(u.menu_choice){
        case 1:
            std::cin.ignore();
        std::cout << blue << "Enter new note:\n";
        std::getline(std::cin, *u.add_note_enter);
        u.add_note(*u.add_note_enter);
        break;
        case 2:
            u.remove_note();
        break;
        case 3:
            std::cin.ignore();
        std::cout << blue << "Enter new note:\n";
        std::getline(std::cin, *u.password_note_holder);
        u.add_password_note(*u.password_note_holder);
        break;
        case 4:
            u.remove_password_note();
        break;
        case 5:
            u.show_notes();
        break;
        case 6:
            u.show_removed_notes();
        break;
        case 7:
            u.show_password_note();
        break;
        case 8:
            u.show_removed_password_notes();
        break;
        case 9:
            exit(0);
        default:
            std::cerr << "Invalid Choice!" << std::endl;
        return;
    }
}
