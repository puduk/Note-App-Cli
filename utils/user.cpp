#include <iostream>
#include "terminal.hpp"
#include <algorithm>
#include "menu.hpp"
#include <fstream>

user::user(){
  capacity = 10;
  current_size = 0;

  notes = new std::string[capacity];
  first_note_enter = new std::string();
  add_note_enter = new std::string();
  note_adder_choice = new std::string();

  free_slot = capacity - current_size;
  free_slots_check = new std::string();

  current_adding_size = current_size + note_adder_size;

  password_notes = new std::string[capacity];
  password_note_holder = new std::string();
  password_notes_size = 0;

  current_removed_size = new int(0);
  removed_notes = new std::string[capacity];

  current_removed_password_size = new int(0);
  removed_password_notes = new std::string[capacity];

  note_password = 0;
  first_page_choice = 0;
  menu_choice = 0;
  note_adder_size = 0;
  remover_choice = 0;
  password_note_deleter_choice = new int(0);
}

void user::first_note(const std::string& firstnote){
  std::ofstream check_note_file(username + ".txt", std::ios::app);
  if(!check_note_file.is_open()){
    std::cerr << "Could not added note file" << std::endl;
    exit(0);
  }

  std::ofstream first_note_file(username + ".txt", std::ios::app);
  first_note_file << "Notes: \n";
  notes[current_size] = *first_note_enter ;
  first_note_file << current_size + 1 << ". " <<  notes[current_size] << std::endl;
  current_size++;
  free_slot --;
  return menu(*this);
}

void user::add_note(const std::string& note){
  std::ofstream check_adder_file(username + ".txt", std::ios::app);
  if(!check_adder_file.is_open()){
    std::cerr << "Could not added note file" << std::endl;
    return menu(*this);
  }

  std::ofstream adder_file(username + ".txt", std::ios::app);

  notes[current_size] = *add_note_enter ;
  adder_file << current_size + 1 << ". "<< notes[current_size] << std::endl;
  current_size++;
  free_slot --;

  std::cout << blue << "Note added: " << *add_note_enter << std::endl;
  std::cout << blue << "Do you want to add more notes:\n";
  std::cin >> *note_adder_choice;
  std::cin.ignore();
  std::cin.clear();
  std::transform(note_adder_choice->begin(), note_adder_choice->end(), note_adder_choice->begin(), ::tolower);

  if(*note_adder_choice == "no"){
    std::cout << blue << "Returning Menu...\n";
    return menu(*this);
  }

  if(*note_adder_choice == "yes") {
    std::cout << blue << "How many new notes you want to add:\n";
    std::cout << blue << "You have " << free_slot << " free note slots.\n";
    std::cin >> note_adder_size;
    std::cin.ignore();
    std::cin.clear();

    if(note_adder_size > free_slot){
      std::cout << blue << "You want to add more than your free slots\n";
      std::cin >> *free_slots_check;
      std::cin.ignore();
      std::cin.clear();
      std::transform(free_slots_check->begin(), free_slots_check->end(), free_slots_check->begin(), ::tolower);

      if(*free_slots_check == "yes"){
        resize_notes();
        for (int i = current_size; i < current_size + note_adder_size; i++) {
          std::cout << blue << "Enter your " << i + 1 << " note: ";
          std::getline(std::cin, notes[i]);
        }
        current_size += note_adder_size;
        free_slot -= note_adder_size;
      } else {
        std::cerr << "Notes are not going to add more than your free slots\n";
        return menu(*this);
      }

    } else {
      for (int i = current_size; i < current_size + note_adder_size; i++){
        std::cout << green << "Enter your note:\n";
        std::getline(std::cin, notes[i]);
      }
      current_size += note_adder_size;
      free_slot -= note_adder_size;
    }

    std::ofstream extra_adder_file(username + ".txt", std::ios::out);
    for (int i = 0; i < current_size; i++){
      extra_adder_file << i + 1 << ". " << notes[i] << std::endl;
    }
  }

  std::cout << blue << "Returning Menu...\n";
  return menu(*this);
}

void user::resize_notes(){
  capacity *= 2;
  auto* temp_notes = new std::string[capacity];
  for(int i = 0; i < current_size; i++){
    temp_notes[i] = notes[i];
  }
  delete[] notes;
  notes = temp_notes;
  free_slot = capacity - current_size;
}

