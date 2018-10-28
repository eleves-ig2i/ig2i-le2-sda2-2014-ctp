all : exo1.exe exo2.exe

exo1.exe : exo1.c
	gcc exo1.c -o exo1.exe

exo2.exe : exo2.c
	gcc exo2.c -o exo2.exe

clean :
	rm -rf *.exe
