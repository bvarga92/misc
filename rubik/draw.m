% Kirajzolja a kockat.
    % colors: a kocka szinmatrixa
    % fig: a hasznalni kivant abra sorszama

function draw(colors,fig)
    n=size(colors,1);
    if size(colors,2)~=n || size(colors,3)~=6
        disp('Color matrix dimension mismatch.');
        return;
    end
    colors2=cell([n n 6]);
    colors2((colors=='O'))={[1 0.5 0]};
    colors2((colors=='G'))={[0 1 0]};
    colors2((colors=='R'))={[1 0 0]};
    colors2((colors=='B'))={[0 0 1]};
    colors2((colors=='Y'))={[1 1 0]};
    colors2((colors=='W'))={[1 1 1]};
    figure(fig);
    clf(fig);
    for ii=0:n-1
        for jj=0:n-1
            rectangle('Position',[ 0+ii    0+jj 1 1],'FaceColor',cell2mat(colors2(n-jj,ii+1,1))); % felso
            rectangle('Position',[ 0+ii   -n+jj 1 1],'FaceColor',cell2mat(colors2(n-jj,ii+1,2))); % elso
            rectangle('Position',[ 0+ii -2*n+jj 1 1],'FaceColor',cell2mat(colors2(n-jj,ii+1,5))); % also
            rectangle('Position',[ 0+ii -3*n+jj 1 1],'FaceColor',cell2mat(colors2(n-jj,ii+1,6))); % hatso
            rectangle('Position',[-n+ii   -n+jj 1 1],'FaceColor',cell2mat(colors2(n-jj,ii+1,3))); % bal
            rectangle('Position',[ n+ii   -n+jj 1 1],'FaceColor',cell2mat(colors2(n-jj,ii+1,4))); % jobb
        end
    end
    axis equal off;
    axis([-n-1 2*n+1 -3*n-1 n+1]);
