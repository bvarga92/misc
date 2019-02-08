clear all;
clc;

%% parameterek
r=0.37e-3;     % belso vezeto sugara [m]
R=2.35e-3;     % kulso vezeto belso sugara [m]
er=2.1;        % dielektrikum relativ permittivitasa
e0=8.8542e-12; % vakuum permittivitasa [F/m]
mur=1;         % dielektrikum relativ permeabilitasa
mu0=4*pi*1e-7; % vakuum permeabilitasa [H/m]

%% geometria
C1=[1 0 0 R]';
C2=[1 0 0 r]';
geom=decsg([C1 C2], 'C1-C2', ['C1';'C2']');
%figure(123); pdegplot(geom,'edgeLabels','on'); xlim([-R R]); axis equal;

%% halogeneralas
[p,e,t]=initmesh(geom);
[p,e,t]=refinemesh(geom,p,e,t);
[p,e,t]=refinemesh(geom,p,e,t);
[p,e,t]=refinemesh(geom,p,e,t);
p=jigglemesh(p,e,t);
%figure(1234); pdemesh(p,e,t); xlim([-R R]); axis equal;

%% peremfeltetelek
ne=size(e,2);
qmatrix=zeros(1,ne);
gmatrix=zeros(1,ne);
hmatrix=zeros(1,2*ne);
rmatrix=zeros(1,2*ne);
for k=1:ne
    switch e(5,k)
        case {1,2,3,4} % kulso vezeto: homogen Dirichlet (u=0)
            hmatrix(k)=1;
            hmatrix(k+ne)=1;
            rmatrix(k)=0;
            rmatrix(k+ne)=0;
        case {5,6,7,8} % belso vezeto: Dirichlet (u=1)
            hmatrix(k)=1;
            hmatrix(k+ne)=1;
            rmatrix(k)=1;
            rmatrix(k+ne)=1;
    end
end
boundaryfunc=@(p,e,u,time) deal(qmatrix,gmatrix,hmatrix,rmatrix);

%% PDE megoldasa (skalaris Laplace-Poisson-egyenlet)
u=assempde(boundaryfunc, p, e, t, 1, 0, 0);

%% hosszegysegre eso kapacitas szamitasa
% Az u megoldast az elektromos skalarpotencialnak tekintjuk, a PDE
% Laplace(u)=-rho/epsilon alaku. A peremfeltetelek jelentese: a belso vezeton
% 1 V feszultseg van, a kulso vezeto pedig foldpotencialon van.

[Ex,Ey]=pdegrad(p,t,u); Ex=-Ex; Ey=-Ey; % E=-grad(u)
E=sqrt(Ex.^2+Ey.^2);                    % az elektromos mezo nagysaga
T=pdetrg(p,t);                          % a haromszogek teruletei
We=0.5*e0*er*sum((E.^2).*T);            % az elektromos mezo energiaja
C=2*We                                  % hosszegysegre eso kapacitas [F/m]
C_theoretical=2*pi*e0*er/log(R/r)       % analitikus eredmeny

%% hosszegysegre eso induktivitas szamitasa
% Az u megoldast a magneses vektorpotencial z komponensenek tekintjuk (ha
% B-nek csak x es y iranyu komponense van, akkor A-nak csak z iranyu komponense
% van, es a PDE a Laplace(Az)=-mu*Jz alakot olti). A vektorpotencial ebben a
% specialis esetben a hosszegysegre eso fluxus potencialja: Psi=A2-A1. A magneses
% mezo energiaja W=0.5*L*I^2=0.5*L*(Psi/L)^2=0.5*(A2-A1)^2/L=1/(2L).

[By,Bx]=pdegrad(p,t,u); By=-By;     % B=[dAz/dy , -dAz/dx , 0]
B=sqrt(Bx.^2+By.^2);                % a magneses indukcio nagysaga
T=pdetrg(p,t);                      % a haromszogek teruletei
Wm=0.5/(mu0*mur)*sum((B.^2).*T);    % a magneses mezo energiaja
L=1/(2*Wm)                          % hosszegysegre eso kapacitas [H/m]
L_theoretical=mu0*mur/2/pi*log(R/r) % analitikus eredmeny

%% hullamimpedancia szamitasa
Z0=sqrt(L/C)
Z0_theoretical=sqrt(L_theoretical/C_theoretical)

%% abrazolas
figure(1);
pdeplot(p,e,t,'xydata',u,'flowdata',[Ex;Ey],'colormap','gray','colorbar','on','mesh','off');
axis equal off;
title('Elektromos mezo (\phi es E)');
figure(2);
pdeplot(p,e,t,'xydata',u,'flowdata',[Bx;By],'colormap','gray','colorbar','on','mesh','off');
axis equal off;
title('Magneses mezo (A_z es B)');