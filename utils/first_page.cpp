#include "first_page.hpp"
#include "sign_in.hpp"
#include "create_account.hpp"
#include "terminal.hpp"
#include <iostream>

void first_page(user &u) {
    std::cout << blue << "Welcome Note Application:\n";
    std::cout << green << "1. Sign in\n";
    std::cout << green << "2. Create Account\n";
    std::cout << green << "3. Exit\n";

    std::cin >> u.first_page_choice;
    std::cin.ignore();
    std::cin.clear();

    switch (u.first_page_choice) {
        case 1:
            sign_in(u);
        break;
        case 2:
            create_account(u);
        break;
        case 3:
            exit(0);
        default:
            std::cerr << red << "Wrong input! Try again...\n";
        first_page(u);
    }
}
