#ifndef USER_HPP
#define USER_HPP

#include <string>

class user {
public:
    user();
    ~user();

    void first_note(const std::string& firstnote);
    void add_note(const std::string& note);
    void resize_notes();
    void show_notes();

    void add_password_note(const std::string& password_note_adder);
    void show_password_note();
    void remove_password_note();
    void show_removed_password_notes();

    void remove_note();
    void show_removed_notes();

    std::string username;
    std::string password;

    std::string* first_note_enter;
    std::string* add_note_enter;
    std::string* note_adder_choice;
    std::string* free_slots_check;
    std::string* password_note_holder;

    std::string* notes;
    std::string* password_notes;
    std::string* removed_notes;
    std::string* removed_password_notes;

    int* current_removed_size;
    int* current_removed_password_size;
    int* password_note_deleter_choice;

    int capacity;
    int current_size;
    int free_slot;
    int current_adding_size;
    int password_notes_size;

    int first_page_choice;
    int menu_choice;
    int note_password;
    int note_adder_size;
    int remover_choice;

};

void menu(user &u);

#endif