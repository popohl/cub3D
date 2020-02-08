SRCS		= display.c parsing.c wouf.c

SRCS_BONUS	=

LIBS		= libft libmlx

OBJ_DIR		= objs
SRC_DIR		= srcs

OBJS		:= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
OBJS_BONUS	:= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS_BONUS))
DEP			:= $(patsubst %.o,%.d,$(OBJS))
DEP			+= $(patsubst %.o,%.d,$(OBJS_BONUS))

NAME		= cub3d
CC			= gcc
CFLAGS		= -Wall -Wextra -g3 -fsanitize=address
LDFLAGS		= -framework OpenGL -framework AppKit
INCLUDES	:= -I . $(patsubst %,-I %,$(LIBS))

all:
	@$(foreach L, $(LIBS), $(MAKE) -C $L -j;)
	@$(MAKE) $(NAME) -j

$(NAME):		$(OBJS) $(foreach L,$(LIBS),$L/$L.a)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

bonus:			$(OBJS) $(OBJS_BONUS) $(foreach L,$(LIBS),$L/$L.a)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

-include $(DEP)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCLUDES)

libft/libft.a:
	@$(MAKE) -C libft


libmlx/libmlx.a:
	@$(MAKE) -C libmlx

clean:
	@$(foreach L, $(LIBS), $(MAKE) -C $L clean;)
	$(RM) -r $(OBJ_DIR)

fclean:	clean
	$(RM) $(NAME) $(foreach L,$(LIBS),$L/$L.a)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all bonus clean fclean re libft libmlx
