CC=g++
CFLAGS=-g -O2 -D_REENTRANT -I/usr/local/include/SDL2 -DHAVE_OPENGL -g -lOpenCL


LDFLAGS=-lSDL2_test -L/usr/local/lib -Wl,-rpath,/usr/local/lib -Wl,--enable-new-dtags -lSDL2 -lGL -lm  -lOpenCL
INC = -I include
EXEC=window

SRC_NAME= main.cpp 
SRC_PATH= source/
SRC=$(addprefix $(SRC_PATH), $(SRC_NAME))

OBJ_NAME= $(SRC_NAME:.cpp=.o)
OBJ_PATH= object/
OBJ=$(addprefix $(OBJ_PATH),$(OBJ_NAME))

SDL_PATH= librairy/

all: $(SDL_PATH) $(OBJ_PATH) $(EXEC)

shell:
	@echo $(shell uname)

$(SDL_PATH):
	@mkdir -p $@
	curl -o sdl.zip https://www.libsdl.org/release/SDL2-2.0.12.zip
	@unzip sdl.zip -d $(SDL_PATH)
	@rm -rf sdl.zip
	@cd $(SDL_PATH)/SDL*/ && ./configure; make;sudo make install

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_PATH):
	@mkdir -p $@

main.o: hello.hpp

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp 
	$(CC) $(INC) -o $@ -c $< $(CFLAGS)

.PHONY: clean fclean re

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(EXEC)

re: fclean all

lclean:
	rm -rf $(SDL_PATH)
