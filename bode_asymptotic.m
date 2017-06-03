clear all;
clc;

%% A VIZSGALANDO RENDSZER
% sys=tf(100,[1 30])
sys=tf([100 100],[1 110 1000])
% sys=tf([10 100],[1 3 0])
% sys=tf([-100 0],[1 12 21 10])
% sys=tf([30 300],[1 3 50])
% sys=tf([4 4 100],[1 100 0 0])

%% TORESPONTOK
p=abs(roots(sys.den{1}));
z=abs(roots(sys.num{1}));
w=union(p,z);
if w(1)==0
    w(1)=0.1*10^floor(log10(w(2)));
else
    w=[0.1*10^floor(log10(w(1))); w];
end
w=[w; 10*10^ceil(log10(w(end)))];

%% ATVITEL SZAMITASA
H=zeros(size(w));
H(1)=20*log10(abs(evalfr(sys,w(1))));
t=(sum(z==0)-sum(p==0))*20;
for ii=2:length(w)
    H(ii)=H(ii-1)+log10(w(ii)/w(ii-1))*t;
    t=t+(sum(z==w(ii))-sum(p==w(ii)))*20;
end;
w2=linspace(w(1),w(end),8192);
H2=bode(sys,w2);
H2=20*log10(abs(H2(:)));

%% ABRAZOLAS
figure(1);
semilogx(w,H,w2,H2);
title('Amplitudokarakterisztika');
xlabel('\omega [rad/s]');
ylabel('|H| [dB]');
Hmax=max([H(:); H2(:)])+5;
Hmin=min([H(:); H2(:)])-5;
axis([w(1) w(end) Hmin Hmax]);
for ii=2:length(w)-1
    line([w(ii) w(ii)],[Hmin H(ii)],'LineStyle',':');
end;
xticks=get(gca,'XTick')';
xticks=union(xticks,w);
set(gca,'XTick',xticks);
