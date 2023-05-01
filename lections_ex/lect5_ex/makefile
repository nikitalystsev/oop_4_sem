$(shell mkdir -p out)

CC := g++

CFLAGS := -std=c++20 -Wall -pedantic -Wextra -Wfloat-equal -Wfloat-conversion -Iinc -Wvla

PREF_SRC := ./src/
PREF_INC := ./inc/
PREF_OUT := ./out/

# получаем список си файлов в подпапке ./src/
SRC := $(wildcard $(PREF_SRC)*.cpp)

# получаем заменой список объектных файлов для файлов из подпапки ./src/
EX_EXE := $(patsubst $(PREF_SRC)%.cpp, %.exe, $(SRC))

.PHONY: all clean

all: $(EX_EXE)

# получаем exe файлы с помощью си файлов из подпапки ./src/
%.exe : $(PREF_OUT)%.o
	$(CC)  $< -o $@ 

# получаем объектные файлы с помощью си файлов из подпапки ./src/
$(PREF_OUT)%.o : $(PREF_SRC)%.cpp
	$(CC) $(CFLAGS) -c -MD $< -o $@


clean : 
	rm -Rf $(PREF_OUT) ./*.exe