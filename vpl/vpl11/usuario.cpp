#include "usuario.hpp"

Usuario::Usuario(const std::string& login, const std::string& password) {
  this->login = login;
  this->password = password;
}

std::string Usuario::getLogin() const {
  return login;
}

std::string Usuario::getPassword() const {
  return password;
}

void Usuario::setPassword(const std::string& password) {
  this->password = password;
}

void Usuario::setLogin(const std::string& login) {
  this->login = login;
}
