clear all;
clc;

%% PARAMETEREK
euler=false; % Euler- vagy Runge-Kutta-modszerrel dolgozzunk?
g=9.81;      % nehezsegi gyorsulas [m/s^2]
L=1;         % felfuggesztes hossza [m]
D=2;         % ingak tavolsaga [m]
m=1;         % testek tomege [kg]
k=1;         % rugoallando [N/m]
x10=-0.5;    % 1. inga kezdeti kiterese [m]
x20=-0;      % 2. inga kezdeti kiterese [m]
v10=0;       % 1. inga kezdeti sebessege [m/s]
v20=0;       % 2. inga kezdeti sebessege [m/s]
Ts=0.01;     % szimulacios idokoz [s]
N=10000;     % szimulacios utemszam

%% A DIFFERENCIALEGYENLET MEGOLDASA
%  eredeti masodrendu:  x1'' = -g/L*x1+k/m*(x2-x1)
%                       x2'' = -g/L*x2-k/m*(x2-x1)
%  szetbontva negy csatolt elsorendure:  v1' = -g/L*x1+k/m*(x2-x1)
%                                        v2' = -g/L*x2-k/m*(x2-x1)
%                                        x1' = v1
%                                        x2' = v2

dV1=@(x1,x2) -g/L*x1+k/m*(x2-x1);
dV2=@(x1,x2) -g/L*x2-k/m*(x2-x1);
dX1=@(v1) v1;
dX2=@(v2) v2;

x1=x10;
x2=x20;
v1=v10;
v2=v20;
x1Save=zeros(1,N);
x2Save=zeros(1,N);
v1Save=zeros(1,N);
v2Save=zeros(1,N);

if euler % Euler-modszer
    for ii=1:N
        x1Save(ii)=x1;
        x2Save(ii)=x2;
        v1Save(ii)=v1;
        v2Save(ii)=v2;
        v1_=v1+Ts*dV1(x1,x2);
        v2_=v2+Ts*dV2(x1,x2);
        x1_=x1+Ts*dX1(v1);
        x2_=x2+Ts*dX2(v2);
        v1=v1_;
        v2=v2_;
        x1=x1_;
        x2=x2_;
    end
else % Runge-Kutta-modszer
    for ii=1:N
        x1Save(ii)=x1;
        x2Save(ii)=x2;
        v1Save(ii)=v1;
        v2Save(ii)=v2;
        a_v1=dV1(x1,x2);
        a_v2=dV2(x1,x2);
        a_x1=dX1(v1);
        a_x2=dX2(v2);
        b_v1=dV1(x1+0.5*Ts*a_x1,x2+0.5*Ts*a_x2);
        b_v2=dV2(x1+0.5*Ts*a_x1,x2+0.5*Ts*a_x2);
        b_x1=dX1(v1+0.5*Ts*a_v1);
        b_x2=dX2(v2+0.5*Ts*a_v2);    
        c_v1=dV1(x1+0.5*Ts*b_x1,x2+0.5*Ts*b_x2);
        c_v2=dV2(x1+0.5*Ts*b_x1,x2+0.5*Ts*b_x2);
        c_x1=dX1(v1+0.5*Ts*b_v1);
        c_x2=dX2(v2+0.5*Ts*b_v2);
        d_v1=dV1(x1+Ts*c_x1,x2+Ts*c_x2);
        d_v2=dV2(x1+Ts*c_x1,x2+Ts*c_x2);
        d_x1=dX1(v1+Ts*c_v1);
        d_x2=dX2(v2+Ts*c_v2);
        v1=v1+Ts*(a_v1+2*b_v1+2*c_v1+d_v1)/6;
        v2=v2+Ts*(a_v2+2*b_v2+2*c_v2+d_v2)/6;
        x1=x1+Ts*(a_x1+2*b_x1+2*c_x1+d_x1)/6;
        x2=x2+Ts*(a_x2+2*b_x2+2*c_x2+d_x2)/6;
    end
end

%% ABRAZOLAS
figure(1);
subplot(211);
plot((0:N-1)*Ts,x1Save,(0:N-1)*Ts,x2Save);
xlim([0 (N-1)*Ts]);
xlabel('t [s]');
ylabel('x [m]');
legend('x_1','x_2');
title('Elmozdulas');
subplot(212);
plot((0:N-1)*Ts,v1Save,(0:N-1)*Ts,v2Save);
xlim([0 (N-1)*Ts]);
xlabel('t [s]');
ylabel('v [m/s]');
legend('v_1','v_2');
title('Sebesseg');
figure(2);
for ii=1:10:N
    x1=-D/2+x1Save(ii);
    y1=L-sqrt(L^2-x1Save(ii)^2);
    x2=D/2+x2Save(ii);
    y2=L-sqrt(L^2-x2Save(ii)^2);
    plot(x1,y1,'o','MarkerFaceColor','b');
    hold on;
    plot(x2,y2,'o','MarkerFaceColor','b');
    plot([-D/2 x1],[L y1]);
    plot([D/2 x2],[L y2]);
    plot([x1 x2],[y1 y2],'r');
    hold off;
    axis equal off;
    axis([-D/2-L D/2+L 0 L]);
    title(sprintf('t=%.2f s',ii*Ts));
    pause
end