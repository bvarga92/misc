clear all;
clc;

sats=[
   15600   7540  20140;
   18760   2750  18610;
   17610  14630  13480;
   19170    610  18390;
   %17800   6400  18660;
   %17500   7590  18490
];
t=[
   0.07074;
   0.07220;
   0.07690;
   0.07242;
   %0.07320;
   %0.07350
];
Re=6371;
c=3e5;

res=@(xyzd) sqrt((sats(:,1)-xyzd(1)).^2+(sats(:,2)-xyzd(2)).^2+(sats(:,3)-xyzd(3)).^2)-c*(t-xyzd(4));
xyzd=fsolve(res,[0 0 0 0],optimset('Display','none'));
error=res(xyzd)
x=xyzd(1)
y=xyzd(2)
z=xyzd(3)
d=xyzd(4)

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