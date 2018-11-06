clear all;
clc;

T_bottom=9.9;
T_top=9.2;
T_c=10;
eta=0.1;
epsilon=0.5;
sigma=0.05;
alpha=10;
Nx=100;
Ny=100;
Nt=1000;

T=ones(Nx,Ny)*T_top+0.2*rand(Nx,Ny);
T(:,1)=T_bottom;
T1=T;
T2=T;

for it=1:Nt
    for iy=2:Ny
        if iy==Ny, T_up=T_top; else T_up=T(:,iy+1); end
        T1(:,iy)=T(:,iy)+epsilon/4*([T(Nx,iy) ; T(1:Nx-1,iy)]+[T(2:Nx,iy) ; T(1,iy)]+T(:,iy-1)+T_up-4*T(:,iy));
    end
    T2(:,2:Ny)=T1(:,2:Ny).*(1-sigma/2*(tanh(alpha*([T1(:,3:Ny) T_top*ones(Nx,1)]-T_c))-tanh(alpha*(T1(:,1:Ny-1)-T_c))));
    T1=T2;
    for iy=2:Ny-1
        T1(2:Nx-1,iy)=T1(2:Nx-1,iy)+eta*(T2(1:Nx-2,iy)<T_c & T(1:Nx-2,iy)>T_c);
        T1(2:Nx-1,iy)=T1(2:Nx-1,iy)+eta*(T2(3:Nx,iy)<T_c & T(3:Nx,iy)>T_c);
        T1(2:Nx-1,iy)=T1(2:Nx-1,iy)+eta*(T2(2:Nx-1,iy-1)<T_c & T(2:Nx-1,iy-1)>T_c);
        T1(2:Nx-1,iy)=T1(2:Nx-1,iy)+eta*(T2(2:Nx-1,iy+1)<T_c & T(2:Nx-1,iy+1)>T_c);
        T1(2:Nx-1,iy)=T1(2:Nx-1,iy)-eta*(T2(1:Nx-2,iy)>T_c & T(1:Nx-2,iy)<T_c);
        T1(2:Nx-1,iy)=T1(2:Nx-1,iy)-eta*(T2(3:Nx,iy)>T_c & T(3:Nx,iy)<T_c);
        T1(2:Nx-1,iy)=T1(2:Nx-1,iy)-eta*(T2(2:Nx-1,iy-1)>T_c & T(2:Nx-1,iy-1)<T_c);
        T1(2:Nx-1,iy)=T1(2:Nx-1,iy)-eta*(T2(2:Nx-1,iy+1)>T_c & T(2:Nx-1,iy+1)<T_c);
    end
    T=T1;
    figure(1);
    imagesc(T',[9 12]);
    set(gca,'YDir','normal');
    colorbar;
    drawnow;
end
