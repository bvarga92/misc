clear all;
clc;

%% PARAMETEREK
if 1
    m1=0.03;   % 1. egitest tomege
    x10=2;     % 1. egitest kezdeti poziciojanak x koordinataja
    vx10=0.2;  % 1. egitest kezdeti sebessegenek x iranyu komponense
    y10=2;     % 1. egitest kezdeti poziciojanak y koordinataja
    vy10=-0.2; % 1. egitest kezdeti sebessegenek y iranyu komponense
    m2=0.5;    % 2. egitest tomege
    x20=0;     % 2. egitest kezdeti poziciojanak x koordinataja
    vx20=0;    % 2. egitest kezdeti sebessegenek x iranyu komponense
    y20=0;     % 2. egitest kezdeti poziciojanak y koordinataja
    vy20=0;    % 2. egitest kezdeti sebessegenek y iranyu komponense
    m3=0.03;   % 3. egitest tomege
    x30=-2;    % 3. egitest kezdeti poziciojanak x koordinataja
    vx30=-0.2; % 3. egitest kezdeti sebessegenek x iranyu komponense
    y30=-2;    % 3. egitest kezdeti poziciojanak y koordinataja
    vy30=0.2;  % 3. egitest kezdeti sebessegenek y iranyu komponense
else
    m1=1;        % 1. egitest tomege
    x10=-0.97;   % 1. egitest kezdeti poziciojanak x koordinataja
    vx10=-0.466; % 1. egitest kezdeti sebessegenek x iranyu komponense
    y10=0.243;   % 1. egitest kezdeti poziciojanak y koordinataja
    vy10=-0.433; % 1. egitest kezdeti sebessegenek y iranyu komponense
    m2=1;        % 2. egitest tomege
    x20=0.970;   % 2. egitest kezdeti poziciojanak x koordinataja
    vx20=-0.466; % 2. egitest kezdeti sebessegenek x iranyu komponense
    y20=-0.243;  % 2. egitest kezdeti poziciojanak y koordinataja
    vy20=-0.433; % 2. egitest kezdeti sebessegenek y iranyu komponense
    m3=1;        % 3. egitest tomege
    x30=0;       % 3. egitest kezdeti poziciojanak x koordinataja
    vx30=0.932;  % 3. egitest kezdeti sebessegenek x iranyu komponense
    y30=0;       % 3. egitest kezdeti poziciojanak y koordinataja
    vy30=0.866;  % 3. egitest kezdeti sebessegenek y iranyu komponense
end
g=1;        % gravitacios allando
Ts=0.01;    % szimulacios idokoz
N=10000;    % szimulacios utemszam

%% A DIFFERENCIALEGYENLET MEGOLDASA
%  eredeti masodrendu:
%       x1''=g*m2*(x2-x1)/((x1-x2)^2+(y1-y2)^2)^1.5+g*m3*(x3-x1)/((x1-x3)^2+(y1-y3)^2)^1.5
%       y1''=g*m2*(y2-y1)/((x1-x2)^2+(y1-y2)^2)^1.5+g*m3*(y3-y1)/((x1-x3)^2+(y1-y3)^2)^1.5
%       x2''=g*m1*(x1-x2)/((x1-x2)^2+(y1-y2)^2)^1.5+g*m3*(x3-x2)/((x2-x3)^2+(y2-y3)^2)^1.5
%       y2''=g*m1*(y1-y2)/((x1-x2)^2+(y1-y2)^2)^1.5+g*m3*(y3-y2)/((x2-x3)^2+(y2-y3)^2)^1.5
%       x3''=g*m1*(x1-x3)/((x1-x3)^2+(y1-y3)^2)^1.5+g*m2*(x2-x3)/((x2-x3)^2+(y2-y3)^2)^1.5
%       y3''=g*m1*(y1-y3)/((x1-x3)^2+(y1-y3)^2)^1.5+g*m2*(y2-y3)/((x2-x3)^2+(y2-y3)^2)^1.5
%  szetbontva elsorenduekre:
%       x1'=vx1
%       vx1'=g*m2*(x2-x1)/((x1-x2)^2+(y1-y2)^2)^1.5+g*m3*(x3-x1)/((x1-x3)^2+(y1-y3)^2)^1.5
%       y1'=vy1
%       vy1'=g*m2*(y2-y1)/((x1-x2)^2+(y1-y2)^2)^1.5+g*m3*(y3-y1)/((x1-x3)^2+(y1-y3)^2)^1.5
%       x2'=vx2
%       vx2'=g*m1*(x1-x2)/((x1-x2)^2+(y1-y2)^2)^1.5+g*m3*(x3-x2)/((x2-x3)^2+(y2-y3)^2)^1.5
%       y2'=vy2
%       vy2'=g*m1*(y1-y2)/((x1-x2)^2+(y1-y2)^2)^1.5+g*m3*(y3-y2)/((x2-x3)^2+(y2-y3)^2)^1.5
%       x3'=vx3
%       vx3'=g*m1*(x1-x3)/((x1-x3)^2+(y1-y3)^2)^1.5+g*m2*(x2-x3)/((x2-x3)^2+(y2-y3)^2)^1.5
%       y3'=vy3
%       vy3'=g*m1*(y1-y3)/((x1-x3)^2+(y1-y3)^2)^1.5+g*m2*(y2-y3)/((x2-x3)^2+(y2-y3)^2)^1.5

