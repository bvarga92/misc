clear all;
clc;

%% SZIMULACIOS PARAMETEREK
Ts=0.01;    % szimulacios idokoz
N=10000;    % szimulacios utemszam
toSave=1:6; % csak ezen indexu allapotvaltozokat mentjuk el

%% A DIFFERENCIALEGYENLET ES A KEZDETI ALLAPOT MEGADASA
%  eredeti masodrendu:
%       x1''=g*m2*(x2-x1)/((x1-x2)^2+(y1-y2)^2)^1.5+g*m3*(x3-x1)/((x1-x3)^2+(y1-y3)^2)^1.5
%       y1''=g*m2*(y2-y1)/((x1-x2)^2+(y1-y2)^2)^1.5+g*m3*(y3-y1)/((x1-x3)^2+(y1-y3)^2)^1.5
%       x2''=g*m1*(x1-x2)/((x1-x2)^2+(y1-y2)^2)^1.5+g*m3*(x3-x2)/((x2-x3)^2+(y2-y3)^2)^1.5
%       y2''=g*m1*(y1-y2)/((x1-x2)^2+(y1-y2)^2)^1.5+g*m3*(y3-y2)/((x2-x3)^2+(y2-y3)^2)^1.5
%       x3''=g*m1*(x1-x3)/((x1-x3)^2+(y1-y3)^2)^1.5+g*m2*(x2-x3)/((x2-x3)^2+(y2-y3)^2)^1.5
%       y3''=g*m1*(y1-y3)/((x1-x3)^2+(y1-y3)^2)^1.5+g*m2*(y2-y3)/((x2-x3)^2+(y2-y3)^2)^1.5
%  szetbontva elsorenduekre:
%       x1'=vx1
%       y1'=vy1
%       x2'=vx2
%       y2'=vy2
%       x3'=vx3
%       y3'=vy3
%       vx1'=g*m2*(x2-x1)/((x1-x2)^2+(y1-y2)^2)^1.5+g*m3*(x3-x1)/((x1-x3)^2+(y1-y3)^2)^1.5
%       vy1'=g*m2*(y2-y1)/((x1-x2)^2+(y1-y2)^2)^1.5+g*m3*(y3-y1)/((x1-x3)^2+(y1-y3)^2)^1.5
%       vx2'=g*m1*(x1-x2)/((x1-x2)^2+(y1-y2)^2)^1.5+g*m3*(x3-x2)/((x2-x3)^2+(y2-y3)^2)^1.5
%       vy2'=g*m1*(y1-y2)/((x1-x2)^2+(y1-y2)^2)^1.5+g*m3*(y3-y2)/((x2-x3)^2+(y2-y3)^2)^1.5
%       vx3'=g*m1*(x1-x3)/((x1-x3)^2+(y1-y3)^2)^1.5+g*m2*(x2-x3)/((x2-x3)^2+(y2-y3)^2)^1.5
%       vy3'=g*m1*(y1-y3)/((x1-x3)^2+(y1-y3)^2)^1.5+g*m2*(y2-y3)/((x2-x3)^2+(y2-y3)^2)^1.5
%  allapotvektor:
%       x=[x1, y1, x2, y2, x3, y3, vx1, vy1, vx2, vy2, vx3, vy3]

m1=1;
m2=1;
m3=1;
g=1;

dXdt=@(x)[
    x(7);
    x(8);
    x(9);
    x(10);
    x(11);
    x(12);
    g*m2*(x(3)-x(1))/((x(1)-x(3))^2+(x(2)-x(4))^2)^1.5+g*m3*(x(5)-x(1))/((x(1)-x(5))^2+(x(2)-x(6))^2)^1.5;
    g*m2*(x(4)-x(2))/((x(1)-x(3))^2+(x(2)-x(4))^2)^1.5+g*m3*(x(6)-x(2))/((x(1)-x(5))^2+(x(2)-x(6))^2)^1.5;
    g*m1*(x(1)-x(3))/((x(1)-x(3))^2+(x(2)-x(4))^2)^1.5+g*m3*(x(5)-x(3))/((x(3)-x(5))^2+(x(4)-x(6))^2)^1.5;
    g*m1*(x(2)-x(4))/((x(1)-x(3))^2+(x(2)-x(4))^2)^1.5+g*m3*(x(6)-x(4))/((x(3)-x(5))^2+(x(4)-x(6))^2)^1.5;
    g*m1*(x(1)-x(5))/((x(1)-x(5))^2+(x(2)-x(6))^2)^1.5+g*m2*(x(3)-x(5))/((x(3)-x(5))^2+(x(4)-x(6))^2)^1.5;
    g*m1*(x(2)-x(6))/((x(1)-x(5))^2+(x(2)-x(6))^2)^1.5+g*m2*(x(4)-x(6))/((x(3)-x(5))^2+(x(4)-x(6))^2)^1.5;
];

x=[-0.97 ; 0.243 ; 0.970 ; -0.243 ; 0 ; 0 ; -0.466 ; -0.433 ; -0.466 ; -0.433 ; 0.932 ; 0.866];

%% RUNGE-KUTTA-MODSZER
xSave=zeros(length(toSave),N);
for ii=1:N
    xSave(:,ii)=x(toSave);
    a=dXdt(x);
    b=dXdt(x+0.5*Ts*a);
    c=dXdt(x+0.5*Ts*b);
    d=dXdt(x+Ts*c);
    x=x+Ts*(a+2*b+2*c+d)/6;
end

%% ABRAZOLAS
figure(1);
for ii=1:N
    plot(xSave(1,:),xSave(2,:),'r--');
    hold on;
    plot(xSave(3,:),xSave(4,:),'k--');
    plot(xSave(5,:),xSave(6,:),'b--');
    plot(xSave(1,ii),xSave(2,ii),'o','MarkerFaceColor','r');
    plot(xSave(3,ii),xSave(4,ii),'o','MarkerFaceColor','k');
    plot(xSave(5,ii),xSave(6,ii),'o','MarkerFaceColor','b');
    hold off;
    axis equal off;
    axis([minmax([xSave(1,:) xSave(3,:) xSave(5,:)]) minmax([xSave(2,:) xSave(4,:) xSave(6,:)])]);
    title(sprintf('t=%.2f',ii*Ts));
    pause(0.01);
end