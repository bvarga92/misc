% Ugyanez programozottan, a GUI hasznalata nelkul.

clear all;
clc;

%% geometria
R1=[3 4 0 0.5 0.5 0 0 0 0.5 0.5]';
R2=[3 4 0.1 0.25 0.25 0.1 0.15 0.15 0.35 0.35]';
geom=decsg([R1,R2], 'R1-R2', ['R1';'R2']');
%pdegplot(geom,'edgeLabels','on'); xlim([-0.1 0.6]); axis equal;

%% halogeneralas
[p,e,t]=initmesh(geom);
[p,e,t]=refinemesh(geom,p,e,t);
[p,e,t]=refinemesh(geom,p,e,t);
p=jigglemesh(p,e,t);

%% peremfeltetelek
ne=size(e,2);
qmatrix=zeros(1,ne);
gmatrix=zeros(1,ne);
hmatrix=zeros(1,2*ne);
rmatrix=zeros(1,2*ne);
for k=1:ne
    switch e(5,k)
        case {1,2,6,7} % kulso perem: Dirichlet, 25 fok
            hmatrix(k)=1;
            hmatrix(k+ne)=1;
            rmatrix(k)=298.15;
            rmatrix(k+ne)=298.15;
        case {3,4,5,8} % belso perem: Dirichlet, 100 fok
            hmatrix(k)=1;
            hmatrix(k+ne)=1;
            rmatrix(k)=373.15;
            rmatrix(k+ne)=373.15;
    end
end
boundaryfunc=@(p,e,u,time) deal(qmatrix,gmatrix,hmatrix,rmatrix);

%% megoldas
time=0:200;
u=parabolic(298.15, time, boundaryfunc, p, e, t, 1e-4, 0, 0, 1);

%% animacio
hw=newplot;
h=get(hw,'Parent');
set(h,'Renderer','zbuffer','Position',[400 100 800 800]);
F=moviein(size(u,2),h);
for ii=1:size(u,2)
    pdeplot(p,e,t,'xydata',u(:,ii),'mesh','off','colorbar','on');
    colormap(jet);
    caxis([min(min(u)) max(max(u))]);
    axis equal off;
    F(:,ii)=getframe;
end
movie(hw,F,30);