clear all;
clc;

%% SZIMULACIOS PARAMETEREK
Ts=0.02;    % szimulacios idokoz
N=10000;    % szimulacios utemszam

%% A DIFFERENCIALEGYENLET ES A KEZDETI ALLAPOT MEGADASA
%  diffegyenlet:
%       x'=-y-z
%       y'=x+A*y
%       z'=B+z*(x-C)
%  allapotvektor:
%       X=[x, y, z]

A=0.2; B=0.2; C=5.7;
% A=0.1; B=0.1; C=14;

dXdt=@(x)[
    -x(2)-x(3);
	x(1)+A*x(2);
	B+x(3)*(x(1)-C);
];

% x=[(C-sqrt(C^2-4*A*B))/2 ; (-C+sqrt(C^2-4*A*B))/2/A ; (C-sqrt(C^2-4*A*B))/2/A]+rand(3,1); % egyik fixpont
x=[(C+sqrt(C^2-4*A*B))/2 ; (-C-sqrt(C^2-4*A*B))/2/A ; (C+sqrt(C^2-4*A*B))/2/A]+rand(3,1); % masik fixpont

%% RUNGE-KUTTA-MODSZER
xSave=zeros(length(x),N);
for ii=1:N
    xSave(:,ii)=x;
    a=dXdt(x);
    b=dXdt(x+0.5*Ts*a);
    c=dXdt(x+0.5*Ts*b);
    d=dXdt(x+Ts*c);
    x=x+Ts*(a+2*b+2*c+d)/6;
end

%% ABRAZOLAS
figure(1);
plot3(xSave(1,:),xSave(2,:),xSave(3,:));
xlabel('x');
ylabel('y');
zlabel('z');
axis equal;
axis([minmax(xSave(1,:)) minmax(xSave(2,:)) minmax(xSave(3,:))])