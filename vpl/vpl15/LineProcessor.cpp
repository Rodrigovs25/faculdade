#include <regex>
#include <math.h>
#include <string>
#include <vector>
#include <sstream>

#include "LineProcessor.hpp"

void LinePrinter::processaLinha(const std::string &str) {
  std::cout << str << std::endl;
}

bool ContadorPopRural::linhaValida(const std::string &str) const {
  // Neste exemplo usaremos expressoes regulares para verificar se uma linha
  // eh valida ou nao.
  //
  // Esta expressao regular eh formada por cinco partes. Cada uma dessas
  // partes eh um dos tres tipos de padrao regular abaixo:
  //
  // \\w+ eh qualquer palavra com um ou mais digitos, letras e sublinhas (_)
  // \\s* eh qualquer sequencia de zero ou mais espacos (inclui tab)
  // \\d+ eh qualquer sequencia de um ou mais digitos
  std::regex regularExpr("\\w+\\s*\\d+\\s*\\d+");

  // A funcao regex_match vai retornar verdadeiro se a string str casa-se com
  // a expressao regular que acabamos de criar:
  return std::regex_match(str, regularExpr);
}

void ContadorPopRural::processaLinha(const std::string &str) {
  //
  // Em geral eh mais facil ler dados de uma string se a string eh transformada
  // em um objeto do tipo stringstream:
  std::stringstream ss(str);
  //
  // Iremos ler os dados da string nestas tres variaveis abaixo:
  std::string nomePais;
  unsigned populacao, percUrbana;
  //
  // Como sabemos que a linha contem string int int, podemos fazer a leitura
  // facilmente usando o operador de streaming:
  ss >> nomePais >> populacao >> percUrbana;
  //
  // Note que precisamos arredondar o valor que serah impresso. O arredondamento
  // serah feito via a funcao floor. Ou seja, decimais serao sempre
  // arredondados para baixo:
  unsigned popRural = floor(populacao - (populacao * (percUrbana/100.0)));
  //
  // Uma vez encontrados os valores que precisam ser impressos, seguimos o
  // modelo do enunciado do exercicio:
  std::cout << popRural << " pessoas vivem no campo no " << nomePais << std::endl;
}

bool ContadorNumNaturais::linhaValida(const std::string &str) const {
  std::string expressao = "[\\s*\\d\\s*]+";
  std::regex regularExpr(expressao);
  return std::regex_match(str, regularExpr);
}

void ContadorNumNaturais::processaLinha(const std::string &str) {
  std::string aux = "";
    int soma = 0;
    for (int i = 0; i < str.size(); ++i){
        if(str[i] != 32){
            aux.push_back(str[i]);
        } else {
            soma += stoi(aux);
            aux = "";
        }
    }
    soma += stoi(aux);
    std::cout << soma << std::endl;
}

bool LeitorDeFutebol::linhaValida(const std::string &str) const {
  std::string expressao = "\\s*\\w+\\s*\\d+\\s*\\w+\\s*\\d+\\s*";
  std::regex regularExpr(expressao);
  return std::regex_match(str, regularExpr);
}

void LeitorDeFutebol::processaLinha(const std::string &str) {
  std::stringstream stream(str);
  std::string mandante = "";
  std::string visitante = "";
  int gol_m = 0;
  int gol_v = 0;
  stream >> mandante >> gol_m >> visitante >> gol_v;
  if(gol_m > gol_v){
    std::cout << "Vencedor: " << mandante << std::endl;
  } else if(gol_m < gol_v){
    std::cout << "Vencedor: " << visitante << std::endl;
  } else {
    std::cout << "Empate" << std::endl;
  }

}

void ContadorDePalavras::processaLinha(const std::string &str) {
  std::stringstream stream(str);
  std::vector<std::string> frase = {};
  std::string palavra = "";
  while(stream >> palavra){
    frase.emplace_back(palavra);
  }
  std::cout << frase.size() << std::endl;
}

bool InversorDeFrases::linhaValida(const std::string &str) const {
  std::string expressao = "[\\s*A-Za-z\\s*]+"; // "[ A-Za-z ]+"
  std::regex regularExpr(expressao); 
  return std::regex_match(str, regularExpr);
}

void InversorDeFrases::processaLinha(const std::string &str) {
  std::stringstream stream(str);
  std::vector<std::string> frase = {};
  std::string palavra = "";
  int i = 0;
  while(stream >> palavra){
    frase.push_back(palavra);
  }
  if(frase.size() > 0){
    i = frase.size() - 1;
    std::cout << frase[i--];
    while(i >= 0){
      std::cout << " " << frase[i];
      i--;
    }
    std::cout << std::endl;
  }
}

bool EscritorDeDatas::linhaValida(const std::string &str) const {
  std::string dateFormat = "\\s*\\d\\d?/\\d\\d?/\\d{4}";
  std::regex regularExpr(dateFormat);
  return std::regex_match(str, regularExpr);
}

void EscritorDeDatas::processaLinha(const std::string &str) {
  int dia = 0;
  int mes = 0;
  int ano = 0;
  char barra = ' ';
  std::stringstream stream(str);
  stream >> dia >> barra >> mes >> barra >> ano;
  std::vector<std::string> meses = {"Jan", "Fev", "Mar", "Abr", "Mai", "Jun", 
                                    "Jul", "Ago", "Set", "Out", "Nov", "Dez"};
  std::cout << meses[mes-1] << std::endl;
}