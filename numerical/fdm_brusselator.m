clear all;
clc;

%% parameterek
maxIter=500;  % iteracioszam
dt=0.01;      % ido felbontasa
Nx=100;       % pontok szama x iranyban
Ny=100;       % pontok szama y iranyban
dx=1;         % hely felbontasa
Du=5;         % u diffuzios egyutthatoja
Dv=20;        % v diffuzios egyutthatoja
A=4.5;        % egyik reakciokinetikai parameter
B=7;          % masik reakciokinetikai parameter
u0=A;         % u kezdeti allapota (egyensuly: u0=A)
v0=B/A;       % v kezdeti allapota (egyensuly: v0=B)
dmax=0.05;    % a kezdeti allapotok veletlen perturbaciojanak amplitudoja

%% PDE megoldasa vegesdifferencia-modszerrel
%      du/dt=Du*((d^2/dx^2)+(d^2/dy^2))u+A-(B+1)*u+v*u^2
%      dv/dt=Dv*((d^2/dx^2)+(d^2/dy^2))v+B*u-v*u^2
%      periodikus peremfeltetel
u=u0+dmax*(2*rand(Ny,Nx)-1);
v=v0+dmax*(2*rand(Ny,Nx)-1);
for it=1:maxIter
    for iy=1:Ny
        for ix=1:Nx
            laplaceU=( u(iy,(ix~=Nx)*(ix+1)+(ix==Nx)*1) + u(iy,(ix~=1)*(ix-1)+(ix==1)*Nx) + u((iy~=1)*(iy-1)+(iy==1)*Ny,ix) + u((iy~=Ny)*(iy+1)+(iy==Ny)*1,ix) - 4*u(iy,ix) )/dx^2;
            laplaceV=( v(iy,(ix~=Nx)*(ix+1)+(ix==Nx)*1) + v(iy,(ix~=1)*(ix-1)+(ix==1)*Nx) + v((iy~=1)*(iy-1)+(iy==1)*Ny,ix) + v((iy~=Ny)*(iy+1)+(iy==Ny)*1,ix) - 4*v(iy,ix) )/dx^2;
            u(iy,ix)=u(iy,ix)+dt*(Du*laplaceU+A-(B+1)*u(iy,ix)+v(iy,ix)*u(iy,ix)^2);
            v(iy,ix)=v(iy,ix)+dt*(Dv*laplaceV+B*u(iy,ix)-v(iy,ix)*u(iy,ix)^2);
        end
    end
    if mod(it-1,10)==0 || it==maxIter
        figure(1);
        subplot(121);
        imagesc(u);
        axis off;
        set(gca,'YDir','normal');
        title(sprintf('u(x,y,t=%.2f)',(it-1)*dt));
        subplot(122);
        imagesc(v);
        axis off;
        set(gca,'YDir','normal');
        title(sprintf('v(x,y,t=%.2f)',(it-1)*dt));
        drawnow;
    end
end