dx1=@(vx1) vx1;
dvx1=@(x1,y1,x2,y2,x3,y3) g*m2*(x2-x1)/((x1-x2)^2+(y1-y2)^2)^1.5+g*m3*(x3-x1)/((x1-x3)^2+(y1-y3)^2)^1.5;
dy1=@(vy1) vy1;
dvy1=@(x1,y1,x2,y2,x3,y3) g*m2*(y2-y1)/((x1-x2)^2+(y1-y2)^2)^1.5+g*m3*(y3-y1)/((x1-x3)^2+(y1-y3)^2)^1.5;
dx2=@(vx2) vx2;
dvx2=@(x1,y1,x2,y2,x3,y3) g*m1*(x1-x2)/((x1-x2)^2+(y1-y2)^2)^1.5+g*m3*(x3-x2)/((x2-x3)^2+(y2-y3)^2)^1.5;
dy2=@(vy2) vy2;
dvy2=@(x1,y1,x2,y2,x3,y3) g*m1*(y1-y2)/((x1-x2)^2+(y1-y2)^2)^1.5+g*m3*(y3-y2)/((x2-x3)^2+(y2-y3)^2)^1.5;
dx3=@(vx3) vx3;
dvx3=@(x1,y1,x2,y2,x3,y3) g*m1*(x1-x3)/((x1-x3)^2+(y1-y3)^2)^1.5+g*m2*(x2-x3)/((x2-x3)^2+(y2-y3)^2)^1.5;
dy3=@(vy3) vy3;
dvy3=@(x1,y1,x2,y2,x3,y3) g*m1*(y1-y3)/((x1-x3)^2+(y1-y3)^2)^1.5+g*m2*(y2-y3)/((x2-x3)^2+(y2-y3)^2)^1.5;

x1=x10;
y1=y10;
x2=x20;
y2=y20;
x3=x30;
y3=y30;
vx1=vx10;
vy1=vy10;
vx2=vx20;
vy2=vy20;
vx3=vx30;
vy3=vy30;
x1Save=zeros(1,N);
y1Save=zeros(1,N);
x2Save=zeros(1,N);
y2Save=zeros(1,N);
x3Save=zeros(1,N);
y3Save=zeros(1,N);

