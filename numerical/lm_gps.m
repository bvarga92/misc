clear all;
clc;

%% parameterek
use_fsolve=false;       % fsolve-val vagy sajat eljarassal oldjuk meg?
sats=[                  % muholdak pozicioja
   15600   7540  20140;
   18760   2750  18610;
   17610  14630  13480;
   19170    610  18390;
%    17800   6400  18660;
%    17500   7590  18490
];
t=[                     % kesleltetesek
   0.07074;
   0.07220;
   0.07690;
   0.07242;
%    0.07320;
%    0.07350
];
Re=6371;                % a Fold sugara
c=3e5;                  % fenysebesseg
res=@(xyzd) sqrt((sats(:,1)-xyzd(1)).^2+(sats(:,2)-xyzd(2)).^2+(sats(:,3)-xyzd(3)).^2)-c*(t-xyzd(4));

%% megoldas
if use_fsolve
    xyzd=fsolve(res,[0 0 0 0],optimset('Display','none'));
else
    % parameterek
    maxIter=100;                      % legfeljebb ennyi iteracio futhat le
    x=[0 ; 0 ; 0 ; 0];                % kezdeti becsles
    fTol=[1e-7 ; 1e-7 ; 1e-7 ; 1e-7]; % ha a fuggvenyertek ez ala csokken, leallunk
    xTol=[1e-6 ; 1e-6 ; 1e-6 ; 1e-6]; % ha ennel kisebbet modositottunk, leallunk
    % Levenberg-Marquardt-eljaras
    r=res(x);
    S=sum(r.^2);
    J=zeros(length(r),length(x));
    for ii=1:length(x)
        J(:,ii)=(res([x(1:ii-1) ; x(ii)+0.25*xTol(ii) ;  x(ii+1:end)])-r)/(0.25*xTol(ii));
    end
    A=J'*J;
    v=J'*r;
    lambda=1;
    lambda_c=0.75;
    d=xTol;
    ii=1;
    while ii<=maxIter && any(abs(d)>=xTol) && any(abs(r)>=fTol(:))
        d=pinv(A+lambda*eye(length(x)))*v;
        xd=x-d;
        rd=res(xd);
        Sd=sum(rd.^2);
        dS=d'*(2*v-A*d);    
        R=(S-Sd)/dS;
        if R>0.75
            lambda=(lambda>=2*lambda_c)*lambda/2;
        elseif R<0.25
            if lambda==0
                lambda_c=1/max(abs(diag(inv(A))));
                lambda=lambda_c/2;
            end
            lambda=min(max((Sd-S)/(d'*v)+2,2),10)*lambda;
        end
        if Sd<S
            S=Sd;
            x=xd;
            r=rd;
            J=zeros(length(r),length(x));
            for ii=1:length(x)
                J(:,ii)=(res([x(1:ii-1) ; x(ii)+0.25*xTol(ii) ; x(ii+1:end)])-r)/(0.25*xTol(ii));
            end
            A=J'*J;
            v=J'*r;
        end
        ii=ii+1;
    end
    xyzd=x;
end
error=res(xyzd)
x=xyzd(1)
y=xyzd(2)
z=xyzd(3)
d=xyzd(4)

%% abrazolas
figure(1);
[sx,sy,sz]=sphere(30);
surf(sx*Re,sy*Re,sz*Re,'EdgeColor',[0.8 0.8 0.8],'FaceColor',[0 0.3 0.7],'FaceAlpha',0.5);
hold on;
scatter3(sats(:,1),sats(:,2),sats(:,3),'k','fill');
scatter3(x,y,z,'k','fill');
for ii=1:size(sats,1)
    plot3([x sats(ii,1)],[y sats(ii,2)],[z sats(ii,3)],'r');
end
hold off;
axis square;
xlabel('x [km]');
ylabel('y [km]');
zlabel('z [km]');