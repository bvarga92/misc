def rcon(i):
    rc=1
    for _ in range(2,i+1):
        if(rc<0x80):
            rc=rc<<1
        else:
            rc=(rc<<1)^0x11B
    return rc<<24

def gmul(a,b):
    p=0
    while a!=0 and b!=0:
        if b&0x01:
            p^=a
        if a&0x80:
            a=(a<<1)^0x11B
        else:
            a<<=1
        b>>=1
    return p

def RotWord(w):
    return ((w&0x00FFFFFF)<<8)|(w>>24)

def SubByte(b):
    invb=b
    for i in range(13):
        if i%2==1:
            invb=gmul(invb,b)
        else:
            invb=gmul(invb,invb)
    s=invb^0x63
    for i in range(1,5):
        s^=((invb<<i)&0xFF)|(invb>>(8-i))
    return s

def InvSubByte(s):
    b=0x05
    for i in [1,3,6]:
        b^=((s<<i)&0xFF)|(s>>(8-i))
    invb=b
    for i in range(13):
        if i%2==1:
            invb=gmul(invb,b)
        else:
            invb=gmul(invb,invb)
    return invb

def SubWord(w):
    result=0
    for i in range(4):
        result+=SubByte((w>>(8*i))&0xFF)<<(8*i)
    return result

def KeyExpansion(key):
    if len(key)==32:   # AES-128
        N=4
        R=11
    elif len(key)==48: # AES-192
        N=6
        R=13
    elif len(key)==64: # AES-256
        N=8
        R=15
    W=[]
    for i in range(4*R):
        if i<N:
            W.append(int(key[8*i:8*(i+1)],16))
        elif i%N==0:
            W.append(W[i-N]^RotWord(SubWord(W[i-1]))^rcon(int(i/N)))
        elif N>6 and i%N==4:
            W.append(W[i-N]^SubWord(W[i-1]))
        else:
            W.append(W[i-N]^W[i-1])
    return ''.join(format(w,'08x') for w in W)

def AddRoundKey(state,roundkey):
    return [[s^int(roundkey[(2*i+8*j):(2*i+8*j+2)],16) for j,s in enumerate(row)] for i,row in enumerate(state)]

def SubBytes(state):
    return [[SubByte(s) for s in row] for row in state]

def InvSubBytes(state):
    return [[InvSubByte(s) for s in row] for row in state]

def ShiftRows(state):
    state[1][:]=[state[1][1],state[1][2],state[1][3],state[1][0]]
    state[2][:]=[state[2][2],state[2][3],state[2][0],state[2][1]]
    state[3][:]=[state[3][3],state[3][0],state[3][1],state[3][2]]
    return state

def InvShiftRows(state):
    state[1][:]=[state[1][3],state[1][0],state[1][1],state[1][2]]
    state[2][:]=[state[2][2],state[2][3],state[2][0],state[2][1]]
    state[3][:]=[state[3][1],state[3][2],state[3][3],state[3][0]]
    return state

def MixColumns(state):
    temp=[[0]*4 for i in range(4)]
    for j in range(4):
        temp[0][j] = gmul(2,state[0][j]) ^ gmul(3,state[1][j]) ^        state[2][j]  ^        state[3][j]
        temp[1][j] =        state[0][j]  ^ gmul(2,state[1][j]) ^ gmul(3,state[2][j]) ^        state[3][j]
        temp[2][j] =        state[0][j]  ^        state[1][j]  ^ gmul(2,state[2][j]) ^ gmul(3,state[3][j])
        temp[3][j] = gmul(3,state[0][j]) ^        state[1][j]  ^        state[2][j]  ^ gmul(2,state[3][j])
    return temp

def InvMixColumns(state):
    temp=[[0]*4 for i in range(4)]
    for j in range(4):
        temp[0][j] = gmul(14,state[0][j]) ^ gmul(11,state[1][j]) ^ gmul(13,state[2][j]) ^ gmul( 9,state[3][j])
        temp[1][j] = gmul( 9,state[0][j]) ^ gmul(14,state[1][j]) ^ gmul(11,state[2][j]) ^ gmul(13,state[3][j])
        temp[2][j] = gmul(13,state[0][j]) ^ gmul( 9,state[1][j]) ^ gmul(14,state[2][j]) ^ gmul(11,state[3][j])
        temp[3][j] = gmul(11,state[0][j]) ^ gmul(13,state[1][j]) ^ gmul( 9,state[2][j]) ^ gmul(14,state[3][j])
    return temp

