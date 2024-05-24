#include "pizza.hpp"

std::string Pizza::descricao() const {
  std::string qtd_str = std::to_string(m_qtd);
  std::string pedaco_str = std::to_string(p_pedacos);
  std::string borda = "";
  if(p_borda_recheada == 1){
    borda = "e";
  }
  else{
    borda = "e sem";
  }
  std::string final = qtd_str + "X Pizza " + p_sabor + ", " + pedaco_str + " pedacos " + borda + " borda recheada."; 
  return final;
}

Pizza::Pizza(const std::string& sabor,
             int pedacos,
             bool borda_recheada,
             int qtd,
             float valor_unitario) {
  p_sabor = sabor;
  p_pedacos = pedacos;
  p_borda_recheada= borda_recheada;
  m_qtd = qtd;
  m_valor_unitario = valor_unitario;
}
