all: compile link

compile:
	g++ -I"C:\SFML-2.6.1\include" -c main.cpp -o main.o

link:
	g++ main.o -o app.exe -L"C:\SFML-2.6.1\lib" -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows

clean:
	rm -f app.exe *.o