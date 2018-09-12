%% 1. feladat
% P(A|B)=0.7 �s P(AB)=0.3 �s P(B|Ac)=0.6. Mennyi P(A)?
% (A c index a komplementer esem�nyt jel�li.)
% Megold�s: Bayes-t�tel, kihaszn�lva a felt�teles val�sz�n�s�g defin�ci�j�t
%     P(A|B)=P(B|A)*P(A)/(P(B|A)*P(A)+P(B|Ac)*P(Ac))
%     P(A|B)=P(AB)/(P(AB)+P(B|Ac)*(1-P(A)))
%     0.7=0.3/(0.3+0.6-0.6*P(A))
%     P(A)=11/14

clear all;
close all;
clc;

N=1e6;                % ennyi k�s�rletet v�gz�nk
B=rand(1,N)<3/7;      % P(B)=P(AB)/P(A|B)=0.3/0.7=3/7
A=rand(1,N);
A(B==1)=A(B==1)<0.7;  % P(A|B)=0.7
A(B==0)=A(B==0)<0.85; % P(A)=P(A|B)*P(B)+P(A|Bc)*P(Bc)=P(AB)+P(A|Bc)*P(Bc) --> P(A|Bc)=(P(A)-P(AB))/P(Bc)=(11/14-0.3)/(4/7)=0.85

fprintf('P(A)    = %.3f\n',sum(A)/N);               % 11/14=0.7857
fprintf('P(B)    = %.3f\n',sum(B)/N);               % 3/7=0.4286
fprintf('P(A|B)  = %.3f\n',sum(A(B==1))/sum(B==1)); % 0.7
fprintf('P(B|Ac) = %.3f\n',sum(B(A==0))/sum(A==0)); % 0.6
fprintf('P(AB)   = %.3f\n',sum(A.*B)/N);            % 0.3
fprintf('P(B|A)  = %.3f\n',sum(B(A==1))/sum(A==1)); % P(B|A)=P(AB)/P(A)=0.3/(11/14)=21/55=0.3818

pause;


%% 2. feladat
% Egy egyt�rol�s rendszer "tau" id��lland�j�t m�rj�k �gy, hogy ide�lis
% n�gysz�gjelet adunk a rendszer bemenet�re, �s oszcilloszk�ppal m�rj�k,
% hogy a rendszer kimenete a n�gysz�gjel felfut� �l�t k�vet�en mikor �ri el
% az "A"-val jel�lt v�g�rt�k "a" r�szar�ny�t. Legyen ez az id� "t2". Hogyan
% kaphat� meg a "tau" id��lland� a "t2" �s "a" adatokb�l?

clear all;
close all;
clc;

tau=0.2;
A=3;
a=0.6;
highpass=false; % alul- vagy fel�l�tereszt� jelleg� legyen a rendszer?

T=20*tau;
t=linspace(0,T,4096); t=t(1:end-1);
u=A/2*(1-square(2*pi/T*t)); % gerjeszt�s
if highpass==false % alul�tereszt� eset
    % Az ugr�sv�lasz  A*(1-exp(-t/tau))  alak�, teh�t az  A*(1-exp(-t2/tau))=a*A
    % egyenletet kell megoldanunk tau-ra. A megold�s:  tau=-t2/ln(1-a)
    sys=tf(1,[tau 1]) % egyt�rol�s tag
    y=lsim(sys,u,t); % v�lasz
    t2=length(find(y(u>A/2)<A*a))*(t(2)-t(1)) % m�rt t2
    tau_est=-t2/log(1-a) % becs�lt id��lland�
else % fel�l�tereszt� eset
    % Az ugr�sv�lasz  A*exp(-t/tau)  alak�, teh�t az  A*exp(-t2/tau)=a*A
    % egyenletet kell megoldanunk tau-ra. A megold�s:  tau=-t2/ln(a)
    sys=tf([tau 0],[tau 1]) % egyt�rol�s tag
    y=lsim(sys,u,t); % v�lasz
    t2=length(find(y(u>A/2)>A*a))*(t(2)-t(1)) % m�rt t2
    tau_est=-t2/log(a) % becs�lt id��lland�
end

