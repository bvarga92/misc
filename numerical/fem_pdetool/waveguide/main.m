% TE01 modus terjedese negyszog keresztmetszetu csotapvonalban, 15 GHz-en.

% Megnyilik a PDE Toolbox, a megoldas automatikusan elkeszul. Ezutan
% exportaljuk a halot (Mesh --> Export Mesh) a p, e, t valtozokba, a
% megoldast pedig (Solve --> Export Solution) az u valtozoba! A program
% gombnyomasra lep tovabb.

clear all;
clc;

pdemodel;
pause;

hw=newplot;
h=get(hw,'Parent');
set(h,'Renderer','zbuffer','Position',[400 100 800 800]);
frames=45;
F=moviein(frames,h);
for ii=1:frames
    E=real(u*exp(j*2*pi/frames*ii));
    pdeplot(p,e,t,'xydata',E,'colorbar','off','mesh','off');
    colormap(jet);
    caxis([-max(abs(u)) max(abs(u))]);
    axis equal off;
    title('TE_{01} mode at 15 GHz');
    F(:,ii)=getframe;
end
movie(hw,F,30);
