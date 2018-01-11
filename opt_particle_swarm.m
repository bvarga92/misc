clear all;
clc;

%% PARAMETEREK
x=1:0.01:5;
f=@(x) 3*log(x)-sin(x.^2); % ennek keressuk a maximumat
L=50;          % iteraciok szama
N=200;         % reszecskek szama
guess=2;       % kezdeti becsles
omega=0.5;     % minden reszecske ilyen sullyal veszi figyelembe a jelenlegi sebesseget
phi_local=0.4; % minden reszecske ilyen sullyal veszi figyelembe a sajat legjobb becsleset
phi_swarm=1;   % minden reszecske ilyen sullyal veszi figyelembe a raj legjobb becsleset

%% PARTICLE SWARM
position=x(1)+(x(end)-x(1))*rand(1,N);
localBest=position;
swarmBest=guess;
[m,mi]=max(f(localBest));
if m>f(swarmBest); swarmBest=localBest(mi); end
velocity=-(x(end)-x(1))+2*(x(end)-x(1))*rand(1,N);
for ii=1:L
    plot(x,f(x),position,f(position),'ro',[swarmBest swarmBest],ylim,'r--');
    title(sprintf('Iteracio: %d',ii));
    pause(0.1);
    velocity=omega*velocity+phi_local*rand(1,N).*(localBest-position)+phi_swarm*rand(1,N).*(swarmBest-position);
    position=position+velocity;        
    position(position>x(end))=x(end);
    position(position<x(1))=x(1);
    better=find(f(position)>f(localBest));
    better(f(position(better))<=f(localBest(better)))=[];
    localBest(better)=position(better);
    better(f(localBest(better))<=f(swarmBest))=[];
    m=max(localBest(better));
    if m>swarmBest; swarmBest=m; end;
end
fprintf('Megtalalt maximumhely: %f\n\n',swarmBest);
