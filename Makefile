SRC_DIR := src
BIN_DIR := bin
INC_DIR := inc
DEP_DIR := dep

CXX_FLAGS := -std=c++17

EXES := test time_normal time_binary

EXE_time_normal_DEFINES := -DUSE_NORMAL_NAV
EXE_time_binary_DEFINES := -DUSE_BINARY_NAV
EXE_test_DEFINES := -DUSE_NORMAL_NAV -DUSE_BINARY_NAV

.PHONY: all clean

all: $(addprefix $(BIN_DIR)/, $(EXES))

$(addprefix $(BIN_DIR)/, $(EXES)): $(DEP_DIR) $(BIN_DIR) $(SRC_DIR)/main.cpp
	$(CXX) $(CXX_FLAGS) -I$(INC_DIR) \
		-MMD -MP -MF $(DEP_DIR)/$(@:$(BIN_DIR)/%=%).d -o $@ \
		$(EXE_$(@:$(BIN_DIR)/%=%)_DEFINES) $(SRC_DIR)/main.cpp

$(DEP_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

clean:
	rm -rf $(BIN_DIR)
	rm -rf $(DEP_DIR)

-include $(addprefix $(DEP_DIR)/, $(addsuffix .d,$(EXES)))
