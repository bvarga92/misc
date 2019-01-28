% Kor alaku membran rezgesenek szimulacioja.

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
F=moviein(size(u,2),h);
for ii=1:size(u,2)
    trisurf(t(1:3,:)',p(1,:),p(2,:),u(:,ii));
    axis([-1 1 -1 1 min(min(u)) max(max(u))]);
    caxis([min(min(u)) max(max(u))]);
    F(:,ii)=getframe;
end
movie(hw,F,30);
