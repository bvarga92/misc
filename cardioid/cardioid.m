function cardioid(varargin)
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
    handles.output=hObject;
    guidata(hObject,handles);
    P=ceil(get(handles.sliderP,'Value'));
    N=ceil(get(handles.sliderN,'Value'));
    set(handles.textP,'String',sprintf('%d',P));
    set(handles.textN,'String',sprintf('%d',N));
    drawPlot(P,N);


function sliderP_CreateFcn(hObject,eventdata,handles)
function sliderP_Callback(hObject,eventdata,handles)
    P=ceil(get(handles.sliderP,'Value'));
    N=ceil(get(handles.sliderN,'Value'));
    set(handles.textP,'String',sprintf('%d',P));
    set(handles.textN,'String',sprintf('%d',N));
    drawPlot(P,N);


function sliderN_CreateFcn(hObject,eventdata,handles)
function sliderN_Callback(hObject,eventdata,handles)
    P=ceil(get(handles.sliderP,'Value'));
    N=ceil(get(handles.sliderN,'Value'));
    set(handles.textP,'String',sprintf('%d',P));
    set(handles.textN,'String',sprintf('%d',N));
    drawPlot(P,N);


function drawPlot(P,N)
    points=exp(1j*2*pi/P*(0:P-1));
    plot(points,'.');
    axis equal off;
    hold on;
    for ii=2:P
        plot([points(ii) points(mod((ii-1)*N,P)+1)]);
    end
    hold off;
