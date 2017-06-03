function moire(varargin)


gui_State=struct('gui_Name',       mfilename, ...
                 'gui_Singleton',  1, ...
                 'gui_OpeningFcn', @OpeningFcn, ...
                 'gui_OutputFcn',  @OutputFcn, ...
                 'gui_LayoutFcn',  [] , ...
                 'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback=str2func(varargin{1});
end
gui_mainfcn(gui_State,varargin{:});


function OutputFcn(hObject,eventdata,handles)
function OpeningFcn(hObject,eventdata,handles,varargin)
    clc;
    [deg,dx,dy,N,rnd]=getControls(handles);
    handles=initData(handles,N,rnd);
    guidata(hObject,handles);
    drawPlot(handles.x,handles.y,deg,dx,dy);


function angleSlider_CreateFcn(hObject,eventdata,handles)
function angleSlider_Callback(hObject,eventdata,handles)
    [deg,dx,dy,N,rnd]=getControls(handles);
    set(handles.angleText,'String',sprintf('ANGLE: %.1f',deg));
    drawPlot(handles.x,handles.y,deg,dx,dy);


function xSlider_CreateFcn(hObject,eventdata,handles)
function xSlider_Callback(hObject,eventdata,handles)
    [deg,dx,dy,N,rnd]=getControls(handles);
    set(handles.xText,'String',sprintf('dX: %.1f',dx));
    drawPlot(handles.x,handles.y,deg,dx,dy);


function ySlider_CreateFcn(hObject,eventdata,handles)
function ySlider_Callback(hObject,eventdata,handles)
    [deg,dx,dy,N,rnd]=getControls(handles);
    set(handles.yText,'String',sprintf('dY: %.1f',dy));
    drawPlot(handles.x,handles.y,deg,dx,dy);


function NText_CreateFcn(hObject,eventdata,handles)
function NText_Callback(hObject,eventdata,handles)
    [deg,dx,dy,N,rnd]=getControls(handles);
    handles=initData(handles,N,rnd);
    guidata(hObject,handles);
    drawPlot(handles.x,handles.y,deg,dx,dy);


function rndCheckBox_Callback(hObject,eventdata,handles)
    [deg,dx,dy,N,rnd]=getControls(handles);
    handles=initData(handles,N,rnd);
    guidata(hObject,handles);
    drawPlot(handles.x,handles.y,deg,dx,dy);


function [deg,dx,dy,N,rnd]=getControls(handles)
    deg=get(handles.angleSlider,'Value');
    dx=get(handles.xSlider,'Value');
    dy=get(handles.ySlider,'Value');
    N=abs(round(str2double(get(handles.NText,'String'))));
    rnd=get(handles.rndCheckBox,'Value');
    

function h=initData(handles,N,rnd)
    if(rnd)
        handles.x=rand(N,1)-0.5;
        handles.y=rand(N,1)-0.5;
    else
        n=round(sqrt(N));
        N=n^2;
        handles.x=zeros(N,1);
        handles.y=zeros(N,1);
        for ii=0:N-1
            handles.x(ii+1)=1/n*mod(ii,n)-0.5;
            handles.y(ii+1)=1/n*floor(ii/n)-0.5;
        end
    end
    h=handles;

    
function drawPlot(x,y,deg,dx,dy)
    ang=deg*pi/180;
    dx=dx/10;
    dy=dy/10;
    xr=zeros(size(x));
    yr=zeros(size(y));
    for ii=1:length(x)
        xr(ii)=x(ii)*cos(ang)-y(ii)*sin(ang)+dx;
        yr(ii)=x(ii)*sin(ang)+y(ii)*cos(ang)+dy;
    end
    plot(x,y,'k.');
    hold on;
    plot(xr,yr,'k.');
    hold off;
    axis([-1 1 -1 1]*sqrt(2)/2);
    axis off;