void user::show_notes(){
  std::ifstream show_file(username + ".txt", std::ios::in);
  if(!show_file.is_open()){
    std::cerr << "Could not load your notes." << std::endl;
    return menu(*this);
  }

  std::string line;
  while (std::getline(show_file, line)) {
    std::cout << line << std::endl;
  }

  std::cout << blue << "Returning Menu...\n";
  return menu(*this);
}
void user::add_password_note(const std::string& password_note_adder){
  std::ofstream password_file_check(username + "lock_note.txt", std::ios::app);
  if(!password_file_check.is_open()){
    std::cerr << "Could not added note file" << std::endl;
    return menu(*this);
  }

  std::ofstream password_file_notes(username + "lock_note.txt", std::ios::app);
  password_notes[password_notes_size] = *password_note_holder;
  password_file_notes << password_notes_size + 1 << ". " << password_notes[password_notes_size] << std::endl;
  password_notes_size++;

  std::cout << blue << "Note added:\n";
  std::cout << blue << "Do you want to add more notes:\n";
  std::cin >> *note_adder_choice;
  std::cin.ignore();
  std::cin.clear();
  std::transform(note_adder_choice->begin(), note_adder_choice->end(), note_adder_choice->begin(), ::tolower);

  if(*note_adder_choice == "yes") {
    std::cout << blue << "How many new notes you want to add:\n";
    std::cout << blue << "You have " << free_slot << " free note slots.\n";
    std::cin >> note_adder_size;
    std::cin.ignore();
    std::cin.clear();

    if(note_adder_size > free_slot){
      std::cout << blue << "You want to add more then your free slots\n";
      std::cin >> *free_slots_check;
      std::cin.ignore();
      std::cin.clear();
      std::transform(free_slots_check->begin(), free_slots_check->end(), free_slots_check->begin(), ::tolower);
      if(*free_slots_check == "yes"){
        resize_notes();
      } else {
        std::cerr << "Notes are not going to add more then your free slots\n";
        return menu(*this);
      }
    }

    for (int i = password_notes_size - 1; i < note_adder_size + password_notes_size - 1; i++) {
      std::cout << blue << "Enter your note:\n";
      std::getline(std::cin, password_notes[i]);
      password_notes_size++;
    }

    std::ofstream renew_password_notes(username + "lock_note.txt", std::ios::out);
    for(int i = 0; i < password_notes_size; i++) {
      renew_password_notes << i + 1 << ". " << password_notes[i] << std::endl;
    }
  }

  std::cout << blue << "Returning Menu...\n";
  return menu(*this);
}

void user::show_password_note() {
  std::cout << blue << "Need Username and Password for showing:" << std::endl;
  std::cout << "Username: ";
  std::cin >> username;
  std::cin.ignore();
  std::cin.clear();
  std::cout << "Password: ";
  std::cin >> password;
  std::cin.ignore();
  std::cin.clear();

  std::ifstream check_password("user.txt", std::ios::in);
  if (!check_password.is_open()) {
    std::cerr << "Could not load your password notes." << std::endl;
    return menu(*this);
  }

  std::string note_found_username;
  std::string note_found_password;
  std::string password_line;
  bool show_note = false;

  while (std::getline(check_password, password_line)) {
    if (password_line.find("Username: ") != std::string::npos) {
      note_found_username = password_line.substr(password_line.find(": ") + 2);
    } else if (password_line.find("Password: ") != std::string::npos) {
      note_found_password = password_line.substr(password_line.find(": ") + 2);
      if (username == note_found_username && password == note_found_password) {
        show_note = true;
      }
    }
  }

  if (!show_note) {
    std::cerr << "You did not enter the correct password!" << std::endl;
    return menu(*this);
  }

  std::ifstream show_password_notes(username + "lock_note.txt", std::ios::in);
  if (!show_password_notes.is_open()) {
    std::cerr << "Could not load your locked notes." << std::endl;
    return menu(*this);
  }

  std::string line;
  while (std::getline(show_password_notes, line)) {
    std::cout << blue << line << std::endl;
  }
}

void user::remove_note(){
  std::cout << blue << "Which note you want to remove?" << std::endl;
  for (int i = 0 ; i < current_size ; i ++){
    std::cout << i + 1 << ". " << green << notes[i] << std::endl;
  }

  std::cin >> remover_choice;
  std::cin.ignore();
  std::cin.clear();

  if(remover_choice <= 0 || remover_choice > current_size){
    std::cerr << "You did not have the correct choice!" << std::endl;
    return menu(*this);
  }

  remover_choice--;

  std::ofstream remover_list(username + "removed.txt", std::ios::app);
  if(!remover_list.is_open()){
    std::cerr << "Could not removed your notes." << std::endl;
    return menu(*this);
  }

  removed_notes[*current_removed_size] = notes[remover_choice];
  remover_list << notes[remover_choice];
  (*current_removed_size)++;

  for (int i = remover_choice ; i < current_size - 1 ; i++){
    notes[i] = notes[i + 1];
  }
  current_size--;

  std::ofstream renew_notes(username + ".txt", std::ios::out);
  if(!renew_notes.is_open()){
    std::cerr << "Could not remove your notes." << std::endl;
    return menu(*this);
  }

  for (int i = 0 ; i < current_size ; i++){
    renew_notes << i + 1 << ". " << notes[i] << std::endl;
  }

  return menu(*this);
}

void user::show_removed_notes(){
  std::ifstream show_removed_notes(username + "removed.txt", std::ios::in);
  if(!show_removed_notes.is_open()){
    std::cerr << "Could not load your removed notes." << std::endl;
    return menu(*this);
  }

  if (current_removed_size == 0) {
    std::cerr << "You dont have deleted notes!" << std::endl;
    return menu(*this);
  }

  std::string remover_reader;
  while(std::getline(show_removed_notes, remover_reader)){
    std::cout << green << remover_reader << std::endl;
  }
}

