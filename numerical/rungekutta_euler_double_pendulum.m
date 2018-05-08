clear all;
clc;

%% PARAMETEREK
euler=false; % Euler- vagy Runge-Kutta-modszerrel dolgozzunk?
g=9.81;      % nehezsegi gyorsulas [m/s^2]
L1=2;        % 1. inga hossza [m]
L2=1;        % 2. inga hossza [m]
m1=1;        % 1. inga tomege [kg]
m2=0.3;      % 2. inga tomege [kg]
theta10=60;  % 1. inga kezdeti kiterese [fok]
theta20=0;   % 2. inga kezdeti kiterese [fok]
omega10=0;   % 1. inga kezdeti szogsebessege [fok/s]
omega20=0;   % 2. inga kezdeti szogsebessege [fok/s]
Ts=0.005;    % szimulacios idokoz [s]
N=10000;     % szimulacios utemszam

%% A DIFFERENCIALEGYENLET MEGOLDASA
dOmega1=@(theta1,theta2,omega1,omega2) (-g*(2*m1+m2)*sin(theta1)-m2*g*sin(theta1-2*theta2)-2*sin(theta1-theta2)*m2*(omega2^2*L2+omega1^2*L1*cos(theta1-theta2)))/(L1*(2*m1+m2-m2*cos(2*theta1-2*theta2)));
dOmega2=@(theta1,theta2,omega1,omega2) 2*sin(theta1-theta2)*(omega1^2*L1*(m1+m2)+g*(m1+m2)*cos(theta1)+omega2^2*L2*m2*cos(theta1-theta2))/(L2*(2*m1+m2-m2*cos(2*theta1-2*theta2)));
dTheta1=@(omega1) omega1;
dTheta2=@(omega2) omega2;

theta1=theta10/180*pi;
theta2=theta20/180*pi;
omega1=omega10/180*pi;
omega2=omega20/180*pi;
theta1Save=zeros(1,N);
theta2Save=zeros(1,N);
omega1Save=zeros(1,N);
omega2Save=zeros(1,N);

if euler % Euler-modszer
    for ii=1:N
        theta1Save(ii)=theta1;
        theta2Save(ii)=theta2;
        omega1Save(ii)=omega1;
        omega2Save(ii)=omega2;
        omega1_=omega1+Ts*dOmega1(theta1,theta2,omega1,omega2);
        omega2_=omega2+Ts*dOmega2(theta1,theta2,omega1,omega2);
        theta1_=theta1+Ts*dTheta1(omega1);
        theta2_=theta2+Ts*dTheta2(omega2);
        theta1=theta1_;
        theta2=theta2_;
        omega1=omega1_;
        omega2=omega2_;
    end
else % Runge-Kutta-modszer
    for ii=1:N
        a_omega1=dOmega1(theta1,theta2,omega1,omega2);
        a_omega2=dOmega2(theta1,theta2,omega1,omega2);
        a_theta1=dTheta1(omega1);
        a_theta2=dTheta2(omega2);
        b_omega1=dOmega1(theta1+0.5*Ts*a_theta1,theta2+0.5*Ts*a_theta2,omega1+0.5*Ts*a_omega1,omega2+0.5*Ts*a_omega2);
        b_omega2=dOmega2(theta1+0.5*Ts*a_theta1,theta2+0.5*Ts*a_theta2,omega1+0.5*Ts*a_omega1,omega2+0.5*Ts*a_omega2);
        b_theta1=dTheta1(omega1+0.5*Ts*a_omega1);
        b_theta2=dTheta2(omega2+0.5*Ts*a_omega2);
        c_omega1=dOmega1(theta1+0.5*Ts*b_theta1,theta2+0.5*Ts*b_theta2,omega1+0.5*Ts*b_omega1,omega2+0.5*Ts*b_omega2);
        c_omega2=dOmega2(theta1+0.5*Ts*b_theta1,theta2+0.5*Ts*b_theta2,omega1+0.5*Ts*b_omega1,omega2+0.5*Ts*b_omega2);
        c_theta1=dTheta1(omega1+0.5*Ts*b_omega1);
        c_theta2=dTheta2(omega2+0.5*Ts*b_omega2);
        d_omega1=dOmega1(theta1+Ts*c_theta1,theta2+Ts*c_theta2,omega1+Ts*c_omega1,omega2+Ts*c_omega2);
        d_omega2=dOmega2(theta1+Ts*c_theta1,theta2+Ts*c_theta2,omega1+Ts*c_omega1,omega2+Ts*c_omega2);
        d_theta1=dTheta1(omega1+Ts*c_omega1);
        d_theta2=dTheta2(omega2+Ts*c_omega2);
        omega1=omega1+Ts*(a_omega1+2*b_omega1+2*c_omega1+d_omega1)/6;
        omega2=omega2+Ts*(a_omega2+2*b_omega2+2*c_omega2+d_omega2)/6;
        theta1=theta1+Ts*(a_theta1+2*b_theta1+2*c_theta1+d_theta1)/6;
        theta2=theta2+Ts*(a_theta2+2*b_theta2+2*c_theta2+d_theta2)/6;
        if(theta1<-2*pi); theta1=theta1+2*pi; end;
        if(theta1>2*pi);  theta1=theta1-2*pi; end;
        if(theta2<-2*pi); theta2=theta2+2*pi; end;
        if(theta2>2*pi);  theta2=theta2-2*pi; end;
        theta1Save(ii)=theta1;
        theta2Save(ii)=theta2;
        omega1Save(ii)=omega1;
        omega2Save(ii)=omega2;
    end
end

%% ABRAZOLAS
figure(1);
subplot(211);
plot((0:N-1)*Ts,theta1Save/pi*180,(0:N-1)*Ts,theta2Save/pi*180);
xlim([0 (N-1)*Ts]);
xlabel('t [s]');
ylabel('\theta [\circ]');
legend('\theta_1','\theta_2');
title('Szogelfordulas');
subplot(212);
plot((0:N-1)*Ts,omega1Save/pi*180,(0:N-1)*Ts,omega2Save/pi*180);
xlim([0 (N-1)*Ts]);
xlabel('t [s]');
ylabel('\omega [\circ/s]');
legend('\omega_1','\omega_2');
title('Szogsebesseg');
figure(2);
for ii=1:10:N
    x1=L1*sin(theta1Save(ii));
    y1=L1-L1*cos(theta1Save(ii));
    x2=x1+L2*sin(theta2Save(ii));
    y2=y1-L2*cos(theta2Save(ii));
    plot(x1,y1,'o','MarkerFaceColor','b');
    hold on;
    plot(x2,y2,'o','MarkerFaceColor','b');
    plot([0 x1],[L1 y1]);
    plot([x1 x2],[y1 y2]);
    hold off;
    axis equal off;
    axis([-(L1+L2) L1+L2 -(L1+L2) L1+L2]);
    title(sprintf('t=%.2f s',ii*Ts));
    pause
end