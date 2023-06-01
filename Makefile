#COMPILATION
CC      := gcc
CFLAGS  := -Wall -Werror -Wextra

#CLEAN & FCLEAN
RM_DIR  := rm -rf
RM      := rm -f

#INCLUDES
INCL   := -I H_Files/

#SDL
SDL2_INCL := -I 00-SDL/SDL2/includes/
SDL2_LIB  := -L 00-SDL/SDL2/lib/ -lSDL2

SDLI_INCL := -I 00-SDL/SDL_Image/include/
SDLI_LIB := -I 00-SDL/SDL_Image/lib/ -lSDL2_image

SDLTTF_INCL := -I 00-SDL/sdl2_ttf/include/
SDLTTF_LIB := -I 00-SDL/sdl2_ttf/lib/ -lSDL2_ttf

#C_FILES
SRC_DIR = 	C_Files/
FILES 	:=	animAsteroid.c \
			animFondu.c \
			event.c \
			graphic.c \
			main.c \
			mainGame.c \
			mainIntro.c \
			mainMenu.c \
			menuMain.c \
			menuNewGame.c \
			menuTitle.c \
			textureToList.c \
			timer.c \
			utils.c \
			utilsSDL.c \

#OBJECTS
OBJ= $(FILES:.c=.o)
OBJ_DIR := ./O_Files/
OBJS     := $(addprefix $(OBJ_DIR), $(FILES:%.c=%.o))

NAME := Space_Survivor

all:$(NAME)

$(NAME):$(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_DIR)*.o $(SDL2_LIB) $(SDLI_LIB) $(SDLTTF_LIB)

%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $(OBJ_DIR)$@ -c $< $(SDL2_INCL) $(SDLI_INCL) $(SDLTTF_INCL) $(INCL)

clean:
	$(RM_DIR) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re