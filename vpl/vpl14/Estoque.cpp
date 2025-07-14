#include <string>


#include "Estoque.hpp"

void Estoque::add_mercadoria(const std::string& mercadoria, unsigned int qtd) {
  estoque[mercadoria] += qtd;
}

void Estoque::sub_mercadoria(const std::string& mercadoria, unsigned int qtd) {
  if(estoque.find(mercadoria) != estoque.end()){
    if(estoque[mercadoria] < qtd){
      estoque[mercadoria] -= qtd;
    } else {
      std::cout << mercadoria << " insuficiente" << std::endl;
    }
  } else {
    std::cout << mercadoria << " inexistente" << std::endl;
  }
}

unsigned int Estoque::get_qtd(const std::string& mercadoria) const {
  auto i = estoque.find(mercadoria); 
  if(i == estoque.end()){
      return 0;
  } 
  return i->second;
}

void Estoque::imprime_estoque() const {
  for(auto it: estoque){
    std::cout << it.first << ", " << it.second << std::endl;
  }
}

Estoque& Estoque::operator += (const Estoque& rhs) {
  for(auto it: rhs.estoque){
    this->add_mercadoria(it.first, it.second);
    //estoque->add_mercadoria(it.first, it.second);
  }
  return *this;
  //return estoque;
}

Estoque& Estoque::operator -= (const Estoque& rhs) {
  for(auto it: rhs.estoque){
    this->sub_mercadoria(it.first, it.second);
  }
  return *this;
}

bool operator < (Estoque& lhs, Estoque& rhs) {
  bool resposta = false;
  for(auto it: lhs.estoque){
    if(rhs.estoque.find(it.first) == rhs.estoque.end() || 
       rhs.estoque[it.first] <= it.second){ 
      resposta = false;
      return false;
    }
    else{
      resposta = true;
      return true;
    }
  }
  //return resposta; 
}

bool operator > (Estoque& lhs, Estoque& rhs) {
  bool resposta = false;
  for(auto it: rhs.estoque){
    if(lhs.estoque.find(it.first) == lhs.estoque.end() ||
      lhs.estoque[it.first] <= it.second){ 
      resposta = false;
      return false;
    }
    else{
      resposta = true;
      return true;
    }
  }
  //return resposta; 
}