for ii=1:N
    x1Save(ii)=x1;
    y1Save(ii)=y1;
    x2Save(ii)=x2;
    y2Save(ii)=y2;
    x3Save(ii)=x3;
    y3Save(ii)=y3;
    a_x1=dx1(vx1);
    a_vx1=dvx1(x1, y1, x2, y2, x3, y3);
    a_y1=dy1(vy1);
    a_vy1=dvy1(x1, y1, x2, y2, x3, y3);
    a_x2=dx2(vx2);
    a_vx2=dvx2(x1, y1, x2, y2, x3, y3);
    a_y2=dy2(vy2);
    a_vy2=dvy2(x1, y1, x2, y2, x3, y3);
    a_x3=dx3(vx3);
    a_vx3=dvx3(x1, y1, x2, y2, x3, y3);
    a_y3=dy3(vy3);
    a_vy3=dvy3(x1, y1, x2, y2, x3, y3);
    b_x1=dx1(vx1+0.5*Ts*a_vx1);
    b_vx1=dvx1(x1+0.5*Ts*a_x1, y1+0.5*Ts*a_y1, x2+0.5*Ts*a_x2, y2+0.5*Ts*a_y2, x3+0.5*Ts*a_x3, y3+0.5*Ts*a_y3);
    b_y1=dy1(vy1+0.5*Ts*a_vy1);
    b_vy1=dvy1(x1+0.5*Ts*a_x1, y1+0.5*Ts*a_y1, x2+0.5*Ts*a_x2, y2+0.5*Ts*a_y2, x3+0.5*Ts*a_x3, y3+0.5*Ts*a_y3);
    b_x2=dx2(vx2+0.5*Ts*a_vx2);
    b_vx2=dvx2(x1+0.5*Ts*a_x1, y1+0.5*Ts*a_y1, x2+0.5*Ts*a_x2, y2+0.5*Ts*a_y2, x3+0.5*Ts*a_x3, y3+0.5*Ts*a_y3);
    b_y2=dy2(vy2+0.5*Ts*a_vy2);
    b_vy2=dvy2(x1+0.5*Ts*a_x1, y1+0.5*Ts*a_y1, x2+0.5*Ts*a_x2, y2+0.5*Ts*a_y2, x3+0.5*Ts*a_x3, y3+0.5*Ts*a_y3);
    b_x3=dx3(vx3+0.5*Ts*a_vx3);
    b_vx3=dvx3(x1+0.5*Ts*a_x1, y1+0.5*Ts*a_y1, x2+0.5*Ts*a_x2, y2+0.5*Ts*a_y2, x3+0.5*Ts*a_x3, y3+0.5*Ts*a_y3);
    b_y3=dy3(vy3+0.5*Ts*a_vy3);
    b_vy3=dvy3(x1+0.5*Ts*a_x1, y1+0.5*Ts*a_y1, x2+0.5*Ts*a_x2, y2+0.5*Ts*a_y2, x3+0.5*Ts*a_x3, y3+0.5*Ts*a_y3);
    c_x1=dx1(vx1+0.5*Ts*b_vx1);
    c_vx1=dvx1(x1+0.5*Ts*b_x1, y1+0.5*Ts*b_y1, x2+0.5*Ts*b_x2, y2+0.5*Ts*b_y2, x3+0.5*Ts*b_x3, y3+0.5*Ts*b_y3);
    c_y1=dy1(vy1+0.5*Ts*b_vy1);
    c_vy1=dvy1(x1+0.5*Ts*b_x1, y1+0.5*Ts*b_y1, x2+0.5*Ts*b_x2, y2+0.5*Ts*b_y2, x3+0.5*Ts*b_x3, y3+0.5*Ts*b_y3);
    c_x2=dx2(vx2+0.5*Ts*b_vx2);
    c_vx2=dvx2(x1+0.5*Ts*b_x1, y1+0.5*Ts*b_y1, x2+0.5*Ts*b_x2, y2+0.5*Ts*b_y2, x3+0.5*Ts*b_x3, y3+0.5*Ts*b_y3);
    c_y2=dy2(vy2+0.5*Ts*b_vy2);
    c_vy2=dvy2(x1+0.5*Ts*b_x1, y1+0.5*Ts*b_y1, x2+0.5*Ts*b_x2, y2+0.5*Ts*b_y2, x3+0.5*Ts*b_x3, y3+0.5*Ts*b_y3);
    c_x3=dx3(vx3+0.5*Ts*b_vx3);
    c_vx3=dvx3(x1+0.5*Ts*b_x1, y1+0.5*Ts*b_y1, x2+0.5*Ts*b_x2, y2+0.5*Ts*b_y2, x3+0.5*Ts*b_x3, y3+0.5*Ts*b_y3);
    c_y3=dy3(vy3+0.5*Ts*b_vy3);
    c_vy3=dvy3(x1+0.5*Ts*b_x1, y1+0.5*Ts*b_y1, x2+0.5*Ts*b_x2, y2+0.5*Ts*b_y2, x3+0.5*Ts*b_x3, y3+0.5*Ts*b_y3);
    d_x1=dx1(vx1+Ts*c_vx1);
    d_vx1=dvx1(x1+Ts*c_x1, y1+Ts*c_y1, x2+Ts*c_x2, y2+Ts*c_y2, x3+Ts*c_x3, y3+Ts*c_y3);
    d_y1=dy1(vy1+Ts*c_vy1);
    d_vy1=dvy1(x1+Ts*c_x1, y1+Ts*c_y1, x2+Ts*c_x2, y2+Ts*c_y2, x3+Ts*c_x3, y3+Ts*c_y3);
    d_x2=dx2(vx2+Ts*c_vx2);
    d_vx2=dvx2(x1+Ts*c_x1, y1+Ts*c_y1, x2+Ts*c_x2, y2+Ts*c_y2, x3+Ts*c_x3, y3+Ts*c_y3);
    d_y2=dy2(vy2+Ts*c_vy2);
    d_vy2=dvy2(x1+Ts*c_x1, y1+Ts*c_y1, x2+Ts*c_x2, y2+Ts*c_y2, x3+Ts*c_x3, y3+Ts*c_y3);
    d_x3=dx3(vx3+Ts*c_vx3);
    d_vx3=dvx3(x1+Ts*c_x1, y1+Ts*c_y1, x2+Ts*c_x2, y2+Ts*c_y2, x3+Ts*c_x3, y3+Ts*c_y3);
    d_y3=dy3(vy3+Ts*c_vy3);
    d_vy3=dvy3(x1+Ts*c_x1, y1+Ts*c_y1, x2+Ts*c_x2, y2+Ts*c_y2, x3+Ts*c_x3, y3+Ts*c_y3);
    x1=x1+Ts*(a_x1+2*b_x1+2*c_x1+d_x1)/6;
    vx1=vx1+Ts*(a_vx1+2*b_vx1+2*c_vx1+d_vx1)/6;
    y1=y1+Ts*(a_y1+2*b_y1+2*c_y1+d_y1)/6;
    vy1=vy1+Ts*(a_vy1+2*b_vy1+2*c_vy1+d_vy1)/6;
    x2=x2+Ts*(a_x2+2*b_x2+2*c_x2+d_x2)/6;
    vx2=vx2+Ts*(a_vx2+2*b_vx2+2*c_vx2+d_vx2)/6;
    y2=y2+Ts*(a_y2+2*b_y2+2*c_y2+d_y2)/6;
    vy2=vy2+Ts*(a_vy2+2*b_vy2+2*c_vy2+d_vy2)/6;
    x3=x3+Ts*(a_x3+2*b_x3+2*c_x3+d_x3)/6;
    vx3=vx3+Ts*(a_vx3+2*b_vx3+2*c_vx3+d_vx3)/6;
    y3=y3+Ts*(a_y3+2*b_y3+2*c_y3+d_y3)/6;
    vy3=vy3+Ts*(a_vy3+2*b_vy3+2*c_vy3+d_vy3)/6;
end

%% ABRAZOLAS
figure(1);
for ii=1:N
    plot(x1Save,y1Save,'r--');
    hold on;
    plot(x2Save,y2Save,'k--');
    plot(x3Save,y3Save,'b--');
    plot(x1Save(ii),y1Save(ii),'o','MarkerFaceColor','r');
    plot(x2Save(ii),y2Save(ii),'o','MarkerFaceColor','k');
    plot(x3Save(ii),y3Save(ii),'o','MarkerFaceColor','b');
    hold off;
    axis equal off;
    axis([minmax([x1Save x2Save x3Save]) minmax([y1Save y2Save y3Save])]);
    title(sprintf('t=%.2f',ii*Ts));
    pause(0.01)
end