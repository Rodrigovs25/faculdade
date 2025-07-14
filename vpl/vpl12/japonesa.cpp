#include "japonesa.hpp"

std::string Japonesa::descricao() const {
  std::string qtd_str = std::to_string(m_qtd);
  std::string sushi_str = std::to_string(j_sushis);
  std::string temaki_str = std::to_string(j_temakis);
  std::string hot_str = std::to_string(j_hots);
  std::string final = qtd_str + "X Comida japonesa - " + j_combinado + ", " + sushi_str +
                      " sushis, " + temaki_str + " temakis e " + hot_str + " hots."; 
  return final;
}

Japonesa::Japonesa(const std::string& combinado,
                   int sushis,
                   int temakis,
                   int hots,
                   int qtd,
                   float valor_unitario) {
  j_combinado = combinado;
  j_sushis = sushis;
  j_temakis = temakis;
  j_hots = hots;
  m_valor_unitario = valor_unitario;
  m_qtd = qtd;
}
