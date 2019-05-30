#-------------------------------------------------------
# BCC Developer 1.2.21
# Copyright (C) 2003 jun_miura@hi-ho.ne.jp
#-------------------------------------------------------
.autodepend
CC=bcc32
RC=brc32
CFLAG=-W  -3 -Od -w- -AT -pc -H- -k -b -v -y  -DDEBUG
OUTDIR=-nDebug
CINCS=
TARGET=Debug\tetris.exe
SRC1="C:\Users\ajun\Documents\bcc developer\tetris\Main.cpp"
OBJ1=Debug\Main.obj
SRC2="C:\Users\ajun\Documents\bcc developer\tetris\Title.cpp"
OBJ2=Debug\Title.obj
SRC3="C:\Users\ajun\Documents\bcc developer\tetris\Menu.cpp"
OBJ3=Debug\Menu.obj
SRC4="C:\Users\ajun\Documents\bcc developer\tetris\Tetris.cpp"
OBJ4=Debug\Tetris.obj
SRC5="C:\Users\ajun\Documents\bcc developer\tetris\GA.cpp"
OBJ5=Debug\GA.obj
SRC6="C:\Users\ajun\Documents\bcc developer\tetris\Option.cpp"
OBJ6=Debug\Option.obj
SRC7="C:\Users\ajun\Documents\bcc developer\tetris\Keyboard.cpp"
OBJ7=Debug\Keyboard.obj
SRC8="C:\Users\ajun\Documents\bcc developer\tetris\SceneMgr.cpp"
OBJ8=Debug\SceneMgr.obj

TARGET: $(TARGET)

$(TARGET): $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5) $(OBJ6) $(OBJ7) $(OBJ8)
    $(CC) $(CFLAG) -e$(TARGET) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5) $(OBJ6) $(OBJ7) $(OBJ8)

$(OBJ1): $(SRC1)
    $(CC) $(CFLAG) $(OUTDIR) $(CINCS) -c $(SRC1)

$(OBJ2): $(SRC2)
    $(CC) $(CFLAG) $(OUTDIR) $(CINCS) -c $(SRC2)

$(OBJ3): $(SRC3)
    $(CC) $(CFLAG) $(OUTDIR) $(CINCS) -c $(SRC3)

$(OBJ4): $(SRC4)
    $(CC) $(CFLAG) $(OUTDIR) $(CINCS) -c $(SRC4)

$(OBJ5): $(SRC5)
    $(CC) $(CFLAG) $(OUTDIR) $(CINCS) -c $(SRC5)

$(OBJ6): $(SRC6)
    $(CC) $(CFLAG) $(OUTDIR) $(CINCS) -c $(SRC6)

$(OBJ7): $(SRC7)
    $(CC) $(CFLAG) $(OUTDIR) $(CINCS) -c $(SRC7)

$(OBJ8): $(SRC8)
    $(CC) $(CFLAG) $(OUTDIR) $(CINCS) -c $(SRC8)
