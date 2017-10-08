clear all;
clc;

%% A PROPELLER MEGRAJZOLASA
a=2;    %lapatok hossza
k=5;    %ha ptl: lapatok szama, ha ps: lapatok szamanak fele
N=5000; %pontok szama
phi=linspace(0,2*pi,N);
points=[a*cos(k*phi).*cos(phi) ; a*cos(k*phi).*sin(phi)];
clear phi;

%% FORGATAS
K=720;      %kepkockak szama
ang=2*pi/K; %szogelfordulas egy kepkocka alatt
R=[cos(ang) -sin(ang) ; sin(ang) cos(ang)];
posY=-a;
x=[];
y=[];
figure(1);
for ii=1:K
    points=R*points;
    posY=posY+2*a/K;
    sect=abs(points(2,:)-posY)<a/K*5;
    x=[x points(1,sect)];
    y=[y points(2,sect)];
    plot([-a a],[posY posY],'k','LineWidth',2);
    hold on;
    plot(points(1,:),points(2,:),'b','LineWidth',2);
    plot(x,y,'r.','LineWidth',1);
    hold off;
    axis([-a a -a a]);
    axis square off;
    pause(0.01);
end
