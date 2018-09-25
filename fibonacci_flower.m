clear all;
clc;

w=450;
h=450;
radius=5;
constantRadius=true;
switch 0
    case 0, alpha=2*pi*(1+sqrt(5))/2;
    case 1, alpha=2*pi*(21/34);
    case 2, alpha=2*pi*(34/55);
end

figure(1);
clf;
axis square off;
for ii=0:900
    if constantRadius
        x=w/2+sqrt(ii)*radius*cos(ii*alpha);
        y=h/2+sqrt(ii)*radius*sin(ii*alpha);
        r=radius;
    else
        x=w/2+ii*radius/22*cos(ii*alpha);
        y=h/2+ii*radius/22*sin(ii*alpha);
        r=radius*ii/500;
    end
    if r<=0
        continue;
    end
    rectangle('Position',[x-r y-r 2*r 2*r],'Curvature',[1 1],'FaceColor','yellow','EdgeColor','black');
end