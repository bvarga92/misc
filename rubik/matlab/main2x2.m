clear all;
clc;

%% KEZDOALLAS
start(:,:,1)=['W' 'W';'W' 'W']; % felso
start(:,:,2)=['G' 'G';'G' 'G']; % elso
start(:,:,3)=['O' 'O';'O' 'O']; % bal
start(:,:,4)=['R' 'R';'R' 'R']; % jobb
start(:,:,5)=['Y' 'Y';'Y' 'Y']; % also
start(:,:,6)=['B' 'B';'B' 'B']; % hatso

%% KEVERES (ures vektor eseten veletlen keveres)
N=20; % egy veletlen keveres hossza
scrmbl=[];
% scrmbl='dBFFDfblUL';

%% KEZDOALLAS KIRAJZOLASA
draw(start,1);
title('Eredeti kocka');

%% KEVERES
if isempty(scrmbl)
    opts='LlRrFfBbUuDdXxYyZz';
    scrmbl=opts(ceil(length(opts)*rand(1,N)));
end
fprintf('Keveres %d lepesben:\n%s\n\n',length(scrmbl),scrmbl);
colors=move(scrmbl,start);
draw(colors,2);
title('Kevert kocka');

%% KIRAKAS
solution=solve2x2(colors);
fprintf('Megoldas %d lepesben:\n%s\n\n',length(solution),solution);
colors=move(solution,colors);
draw(colors,3);
title('Kirakott kocka');

%% STATISZTIKA
N=20;   % a veletlen keveresek hossza
M=1000; % kiserletszam
stat=zeros(1,M);
opts='LlRrFfBbUuDdXxYyZz';
for ii=1:M
    stat(ii)=length(solve2x2(move(opts(ceil(length(opts)*rand(1,N))),start)));
end
fprintf('Atlagos lepesszam %.1f, szoras %.1f.\n\n',mean(stat),std(stat));
figure(4);
hist(stat,50);
title('Lepesszamok hisztogramja');
