clear all;
clc;

%% parameterek
alpha=0;
x10=1;
x20=0;
t0=0.1;
Ts=0.1;
N=1000;

%% diffegyenlet megoldasa
% eredeti masodrendu t^2*x''+t*x'+(t^2-alpha)*x=0
% szetbontva ket csatolt elsorendure: x1'=x2
%                                     x2'=-(t*x2+(t^2-alpha)*x1)/t^2
dx1=@(x2) x2;
dx2=@(x1,x2,t) -(t*x2+(t^2-alpha)*x1)/t^2;

x1=x10;
x2=x20;
xSave=zeros(1,N);

for ii=1:N
    xSave(ii)=x1;
    a_x1=dx1(x2);
    a_x2=dx2(x1,x2,t0+(ii-1)*Ts);
    b_x1=dx1(x2+0.5*Ts*a_x2);
    b_x2=dx2(x1+0.5*Ts*a_x1,x2+0.5*Ts*a_x2,t0+(ii-1)*Ts);
    c_x1=dx1(x2+0.5*Ts*b_x2);
    c_x2=dx2(x1+0.5*Ts*b_x1,x2+0.5*Ts*b_x2,t0+(ii-1)*Ts);
    d_x1=dx1(x2+Ts*c_x2);
    d_x2=dx2(x1+Ts*c_x1,x2+Ts*c_x2,t0+(ii-1)*Ts);
    x1=x1+Ts*(a_x1+2*b_x1+2*c_x1+d_x1)/6;
    x2=x2+Ts*(a_x2+2*b_x2+2*c_x2+d_x2)/6;
end

%% abrazolas
figure(1);
plot(t0+(0:N-1)*Ts,xSave,'LineWidth',2);
xlim([t0 t0+(N-1)*Ts]);
xlabel('t');
ylabel('x(t)');
grid on;