void user::remove_password_note(){
  std::ifstream security_check("user.txt", std::ios::in);
  if(!security_check.is_open()){
    std::cerr << "Could not load your password notes." << std::endl;
    return menu(*this);
  }

  std::string found_password;
  std::string found_username;
  std::string security_reader;
  bool can_remove = false;

  std::cout << blue << "Need username and password for deleting:" << std::endl;
  std::cout << blue << "Username: " << std::endl;
  std::cin >> username;
  std::cin.ignore();
  std::cin.clear();
  std::cout << blue << "Password: " << std::endl;
  std::cin >> password;
  std::cin.ignore();
  std::cin.clear();

  while(std::getline(security_check, security_reader)){
    if(security_reader.find("Username: ") != std::string::npos){
      found_username = security_reader.substr(security_reader.find(": ") + 2);
    } else if(security_reader.find("Password: ") != std::string::npos){
      found_password = security_reader.substr(security_reader.find(": ") + 2);
      if(found_username == username && found_password == password){
        can_remove = true;
      }
    }
  }

  if(!can_remove){
    std::cerr << "Username or password not found." << std::endl;
    return menu(*this);
  }

  if(password_notes_size == 0 ){
    std::cerr << "You don't have locked notes." << std::endl;
    return menu(*this);
  }

  std::cout << blue << "Password Notes List: " << std::endl;
  for(int i = 0 ; i < password_notes_size  ; i++){
    std::cout << i + 1 << ". " << password_notes[i] << std::endl;
  }

  std::cout << blue << "Which option you want to delete:" << std::endl;
  std::cin >> *password_note_deleter_choice;
  std::cin.ignore();
  std::cin.clear();

  if(*password_note_deleter_choice <= 0  || *password_note_deleter_choice > password_notes_size){
    std::cerr << "You don't have that note." << std::endl;
    return menu(*this);
  }

  (*password_note_deleter_choice)--;

  std::ofstream removed_password_adder(username + "removed_lock.txt" , std::ios::app);
  if(!removed_password_adder.is_open()){
    std::cerr << "Could not remove your notes." << std::endl;
    return menu(*this);
  }

  removed_password_notes[*current_removed_password_size] = password_notes[*password_note_deleter_choice];
  removed_password_adder << *current_removed_password_size + 1 << ". " << password_notes[*password_note_deleter_choice] << std::endl;
  (*current_removed_password_size)++;

  for(int i = *password_note_deleter_choice; i < password_notes_size - 1; i++){
    password_notes[i] = password_notes[i + 1];
  }

  password_notes_size--;

  std::ofstream renew_password_notes(username + "lock_done.txt", std::ios::out);
  if(!renew_password_notes.is_open()){
    std::cerr << "Could not update your notes." << std::endl;
    return menu(*this);
  }

  for(int i = 0 ; i < password_notes_size ; i++){
    renew_password_notes << i + 1 << ". " << password_notes[i] << std::endl;
  }

  std::cout << blue << "Note deleted and saved in removed notes.\n";
  return menu(*this);
}

void user::show_removed_password_notes(){
  std::ifstream removed_password_security("user.txt", std::ios::in);
  if(!removed_password_security.is_open()){
    std::cerr << "Could not load your password notes." << std::endl;
    return menu(*this);
  }

  std::cout << blue << "We need your username and password for showing you this notes." << std::endl;
  std::cout << blue << "Username: " << std::endl;
  std::cin >> username;
  std::cin.ignore();
  std::cin.clear();
  std::cout << blue << "Password: " << std::endl;
  std::cin >> password;
  std::cin.ignore();
  std::cin.clear();

  std::string show_found_password;
  std::string show_found_username;
  std::string security_removed_reader;
  bool can_see = false;

  while(std::getline(removed_password_security, security_removed_reader)){
    if(security_removed_reader.find("Username: ") != std::string::npos){
      show_found_username = security_removed_reader.substr(security_removed_reader.find(": ") + 2);
    }else if (security_removed_reader.find("Password: ") != std::string::npos){
      show_found_password = security_removed_reader.substr(security_removed_reader.find(": ") + 2);
      if (show_found_username == username && show_found_password == password){
        can_see = true;
      }
    }
  }

  if(!can_see){
    std::cerr << "Username or password wrong." << std::endl;
    return menu(*this);
  }

  std::ifstream shower_removed_password_notes(username + "removed_lock.txt", std::ios::in);
  if(!shower_removed_password_notes.is_open()) {
    std::cerr << "Could not load your data." << std::endl;
    return menu(*this);
  }

  std::string removed_password_notes;
  while (std::getline(shower_removed_password_notes, removed_password_notes)) {
    std::cout << blue << removed_password_notes << std::endl;
  }

  return menu(*this);
}

user::~user(){
  delete first_note_enter;
  delete add_note_enter;
  delete note_adder_choice;
  delete free_slots_check;
  delete[] password_notes;
  delete password_note_holder;
  delete[] notes;
  delete[] removed_notes;
  delete[] removed_password_notes;
  delete current_removed_password_size;
  delete password_note_deleter_choice;
  delete current_removed_size;
}


