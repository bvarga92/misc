clear all;
clc;

%% parameterek
maxIter=15000;
dt=0.001;
Nx=30;
Ny=30;
c=0.5;

%% kezdeti feltetel: a membran kezdeti alakja ( z(x,y,t=0)=f(x,y) )
f=@(x,y) (sqrt(x.^2+y.^2)<=0.5).*(1+cos(2*pi*sqrt(x.^2+y.^2)));
[x,y]=meshgrid(linspace(-1,1,Nx),linspace(-1,1,Ny));
z=f(x,y);

%% PDE megoldasa vegesdifferencia-modszerrel
%      (d^2/dt^2)z=c^2*((d^2/dx^2)+(d^2/dy^2))z
%      Dirichlet-peremfeltetel: z(x=-1,y,t)=z(x=1,y,t)=z(x,y=-1,t)=z(x,y=1,t)=0
dx=2/Nx;
dy=2/Ny;
zprev=z;
for it=1:maxIter
    for ix=2:Nx-1
        for iy=2:Ny-1
            laplaceZ=(z(ix-1,iy)-2*z(ix,iy)+z(ix+1,iy))/dx^2+(z(ix,iy-1)-2*z(ix,iy)+z(ix,iy+1))/dy^2;
            temp=z(ix,iy);
            z(ix,iy)=c^2*dt^2*laplaceZ+2*z(ix,iy)-zprev(ix,iy);
            zprev(ix,iy)=temp;
        end
    end
    if mod(it-1,10)==0 || it==maxIter
        figure(1);
        surf(x,y,z,'FaceAlpha',0.5);
        axis([-1 1 -1 1 -2 2]);
        xlabel('x');
        ylabel('y');
        zlabel('z(x,y,t)');
        drawnow;
    end
end