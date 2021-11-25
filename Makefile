default: all
#==============================================================================#
#--------------------------------- SHELL --------------------------------------#
#==============================================================================#
SHELL			:= /bin/sh
OS				 = $(shell uname)
#==============================================================================#
#------------------------------ DIRECTORIES -----------------------------------#
#==============================================================================#
SRCS_DIR		 = src/
OBJS_DIR		 = obj/
#==============================================================================#
#--------------------------------- FILES --------------------------------------#
#==============================================================================#
SRCS_NAME		 = main
SRCS_NAME		 += ft_malloc
SRCS_NAME		 += ft_free
#------------------------------------------------------------------------------#
SRCS			 = $(addprefix ${SRCS_DIR}, $(addsuffix .c, ${SRCS_NAME}))
#------------------------------------------------------------------------------#
INCS_NAME		 = main
#------------------------------------------------------------------------------#
INCS			 = $(addprefix ${SRCS_DIR}, $(addsuffix .h, ${INCS_NAME}))
INCS			+= $(patsubst %.c,%.h,${SRCS})
#------------------------------------------------------------------------------#
OBJS			 = $(patsubst ${SRCS_DIR}%.c,${OBJS_DIR}%.o,${SRCS})
#------------------------------------------------------------------------------#
NAME			 = malo
#------------------------------------------------------------------------------#
#==============================================================================#
#-------------------------------- COMPILER ------------------------------------#
#==============================================================================#
ifeq (${OS}, FreeBSD)
CC				 = cc
endif
ifeq (${OS}, Linux)
CC				 = clang
endif
ifeq (${OS}, Darwin)
CC				 = cc
endif
CFLAGS			= -Wall
CFLAGS			+= -Wextra
CFLAGS			+= -Werror
#------------------------------------------------------------------------------#
#------------------------------------------------------------------------------#
#==============================================================================#
#--------------------------------- UNIX ---------------------------------------#
#==============================================================================#
RM				= rm -rf
MKDIR			= mkdir -p
#==============================================================================#
#--------------------------------- RULES --------------------------------------#
#==============================================================================#
#------------------------------------------------------------------------------#
${OBJS_DIR}%.o:	${SRCS_DIR}%.c ${INCS}
	${CC} -c ${CFLAGS} ${CDEFS} -o $@ $<
#------------------------------------------------------------------------------#
${OBJS_DIR}:
	${MKDIR} ${OBJS_DIR}
#------------------------------------------------------------------------------#
$(NAME): ${OBJS} 
	${CC} ${CFLAGS} ${CDEFS} -o ${NAME} ${OBJS} ${LDFLAGS}
#------------------------------------------------------------------------------#
all: ${OBJS_DIR} ${NAME}
#------------------------------------------------------------------------------#
debug: CFLAGS += -glldb
debug: LFTRULE = debug
debug: all
#------------------------------------------------------------------------------#
asan: CFLAGS += -glldb
asan: CFLAGS += -fsanitize=address
asan: LFTRULE = asan
asan: all
#------------------------------------------------------------------------------#
msan: CFLAGS += -glldb
msan: CFLAGS += -fsanitize=memory
msan: CFLAGS += -fsanitize-memory-track-origins
msan: CFLAGS += -fno-common
msan: CFLAGS += -fno-omit-frame-pointer
msan: LFTRULE = msan
msan: all
#------------------------------------------------------------------------------#
clean:
	${RM} ${OBJS_DIR} vgcore*
#------------------------------------------------------------------------------#
fclean: clean
	${RM} ${NAME} ${NAME}.core ${NAME}.dSYM/
#------------------------------------------------------------------------------#
re: fclean all
#------------------------------------------------------------------------------#
run: all
	./${NAME} google.com
#------------------------------------------------------------------------------#
.PHONY:	all clean clean fclean re debug asan run
