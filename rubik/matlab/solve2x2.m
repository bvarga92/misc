% Megoldofuggveny 2x2x2-es kockahoz.
    % colors: a kocka szinmatrixa (2x2x6 meretu)
    % moves: a megoldashoz vezeto lepessorozat

function moves=solve2x2(colors)
    %% stimmel a meret?
    if ~isequal(size(colors),[2 2 6])
        disp('Color matrix dimension mismatch.');
        moves=[];
        return;
    end

    %% a W-O-G sarkot a FLU helyre forgatjuk (igy vegig konkret szinekkel dolgozhatunk)
    moves=[]; temp=[];
    if strcmp(sort([colors(2,2,1) colors(1,2,2) colors(1,1,4)]),'GOW')     % FRU
        temp='z';
    elseif strcmp(sort([colors(2,1,2) colors(2,2,3) colors(1,1,5)]),'GOW') % FLD
        temp='X';
    elseif strcmp(sort([colors(2,2,2) colors(2,1,4) colors(1,2,5)]),'GOW') % FRD
        temp='YX';
    elseif strcmp(sort([colors(1,1,3) colors(1,1,1) colors(2,1,6)]),'GOW') % BLU
        temp='x';
    elseif strcmp(sort([colors(1,2,4) colors(1,2,1) colors(2,2,6)]),'GOW') % BRU
        temp='xY';
    elseif strcmp(sort([colors(2,1,3) colors(2,1,5) colors(1,1,6)]),'GOW') % BLD
        temp='xx';
    elseif strcmp(sort([colors(2,2,4) colors(2,2,5) colors(1,2,6)]),'GOW') % BRD
        temp='xxz';
    end
    moves=[moves temp]; colors=move(temp,colors); temp=[];
    if colors(1,1,2)=='W'     % elso lapon van a feher
        temp='Xy';
    elseif colors(1,2,3)=='W' % balra nez a feher
        temp='ZY';
    end
    moves=[moves temp]; colors=move(temp,colors); temp=[];

    %% ha van feher a felso sorban, beforgatjuk a helyere
    if colors(1,2,2)=='W'     % FRU eleje
        temp='rDRdrDR';
    elseif colors(1,1,4)=='W' % FRU jobb
        temp='rdRDrdR';
    end
    moves=[moves temp]; colors=move(temp,colors); temp=[];
    if colors(2,2,6)=='W'     % BRU hatulja
        temp='bdBDbdB';
    elseif colors(1,2,4)=='W' % BRU jobb
        temp='bDBdbDB';
    end
    moves=[moves temp]; colors=move(temp,colors); temp=[];
    if colors(2,1,6)=='W'     % BLU hatulja
        temp='lDLdlDL';
    elseif colors(1,1,3)=='W' % BLU bal
        temp='ldLDldL';
    end
    moves=[moves temp]; colors=move(temp,colors); temp=[];

    %% az also sorbol felvisszuk a fehereket
    if colors(2,2,1)~='W' % FRU teteje nem feher
        while colors(1,2,5)~='W' && colors(2,2,2)~='W' && colors(2,1,4)~='W' % alaforgatunk egy feheret
            moves=[moves 'd'];
            colors=move('d',colors);
        end
        if colors(1,2,5)=='W'     % FRD alja feher
            temp='rddRDrdR';
        elseif colors(2,2,2)=='W' % FRD eleje feher
            temp='FDf';
        elseif colors(2,1,4)=='W' % FRD jobb oldala feher
            temp='rdR';
        end
    end
    moves=[moves temp]; colors=move(temp,colors); temp=[];
    if colors(1,2,1)~='W' % BRU teteje nem feher
        while colors(2,2,5)~='W' && colors(1,2,6)~='W' && colors(2,2,4)~='W' % alaforgatunk egy feheret
            moves=[moves 'd'];
            colors=move('d',colors);
        end
        if colors(2,2,5)=='W'     % BRD alja feher
            temp='bddBDbdB';
        elseif colors(1,2,6)=='W' % BRD hatulja feher
            temp='bdB';
        elseif colors(2,2,4)=='W' % BRD jobb oldala feher
            temp='RDr';
        end
    end
    moves=[moves temp]; colors=move(temp,colors); temp=[];
    if colors(1,1,1)~='W' % BLU teteje nem feher
        while colors(2,1,5)~='W' && colors(1,1,6)~='W' && colors(2,1,3)~='W' % alaforgatunk egy feheret
            moves=[moves 'd'];
            colors=move('d',colors);
        end
        if colors(2,1,5)=='W'     % BLD alja feher
            temp='lddLDldL';
        elseif colors(1,1,6)=='W' % BLD hatulja feher
            temp='BDb';
        elseif colors(2,1,3)=='W' % BLD bal oldala feher
            temp='ldL';
        end
    end
    moves=[moves temp]; colors=move(temp,colors); temp=[];

    %% also reteg orientalasa (OLL)
    pattern=colors(:,:,5)=='Y';
    if isequal(pattern,[0 1;0 1])
        if colors(2,1,3)=='Y'
            temp='BRDrdb';
        else
            temp='RDrdrBRb';
        end
    elseif isequal(pattern,[1 1;0 0])
        if colors(1,1,6)=='Y'
            temp='RFDfdr';
        else
            temp='FDfdfRFr';
        end
    elseif isequal(pattern,[1 0;1 0])
        if colors(2,1,4)=='Y'
            temp='FLDldf';
        else
            temp='LDldlFLf';
        end
    elseif isequal(pattern,[0 0;1 1])
        if colors(2,1,2)=='Y'
            temp='LBDbdl';
        else
            temp='BDbdbLBl';
        end
    elseif isequal(pattern,[1 0;0 1])
        if colors(2,2,2)=='Y'
            temp='FLdldLDlf';
        else
            temp='BRdrdRDrb';
        end
    elseif isequal(pattern,[0 1;1 0])
        if colors(2,2,4)=='Y'
            temp='RFdfdFDfr';
        else
            temp='dBRdrdRDrb';
        end
    elseif isequal(pattern,[0 0;1 0])
        if colors(2,1,2)=='Y'
            temp='RDrDRDDr';
        else
            temp='LDDldLdl';
        end
    elseif isequal(pattern,[0 0;0 1])
        if colors(2,1,3)=='Y'
            temp='FDfDFDDf';
        else
            temp='BDDbdBdb';
        end
    elseif isequal(pattern,[1 0;0 0])
        if colors(2,1,4)=='Y'
            temp='BDbDBDDb';
        else
            temp='FDDfdFdf';
        end
    elseif isequal(pattern,[0 1;0 0])
        if colors(1,2,6)=='Y'
            temp='LDlDLDDl';
        else
            temp='RDDrdRdr';
        end
    elseif isequal(pattern,[0 0;0 0]);
        if isequal([colors(2,1,2) colors(2,2,2) colors(1,1,6) colors(1,2,6)],'YYYY')
            temp='RRDDRDDRR';
        elseif isequal([colors(2,1,3) colors(2,2,3) colors(2,1,4) colors(2,2,4)],'YYYY')
            temp='FFDDFDDFF';
        elseif isequal([colors(2,1,3) colors(2,2,3) colors(2,2,2) colors(1,2,6)],'YYYY')
            temp='BRDrdRDrdb';
        elseif isequal([colors(2,1,2) colors(2,2,2) colors(2,1,3) colors(2,2,4)],'YYYY')
            temp='LBDbdBDbdl';
        elseif isequal([colors(2,1,4) colors(2,2,4) colors(2,1,2) colors(1,1,6)],'YYYY')
            temp='FLDldLDldf';
        elseif isequal([colors(1,1,6) colors(1,2,6) colors(2,2,3) colors(2,1,4)],'YYYY')
            temp='RFDfdFDfdr';
        end
    end
    moves=[moves temp]; colors=move(temp,colors); temp=[];

    %% ugy forgatjuk az also sort, hogy az FLD elem a helyen legyen
    while colors(2,1,2)~='G'
        moves=[moves 'd'];
        colors=move('d',colors);
    end

    %% mindket reteg permutalasa (PBL)
    switch [colors(1,2,2) colors(1,1,4) colors(1,2,4) colors(2,2,6) colors(2,1,6) colors(1,1,3)]
        case 'GRRBBO'; topCase=1; % felso reteg OK
        case 'GRBORB'; topCase=2; % felso retegben BRU <--> BLU
        case 'BORBGR'; topCase=3; % felso retegben FRU <--> BLU
        case 'RBGRBO'; topCase=4; % felso retegben FRU <--> BRU
        case 'RBBOGR'; topCase=5; % felso retegben FRU --> BRU --> BLU --> FRU
        case 'BOGRRB'; topCase=6; % felso retegben FRU --> BLU --> BRU --> FRU
    end
    switch [colors(2,2,2) colors(2,1,4) colors(2,2,4) colors(1,2,6) colors(1,1,6) colors(2,1,3)]
        case 'GRRBBO'; btmCase=1; % also reteg OK
        case 'GRBORB'; btmCase=2; % also retegben BRD <--> BLD
        case 'BORBGR'; btmCase=3; % also retegben FRD <--> BLD
        case 'RBGRBO'; btmCase=4; % also retegben FRD <--> BRD
        case 'RBBOGR'; btmCase=5; % also retegben FRD --> BRD --> BLD --> FRD
        case 'BOGRRB'; btmCase=6; % also retegben FRD --> BLD --> BRD --> FRD
    end
    switch 10*topCase+btmCase
        case 12; temp='BDbdbLbbdbdBDbl'; % alul hatul csere
        case 21; temp='BUbubRbbubuBUbr'; % felul hatul csere
        case 22; temp='llulluuffuff';    % mindket retegben hatul csere

        case 13; temp='RFdfdFDfrFDfdfRFr'; % alul keresztbe csere
        case 31; temp='FRuruRUrfRUrurFRf'; % felul keresztbe csere
        case 33; temp='llffll';            % mindket retegben keresztbe csere

        case 14; temp='RDrdrBrrdrdRDrb'; % alul jobb oldalon csere
        case 41; temp='RUrurFrruruRUrf'; % felul jobb oldalon csere
        case 44; temp='bbubbuullull';    % mindket retegben jobb oldalon csere

        case 15; temp='rrbbrfRbbrFr'; % alul CW forgatas
        case 51; temp='RRBBRFrBBRfR'; % felul CCW forgatas
        case 55; temp='ffUlluuffUff'; % alul CW, felul CCW forgatas

        case 16; temp='RfRBBrFRBBRR'; % alul CCW forgatas
        case 61; temp='rFrbbRfrbbrr'; % felul CW forgatas
        case 66; temp='rrUffuurrUrr'; % alul CCW, felul CW forgatas

        case 23; temp='dRuRffrUrD'; % felul hatul csere, alul keresztbe csere
        case 32; temp='LdLfflDl';   % felul keresztbe csere, alul hatul csere

        case 24; temp='Ubbubbuullullu'; % felul hatul csere, alul jobb oldalon csere
        case 42; temp='dbbubbuullullD'; % felul jobb oldalon csere, alul hatul csere

        case 25; temp='dllulluuffuffdd'; % felul hatul csere, alul CW forgatas
        case 52; temp='UllulluuffuffUU'; % alul hatul csere, felul CCW forgatas

        case 26; temp='ddllulluuffuffU'; % felul hatul csere, alul CCW forgatas
        case 62; temp='udbbubbuullullu'; % alul hatul csere, felul CW forgatas

        case 34; temp='DLdLfflDld';   % felul keresztbe csere, alul jobb oldalon csere
        case 43; temp='udRuRffrUrDU'; % alul keresztbe csere, felul jobb oldalon csere

        case 35; temp='dLdLfflDldd'; % felul keresztbe csere, alul CW forgatas
        case 53; temp='BuBrrbUbu';   % alul keresztbe csere, felul CCW forgatas

        case 36; temp='DDLdLFFlDlD'; % felul keresztbe csere, alul CCW forgatas
        case 63; temp='UBuBRRbUb';   % alul keresztbe csere, felul CW forgatas

        case 45; temp='ddbbubbuullulld'; % felul jobb oldalon csere, alul CW forgatas
        case 54; temp='UUbbubbuullullU'; % alul jobb oldalon csere, felul CCW forgatas

        case 46; temp='DbbubbuullullDD'; % felul jobb oldalon csere, alul CCW forgatas
        case 64; temp='ubbubbuullulluu'; % alul jobb oldalon csere, felul CW forgatas

        case 56; temp='dffuffuurrurrd'; % mindket retegben CCW forgatas
        case 65; temp='UffuffuurrurrD'; % mindket retegben CW forgatas
    end
    moves=[moves temp];

    %% forgatasok kiszurese (helyettuk inkabb transzformaljuk a permutaciot) es trivialis egyszerusitesek
    found=1;
    while found
        found=0;
        ii=1;
        while ii<=length(moves)-1 
            if strcmp(moves([ii ii+1]),'Ud') || strcmp(moves([ii ii+1]),'dU') || moves(ii)=='Y'
                found=1;
                if moves(ii)=='Y'; moves(ii)=[]; else moves([ii ii+1])=[]; end
                for jj=ii:length(moves)
                    switch moves(jj)
                        case 'F'; moves(jj)='R';
                        case 'f'; moves(jj)='r';
                        case 'B'; moves(jj)='L';
                        case 'b'; moves(jj)='l';
                        case 'L'; moves(jj)='F';
                        case 'l'; moves(jj)='f';
                        case 'R'; moves(jj)='B';
                        case 'r'; moves(jj)='b';
                        case 'X'; moves(jj)='z';
                        case 'x'; moves(jj)='Z';
                        case 'Z'; moves(jj)='X';
                        case 'z'; moves(jj)='x';
                    end
                end
            elseif strcmp(moves([ii ii+1]),'uD') || strcmp(moves([ii ii+1]),'Du') || moves(ii)=='y'
                found=1;
                if moves(ii)=='y'; moves(ii)=[]; else moves([ii ii+1])=[]; end
                for jj=ii:length(moves)
                    switch moves(jj)
                        case 'F'; moves(jj)='L';
                        case 'f'; moves(jj)='l';
                        case 'B'; moves(jj)='R';
                        case 'b'; moves(jj)='r';
                        case 'L'; moves(jj)='B';
                        case 'l'; moves(jj)='b';
                        case 'R'; moves(jj)='F';
                        case 'r'; moves(jj)='f';
                        case 'X'; moves(jj)='Z';
                        case 'x'; moves(jj)='z';
                        case 'Z'; moves(jj)='x';
                        case 'z'; moves(jj)='X';
                    end
                end
            elseif strcmp(moves([ii ii+1]),'fB') || strcmp(moves([ii ii+1]),'Bf') || moves(ii)=='z'
                found=1;
                if moves(ii)=='z'; moves(ii)=[]; else moves([ii ii+1])=[]; end
                for jj=ii:length(moves)
                    switch moves(jj)
                        case 'U'; moves(jj)='R';
                        case 'u'; moves(jj)='r';
                        case 'D'; moves(jj)='L';
                        case 'd'; moves(jj)='l';
                        case 'L'; moves(jj)='U';
                        case 'l'; moves(jj)='u';
                        case 'R'; moves(jj)='D';
                        case 'r'; moves(jj)='d';
                        case 'X'; moves(jj)='y';
                        case 'x'; moves(jj)='Y';
                        case 'Y'; moves(jj)='X';
                        case 'y'; moves(jj)='x';
                    end
                end
            elseif strcmp(moves([ii ii+1]),'Fb') || strcmp(moves([ii ii+1]),'bF') || moves(ii)=='Z'
                found=1;
                if moves(ii)=='Z'; moves(ii)=[]; else moves([ii ii+1])=[]; end
                for jj=ii:length(moves)
                    switch moves(jj)
                        case 'U'; moves(jj)='L';
                        case 'u'; moves(jj)='l';
                        case 'D'; moves(jj)='R';
                        case 'd'; moves(jj)='r';
                        case 'L'; moves(jj)='D';
                        case 'l'; moves(jj)='d';
                        case 'R'; moves(jj)='U';
                        case 'r'; moves(jj)='u';
                        case 'X'; moves(jj)='Y';
                        case 'x'; moves(jj)='y';
                        case 'Y'; moves(jj)='x';
                        case 'y'; moves(jj)='X';
                    end
                end
            elseif strcmp(moves([ii ii+1]),'lR') || strcmp(moves([ii ii+1]),'Rl') || moves(ii)=='X'
                found=1;
                if moves(ii)=='X'; moves(ii)=[]; else moves([ii ii+1])=[]; end
                for jj=ii:length(moves)
                    switch moves(jj)
                        case 'U'; moves(jj)='F';
                        case 'u'; moves(jj)='f';
                        case 'D'; moves(jj)='B';
                        case 'd'; moves(jj)='b';
                        case 'F'; moves(jj)='D';
                        case 'f'; moves(jj)='d';
                        case 'B'; moves(jj)='U';
                        case 'b'; moves(jj)='u';
                        case 'Y'; moves(jj)='Z';
                        case 'y'; moves(jj)='z';
                        case 'Z'; moves(jj)='y';
                        case 'z'; moves(jj)='Y';
                    end
                end
            elseif strcmp(moves([ii ii+1]),'Lr') || strcmp(moves([ii ii+1]),'rL') || moves(ii)=='x'
                found=1;
                if moves(ii)=='x'; moves(ii)=[]; else moves([ii ii+1])=[]; end
                for jj=ii:length(moves)
                    switch moves(jj)
                        case 'U'; moves(jj)='B';
                        case 'u'; moves(jj)='b';
                        case 'D'; moves(jj)='F';
                        case 'd'; moves(jj)='f';
                        case 'F'; moves(jj)='U';
                        case 'f'; moves(jj)='u';
                        case 'B'; moves(jj)='D';
                        case 'b'; moves(jj)='d';
                        case 'Y'; moves(jj)='z';
                        case 'y'; moves(jj)='Z';
                        case 'Z'; moves(jj)='Y';
                        case 'z'; moves(jj)='y';
                    end
                end
            end
            ii=ii+1;
        end
        ii=1;
        while ii<=length(moves)-2 % tripla forgatas helyett inkabb masik irany
            if moves(ii)==moves(ii+1) && moves(ii+1)==moves(ii+2)
                found=1;
                if moves(ii)>90; moves(ii)=moves(ii)-32; else moves(ii)=moves(ii)+32; end
                moves([ii+1 ii+2])=[];
            end
            ii=ii+1;
        end
        ii=1;
        while ii<=length(moves)-1 % oda-vissza forgatasok kiszurese
            if abs(moves(ii)-moves(ii+1))==32
                found=1;
                moves([ii ii+1])=[];
            else
                ii=ii+1;
            end
        end
    end
    if moves(end)=='X' || moves(end)=='x' || moves(end)=='Y' || moves(end)=='y' || moves(end)=='Z' || moves(end)=='z'
        moves(end)=[];
    end