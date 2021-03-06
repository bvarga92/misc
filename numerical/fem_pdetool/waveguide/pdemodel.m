function pdemodel
[pde_fig,ax]=pdeinit;
pdetool('appl_cb',1);
set(ax,'DataAspectRatio',[1 1 1]);
set(ax,'PlotBoxAspectRatio',[998.40000000000009 607.5 3796.875]);
set(ax,'XLimMode','auto');
set(ax,'YLim',[-0.080000000000000002 0.080000000000000002]);
set(ax,'XTickMode','auto');
set(ax,'YTickMode','auto');
pdetool('gridon','on');

% Geometry description:
pdepoly([ 0,...
 0.10000000000000001,...
 0.10000000000000001,...
 0.1158,...
 0.1158,...
 0.11,...
 0.11,...
 0.1158,...
 0.1158,...
 0.10000000000000001,...
 0.10000000000000001,...
 0,...
],...
[ 0.0079000000000000008,...
 0.0079000000000000008,...
 0.059999999999999998,...
 0.059999999999999998,...
 0.0030000000000000001,...
 0.0030000000000000001,...
 -0.0030000000000000001,...
 -0.0030000000000000001,...
 -0.059999999999999998,...
 -0.059999999999999998,...
 -0.0079000000000000008,...
 -0.0079000000000000008,...
],...
 'P1');
pdeellip(0.1158,0.059999999999999998,0.015800000000000002,0.015800000000000002,...
0,'E1');
pderect([0.1158 0.21579999999999999 0.075800000000000006 0.059999999999999998],'R1');
pdepoly([ 0.080000000000000002,...
 0.1158,...
 0.1158,...
 0.14000000000000001,...
 0.14000000000000001,...
 0.080000000000000002,...
],...
[ 0.059999999999999998,...
 0.059999999999999998,...
 0.075800000000000006,...
 0.075800000000000006,...
 0.040000000000000001,...
 0.040000000000000001,...
],...
 'P2');
pderect([0.16 0.16400000000000001 0.064 0.059999999999999998],'R2');
set(findobj(get(pde_fig,'Children'),'Tag','PDEEval'),'String','P1+(R1-R2)+(E1-P2)')

% Boundary conditions:
pdetool('changemode',0)
pdesetbd(31,...
'dir',...
1,...
'1',...
'0')
pdesetbd(28,...
'dir',...
1,...
'1',...
'0')
pdesetbd(27,...
'dir',...
1,...
'1',...
'0')
pdesetbd(26,...
'dir',...
1,...
'1',...
'0')
pdesetbd(25,...
'dir',...
1,...
'1',...
'0')
pdesetbd(24,...
'dir',...
1,...
'1',...
'0')
pdesetbd(23,...
'dir',...
1,...
'1',...
'0')
pdesetbd(22,...
'dir',...
1,...
'1',...
'0')
pdesetbd(21,...
'dir',...
1,...
'1',...
'0')
pdesetbd(18,...
'dir',...
1,...
'1',...
'0')
pdesetbd(16,...
'dir',...
1,...
'1',...
'0')
pdesetbd(15,...
'dir',...
1,...
'1',...
'0')
pdesetbd(13,...
'dir',...
1,...
'1',...
'0')
pdesetbd(12,...
'dir',...
1,...
'1',...
'0')
pdesetbd(11,...
'dir',...
1,...
'1',...
'0')
pdesetbd(10,...
'dir',...
1,...
'1',...
'0')
pdesetbd(9,...
'dir',...
1,...
'1',...
'0')
pdesetbd(8,...
'neu',...
1,...
'j*sqrt((2*pi*15e9/3e8)^2-(pi/0.0158)^2)',...
'0')
pdesetbd(7,...
'neu',...
1,...
'j*sqrt((2*pi*15e9/3e8)^2-(pi/0.0158)^2)',...
'2*j*sqrt((2*pi*15e9/3e8)^2-(pi/0.0158)^2)*cos(pi*y/0.0158)')
pdesetbd(6,...
'dir',...
1,...
'1',...
'0')
pdesetbd(5,...
'neu',...
1,...
'j*sqrt((2*pi*15e9/3e8)^2-(pi/0.0158)^2)',...
'0')
pdesetbd(4,...
'dir',...
1,...
'1',...
'0')
pdesetbd(3,...
'dir',...
1,...
'1',...
'0')
pdesetbd(2,...
'dir',...
1,...
'1',...
'0')
pdesetbd(1,...
'dir',...
1,...
'1',...
'0')

% Mesh generation:
setappdata(pde_fig,'Hgrad',1.3);
setappdata(pde_fig,'refinemethod','regular');
setappdata(pde_fig,'jiggle',char('on','mean',''));
setappdata(pde_fig,'MesherVersion','preR2013a');
pdetool('initmesh')
pdetool('refine')
pdetool('refine')
pdetool('refine')

% PDE coefficients:
pdeseteq(1,...
'1.0',...
'-(2*pi*15e9/3e8)^2',...
'0',...
'1.0',...
'0:10',...
'0.0',...
'0.0',...
'[0 100]')
setappdata(pde_fig,'currparam',...
['1.0               ';...
'-(2*pi*15e9/3e8)^2';...
'0                 ';...
'1.0               '])

% Solve parameters:
setappdata(pde_fig,'solveparam',...
char('0','20832','10','pdeadworst',...
'0.5','longest','0','1e-4','','fixed','inf'))

% Plotflags and user data strings:
setappdata(pde_fig,'plotflags',[1 1 1 1 3 1 7 1 0 0 0 1 1 1 0 0 0 1]);
setappdata(pde_fig,'colstring','');
setappdata(pde_fig,'arrowstring','[uy; -ux]');
setappdata(pde_fig,'deformstring','');
setappdata(pde_fig,'heightstring','');

% Solve PDE:
pdetool('solve')
