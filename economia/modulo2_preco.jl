function price(u11,u12,u21,u22,e1,e2,bt1,bt2,r,ngrid)
p1=prec_ini(u11,u12,e1,bt1,r)
p2=prec_ini(u21,u22,e2,bt2,r)
p=max(p1,p2)
ngp=p
eq=p
gridp=1/ngrid:1/ngrid:ngp
abs_exc_dem(preco)=abs(exc_demand(preco,u11,u12,u21,u22,e1,e2,bt1,bt2,r,ngrid))
erro_exc_dem=abs_exc_dem.(gridp)
eq=gridp[argmin(erro_exc_dem)]
a1=demand(eq,u11,u12,e1,bt1,r,ngrid)
a2=demand(eq,u21,u22,e2,bt2,r,ngrid)
erro=minimum(erro_exc_dem)
println("Preço = ",eq)
println("Demanda Investidor 1 = ",a1)
println("Demanda Investidor 2 = ",a2)
println("Erro = ",erro)
#return ["Preço="eq,"Erro="erro]
end