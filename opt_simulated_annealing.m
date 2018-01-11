clear all;
clc;

%% PARAMETEREK
f=@(x) 2*(sin(x(:,1))+cos(x(:,2))); % ennek keressuk a maximumat
x1=-3:0.1:5;
x2=-4:0.1:4;

%% SZIMULALT LEHUTES
g=@(x) -f(x); % ennek keressuk a minimumat
[x,gval,exitFlag,output]=simulannealbnd(g,[1 0],[min(x1) min(x2)],[max(x1) max(x2)]);
output
fval=-gval;

%% ABRAZOLAS
[X,Y]=meshgrid(x1,x2);
F=zeros(size(X));
for ii=1:length(x1)
    for jj=1:length(x2)
        F(ii,jj)=f([X(ii,jj) Y(ii,jj)]);
    end
end
surf(X,Y,F);
hold on;
plot3(x(1),x(2),fval,'mo','MarkerSize',20); %nagy lila karika jeloli a maximumot
hold off;
xlabel('x1');
ylabel('x2');
zlabel('f(x1,x2)');
