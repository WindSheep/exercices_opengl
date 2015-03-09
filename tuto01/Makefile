THIS_MAKEFILE = $(lastword $(MAKEFILE_LIST))
THIS_DIR      = $(dir $(realpath $(THIS_MAKEFILE)))
TMPDIR        = /tmp

CC       = g++
DEBUG    = 0

LDLIBS   =
LOADLIBS = $(LDLIBS)
CFLAGS   = -Wall -Wextra -Werror
CFLAGS   = -ansi -Wpedantic -Weffc++
CFLAGS   = -std=c++11
LDFLAGS  = -lglfw3 -lXrandr -lXext -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lm -lXcursor -lXinerama -lGL -lGLEW

ifeq ($(DEBUG), 1)
  CFLAGS += -ggdb3 -DDEBUG
#else
#  CFLAGS += -O3
endif

#insert APP here
APP_1  = tuto01

SRCS_DIR      = $(THIS_DIR)/src
OBJS_DIR      = $(THIS_DIR)/obj
INCS_DIR      = $(THIS_DIR)/include

INCLUDES = -I$(INCS_DIR) $(LDLIBS)
CFLAGS  += $(INCLUDES)

SRCS_EXT    = cpp
OBJS_EXT    = o

SRCS  = $(foreach ext, $(SRCS_EXT), $(shell find $(SRCS_DIR) -type f -name "*.$(ext)"))
OBJS  = $(foreach ext, $(SRCS_EXT), $(patsubst $(SRCS_DIR)/%.$(ext), $(OBJS_DIR)/%.$(ext).$(OBJS_EXT), $(filter %.$(ext), $(SRCS))))

# insert APP here
all: $(APP_1)

# insert APP here
$(APP_1): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

obj: $(OBJS)

$(OBJS_DIR)/%.$(SRCS_EXT).$(OBJS_EXT): src/%.$(SRCS_EXT)
	@mkdir -m 750 -p -v $(dir $@)
	$(CC) -c $^ -o $@ $(CFLAGS)

clean:
	rm -rf $(OBJS_DIR)

# insert APP here
fclean: clean
	rm -f $(APP_1) $(APP_2) $(APP_3)

re: fclean all

.PHONY: all obj clean fclean re
