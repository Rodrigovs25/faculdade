#include "venda.hpp"

#include <iomanip>

Venda::~Venda() {
  for(auto it : m_pedidos){
      delete(it);
  }
}

void Venda::adicionaPedido(Pedido* p) {
  m_pedidos.push_back(p);
}

void Venda::imprimeRelatorio() const {
  int i = 1;
  float total = 0;
  for (auto it : m_pedidos){
    std::cout << "Pedido " << i++ << std::endl;
    std::cout << it->resumo();
    total += it->calculaTotal();
  }
  std::cout << "Relatorio de Vendas" << std::endl;
  std::cout << "Total de Vendas: R$ " << std::fixed << std::setprecision(2) << total << std::endl;
  std::cout << "Total de pedidos: " << i-1 << std::endl;
}
