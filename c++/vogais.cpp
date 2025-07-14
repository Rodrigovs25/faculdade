#include <iostream>
#include <string>

int main(){
    std::string entrada;
    std::cin >> entrada;
    std::cout << std::endl;
    int a=0, e=0, i=0, o=0, u=0;

    std::size_t found = entrada.find_first_of("aeiou");
    while (found!=std::string::npos)
    {
        if(entrada[found] == 'a')
            a++;
        if(entrada[found] == 'e')
            e++;
        if(entrada[found] == 'i')
            //std::cout << "achei" << std::endl;
            i++;
        if(entrada[found] == 'o')
            o++;
        if(entrada[found] == 'u')
            u++;
        found=entrada.find_first_of("aeiou",found+1);
    }
    if(a>0)
        std::cout << "a = " << a << std::endl;
    if(e>0)
        std::cout << "e = " << e << std::endl;
    if(i>0)
        std::cout << "i = " << i << std::endl;
    if(o>0)
        std::cout << "o = " << o << std::endl;
    if(u>0)
        std::cout << "u = " << u << std::endl;
    
    /*
    for (int i=0; entrada[i] != ' '; ++i)
    {
        std::cout << entrada[i];
    }
    //std::cout << "O tamanho é " << entrada.size() << std::endl;

    std::string str ("Please, replace the vowels in this sentence by asterisks.");
    std::size_t found = str.find_first_of("aeiou");
    while (found!=std::string::npos)
    {
        str[found]='*';
        found=str.find_first_of("aeiou",found+1);
    }

    std::cout << str << '\n';
    */
}


//g++ vogais.cpp -o test