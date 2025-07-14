function price(u11,u12,u21,u22,e1,e2,bt1,bt2,r,ngrid)
p1=prec_max(u11,u12,e1,bt1,r,ngrid)
p2=prec_max(u21,u22,e2,bt2,r,ngrid)
ngp=max(p1,p2)
gridp=1/ngrid:1/ngrid:ngp
abs_exc_dem(preco)=abs(exc_demand(preco,u11,u12,u21,u22,e1,e2,bt1,bt2,r,ngrid))
erro_exc_dem=abs_exc_dem.(gridp)
eq=gridp[argmin(erro_exc_dem)]
a1=demand(eq,u11,u12,e1,bt1,r,ngrid)
a2=demand(eq,u21,u22,e2,bt2,r,ngrid)
erro=minimum(erro_exc_dem)
return eq,a1,a2,erro
end
println("Função de preço executada com sucesso")