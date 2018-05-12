clear all;
clc;

%% parameterek
f=2;   % a gerjesztes frekvenciaja [Hz]
L=500; % hossz [m]
c=500; % a hullam terjedesi sebessege [m/s]
t=linspace(0,4,500);   % ido [s]
x=linspace(0,L,100); % pozicio [m]

fprintf('wavelength: %.1f m\n',c/f);
r=c*(t(2)-t(1))/(x(2)-x(1));
fprintf('Courant number: %.4f\n',r);
if r>1
    warning('The CFL condition for numerical stability is not satisfied!');
end

%% gerjesztes
stim=sin(2*pi*f*t(1:floor(1/f/(t(2)-t(1)))));
y=zeros(length(x),length(t));
y(1:2,1:length(stim))=[stim ; stim];

%% vegesdifferencia-modszer
for it=3:length(t)
    for ix=2:length(x)-1
        y(ix,it)=r^2*(y(ix-1,it-1)-2*y(ix,it-1)+y(ix+1,it-1))-y(ix,it-2)+2*y(ix,it-1);
    end
end

%% abrazolas
for it=1:length(t)
    figure(1);
    plot(x,y(:,it));
    axis([minmax(x) min(min(y)) max(max(y))]);
    xlabel('x [m]');
    ylabel('y [m]');
    title(sprintf('t=%.2f s',t(it)));
    pause(0.01);
end