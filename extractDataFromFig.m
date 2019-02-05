function [x,y,z]=extractDataFromFig(fileName)
    f=open(fileName);
    ax=get(gca,'Children');
    x=get(ax,'XData');
    y=get(ax,'YData');
    z=get(ax,'ZData');
    close(f);
