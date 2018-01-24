% Vegrehajtja az atadott forgatasokat. 2x2x2 vagy 3x3x3 kockahoz.
    % seq: a forgatassorozat sztringkent
        % engedelyezett karakterek: F, f, B, b, U, u, D, d, L, l, R, r, X, x, Y, y, Z, z
        % nagybetu az oramutato jarasaval megegyezoen forgat, kisbetu ellenkezoleg
    % colors: a kocka szineit tartalmazo tomb
    % cout: a forgatassorozat vegrehajtasa utan kapott szinek

function cout=move(seq,colors)
    n=size(colors,1);
    if size(colors,2)~=n || size(colors,3)~=6
        disp('Color matrix dimension mismatch.');
        cout=[];
        return;
    end
    for ii=1:length(seq)
        switch seq(ii)
            case 'F'
                temp=colors(n,:,1)';
                colors(n,:,1)=rot90(colors(:,n,3),-1); % felso <-- bal
                colors(:,n,3)=colors(1,:,5)';          % bal <-- also
                colors(1,:,5)=rot90(colors(:,1,4),-1); % also <-- jobb
                colors(:,1,4)=temp;                    % jobb <-- felso
                colors(:,:,2)=rot90(colors(:,:,2),-1); % elso CW
            case 'f'
                temp=rot90(colors(n,:,1));
                colors(n,:,1)=colors(:,1,4)';          % felso <-- jobb
                colors(:,1,4)=rot90(colors(1,:,5));    % jobb <-- also
                colors(1,:,5)=colors(:,n,3)';          % also <-- bal
                colors(:,n,3)=temp;                    % bal <-- felso
                colors(:,:,2)=rot90(colors(:,:,2));    % elso CCW
            case 'B'
                temp=rot90(colors(1,:,1));
                colors(1,:,1)=colors(:,n,4)';          % felso <-- jobb
                colors(:,n,4)=rot90(colors(n,:,5));    % jobb <-- also
                colors(n,:,5)=colors(:,1,3)';          % also <-- bal
                colors(:,1,3)=temp;                    % bal <-- felso
                colors(:,:,6)=rot90(colors(:,:,6),-1); % hatso CW
            case 'b'
                temp=colors(1,:,1)';
                colors(1,:,1)=rot90(colors(:,1,3),-1); % felso <-- bal
                colors(:,1,3)=colors(n,:,5)';          % bal <-- also
                colors(n,:,5)=rot90(colors(:,n,4),-1); % also <-- jobb
                colors(:,n,4)=temp;                    % jobb <-- felso
                colors(:,:,6)=rot90(colors(:,:,6),1);  % hatso CCW
            case 'U'
                temp=colors(1,:,2);
                colors(1,:,2)=colors(1,:,4);           % elso <-- jobb
                colors(1,:,4)=rot90(colors(n,:,6));    % jobb <-- hatso
                colors(n,:,6)=rot90(colors(1,:,3));    % hatso <-- bal
                colors(1,:,3)=temp;                    % bal <-- elso
                colors(:,:,1)=rot90(colors(:,:,1),-1); % felso CW
            case 'u'
                temp=colors(1,:,2);
                colors(1,:,2)=colors(1,:,3);           % elso <-- bal
                colors(1,:,3)=rot90(colors(n,:,6));    % bal <-- hatso
                colors(n,:,6)=rot90(colors(1,:,4));    % hatso <-- jobb
                colors(1,:,4)=temp;                    % jobb <-- elso
                colors(:,:,1)=rot90(colors(:,:,1));    % felso CCW
            case 'D'
                temp=colors(n,:,2);
                colors(n,:,2)=colors(n,:,3);           % elso <-- bal
                colors(n,:,3)=rot90(colors(1,:,6));    % bal <-- hatso
                colors(1,:,6)=rot90(colors(n,:,4));    % hatso <-- jobb
                colors(n,:,4)=temp;                    % jobb <-- elso
                colors(:,:,5)=rot90(colors(:,:,5),-1); % also CW
            case 'd'
                temp=colors(n,:,2);
                colors(n,:,2)=colors(n,:,4);           % elso <-- jobb
                colors(n,:,4)=rot90(colors(1,:,6));    % jobb <-- hatso
                colors(1,:,6)=rot90(colors(n,:,3));    % hatso <-- bal
                colors(n,:,3)=temp;                    % bal <-- elso
                colors(:,:,5)=rot90(colors(:,:,5));    % also CCW
            case 'R'
                temp=colors(:,n,2);
                colors(:,n,2)=colors(:,n,5);           % elso <-- also
                colors(:,n,5)=colors(:,n,6);           % also <-- hatso
                colors(:,n,6)=colors(:,n,1);           % hatso <-- felso
                colors(:,n,1)=temp;                    % felso <-- elso
                colors(:,:,4)=rot90(colors(:,:,4),-1); % jobb CW
            case 'r'
                temp=colors(:,n,2);
                colors(:,n,2)=colors(:,n,1);           % elso <-- felso
                colors(:,n,1)=colors(:,n,6);           % felso <-- hatso
                colors(:,n,6)=colors(:,n,5);           % hatso <-- also
                colors(:,n,5)=temp;                    % also <-- elso
                colors(:,:,4)=rot90(colors(:,:,4));    % jobb CCW
            case 'L'
                temp=colors(:,1,2);
                colors(:,1,2)=colors(:,1,1);           % elso <-- felso
                colors(:,1,1)=colors(:,1,6);           % felso <-- hatso
                colors(:,1,6)=colors(:,1,5);           % hatso <-- also
                colors(:,1,5)=temp;                    % also <-- elso
                colors(:,:,3)=rot90(colors(:,:,3),-1); % bal CW
            case 'l'
                temp=colors(:,1,2);
                colors(:,1,2)=colors(:,1,5);           % elso <-- also
                colors(:,1,5)=colors(:,1,6);           % also <-- hatso
                colors(:,1,6)=colors(:,1,1);           % hatso <-- felso
                colors(:,1,1)=temp;                    % felso <-- elso
                colors(:,:,3)=rot90(colors(:,:,3));    % bal CCW
            case 'X'
                temp=colors(:,:,2);
                colors(:,:,2)=colors(:,:,5);           % elso <-- also
                colors(:,:,5)=colors(:,:,6);           % also <-- hatso
                colors(:,:,6)=colors(:,:,1);           % hatso <-- felso
                colors(:,:,1)=temp;                    % felso <-- elso
                colors(:,:,4)=rot90(colors(:,:,4),-1); % jobb CW
                colors(:,:,3)=rot90(colors(:,:,3));    % bal CCW
            case 'x'
                temp=colors(:,:,2);
                colors(:,:,2)=colors(:,:,1);           % elso <-- felso
                colors(:,:,1)=colors(:,:,6);           % felso <-- hatso
                colors(:,:,6)=colors(:,:,5);           % hatso <-- also
                colors(:,:,5)=temp;                    % also <-- elso
                colors(:,:,4)=rot90(colors(:,:,4));    % jobb CCW
                colors(:,:,3)=rot90(colors(:,:,3),-1); % bal CW
            case 'Y'
                temp=colors(:,:,2);
                colors(:,:,2)=colors(:,:,4);           % elso <-- jobb
                colors(:,:,4)=rot90(colors(:,:,6),2);  % jobb <-- hatso
                colors(:,:,6)=rot90(colors(:,:,3),2);  % hatso <-- bal
                colors(:,:,3)=temp;                    % bal <-- elso
                colors(:,:,1)=rot90(colors(:,:,1),-1); % felso CW
                colors(:,:,5)=rot90(colors(:,:,5));    % also CCW
            case 'y'
                temp=colors(:,:,2);
                colors(:,:,2)=colors(:,:,3);           % elso <-- bal
                colors(:,:,3)=rot90(colors(:,:,6),2);  % bal <-- hatso
                colors(:,:,6)=rot90(colors(:,:,4),2);  % hatso <-- jobb
                colors(:,:,4)=temp;                    % jobb <-- elso
                colors(:,:,1)=rot90(colors(:,:,1));    % felso CCW
                colors(:,:,5)=rot90(colors(:,:,5),-1); % also CW
            case 'Z'
                temp=rot90(colors(:,:,1),-1);
                colors(:,:,1)=rot90(colors(:,:,3),-1); % felso <-- bal
                colors(:,:,3)=rot90(colors(:,:,5),-1); % bal <-- also
                colors(:,:,5)=rot90(colors(:,:,4),-1); % also <-- jobb
                colors(:,:,4)=temp;                    % jobb <-- felso
                colors(:,:,2)=rot90(colors(:,:,2),-1); % elso CW
                colors(:,:,6)=rot90(colors(:,:,6),1);  % hatso CCW
            case 'z'
                temp=rot90(colors(:,:,1));
                colors(:,:,1)=rot90(colors(:,:,4));    % felso <-- jobb
                colors(:,:,4)=rot90(colors(:,:,5));    % jobb <-- also
                colors(:,:,5)=rot90(colors(:,:,3));    % also <-- bal
                colors(:,:,3)=temp;                    % bal <-- felso
                colors(:,:,2)=rot90(colors(:,:,2));    % elso CCW
                colors(:,:,6)=rot90(colors(:,:,6),-1); % hatso CW
        end
    end
    cout=colors;
