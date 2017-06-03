clear all;
clc;

%% PARAMETEREK
f=@(x) sin(x);   %a sorbafejtendo fuggveny
x0=0;            %a sorfejtes kozeppontja
nmax=20;         %ekkora rendig megyunk el a kozelitessel
xlims=[-12 12];  %x hatarai abrazolaskor
ylims=[-2 2];    %y hatarai abrazolaskor
N=1e4;           %abrazolt pontok szama

%% EGYUTTHATOK SZAMITASA
syms z;
df=f(z);
cn=zeros(nmax+1,1);
for n=0:nmax
    if n>0
        df=diff(df);
    end
    cn(n+1)=vpa(subs(df,z,x0))/factorial(n);
end
cn

%% ABRAZOLAS
x=linspace(xlims(1),xlims(2),N);
taylor=zeros(size(x));
for n=0:nmax
    taylor=taylor+cn(n+1)*(x-x0).^n;
    plot(x,f(x),x,taylor);
    title(sprintf('Kozelites rendje: %d',n));
    axis([xlims ylims]);
    grid on;
    pause(0.5);
end