figure(1);
plot(t,u,'b',t,y,'k',t,a*A*ones(size(t)),'r--','LineWidth',2);
hold on;
plot(t2+T/2,a*A,'ro','MarkerSize',15,'LineWidth',2);
hold off
axis([t(2) t(end) -0.5 A+0.5]);
xlabel('t');
legend('gerjeszt�s','v�lasz','a*A','Location','NorthWest');
grid on;
title(sprintf('M�rt t_2: %.3f,   becs�lt tau: %.3f',t2,tau_est))

pause;


%% 3. feladat
% A megadott adatsor a Budapesten regisztr�lt havas napok sz�m�t tartalmazza �venk�nt 1901. �s 2000. k�z�tt.
% a) Szignifik�nsan kevesebb havas nap volt-e 1994-ben Budapesten, mint a kor�bbi �vekben (1901. �ta)?
%    Az elt�r�st szignifik�nsnak tekintj�k, ha p=5%-n�l kisebb a val�sz�n�s�ge egy legal�bb ekkora elt�r�snek.
% b) Szignifik�nsan kevesebb havas nap volt-e a 20. sz�zad utols� �vtized�ben Budapesten, mint az els�ben?
% c) Szignifik�nsan kevesebb havas nap volt-e a 20. sz�zad utols� �vtized�ben Budapesten, mint az 50-es �vekben?
% d) Illessz polinomot a m�r�si adatokra!

clc;
close all;
clear all;

data=[1901,31;1902,30;1903,18;1904,33;1905,34;1906,44;1907,43;1908,44;1909,35;1910,28;1911,31;1912,26;1913,42;1914,24;1915,40;
1916,19;1917,49;1918,37;1919,52;1920,29;1921,26;1922,29;1923,36;1924,38;1925,31;1926,23;1927,33;1928,40;1929,42;1930,27;
1931,48;1932,43;1933,46;1934,27;1935,64;1936,29;1937,48;1938,41;1939,29;1940,63;1941,48;1942,55;1943,31;1944,51;1945,48;
1946,34;1947,58;1948,31;1949,30;1950,32;1951,33;1952,67;1953,42;1954,57;1955,52;1956,65;1957,34;1958,44;1959,31;1960,25;
1961,15;1962,33;1963,33;1964,24;1965,26;1966,23;1967,18;1968,20;1969,36;1970,47;1971,32;1972,17;1973,36;1974,19;1975,21;
1976,38;1977,31;1978,33;1979,29;1980,53;1981,40;1982,23;1983,24;1984,34;1985,31;1986,46;1987,34;1988,29;1989,4;1990,19;
1991,21;1992,26;1993,48;1994,19;1995,43;1996,48;1997,29;1998,22;1999,36;2000,32;];

% a)
data1994=data(data(:,1)==1994,2);   % ennyi havas nap volt 1994-ben: 19
dataPre1994=data(data(:,1)<1994,2); % korabbi evek
N=length(dataPre1994);              % korabbi evek szama az adatsorban: 93
avg=mean(dataPre1994);              % korabbi evek atlaga: 35.30
s=std(dataPre1994);                 % korabbi evek tapasztalati szorasa: 12.1930
t=abs((data1994-avg)/s);            % t-ertek: 1.3369 (92 szabadsagi foku t-eloszlas)
P1=100*(1-tcdf(t,N-1));             % P(X<19)=9.23% --> nem szignifikans az elteres
if P1<5
    fprintf('1.: szignifikans az elteres.\n');
else
    fprintf('1.: nem szignifikans az elteres.\n');
end
fprintf('P1=%.2f%%\n\n',P1);

% b)
data190x=data((data(:,1)>=1901) & (data(:,1)<=1910),2); % elso evtized
data199x=data((data(:,1)>=1991) & (data(:,1)<=2000),2); % utolso evtized
h1=ttest2(data190x,data199x,'Tail','right'); % 0 --> elfogadjuk a nullhipotezist, nem szignifikans az elteres
if h1
    fprintf('2.: szignifikans az elteres.\n');
else
    fprintf('2.: nem szignifikans az elteres.\n');
