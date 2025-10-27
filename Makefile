NAME = testGL
SRCS = test.cpp CreateShader.cpp utils.cpp Shader.cpp Texture.cpp stb_image.cpp
SRCC = glad.c
DIR_OBJ = Obj/
OBJ = $(addprefix $(DIR_OBJ), $(SRCS:.cpp=.o))
OBJ += $(addprefix $(DIR_OBJ), $(SRCC:.c=.o))

CFLAGS = -std=c++20 #-Wall -Wextra -Werror
INC = ./Includes

INCLUDE = -I$(INC) \
		  -I$(INC)/glad/include \
          -I$(HOME)/.local/include \
          -L$(HOME)/.local/lib \
          -Wl,-rpath,$(HOME)/.local/lib \
		  -lglfw3 -ldl -lGL -lpthread -lX11

all: $(NAME)

$(NAME): openGL $(OBJ)
	c++ $(CFLAGS) $(OBJ) $(INCLUDE) -o $(NAME)

# Compile .cpp files with the C++ compiler
$(DIR_OBJ)%.o: %.cpp
	mkdir -p $(DIR_OBJ)
	c++ $(CFLAGS) $(INCLUDE) -c $< -o $@

# Compile .c files with the C compiler
$(DIR_OBJ)%.o: %.c
	gcc $(CFLAGS) $(INCLUDE) -c $< -o $@

openGL:
	cd $(INC)/glfw-3.4 && \
	mkdir -p build && \
	cd build && \
	cmake .. -DGLFW_BUILD_WAYLAND=OFF -DGLFW_BUILD_X11=ON -DCMAKE_INSTALL_PREFIX=$(HOME)/.local && \
	make -j && \
	make install

clean:
	rm -rf $(DIR_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all