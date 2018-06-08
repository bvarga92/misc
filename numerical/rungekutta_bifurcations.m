clear all;
clc;

%% parameterek
N=5000;
Ts=0.001;
example=1;

%% peldak
switch example
    % nyereg-csomo bifurkacio: fixpontok megjelennek/eltunnek
    % r<0 eseten ket valos fixpont van, a negativ stabilis
    % r>0 eseten nincs valos fixpont
    case 1
        r=-4;
        dx=@(x) r+x.^2;
        fix=@(r) {-sqrt(-r),sqrt(-r)};
        stab=@(r) {r<0,zeros(size(r))};
    % transzkritikus bifurkacio: a fixpontok stabilitast cserelnek
    % r<0 eseten x=0 stabilis, x=r labilis fixpont
    % r>0 eseten x=r stabilis, x=0 labilis fixpont
    case 2
        r=5;
        dx=@(x) r*x-x.^2;
        fix=@(r) {zeros(size(r)),r};
        stab=@(r) {r<0,r>0};
    % szuperkritikus vasvilla bifurkacio: az egyik fixpont elveszti stabilitasat, es ket uj stabilis fixpont jelenik meg
    % r<0 eseten x=0 stabilis fixpont
    % r>0 eseten x=0 labilis, x=+-sqrt(r) stabilis fixpont
    case 3
        r=9;
        dx=@(x) r*x-x.^3;
        fix=@(r) {zeros(size(r)),-sqrt(r),sqrt(r)};
        stab=@(r) {r<0,r>0,r>0};
    % szubkritikus vasvilla bifurkacio: az elozo forditottja
    % r<0 eseten x=0 stabilis, x=+-sqrt(r) labilis fixpont
    % r>0 eseten x=0 labilis fixpont, tobb valos fixpont nincs
    case 4
        r=-9;
        dx=@(x) r*x+x.^3;
        fix=@(r) {zeros(size(r)),-sqrt(-r),sqrt(-r)};
        stab=@(r) {r<0,zeros(size(r)),zeros(size(r))};
end

%% megoldas
xSave=zeros(1,N);
x=rand+1j*rand;
for ii=1:N
    xSave(ii)=x;
    a_x=dx(x);
    b_x=dx(x+0.5*Ts*a_x);
    c_x=dx(x+0.5*Ts*b_x);
    d_x=dx(x+Ts*c_x);
    x=x+Ts*(a_x+2*b_x+2*c_x+d_x)/6;
end

%% abrazolas
figure(1);
subplot(211);
plot((0:N-1)*Ts,abs(xSave));
xlim([0 (N-1)*Ts]);
xlabel('t');
ylabel('|x(t)|');
subplot(212);
plot((0:N-1)*Ts,wrapTo2Pi(angle(xSave))/pi*180);
axis([0 (N-1)*Ts 0 360]);
xlabel('t');
ylabel('arg\{x(t)\} [\circ]');
figure(2);
clf();
r=-9:0.01:9;
f=fix(r);
s=stab(r);
hold on;
for ii=1:length(f)
    g=f{ii};
    plot(r(imag(g)==0 & s{ii}==1),g(imag(g)==0 & s{ii}==1),'g','LineWidth',2);
    plot(r(imag(g)==0 & s{ii}==0),g(imag(g)==0 & s{ii}==0),'r','LineWidth',2);
end
hold off;
xlim(minmax(r));
grid on;
xlabel('r');
ylabel('x_*');
title('Valos fixpontok');