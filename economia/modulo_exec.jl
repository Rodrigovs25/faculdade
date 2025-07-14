# Dados de entrada

e1=[8,0];
e2=[4,0];
bt1=0.8;
bt2=0.5;
r=1.5;
ngrid=1000;

u11(c)=log(c);
u12(c)=(c)^(1/2);
u21(c)=log(c);
u22(c)=(c)^(1/2);

#Arquivos de Execução

module principal
include("bloco1_demanda.jl")
include("bloco2_equil.jl")         
end

#Comando Principal Extraído do Módulo Principal
prec_func=principal.price
(eq,a1,a2,erro)=prec_func(u11,u12,u21,u22,e1,e2,bt1,bt2,r,ngrid)

println("Preço = ",eq)
println("Demanda Investidor 1 = ",a1)
println("Demanda Investidor 2 = ",a2)
println("Erro = ",erro)