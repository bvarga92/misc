clear all;
clc;

%% PARAMETEREK
g=1;      % gravitacios allando
m2=1;     % a kozponti egitest tomege
x0=2;     % kezdeti pozicio x koordinataja
vx0=0.1;  % kezdeti sebesseg x iranyu komponense
y0=2;     % kezdeti pozicio y koordinataja
vy0=-0.1; % kezdeti sebesseg y iranyu komponense
Ts=0.01;  % szimulacios idokoz
N=10000;  % szimulacios utemszam

%% A DIFFERENCIALEGYENLET MEGOLDASA
%  eredeti masodrendu:
%       x''=-g*m2*x/(x^2+y^2)^1.5
%       y''=-g*m2*y/(x^2+y^2)^1.5
%  szetbontva elsorenduekre:
%       x'=vx
%       vx'=-g*m2*x/(x^2+y^2)^1.5
%       y'=vy
%       vy'=-g*m2*y/(x^2+y^2)^1.5

dx=@(vx) vx;
dvx=@(x,y) -g*m2*x/(x^2+y^2)^1.5;
dy=@(vy) vy;
dvy=@(x,y) -g*m2*y/(x^2+y^2)^1.5;

x=x0;
y=y0;
vx=vx0;
vy=vy0;
xSave=zeros(1,N);
ySave=zeros(1,N);

for ii=1:N
    xSave(ii)=x;
    ySave(ii)=y;
    a_x=dx(vx);
    a_vx=dvx(x, y);
    a_y=dy(vy);
    a_vy=dvy(x, y);
    b_x=dx(vx+0.5*Ts*a_vx);
    b_vx=dvx(x+0.5*Ts*a_x, y+0.5*Ts*a_y);
    b_y=dy(vy+0.5*Ts*a_vy);
    b_vy=dvy(x+0.5*Ts*a_x, y+0.5*Ts*a_y);
    c_x=dx(vx+0.5*Ts*b_vx);
    c_vx=dvx(x+0.5*Ts*b_x, y+0.5*Ts*b_y);
    c_y=dy(vy+0.5*Ts*b_vy);
    c_vy=dvy(x+0.5*Ts*b_x, y+0.5*Ts*b_y);
    d_x=dx(vx+Ts*c_vx);
    d_vx=dvx(x+0.5*Ts*c_x, y+Ts*c_y);
    d_y=dy(vy+Ts*c_vy);
    d_vy=dvy(x+Ts*c_x, y+Ts*c_y);
    x=x+Ts*(a_x+2*b_x+2*c_x+d_x)/6;
    vx=vx+Ts*(a_vx+2*b_vx+2*c_vx+d_vx)/6;
    y=y+Ts*(a_y+2*b_y+2*c_y+d_y)/6;
    vy=vy+Ts*(a_vy+2*b_vy+2*c_vy+d_vy)/6;
end

%% ABRAZOLAS
figure(1);
for ii=1:N
    plot(xSave,ySave,'r--');
    hold on;
    plot(0,0,'o','MarkerFaceColor','k');
    plot(xSave(ii),ySave(ii),'o','MarkerFaceColor','r');
    hold off;
    axis equal off;
    axis([minmax(xSave) minmax(ySave)]);
    title(sprintf('t=%.2f',ii*Ts));
    pause(0.01)
end