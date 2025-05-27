# Compilador
CXX = g++

# Opciones de compilación
CXXFLAGS = -Wall -Iinclude

# Librerías necesarias
LDFLAGS = -lglfw -ldl

# Archivos fuente
SRC = main.cpp src/glad.c

# Nombre del binario
OUT = build/app

# Regla principal
all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

# Limpiar binario
clean:
	rm -f $(OUT)

