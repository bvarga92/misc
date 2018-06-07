clear all;
clc;

%% parameterek
maxIter=15000;
dt=0.002;
Nr=15;
Ntheta=15;
c=0.2;

%% kezdeti feltetel: a membran kezdeti alakja
z=zeros(Nr,Ntheta);
for ir=1:Nr-1
    for itheta=1:Ntheta
        z(ir,itheta)=cos(0.5*pi*(ir-1)/(Nr-1));
    end
end

%% PDE megoldasa vegesdifferencia-modszerrel
%      derekszogu koordinatarendszerben: (d^2/dt^2)z=c^2*((d^2/dx^2)+(d^2/dy^2))z
%      hengerkoordinatarendszerben:      (d^2/dt^2)z=c^2*((d^2/dr^2)+1/r*(d/dr)+1/r^2*(d^2/dtheta^2))z
%      Dirichlet-peremfeltetel: z(r=1,theta,t)=0
[theta,r]=meshgrid(linspace(0,2*pi,Ntheta),linspace(0,1,Nr));
[x,y]=pol2cart(theta,r);
dr=1/Nr;
dtheta=2*pi/Ntheta;
zprev=z;
for it=1:maxIter
    for ir=1:Nr-1
        for itheta=1:Ntheta
            if ir==1 % origoban specialisan kell szamolni a derivaltakat
                laplaceZ=2*(z(2,itheta)-z(1,itheta))/dr^2;
            elseif ir==Nr-1 % peremfeltetelt kell ervenyesiteni
                laplaceZ=(z(ir-1,itheta)-2*z(ir,itheta))/dr^2-z(ir,itheta)/(dr*(ir-1)*dr)+(z(ir,(itheta~=1)*(itheta-1)+(itheta==1)*Ntheta)-2*z(ir,itheta)+z(ir,(itheta~=Ntheta)*(itheta+1)+(itheta==Ntheta)*1))/(dtheta^2*((ir-1)*dr)^2);
            else % altalanos belso pont
                laplaceZ=(z(ir-1,itheta)-2*z(ir,itheta)+z(ir+1,itheta))/dr^2+(z(ir+1,itheta)-z(ir,itheta))/(dr*(ir-1)*dr)+(z(ir,(itheta~=1)*(itheta-1)+(itheta==1)*Ntheta)-2*z(ir,itheta)+z(ir,(itheta~=Ntheta)*(itheta+1)+(itheta==Ntheta)*1))/(dtheta^2*((ir-1)*dr)^2);
            end
            temp=z(ir,itheta);
            z(ir,itheta)=c^2*dt^2*laplaceZ+2*z(ir,itheta)-zprev(ir,itheta);
            zprev(ir,itheta)=temp;
        end
    end
    if mod(it-1,10)==0 || it==maxIter
        figure(1);
        surf(x,y,z,'FaceAlpha',0.5);
        axis([-1 1 -1 1 -1 1]);
        xlabel('x');
        ylabel('y');
        zlabel('z(x,y,t)');
        drawnow;
    end
end