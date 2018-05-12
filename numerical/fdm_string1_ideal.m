clear all;
clc;

%% parameterek
L=0.765; % a hur hossza [m]
c=425;   % a hullam terjedesi sebessege a huron [m/s]
t=linspace(0,1/278,1000); % ido [s]
x=linspace(0,L,500);      % vizszintes pozicio a hur menten [m]

r=c*(t(2)-t(1))/(x(2)-x(1));
fprintf('Courant number: %.4f\n',r);
if r>1
    warning('The CFL condition for numerical stability is not satisfied!');
end

%% 1. kezdeti feltetel (a hur alakja a t=0 pillanatban): y(x,0)=f(x)
y=zeros(length(x),length(t));
y(:,1)=0.3*(x(end)-2*abs(x-x(end)/2));

%% 2. kezdeti feltetel (a hur minden pontjanak kezdosebessege 0): dy/dt|(t=0)=0
for ix=2:length(x)-1
    y(ix,2)=y(ix,1)-0.5*r^2*(y(ix+1,1)-2*y(ix,1)+y(ix-1,1));
end

%% diffegyenlet megoldasa vegesdifferencia-modszerrel
% PDE: (d^2/dt^2)y=c^2*(d^2/dx^2)y
% Dirichlet-peremfeltetelek: y(0,t)=y(L,t)=0
for it=2:length(t)-1
    for ix=2:length(x)-1
        y(ix,it+1)=r^2*(y(ix-1,it)-2*y(ix,it)+y(ix+1,it))-y(ix,it-1)+2*y(ix,it);
    end
end

%% abrazolas
for it=1:length(t)
    figure(1);
    plot(100*x,100*y(:,it));
    axis(100*[minmax(x) min(min(y)) max(max(y))]);
    xlabel('x [cm]');
    ylabel('y [cm]');
    title(sprintf('t=%.2f ms',1000*t(it)));
    pause(0.01);
end