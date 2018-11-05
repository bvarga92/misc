clear all;
clc;

%% parameterek
playSound=true;
fs=44100;
switch 1
    case 1
        N=100;
        T=800;
        epsilon=0.5;
        f=@(x) 0.995*x;
    case 2
        N=100;
        T=800;
        epsilon=rand(1,N);
        f=@(x) 0.995*x;
    case 3
        N=100;
        T=500;
        epsilon=0.3;
        f=@(x) 1-1.1*x.^2;
    case 4
        N=100;
        T=500;
        epsilon=0.3;
        f=@(x) 1-1.75*x.^2;
    case 5
        N=100;
        T=500;
        epsilon=0.5;
        f=@(x) 1-2*x.^2;
    case 6
        N=100;
        T=500;
        epsilon=0.3;
        frac=@(x) x-floor(x);
        f=@(x) frac(x+5/9-1/(2*pi)*sin(2*pi*x));
    case 7
        N=200;
        T=3000;
        epsilon=1;
        frac=@(x) x-floor(x);
        f=@(x) frac(x+0.5-1/(2*pi)*sin(2*pi*x));
    case 8
        N=100;
        T=10000;
        epsilon=0.12;
        frac=@(x) x-floor(x);
        f=@(x) frac(x+0.2-0.2/(2*pi)*sin(2*pi*x));
end

%% CML mukodtetese
y=zeros(T,N);
y(1,:)=rand(1,N)*2-1; % kezdetben teljesen rendezetlen
for t=2:T
    y(t,:)=(1-epsilon).*f(y(t-1,:))+epsilon/2.*(f([y(t-1,2:N) y(t-1,1)])+f([y(t-1,N) y(t-1,1:N-1)])); % Laplace + periodikus peremfeltetel
end
snd=reshape(y',1,N*T);

%% abrazolas, lejatszas
figure(1);
subplot(121);
colormap bone;
imagesc(1:N,(0:T-1)/fs*1000,y);
xlabel('x');
ylabel('t [ms]');
title('CML');
subplot(122);
plot((0:N*T-1)/fs,snd);
xlim([0 (N*T-1)/fs]);
xlabel('t [s]');
title('Hang');
if playSound
    soundsc(snd,fs);
end