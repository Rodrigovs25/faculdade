#include "google_password.hpp"

#include <iostream>

void GooglePassword::insert(const std::string& url,
                            const std::string& login,
                            const std::string& password) {
  if(checkPassword(password) == 0)
    return;
  Usuario novo(login, password);

  std::map<std::string, Usuario>::iterator it = m_passwords.begin();
  m_passwords.insert (it, std::pair<std::string, Usuario>(url, novo));  
}

void GooglePassword::remove(const std::string& url) {
  m_passwords.erase(url);
}


void GooglePassword::update(const std::string& url,
                            const std::string& login,
                            const std::string& old_password,
                            const std::string& new_password) {
  int verificar_url = 0;
  for (auto it = m_passwords.begin(); it != m_passwords.end(); it++){
    if(it->first == url)
      verificar_url = 1;
  }
  if(verificar_url == 0)
    return;
  
  if(checkPassword(new_password) == 0)
    return;

  for (auto it = m_passwords.begin(); it != m_passwords.end(); it++){
    if(it->first == url){
      if(it->second.getPassword() != old_password)
        return;
      it->second.setLogin(login);
      it->second.setPassword(new_password);
      }
  }
}

void GooglePassword::printPasswords() {
  int i = 0;
  for (auto it = m_passwords.begin(); it != m_passwords.end(); it++){
    i++;
  }
  std::cout << i << std::endl;
  for (auto it = m_passwords.begin(); it != m_passwords.end(); it++){
    std::cout << it->first << ": " << it->second.getLogin() << " and " << it->second.getPassword() << std::endl; 
  }
}

bool GooglePassword::checkPassword(const std::string& password) const {
  int j = 0;
  for (int i = 0; i < password.size(); i++){
    if(password[i] == ' ')
      return 0;
    else if(password[i] == '1' && 
            password[i+1] == '2' && 
            password[i+2] == '3' && 
            password[i+3] == '4' && 
            password[i+4] == '5' && 
            password[i+5] == '6')
      return 0;
    j++;
  }
  if(j < 6 || j > 50)
    return 0;
  return 1;
}
