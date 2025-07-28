# ANSI colors
RESET  = $(ESC)[0m
BOLD   = $(ESC)[1m
BLUE   = $(ESC)[34m
YELLOW = $(ESC)[33m
GREEN  = $(ESC)[32m

ESC := $(shell printf '\033')


ifeq ($(origin CC), default)
	CC = g++
endif

BUILD ?= debug

COMMON_FLAGS ?= -std=c++17 -Wall -Wextra

SANITAZER_FLAGS ?= -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,$\
					integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,$\
					shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr \

DEBUG_FLAGS ?= -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall \
			-Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations \
			-Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion \
			-Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral \
			-Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor \
			-Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls \
			-Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 \
			-Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override \
			-Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast \
			-Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing \
			-Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation \
			-fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer \
			-Wlarger-than=81920 -Wstack-usage=81920 -pie -fPIE -Werror=vla \
			$(SANITAZER_FLAGS)

RELEASE_FLAGS ?= -DNDEBUG -O2 -march=native -flto

ifeq ($(BUILD),debug)
	CFLAGS = $(COMMON_FLAGS) $(DEBUG_FLAGS)
	LDFLAGS = $(SANITAZER_FLAGS)
else
	CFLAGS = $(COMMON_FLAGS) $(RELEASE_FLAGS)
	LDFLAGS = 
endif


OUT_O_DIR ?= build
SRC = ./src

INCLUDE_DIRS := $(shell find src utils -type d)
COMMONINC := $(addprefix -I,$(INCLUDE_DIRS))
override CFLAGS += $(COMMONINC)

ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

CSRC = src/logger.cpp utils/error_handling.cpp

COBJ := $(addprefix $(OUT_O_DIR)/, $(CSRC:.cpp=.o))
DEPS = $(COBJ:.o=.d)


.PHONY: all
all: $(OUT_O_DIR)/liblogger.a

$(OUT_O_DIR)/liblogger.a: $(COBJ)
	@echo "$(GREEN)[LD ]$(RESET) $@"
	@ar rcs $@ $^

$(COBJ) : $(OUT_O_DIR)/%.o : %.cpp
	@mkdir -p $(@D)
	@echo "$(GREEN)[CXX]$(RESET) $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(DEPS) : $(OUT_O_DIR)/%.d : %.cpp
	@mkdir -p $(@D)
	@echo "$(GREEN)[DEP]$(RESET) $<"
	@$(CC) -E $(CFLAGS) $< -MM -MT $(@:.d=.o) > $@

.PHONY: clean
clean:
	rm -rf $(COBJ) $(DEPS) \
	$(OUT_O_DIR)/*.x \
	$(OUT_O_DIR)/*.a \
	$(OUT_O_DIR)/*.log \
	$(OUT_O_DIR)/*.d \
	$(OUT_O_DIR)/*.o

NODEPS = clean

ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
include $(DEPS)
endif