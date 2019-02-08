clear all;
clc;

%% geometria
R1=[3 4 0 98.984e-3 98.984e-3 0 0 0 55.118e-3 55.118e-3]';
C1=[1 4e-3 4e-3 1.6e-3 0 0 0 0 0 0]';
C2=[1 4e-3 51.118e-3 1.6e-3 0 0 0 0 0 0]';
C3=[1 94.984e-3 51.118e-3 1.6e-3 0 0 0 0 0 0]';
C4=[1 94.984e-3 4e-3 1.6e-3 0 0 0 0 0 0]';
geom=decsg([R1 C1 C2 C3 C4], 'R1-C1-C2-C3-C4', ['R1';'C1';'C2';'C3';'C4']');
%pdegplot(geom,'edgeLabels','on'); xlim([-0.01 0.11]); axis equal;

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
        case {1,2,3,4} % kulso perem: homogen Neumann (szabad perem)
            qmatrix(k)=0;
            gmatrix(k)=0;
        case {5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20} % furatok: homogen Dirichlet (mozdulatlan)
            hmatrix(k)=1;
            hmatrix(k+ne)=1;
            rmatrix(k)=0;
            rmatrix(k+ne)=0;
    end
end
boundaryfunc=@(p,e,u,time) deal(qmatrix,gmatrix,hmatrix,rmatrix);

%% megoldas
umax=0.01;
sweeprange=[0 5e4];
[u,lambda]=pdeeig(boundaryfunc, p, e, t, 1, 0, 1, sweeprange);
u=u/max(max(abs(u)))*umax;

%% abrazolas
figure(1);
for ii=1:length(lambda)
    trisurf(t(1:3,:)',p(1,:),p(2,:),u(:,ii));
    caxis([min(min(u)) max(max(u))]);
    shading interp;
    axis equal off;
    zlim([min(min(u)) max(max(u))])
    title(sprintf('Eigenmode %d/%d',ii,length(lambda)));
    pause(0.5);
end