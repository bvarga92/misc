clear all;
clc;

%% PARAMETEREK
x0=0;        % x(0)
dx0=0.01;    % x'(0)
mu=1.5;      % csillapitas
Ts=0.01;     % szimulacios idokoz
N=5000;      % szimulacios utemszam
 
%% A DIFFERENCIALEGYENLET MEGOLDASA
%  eredeti masodrendu:  x''-mu*(1-x^2)*x'+x=0
%  szetbontva ket csatolt elsorendure:  x'=dx
%                                       dx'=mu*(1-x^2)*dx-x

dX=@(dx) dx;
dDx=@(dx,x) mu*(1-x^2)*dx-x;

x=x0;
dx=dx0;
xSave=zeros(1,N);
dxSave=zeros(1,N);

for ii=1:N
    xSave(ii)=x;
    dxSave(ii)=dx;
    a_x=dX(dx);
    a_dx=dDx(dx,x);
    b_x=dX(dx+0.5*Ts*a_dx);
    b_dx=dDx(dx+0.5*Ts*a_dx,x+0.5*Ts*a_x);
    c_x=dX(dx+0.5*Ts*b_dx);
    c_dx=dDx(dx+0.5*Ts*b_dx,x+0.5*Ts*b_x);
    d_x=dX(dx+Ts*c_dx);
    d_dx=dDx(dx+Ts*c_dx,x+Ts*c_x);
    x=x+Ts*(a_x+2*b_x+2*c_x+d_x)/6;
    dx=dx+Ts*(a_dx+2*b_dx+2*c_dx+d_dx)/6;
end

%% ABRAZOLAS
figure(1);
plot((0:N-1)*Ts,xSave);
xlim([0 (N-1)*Ts]);
xlabel('t');
ylabel('x');
figure(2);
plot(xSave,dxSave);
axis equal;
xlabel('x');
ylabel('dx/dt');