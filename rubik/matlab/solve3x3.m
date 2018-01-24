% Megoldofuggveny 3x3x3-as kockahoz.
    % colors: a kocka szinmatrixa (3x3x6 meretu)
    % moves: a megoldashoz vezeto lepessorozat

function moves=solve3x3(colors)
    %% stimmel a meret?
    if ~isequal(size(colors),[3 3 6])
        disp('Color matrix dimension mismatch.');
        moves=[];
        return;
    end

    %% orientacio: F zold, U feher
    moves=[]; temp=[];
    if colors(2,2,2)=='W'     % elol van a feher
        temp='X';
    elseif colors(2,2,4)=='W' % jobb oldalon van a feher
        temp='z';
    elseif colors(2,2,6)=='W' % hatul van a feher
        temp='x';
    elseif colors(2,2,3)=='W' % bal oldalon van a feher
        temp='Z';
    elseif colors(2,2,5)=='W' % alul van a feher
        temp='zz';
    end
    moves=[moves temp]; colors=move(temp,colors); temp=[];
    if colors(2,2,4)=='G'     % jobb oldalon van a zold
        temp='Y';
    elseif colors(2,2,6)=='G' % hatul van a zold
        temp='yy';
    elseif colors(2,2,3)=='G' % bal oldalon van a zold
        temp='y';
    end
    moves=[moves temp]; colors=move(temp,colors); temp=[];

    %% kirakjuk a feher keresztet
    for ii=1:4
        switch ii
            case 1; f='G';
            case 2; f='R';
            case 3; f='B';
            case 4; f='O';
        end
        if colors(1,2,1)=='W' && colors(3,2,6)==f
            temp='BBDDFF';
        elseif colors(1,2,1)==f && colors(3,2,6)=='W'
            temp='bRdffr';
        elseif colors(2,1,1)=='W' && colors(1,2,3)==f
            temp='llDff';
        elseif colors(2,1,1)==f && colors(1,2,3)=='W'
            temp='LF';
        elseif colors(2,3,1)=='W' && colors(1,2,4)==f
            temp='rrdff';
        elseif colors(2,3,1)==f && colors(1,2,4)=='W'
            temp='rf';
        elseif colors(3,2,1)==f && colors(1,2,2)=='W'
            temp='ffdlFL';
        elseif colors(2,1,2)=='W' && colors(2,3,3)==f
            temp='LDlff';
        elseif colors(2,1,2)==f && colors(2,3,3)=='W'
            temp='F';
        elseif colors(2,3,2)=='W' && colors(2,1,4)==f
            temp='rdRff';
        elseif colors(2,3,2)==f && colors(2,1,4)=='W'
            temp='f';
        elseif colors(3,2,2)=='W' && colors(1,2,5)==f
            temp='dlFL';
        elseif colors(3,2,2)==f && colors(1,2,5)=='W'
            temp='ff';
        elseif colors(2,1,3)=='W' && colors(2,1,6)==f
            temp='llFll';
        elseif colors(2,1,3)==f && colors(2,1,6)=='W'
            temp='lDLff';
        elseif colors(2,3,4)=='W' && colors(2,3,6)==f
            temp='rrfrr';
        elseif colors(2,3,4)==f && colors(2,3,6)=='W'
            temp='Rdrff';
        elseif colors(3,2,3)=='W' && colors(2,1,5)==f
            temp='lFL';
        elseif colors(3,2,3)==f && colors(2,1,5)=='W'
            temp='Dff';
        elseif colors(3,2,4)=='W' && colors(2,3,5)==f
            temp='Rfr';
        elseif colors(3,2,4)==f && colors(2,3,5)=='W'
            temp='dff';
        elseif colors(3,2,5)=='W' && colors(1,2,6)==f
            temp='ddff';
        elseif colors(3,2,5)==f && colors(1,2,6)=='W'
            temp='dRfr';
        end
        temp=[temp 'Y'];
        moves=[moves temp]; colors=move(temp,colors); temp=[];
    end

    %% kirakjuk az elso ket reteget (F2L)
    for ii=1:4
        switch ii
            case 1; f='G'; l='O';
            case 2; f='R'; l='G';
            case 3; f='B'; l='R';
            case 4; f='O'; l='B';
        end
        while isequal(sort([colors(3,3,1) colors(1,3,2) colors(1,1,4)]),sort([f l 'W'])) || isequal(sort([colors(2,3,2) colors(2,1,4)]),sort([f l]))
            moves=[moves 'rDR'];
            colors=move('rDR',colors);
        end
        while isequal(sort([colors(1,3,1) colors(1,3,4) colors(3,3,6)]),sort([f l 'W'])) || isequal(sort([colors(2,3,6) colors(2,3,4)]),sort([f l]))
            moves=[moves 'RDr'];
            colors=move('RDr',colors);
        end
        while isequal(sort([colors(1,1,1) colors(1,1,3) colors(3,1,6)]),sort([f l 'W'])) || isequal(sort([colors(2,1,6) colors(2,1,3)]),sort([f l]))
            moves=[moves 'lDL'];
            colors=move('lDL',colors);
        end
        while ~isequal(sort([colors(3,1,2) colors(3,3,3) colors(1,1,5)]),sort([f l 'W'])) && ~isequal(sort([colors(1,1,2) colors(1,3,3) colors(3,1,1)]),sort([f l 'W']))
            moves=[moves 'd'];
            colors=move('d',colors);
        end
        if colors(3,3,3)=='W' && colors(3,1,2)==f && colors(1,1,5)==l && colors(3,2,5)==f && colors(1,2,6)==l
            temp='LDl';
        elseif colors(3,3,3)=='W' && colors(3,1,2)==f && colors(1,1,5)==l && colors(3,2,2)==f && colors(1,2,5)==l
            temp='dfDF';
        elseif colors(3,3,3)=='W' && colors(3,1,2)==f && colors(1,1,5)==l && colors(2,1,2)==f && colors(2,3,3)==l
            temp='DfDFDfDDF';
        elseif colors(3,3,3)=='W' && colors(3,1,2)==f && colors(1,1,5)==l && colors(2,1,2)==l && colors(2,3,3)==f
            temp='DfdFdLDl';
        elseif colors(3,3,3)=='W' && colors(3,1,2)==f && colors(1,1,5)==l && colors(2,1,5)==l && colors(3,2,3)==f
            temp='LdlddfdF';
        elseif colors(3,3,3)=='W' && colors(3,1,2)==f && colors(1,1,5)==l && colors(3,2,5)==l && colors(1,2,6)==f
            temp='DfddFDfddF';
        elseif colors(3,3,3)=='W' && colors(3,1,2)==f && colors(1,1,5)==l && colors(2,3,5)==l && colors(3,2,4)==f
            temp='DfdFDfddF';
        elseif colors(3,3,3)=='W' && colors(3,1,2)==f && colors(1,1,5)==l && colors(3,2,3)==l && colors(2,1,5)==f
            temp='dLdlDLDl';
        elseif colors(3,3,3)=='W' && colors(3,1,2)==f && colors(1,1,5)==l && colors(3,2,4)==l && colors(2,3,5)==f
            temp='dLDlDLDl';
        elseif colors(3,3,3)=='W' && colors(3,1,2)==f && colors(1,1,5)==l && colors(3,2,2)==l && colors(1,2,5)==f
            temp='DfddFdLDl';
        elseif colors(3,3,3)==l && colors(3,1,2)=='W' && colors(1,1,5)==f && colors(3,2,4)==f && colors(2,3,5)==l
            temp='fdF';
        elseif colors(3,3,3)==l && colors(3,1,2)=='W' && colors(1,1,5)==f && colors(2,1,5)==f && colors(3,2,3)==l
            temp='DLdl';
        elseif colors(3,3,3)==l && colors(3,1,2)=='W' && colors(1,1,5)==f && colors(2,1,2)==f && colors(2,3,3)==l
            temp='dLdldLddl';
        elseif colors(3,3,3)==l && colors(3,1,2)=='W' && colors(1,1,5)==f && colors(2,1,2)==l && colors(2,3,3)==f
            temp='dLDlDfdF';
        elseif colors(3,3,3)==l && colors(3,1,2)=='W' && colors(1,1,5)==f && colors(2,1,5)==l && colors(3,2,3)==f
            temp='dLddlDfdF';
        elseif colors(3,3,3)==l && colors(3,1,2)=='W' && colors(1,1,5)==f && colors(3,2,5)==l && colors(1,2,6)==f
            temp='DfdFdfdF';
        elseif colors(3,3,3)==l && colors(3,1,2)=='W' && colors(1,1,5)==f && colors(2,3,5)==f && colors(3,2,4)==l
            temp='dLddldLddl';
        elseif colors(3,3,3)==l && colors(3,1,2)=='W' && colors(1,1,5)==f && colors(3,2,5)==f && colors(1,2,6)==l
            temp='dLDldLddl';
        elseif colors(3,3,3)==l && colors(3,1,2)=='W' && colors(1,1,5)==f && colors(3,2,2)==f && colors(1,2,5)==l
            temp='DfDFdfdF';
        elseif colors(3,3,3)==l && colors(3,1,2)=='W' && colors(1,1,5)==f && colors(3,2,2)==l && colors(1,2,5)==f
            temp='fDFddLDl';
        elseif colors(3,3,3)==f && colors(3,1,2)==l && colors(1,1,5)=='W' && colors(2,3,3)==l && colors(2,1,2)==f
            temp='LDldLDldLDl';
        elseif colors(3,3,3)==f && colors(3,1,2)==l && colors(1,1,5)=='W' && colors(2,3,3)==f && colors(2,1,2)==l
            temp='LdlDfDF';
        elseif colors(3,3,3)==f && colors(3,1,2)==l && colors(1,1,5)=='W' && colors(1,2,5)==f && colors(3,2,2)==l
            temp='LDlddLDldLDl';
        elseif colors(3,3,3)==f && colors(3,1,2)==l && colors(1,1,5)=='W' && colors(2,3,5)==f && colors(3,2,4)==l
            temp='ddLDlDLdl';
        elseif colors(3,3,3)==f && colors(3,1,2)==l && colors(1,1,5)=='W' && colors(3,2,5)==f && colors(1,2,6)==l
            temp='DLddlDLdl';
        elseif colors(3,3,3)==f && colors(3,1,2)==l && colors(1,1,5)=='W' && colors(2,1,5)==f && colors(3,2,3)==l
            temp='LddldLDl';
        elseif colors(3,3,3)==f && colors(3,1,2)==l && colors(1,1,5)=='W' && colors(3,2,3)==f && colors(2,1,5)==l
            temp='fdFDDfdFDfdF';
        elseif colors(3,3,3)==f && colors(3,1,2)==l && colors(1,1,5)=='W' && colors(1,2,6)==f && colors(3,2,5)==l
            temp='ddfdFdfDF';
        elseif colors(3,3,3)==f && colors(3,1,2)==l && colors(1,1,5)=='W' && colors(3,2,4)==f && colors(2,3,5)==l
            temp='dfddFdfDF';
        elseif colors(3,3,3)==f && colors(3,1,2)==l && colors(1,1,5)=='W' && colors(3,2,2)==f && colors(1,2,5)==l
            temp='fddFDfdF';
        elseif colors(1,1,2)==f && colors(1,3,3)==l && colors(3,1,1)=='W' && colors(2,3,3)==f && colors(2,1,2)==l
            temp='LdlDfddFDfDDF';
        elseif colors(1,1,2)==f && colors(1,3,3)==l && colors(3,1,1)=='W' && colors(3,2,2)==f && colors(1,2,5)==l
            temp='DLdldfDF';
        elseif colors(1,1,2)==f && colors(1,3,3)==l && colors(3,1,1)=='W' && colors(3,2,3)==f && colors(2,1,5)==l
            temp='DDLdldfDF';
        elseif colors(1,1,2)==f && colors(1,3,3)==l && colors(3,1,1)=='W' && colors(1,2,6)==f && colors(3,2,5)==l
            temp='dLdldfDF';
        elseif colors(1,1,2)==f && colors(1,3,3)==l && colors(3,1,1)=='W' && colors(3,2,4)==f && colors(2,3,5)==l
            temp='LdldfDF';
        elseif colors(1,1,2)==f && colors(1,3,3)==l && colors(3,1,1)=='W' && colors(2,1,5)==f && colors(3,2,3)==l
            temp='dfDFDLdl';
        elseif colors(1,1,2)==f && colors(1,3,3)==l && colors(3,1,1)=='W' && colors(3,2,5)==f && colors(1,2,6)==l
            temp='fDFDLdl';
        elseif colors(1,1,2)==f && colors(1,3,3)==l && colors(3,1,1)=='W' && colors(2,3,5)==f && colors(3,2,4)==l
            temp='DfDFDLdl';
        elseif colors(1,1,2)==f && colors(1,3,3)==l && colors(3,1,1)=='W' && colors(1,2,5)==f && colors(3,2,2)==l
            temp='ddfDFDLdl';
        elseif colors(1,1,2)==l && colors(1,3,3)=='W' && colors(3,1,1)==f && colors(2,1,2)==f && colors(2,3,3)==l
            temp='LdlDLddlDLdl';
        elseif colors(1,1,2)==l && colors(1,3,3)=='W' && colors(3,1,1)==f && colors(2,3,3)==f && colors(2,1,2)==l
            temp='LDldLdlDDfdF';
        elseif colors(1,1,2)=='W' && colors(1,3,3)==f && colors(3,1,1)==l && colors(2,1,2)==f && colors(2,3,3)==l
            temp='LdldLDldLddl';
        elseif colors(1,1,2)=='W' && colors(1,3,3)==f && colors(3,1,1)==l && colors(2,3,3)==f && colors(2,1,2)==l
            temp='LdlDfdFdfdF';
        elseif colors(1,1,2)==l && colors(1,3,3)=='W' && colors(3,1,1)==f && colors(3,2,2)==f && colors(1,2,5)==l
            temp='fDFdfDF';
        elseif colors(1,1,2)==l && colors(1,3,3)=='W' && colors(3,1,1)==f && colors(3,2,3)==f && colors(2,1,5)==l
            temp='DfDFdfDF';
        elseif colors(1,1,2)==l && colors(1,3,3)=='W' && colors(3,1,1)==f && colors(1,2,6)==f && colors(3,2,5)==l
            temp='DDfDFdfDF';
        elseif colors(1,1,2)==l && colors(1,3,3)=='W' && colors(3,1,1)==f && colors(3,2,4)==f && colors(2,3,5)==l
            temp='dfDFdfDF';
        elseif colors(1,1,2)==l && colors(1,3,3)=='W' && colors(3,1,1)==f && colors(3,2,3)==l && colors(2,1,5)==f
            temp='LDldLDl';
        elseif colors(1,1,2)==l && colors(1,3,3)=='W' && colors(3,1,1)==f && colors(1,2,6)==l && colors(3,2,5)==f
            temp='DLDldLDl';
        elseif colors(1,1,2)==l && colors(1,3,3)=='W' && colors(3,1,1)==f && colors(3,2,4)==l && colors(2,3,5)==f
            temp='DDLDldLDl';
        elseif colors(1,1,2)==l && colors(1,3,3)=='W' && colors(3,1,1)==f && colors(3,2,2)==l && colors(1,2,5)==f
            temp='dLDldLDl';
        elseif colors(1,1,2)=='W' && colors(1,3,3)==f && colors(3,1,1)==l && colors(2,1,5)==f && colors(3,2,3)==l
            temp='LdlDLdl';
        elseif colors(1,1,2)=='W' && colors(1,3,3)==f && colors(3,1,1)==l && colors(3,2,5)==f && colors(1,2,6)==l
            temp='DLdlDLdl';
        elseif colors(1,1,2)=='W' && colors(1,3,3)==f && colors(3,1,1)==l && colors(2,3,5)==f && colors(3,2,4)==l
            temp='DDLdlDLdl';
        elseif colors(1,1,2)=='W' && colors(1,3,3)==f && colors(3,1,1)==l && colors(1,2,5)==f && colors(3,2,2)==l
            temp='dLdlDLdl';
        elseif colors(1,1,2)=='W' && colors(1,3,3)==f && colors(3,1,1)==l && colors(2,1,5)==l && colors(3,2,3)==f
            temp='DfdFDfdF';
        elseif colors(1,1,2)=='W' && colors(1,3,3)==f && colors(3,1,1)==l && colors(3,2,5)==l && colors(1,2,6)==f
            temp='DDfdFDfdF';
        elseif colors(1,1,2)=='W' && colors(1,3,3)==f && colors(3,1,1)==l && colors(2,3,5)==l && colors(3,2,4)==f
            temp='dfdFDfdF';
        elseif colors(1,1,2)=='W' && colors(1,3,3)==f && colors(3,1,1)==l && colors(1,2,5)==l && colors(3,2,2)==f
            temp='fdFDfdF';
        end
        temp=[temp 'Y'];
        moves=[moves temp]; colors=move(temp,colors); temp=[];
    end

    %% utolso reteg orientalasa (OLL)
    found=0;
    if colors(1,1,5)=='Y' && colors(1,2,5)=='Y' && colors(1,3,5)=='Y' && colors(2,1,5)=='Y' && colors(2,3,5)=='Y' && colors(3,1,5)=='Y' && colors(3,2,5)=='Y' && colors(3,3,5)=='Y'
        found=1;
    end
    while found==0
        found=1;
        if colors(1,2,6)=='Y' && colors(3,1,3)=='Y' && colors(3,2,3)=='Y' && colors(3,3,3)=='Y' && colors(3,2,2)=='Y' && colors(3,1,4)=='Y' && colors(3,2,4)=='Y' && colors(3,3,4)=='Y'
            temp='LDbLBLLdlFLf';
        elseif colors(1,2,6)=='Y' && colors(3,1,3)=='Y' && colors(3,2,3)=='Y' && colors(3,1,2)=='Y' && colors(3,2,2)=='Y' && colors(3,3,2)=='Y' && colors(3,2,4)=='Y' && colors(3,3,4)=='Y'
            temp='lFLfddlFLffddF';
        elseif colors(1,1,5)=='Y' && colors(1,3,6)=='Y' && colors(1,2,6)=='Y' && colors(3,1,3)=='Y' && colors(3,2,3)=='Y' && colors(3,2,2)=='Y' && colors(3,1,4)=='Y' && colors(3,2,4)=='Y'
            temp='fbbRbRFddfRbF';
        elseif colors(3,1,5)=='Y' && colors(1,2,6)=='Y' && colors(3,2,3)=='Y' && colors(3,3,3)=='Y' && colors(3,2,2)=='Y' && colors(3,3,2)=='Y' && colors(3,2,4)=='Y' && colors(3,3,4)=='Y'
            temp='lddlFLfdfdFdL';
        elseif colors(3,3,5)=='Y' && colors(1,1,5)=='Y' && colors(1,2,6)=='Y' && colors(1,1,6)=='Y' && colors(3,2,3)=='Y' && colors(3,2,2)=='Y' && colors(3,1,4)=='Y' && colors(3,2,4)=='Y'
            temp='LDlDlFLfddlFLf';
        elseif colors(3,3,5)=='Y' && colors(3,1,5)=='Y' && colors(1,3,5)=='Y' && colors(1,1,5)=='Y' && colors(1,2,6)=='Y' && colors(3,2,3)=='Y' && colors(3,2,2)=='Y' && colors(3,2,4)=='Y'
            temp='lRffLrddlRFLrddlRffLr';
        elseif colors(3,3,5)=='Y' && colors(3,1,5)=='Y' && colors(1,2,6)=='Y' && colors(3,2,3)=='Y' && colors(3,3,3)=='Y' && colors(3,2,2)=='Y' && colors(3,1,4)=='Y' && colors(3,2,4)=='Y'
            temp='lddFLDldffddFL';
        elseif colors(1,3,5)=='Y' && colors(1,1,5)=='Y' && colors(1,3,6)=='Y' && colors(1,2,6)=='Y' && colors(1,1,6)=='Y' && colors(3,2,3)=='Y' && colors(3,2,2)=='Y' && colors(3,2,4)=='Y'
            temp='FLDlDfddfRFr';
        elseif colors(3,2,5)=='Y' && colors(1,2,5)=='Y' && colors(1,3,6)=='Y' && colors(3,1,3)=='Y' && colors(3,2,3)=='Y' && colors(3,3,3)=='Y' && colors(3,3,2)=='Y' && colors(3,2,4)=='Y'
            temp='ldfDfRFrFL';
        elseif colors(3,2,5)=='Y' && colors(1,2,5)=='Y' && colors(3,1,3)=='Y' && colors(3,2,3)=='Y' && colors(3,3,3)=='Y' && colors(3,1,4)=='Y' && colors(3,2,4)=='Y' && colors(3,3,4)=='Y'
            temp='LdbbUbddBubbDl';
        elseif colors(2,3,5)=='Y' && colors(2,1,5)=='Y' && colors(1,3,6)=='Y' && colors(1,2,6)=='Y' && colors(3,1,3)=='Y' && colors(3,3,3)=='Y' && colors(3,2,2)=='Y' && colors(3,3,2)=='Y'
            temp='FDLdlDLdlf';
        elseif colors(2,3,5)=='Y' && colors(2,1,5)=='Y' && colors(1,2,6)=='Y' && colors(3,1,3)=='Y' && colors(3,3,3)=='Y' && colors(3,2,2)=='Y' && colors(3,1,4)=='Y' && colors(3,3,4)=='Y'
            temp='rbRdlDLdlDLrBR';
        elseif colors(3,2,5)=='Y' && colors(2,3,5)=='Y' && colors(2,1,5)=='Y' && colors(1,2,5)=='Y' && colors(1,3,6)=='Y' && colors(3,1,3)=='Y' && colors(3,3,3)=='Y' && colors(3,3,2)=='Y'
            temp='RdlDrDLDlDL';
        elseif colors(3,2,5)=='Y' && colors(2,3,5)=='Y' && colors(2,1,5)=='Y' && colors(1,2,5)=='Y' && colors(3,1,3)=='Y' && colors(3,3,3)=='Y' && colors(3,1,4)=='Y' && colors(3,3,4)=='Y'
            temp='LDlDLdlDLddl';
        elseif colors(3,2,5)=='Y' && colors(2,3,5)=='Y' && colors(2,1,5)=='Y' && colors(1,2,5)=='Y' && colors(1,1,5)=='Y' && colors(1,1,6)=='Y' && colors(3,3,2)=='Y' && colors(3,3,4)=='Y'
            temp='rDLdRDl';
        elseif colors(3,2,5)=='Y' && colors(2,3,5)=='Y' && colors(2,1,5)=='Y' && colors(1,2,5)=='Y' && colors(1,1,5)=='Y' && colors(1,3,6)=='Y' && colors(3,1,3)=='Y' && colors(3,1,4)=='Y'
            temp='lddLDlDL';
        elseif colors(3,3,5)=='Y' && colors(3,2,5)=='Y' && colors(2,3,5)=='Y' && colors(2,1,5)=='Y' && colors(1,3,5)=='Y' && colors(1,2,5)=='Y' && colors(1,1,6)=='Y' && colors(3,1,2)=='Y'
            temp='lfRFLfrF';
        elseif colors(3,3,5)=='Y' && colors(3,2,5)=='Y' && colors(3,1,5)=='Y' && colors(2,3,5)=='Y' && colors(2,1,5)=='Y' && colors(1,2,5)=='Y' && colors(3,1,2)=='Y' && colors(3,3,2)=='Y'
            temp='llUlddLulddl';
        elseif colors(3,3,5)=='Y' && colors(3,2,5)=='Y' && colors(2,3,5)=='Y' && colors(2,1,5)=='Y' && colors(1,2,5)=='Y' && colors(1,1,5)=='Y' && colors(1,1,6)=='Y' && colors(3,1,4)=='Y'
            temp='lfrFLfRF';
        elseif colors(3,3,5)=='Y' && colors(3,1,5)=='Y' && colors(2,3,5)=='Y' && colors(1,3,5)=='Y' && colors(1,2,5)=='Y' && colors(1,1,5)=='Y' && colors(1,2,6)=='Y' && colors(3,2,3)=='Y'
            temp='lRfLrddlRfLr';
        elseif colors(3,3,5)=='Y' && colors(3,1,5)=='Y' && colors(2,3,5)=='Y' && colors(2,1,5)=='Y' && colors(1,3,5)=='Y' && colors(1,1,5)=='Y' && colors(1,2,6)=='Y' && colors(3,2,2)=='Y'
            temp='rLDldRlFLf';
        elseif colors(3,2,5)=='Y' && colors(2,3,5)=='Y' && colors(1,3,5)=='Y' && colors(1,3,6)=='Y' && colors(3,1,3)=='Y' && colors(3,2,3)=='Y' && colors(3,1,2)=='Y' && colors(3,2,2)=='Y'
            temp='RFlFLffr';
        elseif colors(3,3,5)=='Y' && colors(3,2,5)=='Y' && colors(2,3,5)=='Y' && colors(1,1,5)=='Y' && colors(3,1,3)=='Y' && colors(3,2,3)=='Y' && colors(3,2,2)=='Y' && colors(3,3,2)=='Y'
            temp='FlfLDLdl';
        elseif colors(3,2,5)=='Y' && colors(2,3,5)=='Y' && colors(1,1,5)=='Y' && colors(1,1,6)=='Y' && colors(3,2,3)=='Y' && colors(3,2,2)=='Y' && colors(3,3,2)=='Y' && colors(3,3,4)=='Y'
            temp='ldLFlfDFLf';
        elseif colors(3,2,5)=='Y' && colors(2,3,5)=='Y' && colors(1,3,5)=='Y' && colors(1,1,5)=='Y' && colors(1,3,6)=='Y' && colors(1,1,6)=='Y' && colors(3,2,3)=='Y' && colors(3,2,2)=='Y'
            temp='dLddldLdllfdFDL';
        elseif colors(3,2,5)=='Y' && colors(2,3,5)=='Y' && colors(1,1,6)=='Y' && colors(3,2,3)=='Y' && colors(3,1,2)=='Y' && colors(3,2,2)=='Y' && colors(3,1,4)=='Y' && colors(3,3,4)=='Y'
            temp='FLDldLDldf';
        elseif colors(3,2,5)=='Y' && colors(2,3,5)=='Y' && colors(1,3,6)=='Y' && colors(1,1,6)=='Y' && colors(3,2,3)=='Y' && colors(3,1,2)=='Y' && colors(3,2,2)=='Y' && colors(3,3,2)=='Y'
            temp='RfrFddrrBRbR';
        elseif colors(3,2,5)=='Y' && colors(2,1,5)=='Y' && colors(1,3,5)=='Y' && colors(1,1,5)=='Y' && colors(1,3,6)=='Y' && colors(1,1,6)=='Y' && colors(3,2,2)=='Y' && colors(3,2,4)=='Y'
            temp='dlddLDlDllBDbdl';
        elseif colors(3,2,5)=='Y' && colors(3,1,5)=='Y' && colors(2,1,5)=='Y' && colors(3,3,3)=='Y' && colors(3,2,2)=='Y' && colors(3,3,2)=='Y' && colors(3,2,4)=='Y' && colors(3,3,4)=='Y'
            temp='RfflfLfr';
        elseif colors(3,2,5)=='Y' && colors(3,1,5)=='Y' && colors(2,1,5)=='Y' && colors(1,3,5)=='Y' && colors(1,3,6)=='Y' && colors(3,3,3)=='Y' && colors(3,2,2)=='Y' && colors(3,2,4)=='Y'
            temp='lddLLblBlddL';
        elseif colors(3,2,5)=='Y' && colors(2,1,5)=='Y' && colors(1,3,6)=='Y' && colors(3,1,3)=='Y' && colors(3,3,3)=='Y' && colors(3,2,2)=='Y' && colors(3,3,2)=='Y' && colors(3,2,4)=='Y'
            temp='frdRDrdRDF';
        elseif colors(3,2,5)=='Y' && colors(2,1,5)=='Y' && colors(1,1,6)=='Y' && colors(3,1,2)=='Y' && colors(3,2,2)=='Y' && colors(3,1,4)=='Y' && colors(3,2,4)=='Y' && colors(3,3,4)=='Y'
            temp='lFlfllddbLBl';
        elseif colors(3,2,5)=='Y' && colors(2,1,5)=='Y' && colors(1,3,6)=='Y' && colors(1,1,6)=='Y' && colors(3,1,2)=='Y' && colors(3,2,2)=='Y' && colors(3,3,2)=='Y' && colors(3,2,4)=='Y'
            temp='lFLfddllblBl';
        elseif colors(3,1,5)=='Y' && colors(2,3,5)=='Y' && colors(1,2,5)=='Y' && colors(1,3,6)=='Y' && colors(1,2,6)=='Y' && colors(3,2,3)=='Y' && colors(3,1,2)=='Y' && colors(3,1,4)=='Y'
            temp='LDlbLBdblB';
        elseif colors(3,3,5)=='Y' && colors(2,3,5)=='Y' && colors(1,2,5)=='Y' && colors(1,2,6)=='Y' && colors(1,1,6)=='Y' && colors(3,2,3)=='Y' && colors(3,3,3)=='Y' && colors(3,3,2)=='Y'
            temp='rbRdlDLrBR';
        elseif colors(2,3,5)=='Y' && colors(1,2,5)=='Y' && colors(1,1,5)=='Y' && colors(1,2,6)=='Y' && colors(1,1,6)=='Y' && colors(3,2,3)=='Y' && colors(3,3,2)=='Y' && colors(3,3,4)=='Y'
            temp='ddRllfLflffLfLr';
        elseif colors(3,3,5)=='Y' && colors(3,1,5)=='Y' && colors(2,3,5)=='Y' && colors(1,2,5)=='Y' && colors(1,2,6)=='Y' && colors(3,2,3)=='Y' && colors(3,3,3)=='Y' && colors(3,1,4)=='Y'
            temp='bLbllDLDldLbb';
        elseif colors(2,1,5)=='Y' && colors(1,2,5)=='Y' && colors(1,2,6)=='Y' && colors(1,1,6)=='Y' && colors(3,1,2)=='Y' && colors(3,1,4)=='Y' && colors(3,2,4)=='Y' && colors(3,3,4)=='Y'
            temp='RdfddfDFdFddFdr';
        elseif colors(2,1,5)=='Y' && colors(1,3,5)=='Y' && colors(1,2,5)=='Y' && colors(1,3,6)=='Y' && colors(1,2,6)=='Y' && colors(3,1,3)=='Y' && colors(3,1,2)=='Y' && colors(3,2,4)=='Y'
            temp='ddlrrFrFRffrFLr';
        elseif colors(3,3,5)=='Y' && colors(3,1,5)=='Y' && colors(2,1,5)=='Y' && colors(1,2,5)=='Y' && colors(1,2,6)=='Y' && colors(3,3,3)=='Y' && colors(3,1,4)=='Y' && colors(3,2,4)=='Y'
            temp='llDlbLdllDLBl';
        elseif colors(2,1,5)=='Y' && colors(1,2,5)=='Y' && colors(1,1,5)=='Y' && colors(1,3,6)=='Y' && colors(1,2,6)=='Y' && colors(3,1,3)=='Y' && colors(3,1,4)=='Y' && colors(3,2,4)=='Y'
            temp='rbbLBlBR';
        elseif colors(3,3,5)=='Y' && colors(3,2,5)=='Y' && colors(1,3,5)=='Y' && colors(1,2,5)=='Y' && colors(3,1,3)=='Y' && colors(3,2,3)=='Y' && colors(3,3,3)=='Y' && colors(3,2,4)=='Y'
            temp='LDLblBdl';
        elseif colors(2,3,5)=='Y' && colors(2,1,5)=='Y' && colors(1,3,5)=='Y' && colors(1,1,5)=='Y' && colors(1,2,6)=='Y' && colors(3,1,3)=='Y' && colors(3,2,2)=='Y' && colors(3,3,4)=='Y'
            temp='LDldblFLfB';
        elseif colors(2,3,5)=='Y' && colors(2,1,5)=='Y' && colors(1,1,5)=='Y' && colors(1,2,6)=='Y' && colors(1,1,6)=='Y' && colors(3,2,2)=='Y' && colors(3,3,2)=='Y' && colors(3,3,4)=='Y'
            temp='lFLDlfLFdf';
        elseif colors(2,3,5)=='Y' && colors(2,1,5)=='Y' && colors(1,3,5)=='Y' && colors(1,3,6)=='Y' && colors(1,2,6)=='Y' && colors(3,1,3)=='Y' && colors(3,1,2)=='Y' && colors(3,2,2)=='Y'
            temp='RfrdRFrfDF';
        elseif colors(2,3,5)=='Y' && colors(2,1,5)=='Y' && colors(1,1,5)=='Y' && colors(1,3,6)=='Y' && colors(1,2,6)=='Y' && colors(3,1,3)=='Y' && colors(3,2,2)=='Y' && colors(3,1,4)=='Y'
            temp='rbRldLDrBR';
        elseif colors(2,3,5)=='Y' && colors(2,1,5)=='Y' && colors(1,3,5)=='Y' && colors(1,2,6)=='Y' && colors(1,1,6)=='Y' && colors(3,3,3)=='Y' && colors(3,2,2)=='Y' && colors(3,3,4)=='Y'
            temp='LBlRDrdLbl';
        elseif colors(3,3,5)=='Y' && colors(3,2,5)=='Y' && colors(2,3,5)=='Y' && colors(1,3,5)=='Y' && colors(3,1,3)=='Y' && colors(3,2,3)=='Y' && colors(3,3,3)=='Y' && colors(3,2,2)=='Y'
            temp='FDLdlf';
        elseif colors(3,2,5)=='Y' && colors(3,1,5)=='Y' && colors(2,1,5)=='Y' && colors(1,1,5)=='Y' && colors(1,3,6)=='Y' && colors(3,2,2)=='Y' && colors(3,3,2)=='Y' && colors(3,2,4)=='Y'
            temp='ldFDLdlfL';
        elseif colors(3,3,5)=='Y' && colors(3,2,5)=='Y' && colors(2,3,5)=='Y' && colors(1,3,5)=='Y' && colors(1,1,6)=='Y' && colors(3,2,3)=='Y' && colors(3,1,2)=='Y' && colors(3,2,2)=='Y'
            temp='RDfdrDRFr';
        elseif colors(3,2,5)=='Y' && colors(3,1,5)=='Y' && colors(2,1,5)=='Y' && colors(1,1,5)=='Y' && colors(3,2,2)=='Y' && colors(3,1,4)=='Y' && colors(3,2,4)=='Y' && colors(3,3,4)=='Y'
            temp='fdrDRF';
        elseif colors(3,1,5)=='Y' && colors(2,3,5)=='Y' && colors(2,1,5)=='Y' && colors(1,1,5)=='Y' && colors(1,2,6)=='Y' && colors(3,2,2)=='Y' && colors(3,1,4)=='Y' && colors(3,3,4)=='Y'
            temp='FLDldf';
        elseif colors(3,1,5)=='Y' && colors(2,3,5)=='Y' && colors(2,1,5)=='Y' && colors(1,1,5)=='Y' && colors(1,3,6)=='Y' && colors(1,2,6)=='Y' && colors(3,2,2)=='Y' && colors(3,3,2)=='Y'
            temp='LDldlFLf';
        elseif colors(3,1,5)=='Y' && colors(2,1,5)=='Y' && colors(1,3,5)=='Y' && colors(1,2,5)=='Y' && colors(1,2,6)=='Y' && colors(3,1,2)=='Y' && colors(3,2,4)=='Y' && colors(3,3,4)=='Y'
            temp='RDrDRdrdrBRb';
        elseif colors(3,3,5)=='Y' && colors(2,3,5)=='Y' && colors(1,2,5)=='Y' && colors(1,1,5)=='Y' && colors(1,2,6)=='Y' && colors(3,1,3)=='Y' && colors(3,2,3)=='Y' && colors(3,3,2)=='Y'
            temp='ldLdlDLDLblB';
        elseif colors(3,3,5)=='Y' && colors(2,3,5)=='Y' && colors(2,1,5)=='Y' && colors(1,1,5)=='Y' && colors(1,2,6)=='Y' && colors(1,1,6)=='Y' && colors(3,2,2)=='Y' && colors(3,1,4)=='Y'
            temp='lFLDldfDL';
        elseif colors(3,1,5)=='Y' && colors(2,3,5)=='Y' && colors(2,1,5)=='Y' && colors(1,3,5)=='Y' && colors(1,3,6)=='Y' && colors(1,2,6)=='Y' && colors(3,3,3)=='Y' && colors(3,2,2)=='Y'
            temp='RfrdRDFdr';
        else
            found=0;
            moves=[moves 'Y'];
            colors=move('Y',colors);
        end
    end
    moves=[moves temp]; colors=move(temp,colors); temp=[];

    %% orientacio: F zold, U sarga
    if colors(2,2,2)=='Y'     % elol van a sarga
        temp='X';
    elseif colors(2,2,4)=='Y' % jobb oldalon van a sarga
        temp='z';
    elseif colors(2,2,6)=='Y' % hatul van a sarga
        temp='x';
    elseif colors(2,2,3)=='Y' % bal oldalon van a sarga
        temp='Z';
    elseif colors(2,2,5)=='Y' % alul van a sarga
        temp='zz';
    end
    moves=[moves temp]; colors=move(temp,colors); temp=[];
    if colors(2,2,4)=='G'     % jobb oldalon van a zold
        temp='Y';
    elseif colors(2,2,6)=='G' % hatul van a zold
        temp='yy';
    elseif colors(2,2,3)=='G' % bal oldalon van a zold
        temp='y';
    end
    moves=[moves temp]; colors=move(temp,colors); temp=[];

    %% a zold-sarga elet a helyere forgatjuk
    while colors(1,2,2)~='G'
        moves=[moves 'u'];
        colors=move('u',colors);
    end

    %% utolso reteg permutalasa (PLL)
    switch [colors(3,2,6) colors(1,2,4) colors(1,2,3)]
        case 'BOR'; edgeCase=1;
        case 'ROB'; edgeCase=2;
        case 'BRO'; edgeCase=3;
        case 'ORB'; edgeCase=4;
        case 'OBR'; edgeCase=5;
        case 'RBO'; edgeCase=6;
    end
    switch [colors(1,1,2) colors(1,3,2) colors(1,1,3) colors(1,3,3) colors(1,1,4) colors(1,3,4) colors(3,1,6) colors(3,3,6)]
        case 'ORBGGBOR'; cornerCase=1;
        case 'GOORBBGR'; cornerCase=2;
        case 'RROBGOGB'; cornerCase=3;
        case 'RRBBGGOO'; cornerCase=4;
        case 'BBGORGRO'; cornerCase=5;
        case 'ROOBBRGG'; cornerCase=6;
        case 'GBORROGB'; cornerCase=7;
        case 'BGGOOBRR'; cornerCase=8;
        case 'OORGBRBG'; cornerCase=9;
        case 'BRROGGBO'; cornerCase=10;
        case 'RGBBOROG'; cornerCase=11;
        case 'OBBGRROG'; cornerCase=12;
        case 'OBGGRORB'; cornerCase=13;
        case 'GGBROBOR'; cornerCase=14;
        case 'BGROORBG'; cornerCase=15;
        case 'GORRBGBO'; cornerCase=16;
        case 'OOGGBBRR'; cornerCase=17;
        case 'BROOGBGR'; cornerCase=18;
        case 'GBBRRGOO'; cornerCase=19;
        case 'ORRGGOBB'; cornerCase=20;
        case 'BBOORRGG'; cornerCase=21;
        case 'RGGBOORB'; cornerCase=22;
        case 'ROGBBGRO'; cornerCase=23;
        case 'GGRROOBB'; cornerCase=24;
    end
    switch 100*edgeCase+cornerCase
        case 101; temp='BlbRBLbRRfLFRflF';
        case 102; temp='BlBrrbLBrrbb';
        case 103; temp='lBlffLblffll';
        case 108; temp='LfLbblFLbbll';
        case 109; temp='RbRffrBRffrr';
        case 110; temp='fLfrrFlfrrff';
        case 111; temp='bRbllBrbllbb';
        case 113; temp='FrFllfRFllff';
        case 119; temp='rFrbbRfrbbrr';
        case 121; temp='RlRlDRlRlUURlRlDRlRlUU';
        case 123; temp='RbrFRBrFFlBLFlbL';
        case 204; temp='URuRURURururr';
        case 205; temp='uluLffDrURuRdff';
        case 206; temp='UllDfUfuFdllbUB';
        case 207; temp='FRuruRUrfRUrurFRf';
        case 212; temp='UBUbrrdFufUfDrr';
        case 214; temp='rUluuRuruuRLu';
        case 215; temp='bUbulbllulUlBLB';
        case 216; temp='BuubuuBlbuBUBLbbU';
        case 217; temp='ubbUBUbububUb';
        case 218; temp='ubbdRuRUrDbbLul';
        case 220; temp='luuLuulBLUlulbllu';
        case 222; temp='LUlbLUlulBllulu';
        case 304; temp='RlRlDRlRlUrLffRlRlbbrLu';
        case 305; temp='uuFUfufLffufuFUfl';
        case 306; temp='uuBUbubRbbubuBUbr';
        case 307; temp='bUfuuBuFbUfuuBuFu';
        case 312; temp='uubuubulbllulUlBLuB';
        case 314; temp='luuluflffufUfLFuL';
        case 315; temp='BuFuubUfBuFuubUfU';
        case 316; temp='RUrurFrruruRUrf';
        case 317; temp='urLrLDrLrLUrLffrLrLbbrLuu';
        case 318; temp='uufuufurfrrurUrFRuF';
        case 320; temp='ruurubrbbubUbRBuR';
        case 322; temp='LUlulBlluluLUlb';
        case 401; temp='UlUluflffufUfLFL';
        case 402; temp='lldBuBUbDllFuf';
        case 403; temp='UfuuFuufLFUfuflffu';
        case 408; temp='fuFrrDbUBuBdrr';
        case 409; temp='uuffDrUruRdfflUL';
        case 410; temp='ULuuluuLfluLULFllU';
        case 411; temp='UFUflFUfufLffufu';
        case 413; temp='uuLUlbbdRurUrDbb';
        case 419; temp='UbUfuuBubuuBFu';
        case 421; temp='uuBuBUBUBububb';
        case 423; temp='URBubuBUbrBUbubRBr';
        case 424; temp='llULUlululUl';
        case 504; temp='UFuFUFUFufuff';
        case 505; temp='URUrffdLulUlDff';
        case 506; temp='urrdFuFUfDrrBub';
        case 507; temp='rUrubrbbubUbRBR';
        case 512; temp='UbbDlUluLdbbrUR';
        case 514; temp='BUbrBUbubRbbubu';
        case 515; temp='LFufuFUflFUfufLFl';
        case 516; temp='fUbuuFufuuFBu';
        case 517; temp='urrURUrururUr';
        case 518; temp='ubuBllDfUFuFdll';
        case 520; temp='RuuruuRbruRURBrrU';
        case 522; temp='buuBuubRBUbubrbbu';
        case 601; temp='ufUfurfrrurUrFRF';
        case 602; temp='ulUruuLuluuLRu';
        case 603; temp='UUffdLuLUlDffRur';
        case 608; temp='uRUrfRUrurFrruru';
        case 609; temp='uFuufuuFrfuFUFRffU';
        case 610; temp='uuruRbbDlULuLdbb';
        case 611; temp='rrDbUbuBdrrfUF';
        case 613; temp='uruuRuurFRUrurfrru';
        case 619; temp='FUflldBubUbDll';
        case 621; temp='uuffUFUfufufUf';
        case 623; temp='uBLuluLUlbLUlulBLb';
        case 624; temp='LuLULULulull';
    end
    moves=[moves temp];

    %% forgatasok kiszurese (helyettuk inkabb transzformaljuk a permutaciot) es trivialis egyszerusitesek
    found=1;
    while found
        found=0;
        ii=1;
        while ii<=length(moves)
            if moves(ii)=='Y'
                found=1;
                moves(ii)=[];
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
            elseif moves(ii)=='y'
                found=1;
                moves(ii)=[];
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
            elseif moves(ii)=='z'
                found=1;
                moves(ii)=[];
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
            elseif moves(ii)=='Z'
                found=1;
                moves(ii)=[];
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
            elseif moves(ii)=='X'
                found=1;
                moves(ii)=[];
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
            elseif moves(ii)=='x'
                found=1;
                moves(ii)=[];
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