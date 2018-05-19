clear all;
clc;

%% parameterek
a=0.1; % hodiffuzivitas
L=1;   % hossz
t=linspace(0,4,500); % ido
x=linspace(0,L,25);  % pozicio

r=a*(t(2)-t(1))/(x(2)-x(1))^2;
if r>0.5
    warning('numerical instability!');
end

%% kezdeti feltetel: a kezdeti T(x,0) homersekleteloszlas adott
T=zeros(length(x),length(t));
T(:,1)=100*sin(pi*x/L);

%% vegesdifferencia-modszer
%     PDE: dT/dt=a*(d^2/dx^2)T
%     Dirichlet-peremfeltetelek: T(0,t)=T(L,t)=0
for it=1:length(t)-1
    for ix=2:length(x)-1
        T(ix,it+1)=r*(T(ix-1,it)-2*T(ix,it)+T(ix+1,it))+T(ix,it);
    end
end

%% abrazolas
for it=1:length(t)
    figure(1);
    plot(x,T(:,it));
    axis([0 L min(min(T)) max(max(T))]);
    xlabel('x');
    ylabel('T');
    title(sprintf('t=%.2f',t(it)));
    pause(0.01);
end