#include "hamburguer.hpp"

std::string Hamburguer::descricao() const {
  std::string qtd_str = std::to_string(m_qtd);
  std::string artesenal_str = "";
  if(h_artesenal == 1){
    artesenal_str = "artesanal";
  }
  else{
    artesenal_str = "simples";
  }
  std::string final = qtd_str + "X Hamburguer " + h_tipo + " " + artesenal_str + ".";
  return final;
}

Hamburguer::Hamburguer(const std::string& tipo,
                       bool artesanal,
                       int qtd,
                       float valor_unitario) {
  h_artesenal = artesanal;
  h_tipo = tipo;
  m_qtd = qtd;
  m_valor_unitario = valor_unitario;
}