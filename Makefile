
CC        := g++
LD        := g++

MODULES   := world world/blockmetadata gui render network maths managers gameplay editor time frames framework .
SRC_DIR   := $(addprefix src/,$(MODULES))
BUILD_DIR := $(addprefix build/,$(MODULES))

SRC       := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJ       := $(patsubst src/%.cpp,build/%.o,$(SRC))
INCLUDES  := $(addprefix -I,$(SRC_DIR))

vpath %.cpp $(SRC_DIR)

define make-goal
$1/%.o: %.cpp
	$(CC) $(INCLUDES) -g -c $$< -o $$@
endef

.PHONY: all checkdirs clean

all: checkdirs build/BlockCTF

build/BlockCTF: $(OBJ)
	$(LD) $^ -g -o $@ -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lenet -lSDL2_gfx -lSDL2_mixer -lGL -lGLEW


checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))
