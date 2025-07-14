function demand(p,u1,u2,e,bt,r,ngrid)
a=1/ngrid:1/ngrid:1
one_matrix=ones(ngrid)
c1=one_matrix*e[1]-a*p
c2=one_matrix*e[2]+a*r
restric=c1.>=0
u_matrix=(u1.(c1.*restric)+bt*u2.(c2.*restric))
return a[argmax(u_matrix)]
end

function exc_demand(p,u11,u12,u21,u22,e1,e2,bt1,bt2,r,ngrid)
a1=demand(p,u11,u12,e1,bt1,r,ngrid)
a2=demand(p,u21,u22,e2,bt2,r,ngrid)
return a1+a2-1
end

function prec_ini(u1,u2,e,bt,r)
umg1=ngrid*(u1(e[1]+1/ngrid)-u1(e[1]))
umg2=ngrid*(u2(e[2]+1/ngrid)-u2(e[2]))
return r*bt*umg2/umg1
end
println("Funções demanda, excesso de demanda e preço inicial executadas com sucesso")