def EncryptBlock(plaintext,key):
    # sanity check
    if len(plaintext)!=32:
        raise Exception('Plaintext must be 128 bits long.')
    if not all([c in list('0123456789abcdefABCDEF') for c in plaintext]):
        raise Exception('Plaintext must be in hexadecimal format.')
    if len(key)==32:   # AES-128
        rounds=10
    elif len(key)==48: # AES-192
        rounds=12
    elif len(key)==64: # AES-256
        rounds=14
    else:
        raise Exception('Key must be 128, 192 or 256 bits long.')
    if not all([c in list('0123456789abcdefABCDEF') for c in key]):
        raise Exception('Key must be in hexadecimal format.')
    # eloallitjuk a 128 bites bemenetbol a 4x4 bajtos blokkot
    state=[[0]*4 for i in range(4)]
    for i in range(4):
        for j in range(4):
            state[i][j]=int(plaintext[(2*i+8*j):(2*i+8*j+2)],16)
    # a kulcsbol eloallitjuk a kiterjesztett menetkulcsokat
    EK=KeyExpansion(key)
    # a kulcs hozzaadasa a blokkhoz
    state=AddRoundKey(state,EK[0:32])
    # a lenyegi kodolas: 10, 12 vagy 14 kor
    for r in range(rounds):
        state=SubBytes(state)
        state=ShiftRows(state)
        if r<rounds-1: state=MixColumns(state)
        state=AddRoundKey(state,EK[32*(r+1):32*(r+2)])
    # a blokk visszaalakitasa stringge
    result=''
    for i in range(4):
        for j in range(4):
            result+=format(state[j][i],'02x')
    return result

def DecryptBlock(ciphertext,key):
    # sanity check
    if len(ciphertext)!=32:
        raise Exception('Ciphertext must be 128 bits long.')
    if not all([c in list('0123456789abcdefABCDEF') for c in ciphertext]):
        raise Exception('Ciphertext must be in hexadecimal format.')
    if len(key)==32:   # AES-128
        rounds=10
    elif len(key)==48: # AES-192
        rounds=12
    elif len(key)==64: # AES-256
        rounds=14
    else:
        raise Exception('Key must be 128, 192 or 256 bits long.')
    if not all([c in list('0123456789abcdefABCDEF') for c in key]):
        raise Exception('Key must be in hexadecimal format.')
    # eloallitjuk a 128 bites bemenetbol a 4x4 bajtos blokkot
    state=[[0]*4 for i in range(4)]
    for i in range(4):
        for j in range(4):
            state[i][j]=int(ciphertext[(2*i+8*j):(2*i+8*j+2)],16)
    # a kulcsbol eloallitjuk a kiterjesztett menetkulcsokat
    EK=KeyExpansion(key)
    # a kodolasi algoritmus vegrehajtasa visszafele
    for r in range(rounds-1,-1,-1):
        state=AddRoundKey(state,EK[32*(r+1):32*(r+2)])
        if r<rounds-1: state=InvMixColumns(state)
        state=InvShiftRows(state)
        state=InvSubBytes(state)
    state=AddRoundKey(state,EK[0:32])
    # a blokk visszaalakitasa stringge
    result=''
    for i in range(4):
        for j in range(4):
            result+=format(state[j][i],'02x')
    return result

plaintext='59b5088e6dadc3ad5f27a460872d5929'
key128='8d2e60365f17c7df1040d7501b4a7b5a'
key192='e9f065d7c13573587f7875357dfbb16c53489f6a4bd0f7cd'
key256='b43d08a447ac8609baadae4ff12918b9f68fc1653f1269222f123981ded7a92f'
print('Plaintext:  ', plaintext)
print()
print('AES-128:    ', EncryptBlock(plaintext,key128))
print('AES-192:    ', EncryptBlock(plaintext,key192))
print('AES-256:    ', EncryptBlock(plaintext,key256))
print()
print('Decrypt 128:', DecryptBlock('e642556d1c301baf2eba963149cdec79',key128))
print('Decrypt 192:', DecryptBlock('403c6ff9976cc744ed731c7b6ee9272f',key192))
print('Decrypt 256:', DecryptBlock('026dcf9b2b4003fd9e76820674597572',key256))