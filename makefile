CC=g++

INC =-I include/
CFLAGS=-g $(INC)

LDFLAGS=-lm library/SDL2-2.0.12/build/.libs/libSDL2.a `library/SDL2-2.0.12/sdl2-config --static-libs` 
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LDFLAGS+= -lGL
endif
ifeq ($(UNAME_S),Darwin)
	LDFLAGS+= -framework OpenGL
endif

EXEC=window

SRC_NAME=main.cpp SceneOpenGL.cpp
SRC_PATH=source/
SRC=$(addprefix $(SRC_PATH), $(SRC_NAME))

OBJ_NAME= $(SRC_NAME:.cpp=.o)
OBJ_PATH= object/
OBJ=$(addprefix $(OBJ_PATH),$(OBJ_NAME))

SDL_LIB=library/SDL2-2.0.12/build/.libs/libSDL2.a
LIB=library/

all: $(SDL_LIB) $(OBJ_PATH) $(EXEC)

shell:
	@echo $(shell uname)

$(SDL_LIB): $(LIB)
	@rm -rf $(LIB)/SDL2-2.0.12/
	curl -o sdl.zip https://www.libsdl.org/release/SDL2-2.0.12.zip
	@unzip sdl.zip -d $(LIB)
	@rm -rf sdl.zip
	@cd $(LIB)/SDL2-2.0.12/ && ./configure; make

$(LIB):
	@mkdir -p $@

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_PATH):
	@mkdir -p $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp 
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean fclean re

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(EXEC)

re: fclean all

lclean:
	rm -rf $(LIB)
