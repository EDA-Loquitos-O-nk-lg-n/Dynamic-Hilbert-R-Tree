CXX = g++

release:
	$(CXX) lib/*.cc lib/Arbol_R_Hilbert/*.cc lib/Entrada/*.cc src/main.cc -o bin/release/main -lsfml-graphics -lsfml-window -lsfml-system

debug:
	$(CXX) -fdiagnostics-color=always -g lib/*.cc lib/Arbol_R_Hilbert/*.cc lib/Entrada/*.cc src/main.cc -o bin/debug/main -lsfml-graphics -lsfml-window -lsfml-system