clear all;
clc;

% sikbeli gorbe
t=linspace(0,19*pi,3000);
x=31*cos(t)-7*cos(31*t/7);
y=31*sin(t)-7*sin(31*t/7);
subplot(321);
plot(x,y);
axis equal;

% tergorbe
t=linspace(0,10*pi,3000);
x=sin(t);
y=cos(t);
z=t;
subplot(322);
plot3(x,y,z);
axis square;
grid on;

% felulet
u=linspace(0,2*pi,30);
v=linspace(0,2*pi,30);
[u,v]=meshgrid(u,v);
x=(4+cos(u)).*cos(v);
y=(4+cos(u)).*sin(v);
z=sin(u);
subplot(323);
mesh(x,y,z);
axis equal;
box on;
grid off;
subplot(324);
surf(x,y,z,'EdgeColor','none');
axis equal;
axis off;

% Mobius-szalag
u=linspace(0,2*pi,30);
v=linspace(-1,1,15);
[u,v]=meshgrid(u,v);
z=(1+v/2.*cos(u/2)).*cos(u);
y=(1+v/2.*cos(u/2)).*sin(u);
x=v/2.*sin(u/2);
subplot(325);
surf(x,y,z);
view(-120,24);
axis off equal;

% Klein-kancso
a=0.2;
c=0.9;
t1=pi/4:pi/30:5*pi/4;
t2=5*pi/4:pi/30:9*pi/4;
u=pi/2:pi/30:5*pi/2;
[X,Z1]=meshgrid(t1,u);
[Y,Z2]=meshgrid(t2,u);
len=sqrt(sin(X).^2+cos(2*X).^2);
x1=c*ones(size(X)).*(cos(X).*sin(X)-0.5*ones(size(X))+a*sin(Z1).*sin(X)./len);
y1=a*c*cos(Z1).*ones(size(X));
z1=ones(size(X)).*cos(X)+a*c*sin(Z1).*cos(2*X)./len;
subplot(326);
surf(x1,y1,z1,X,'EdgeColor','none','FaceAlpha',.5);
hold on;
r=sin(Y).*cos(Y)-(a+1/2)*ones(size(Y));
x2=c*sin(Z2).*r;
y2=-c*cos(Z2).*r;
z2=ones(size(Y)).*cos(Y);
surf(x2,y2,z2,Y,'EdgeColor','none','FaceAlpha',.5);
hold off;
axis vis3d;
view(-37,30);
axis off;
light('Position',[2 -4 5]);
