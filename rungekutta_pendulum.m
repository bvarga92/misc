clear all;
clc;

%% PARAMETEREK
g=9.81;    %nehezsegi gyorsulas (m/s^2)
L=1;       %inga hossza (m)
theta0=60; %kezdeti kiteres (fok)
omega0=0;  %kezdeti szogsebesseg (fok/s)
Ts=0.01;   %szimulacios idokoz (s)
N=1000;    %szimulacios utemszam

%% A DIFFERENCIALEGYENLET
%  eredeti masodrendu:  theta'' = -g/L*sin(theta)
%  szetbontva ket csatolt elsorendure:  omega' = -g/L*sin(theta)
%                                       theta' = omega
dOmega=@(theta) -g/L*sin(theta);
dTheta=@(omega) omega;

%% RUNGE-KUTTA-MODSZER
theta=theta0/180*pi;
omega=omega0/180*pi;
thetaSave=zeros(1,N);
omegaSave=zeros(1,N);
for ii=1:N
    a_omega=dOmega(theta);
    a_theta=dTheta(omega);
    b_omega=dOmega(theta+0.5*Ts*a_theta);
    b_theta=dTheta(omega+0.5*Ts*a_omega);
    c_omega=dOmega(theta+0.5*Ts*b_theta);
    c_theta=dTheta(omega+0.5*Ts*b_omega);
    d_omega=dOmega(theta+Ts*c_theta);
    d_theta=dTheta(omega+Ts*c_omega);
    omega=omega+Ts*(a_omega+2*b_omega+2*c_omega+d_omega)/6;
    theta=theta+Ts*(a_theta+2*b_theta+2*c_theta+d_theta)/6;
    thetaSave(ii)=theta;
    omegaSave(ii)=omega;
end

%% ABRAZOLAS
figure(1);
plot((0:N-1)*Ts,thetaSave/pi*180,(0:N-1)*Ts,omegaSave/pi*180);
xlim([0 (N-1)*Ts]);
xlabel('t [s]');
legend('\theta [\circ]','\omega [\circ/s]');
figure(2);
for ii=1:N
    x=L*sin(thetaSave(ii));
    y=L-L*cos(thetaSave(ii));
    plot(x,y,'o','MarkerFaceColor','b');
    hold on;
    plot([0 x],[L y]);
    hold off;
    axis equal off;
    axis([-L L -0.05 L]);
    title(sprintf('t=%.2f s',ii*Ts));
    pause
end
