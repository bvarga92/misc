clear all;
clc;

%% parameterek
a=0.5;        % hodiffuzivitas
maxIter=1000; % iteracioszam
dt=0.1;       % ido felbontasa
Nx=50;        % pontok szama x iranyban
Ny=50;        % pontok szama y iranyban
dx=1;         % hely felbontasa
plot3D=true;  % 3D-ben abrazoljunk?

r=a*dt/dx^2;
if r>0.5
    warning('numerical instability!');
end

%% kezdeti feltetel: a kezdeti T(x,y,0) homersekleteloszlas adott
x=(0:Nx-1)*dx;
y=(0:Ny-1)*dx;
T=zeros(length(y),length(x));
for iy=2:Ny-1
    for ix=2:Nx-1
        T(iy,ix)=100*exp((-(x(ix)-x(end)/2).^2-(y(iy)-x(end)/2).^2)/40);
    end
end
maxT=max(max(T));

%% vegesdifferencia-modszer
%     PDE: dT/dt=a*(d^2/dx^2+d^2/dy^2)T
%     Dirichlet-peremfeltetelek: T(0,y,t)=T(L,y,t)=T(x,0,t)=T(x,L,t)=0
for it=1:maxIter
    for iy=2:Ny-1
        for ix=2:Nx-1
            T(iy,ix)=T(iy,ix)+r*(T(iy,ix+1)+T(iy,ix-1)+T(iy-1,ix)+T(iy+1,ix)-4*T(iy,ix));
        end
    end
    if mod(it-1,10)==0 || it==maxIter
        if plot3D
            figure(1);
            surf(x,y,T);
            axis([x(1) x(end) y(1) y(end) 0 maxT]);
            caxis([0 maxT]);
            xlabel('x');
            ylabel('y');
            zlabel('T');
            title(sprintf('t=%.2f',(it-1)*dt));
            drawnow;
        else
            figure(1);
            imagesc(x,y,T);
            caxis([0 maxT]);
            colorbar;
            xlabel('x');
            ylabel('y');
            set(gca,'YDir','normal');
            title(sprintf('T(x,y,t=%.2f)',(it-1)*dt));
            drawnow;
        end
    end
end