end
% vagy manualisan:
N190x=length(data190x); % elso evtizedbeli adatok szama az adatsorban: 10
avg190x=mean(data190x); % elso evtized atlaga: 34
s190x=std(data190x);    % elso evtized tapasztalati szorasa: 8.1650
N199x=length(data199x); % utolso evtizedbeli adatok szama az adatsorban: 10
avg199x=mean(data199x); % utolso evtized atlaga: 32.40
s199x=std(data199x);    % utolso evtized tapasztalati szorasa: 10.9666
t=(avg190x-avg199x)/sqrt((N190x-1)*s190x^2+(N199x-1)*s199x^2)*...
   sqrt(N190x*N199x*(N190x+N199x-2)/(N190x+N199x)); % ketmintas t-proba statisztikaja: 0.3701
P2=100*(1-tcdf(t,N190x+N199x-2)); % P=35.78% --> nem szignifikans az elteres
fprintf('P2=%.2f%%\n\n',P2);

% c)
data195x=data((data(:,1)>=1951) & (data(:,1)<=1960),2); % 50-es evek
h1=ttest2(data195x,data199x,'Tail','right'); % 1 --> elvetjuk a nullhipotezist, szignifikans az elteres
if h1
    fprintf('3.: szignifikans az elteres.\n');
else
    fprintf('3.: nem szignifikans az elteres.\n');
end
% vagy manualisan:
N195x=length(data195x); % 50-es evekbeli adatok szama az adatsorban: 10
avg195x=mean(data195x); % 50-es evek atlaga: 45
s195x=std(data195x);    % 50-es evek tapasztalati szorasa: 14.7121
t=(avg195x-avg199x)/sqrt((N195x-1)*s195x^2+(N199x-1)*s199x^2)*...
   sqrt(N195x*N199x*(N195x+N199x-2)/(N195x+N199x)); % ketmintas t-proba statisztikaja: 2.1714
P3=100*(1-tcdf(t,N195x+N199x-2)); % P=2.18% --> szignifikans az elteres
fprintf('P3=%.2f%%\n\n',P3);

% d)
D=4;                   % az illesztendo polinom fokszama
N=size(data,1);        % meresek szama: 100
x=data(:,1)-data(1,1); % fuggetlen valtozo: az evek, numerikus okokbol 0-tol szamozva
y=data(:,2);           % fuggo valtozo: a havas napok szama
p=polyfit(x,y,D);      % parametervektor (a polinom egyutthatoi)
figure(1);
plot(data(:,1),data(:,2),'b'); % eredeti adatsor
hold on;
plot(linspace(data(1,1),data(end,1),1000),polyval(p,linspace(x(1),x(end),1000)),'r'); % illesztett polinom
hold off;
xlim([data(1,1) data(end,1)]);
xlabel('ev');
ylabel('havas napok szama');
% vagy manualisan: y=X*p --> p=pinv(X)*y
X=[repmat(x(:),1,D).^repmat(D:-1:1,N,1) , ones(N,1)];
p=X\y

pause;


%% 4. feladat
% Egy laborban szinuszos jelb�l 10000 mint�t vesz�nk. A m�rt regisztr�tumon
% DFT-t v�gz�nk, melyet kirajzolva v�rakoz�sainknak megfelel�en k�t cs�cs
% l�tszik, az els� a 2001. pontban. Ezut�n megism�telj�k a m�r�st ugyanarra
% a jelre, n�gyszer akkora mintav�teli frekvenci�val. Az ism�t 10000 pontos
% DFT-ben a cs�csok pontosan ugyanazokra a helyekre esnek. Hogyan
% lehets�ges ez?

clear all;
close all;
clc;

N=10000;
fs1=1;
fs2=4;
t1=(0:N-1)/fs1;
f1=(0:N-1)*fs1/N;
t2=(0:N-1)/fs2;

f=fs1*fs2/(fs1+fs2);
x1=sin(2*pi*f*t1);
x2=sin(2*pi*f*t2);

figure(2);
subplot(221);
plot(t1,x1);
xlabel('t');
ylabel('x_1(t)');
xlim([t1(1) t1(end)]);
title('Alulmintav�telezve');
subplot(222);
plot(t2,x2);
xlabel('t');
ylabel('x_2(t)');
xlim([t2(1) t2(end)]);
title('Helyesen mintav�telezve');
subplot(223);
plot((0:N-1)*fs1/N,abs(fft(x1)/N));
xlim([0 fs1]);
xlabel('f');
ylabel('|X_1(f)| [dB]');
subplot(224);
plot((0:N-1)*fs2/N,abs(fft(x2)/N));
xlim([0 fs2]);
xlabel('f');
ylabel('|X_2(f)| [dB]');

