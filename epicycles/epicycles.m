clear all;
clc;

%% parameterek
img='input5.bmp'; % osszefuggo fekete objektumot abrazolo, 1 bpp szinmelysegu kep
N=60;             % ennyi Fourier-egyutthatoval kozelitjuk a gorbet
P=100;            % ennyi pontbol allitjuk ossze a gorbet
saveAVI=false;    % mentsuk el videokent az animaciot?

%% komplex ponthalmaz generalasa
I=imread(img);
found=false;
for ii=2:size(I,1)-1
    for jj=2:size(I,2)-1
        if I(ii,jj)==0 & (I(ii+1,jj)==1 | I(ii-1,jj)==1 | I(ii,jj+1)==1 | I(ii,jj-1)==1)
            found=true;
            break;
        end
    end
    if found; break; end
end
f=bwtraceboundary(~I,[ii jj],'W')';
f=f(2,:)-1j*f(1,:);
f=f-mean(f);
f=f/max(abs(f));
figure(1);
plot(f);
axis equal;

%% Fourier-transzformalt eloallitasa es frekvenciak szerint rendezese
F=fft(f)/length(f);
idx=[1];  % [1  2  L-1  3  L-2  ...]
freq=[0]; % [0  1  -1   2  -2   ...]
for ii=1:N-1
    if mod(ii,2)==0
        idx=[idx length(F)-ii/2+1];
        freq=[freq -ii/2];
    else
        idx=[idx (ii-1)/2+2];
        freq=[freq (ii-1)/2+1];
    end
end
F=F(idx);

%% koordinatahatarok megkeresese, bejart gorbe eloallitasa
xmin=min(real(f));
xmax=max(real(f));
ymin=min(imag(f));
ymax=max(imag(f));
curve=zeros(1,P);
for ii=1:P
    for jj=2:N
        c=sum(F(1:jj-1));
        r=abs(F(jj));
        if xmin>real(c)-r; xmin=real(c)-r; end
        if xmax<real(c)+r; xmax=real(c)+r; end
        if ymin>imag(c)-r; ymin=imag(c)-r; end
        if ymax<imag(c)+r; ymax=imag(c)+r; end
    end
    curve(ii)=sum(F);
    if ii<P; F=F.*exp(-1j*freq*2*pi/(P-1)); end
end
figure(1);
hold on;
plot(curve,'r');
hold off;

%% animacio
figure(2);
clf;
set(gcf,'color','white','units','normalized','outerposition',[0 0 1 1]);
hw=newplot;
h=get(hw,'Parent');
set(h,'Renderer','zbuffer');
mov=moviein(P,h);
for ii=1:P
    plot(real(curve(1:ii)),imag(curve(1:ii)),'r','LineWidth',3);
    axis equal off;
    axis([xmin xmax ymin ymax]);
    hold on;
    for jj=2:N
        c=sum(F(1:jj-1));
        r=abs(F(jj));
        plot(real(c),imag(c),'k.');
        rectangle('Position',[real(c)-r imag(c)-r 2*r 2*r],'Curvature',[1 1],'EdgeColor','k');
        plot([real(c) real(c)+real(F(jj))],[imag(c) imag(c)+imag(F(jj))],'k');
    end
    plot(real(sum(F)),imag(sum(F)),'r.','MarkerSize',25);
    hold off;
    F=F.*exp(-1j*freq*2*pi/(P-1));
    mov(:,ii)=getframe;
end
if saveAVI
    movie2avi(mov,'output.avi','quality',100,'compression','none');
end
movie(hw,mov,10);