pause;


%% 5. feladat
% Egy v�letlen realiz�ci�j� folyamat az al�bbi alakban adhat� meg:
% x(t)=exp(-a*t^2), ahol az a param�ter egyenletes eloszl�s� a [0...1]
% intervallumon. Hat�rozd meg a folyamat autokorrel�ci�s f�ggv�ny�t �s
% v�rhat� �rt�k�t t kis �rt�keire!

clear all;
close all;
clc;

K=50;  % ennyi k�s�rletet v�gz�nk
N=1e3;  % k�s�rletenk�nt ennyi mint�t gener�lunk negat�v es pozit�v ir�nyban is
fs=1e2; % mintav�teli frekvencia

x=zeros(K,2*N+1);
a=rand(K,1);
t=(-N:N)/fs;
for ii=1:K
    x(ii,:)=exp(-a(ii)*t.^2);
end

x_theoretical=@(t) (1-exp(-t.^2))./t.^2;
R_theoretical=@(t,tau) (1-exp(-t.^2-(t+tau).^2))./(t.^2+(t+tau).^2);

figure(1);
subplot(121);
plot(t,x');
axis([minmax(t) minmax(x(:)')]);
xlabel('t');
ylabel('x(t)');
subplot(122);
plot(t,mean(x,1));
hold on;
plot(t,x_theoretical(t),'r');
hold off;
axis([minmax(t) minmax(x(:)')]);
legend('k�s�rleti','elm�leti');
xlabel('t');
ylabel('x_{avg}(t)');
figure(2);
tau=t;
[T,TAU]=meshgrid(t,tau);
imagesc(t,tau,R_theoretical(T,TAU));
colorbar;
set(gca,'YDir','normal');
xlabel('t');
ylabel('\tau');
title('R_x(t,\tau)');

pause;


%% 6. feladat
% Egy diszkr�t rendszerbe, amelyben a mintav�teli frekvencia fs, IIR
% alul�tereszt� sz�r�t tervez�nk. A sz�r�t �gy ellen�rizz�k, hogy
% gener�lunk egy fs/64 �s egy fs/16 frekvenci�j�, 256 mint�b�l �ll�
% szinuszjelet (az els�t a sz�r�nek m�g �t kell engednie, a m�sodikat m�r
% el kell nyomnia), �s megsz�rj�k a tervezett sz�r�vel, majd az eredm�nyt
% 256 pontos FFT-vel analiz�ljuk. Meglepve tapasztaljuk, hogy a spektrum
% "sz�tken�d�tt", pedig �gyelt�nk arra, hogy a szinuszokb�l eg�sz sz�m�
% peri�dus jusson a regisztr�tumba. Mit rontottunk el, �s hogyan hozhat�
% helyre a hiba?

clear all;
close all;
clc;

fs=1;
fc=fs/30;
[B,A]=ellip(9,1,80,fc/fs*2);
[H,w]=freqz(B,A,8192);
figure(1);
plot(w/pi*fs/2,20*log10(abs(H)));
xlim([0 fs/2]);
xlabel('f');
ylabel('|H(f)| [dB]');

t=(0:255)/fs;
f=(0:255)*fs/256;
x=sin(2*pi*fs/64*t)+sin(2*pi*fs/16*t);
xf=filter(B,A,x);
xf2=filter(B,A,repmat(x,1,32));
xf2=xf2(end-length(x)+1:end);

figure(2);
subplot(231);
plot(t,x);
xlabel('t');
ylabel('x(t)');
xlim([t(1) t(end)]);
subplot(232);
plot(t,xf);
xlabel('t');
ylabel('x_f(t)');
xlim([t(1) t(end)]);
subplot(233);
plot(t,xf2);
xlabel('t');
ylabel('x_{f2}(t)');
xlim([t(1) t(end)]);
subplot(234);
plot(f,20*log10(abs(fft(x)/256)));
xlim([0 fs/2]);
xlabel('f');
ylabel('|X(f)| [dB]');
subplot(235);
plot(f,20*log10(abs(fft(xf)/256)));
xlim([0 fs/2]);
xlabel('f');
ylabel('|X_f(f)| [dB]');
subplot(236);
plot(f,20*log10(abs(fft(xf2)/256)));
xlim([0 fs/2]);
xlabel('f');
ylabel('|X_{f2}(f)| [dB]');

pause;


%% 7. feladat
% Egy zajos szinuszos jel mint�ib�l N=1000 pontos X(f) DFT-t �s ez alapj�n
% |X(f)|^2 teljes�tm�nys�r�s�g-spektrumot k�sz�tve a szinuszos komponens
% cs�csa P0=15 dB-n�l, az �tlagos zajszint pedig Pn=-5 dB-n�l l�that�.
% Mekkora a jel/zaj viszony? Mennyivel v�ltozik P0 �s Pn �rt�ke ugyanarra a
% jelre, ha N=2000 pontos DFT-t k�sz�t�nk?

clear all;
close all;
clc;

N=1000;
fs=1;
P0=15;
Pn=-5;

A=2*10^(P0/20);
sigma=sqrt(10^(Pn/10)*N/0.56);

for ii=1:2
    N=ii*N;
    t=(0:N-1)/fs;
    f=(0:N-1)*fs/N;
    x=A*sin(2*pi*fs/N*200*t)+sigma*randn(1,N);
    X=10*log10(abs(fft(x)/N).^2);
    figure(1);
    subplot(1,2,ii);
    plot(f,X);
    hold on;
    plot(f,mean(X)*ones(size(f)),'r--');
    plot(f,X(201)*ones(size(f)),'r--');
    hold off;
    xlim([0 fs/2]);
    xlabel('f');
    ylabel('|X(f)| [dB]');
    title(sprintf('N=%d, zajszint %.2f dB',N,mean(X)));
end

pause;


%% 8. feladat
% Szinuszos jelb�l mint�kat vesz�nk, a jel effekt�v �rt�k�t pedig �gy
% sz�m�tjuk ki, hogy a mint�kat n�gyzetre emelj�k, majd a n�gyzetre emelt
% mint�kat �tlagoljuk, v�g�l az �tlagb�l gy�k�t vonunk. Az elj�r�s nagyon
% j�l becs�li az effekt�v �rt�ket, ha betartjuk a mintav�teli t�telt.
% Mutasd meg, hogy a pontos becsl�snek nem sz�ks�ges felt�tele a
% mintav�teli t�tel betart�sa!

clear all;
close all;
clc;

Xeff=1;
N=100;
fs=1;
fx=[0.05 0.50 0.55];

t=(0:N-1)/fs;
f=(0:N-1)*fs/N;

for ii=1:length(fx)
    x=Xeff*sqrt(2)*sin(2*pi*fx(ii)*t);
    Xeff_est=sqrt(mean(x.^2));
    error=(Xeff_est-Xeff)/Xeff;
    fprintf('f=%.2f*fs:\n\tA becsult effektiv ertek %.3f, a hiba %.1f%%.\n\n',fx(ii)/fs,Xeff_est,error*100);
    figure(ii);
    subplot(221);
    plot(t,x);
    xlim([t(1) t(end)]);
    xlabel('t');
    ylabel('x(t)');
    subplot(222);
    plot(f,20*log10(abs(fft(x)/N)));
    xlim([0 fs/2]);
    xlabel('f');
    ylabel('|X(f)| [dB]');
    subplot(223);
    plot(t,x.^2);
    xlim([t(1) t(end)]);
    xlabel('t');
    ylabel('y(t)=x^2(t)');
    subplot(224);
    plot(f,20*log10(abs(fft(x.^2)/N)));
    xlim([0 fs/2]);
    xlabel('f');
    ylabel('|Y(f)| [dB]');
end

pause;


%% 9. feladat
% Egy y jel eloszl�sa egyenletes a [0...q] tartom�nyban. Feladatunk a q
% param�ter meghat�roz�sa, amelyet a jelb�l vett N db. minta seg�ts�g�vel
% becsl�nk. A mint�kb�l lehet�s�g�nk van az �tlag (mu) �s a maximum (M)
% kisz�m�t�s�ra. A q param�ter becsl�s�re k�t m�dszert vizsg�lunk:
% q_mu=mu*c_mu �s q_M=M*c_M. Add meg a c_mu �s c_M konstansokat �gy, hogy
% mindk�t becsl� torz�tatlan legyen (azaz q_mu �s q_M v�rhat� �rt�ke q
% legyen)! Sz�m�tsd ki a k�t becsl� sz�r�s�t!

clear all;
close all;
clc;

N=1000; % ennyi mint�t vesz�nk a jelb�l
K=10000; % ennyiszer v�gezz�k el a k�s�rletet
q=20;
c_mu=2;
c_M=(N+1)/N;

y=q*rand(N,K);
q_mu=mean(y)*c_mu;
q_M=max(y)*c_M;

fprintf('q_mu atlaga %.3f, szorasa %.3f (elmeleti %.3f).\n',mean(q_mu),std(q_mu),2*q/sqrt(12*N));
fprintf('q_M atlaga %.3f, szorasa %.3f (elmeleti %.3f).\n\n',mean(q_M),std(q_M),q/sqrt((N^2+2*N)));

figure(1);
subplot(121);
[p,x]=hist(q_mu,100);
bar(x,p/trapz(x,p));
hold on;
df0=q;
sigma=2*q/sqrt(12*N);
x=linspace(x(1),x(end),1000);
p=1/(sqrt(2*pi)*sigma)*exp(-(x-df0).^2/(2*sigma^2));
plot(x,p,'r','LineWidth',2);
hold off;
xlim([x(1) x(end)]);
title('q_\mu eloszlasa');
subplot(122);
[p,x]=hist(q_M,100);
bar(x,p/trapz(x,p));
hold on;
x=linspace(x(1),x(end),1000);
p=N^2/(q*(N+1))*(x*N/(q*(N+1))).^(N-1);
plot(x,p,'r','LineWidth',2);
hold off;
xlim([x(1) x(end)]);
title('q_M eloszlasa');

pause;


%% 10. feladat
% Az inharmonikus zongorah�r felhangjainak frekvenci�i a k�vetkez�
% k�plettel �rhat�k le: fk=k*f0*sqrt(1+B*k^2), ahol k=[1...K] a felhang
% sz�ma, f0 az alapfrekvencia, B pedig az inharmonicit�si egy�tthat�. A
% zongorahang spektruma alapj�n meghat�rozzuk az fk frekvenci�kat, �s
% felt�telezz�k, hogy a frekvenci�k azonos sz�r�s�, norm�lis eloszl�s�,
% f�ggetlen v�letlen hib�val terheltek. Adj elj�r�st f0 �s B min�l
% pontosabb becsl�s�re!

clear all;
close all;
clc;

K=10;
f0=440;
B=0.1;
sigma=20;

k=(1:K)';
fk=k*f0.*sqrt(1+B*k.^2)+sigma*randn(size(k)) % ezek a m�rt frekvenci�k

% A legegyszer�bb megold�s, hogy p�ronk�nti �sszehasonl�t�ssal becsl�nk:
B_est1=0;
for ii=1:K-1
    for jj=ii+1:K
        B_est1=B_est1+(ii^2*fk(jj)^2-jj^2*fk(ii)^2)/(jj^4*fk(ii)^2-ii^4*fk(jj)^2)/nchoosek(K,2);
    end
end
f0_est1=mean(fk./(k.*sqrt(1+B_est1*k.^2)));
fprintf('f0_est1=%.1f (hiba %.1f%%), B_est1=%.4f (hiba %.1f%%).\n\n',f0_est1,(f0_est1-f0)/f0*100,B_est1,(B_est1-B)/B*100);

% Egy m�sik egyszer� lehet�s�g a line�ris LS m�dszer.
% (Ha az fk vektort 0 v�rhat� �rt�k�, sigma sz�r�s� Gauss-zaj terheli, akkor
% az fk.^2 vektor k-adik komponens�t terhel� zaj v�rhat� �rt�ke sigma^2,
% varianci�ja 2*sigma^4+4*sigma^2*(k^2*f0^2+k^4*f0^2*B). A Gauss-Markov-
% felt�telek nem teljes�lnek, �gy ennek a becsl�nek a jav�t�sa nem
% trivi�lis feladat.)
v=pinv([k.^2 k.^4])*(fk.^2);
B_est2=v(2)/v(1);
f0_est2=sqrt(v(1));
fprintf('f0_est2=%.1f (hiba %.1f%%), B_est2=%.4f (hiba %.1f%%).\n\n',f0_est2,(f0_est2-f0)/f0*100,B_est2,(B_est2-B)/B*100);