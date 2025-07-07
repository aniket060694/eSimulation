include makefile.inc

# Included all source files
SRC_FILES = $(SRC_DIR)/charging_station.cpp $(SRC_DIR)/simulation_main.cpp

# Copy all source object files
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Regular simulator module bin
TARGET = $(BIN_DIR)/evtol_simulator

# Test module source file
TEST_OBJ_FILES_PREFIX = $(OBJ_DIR)/test_
TEST_MODE_SRC_FILES = $(SRC_FILES) \
                      $(SRC_DIR)/test_module.cpp

TEST_OBJ_FILES = $(TEST_MODE_SRC_FILES:$(SRC_DIR)/%.cpp=$(TEST_OBJ_FILES_PREFIX)%.o)

# Simulator test module bin
TEST_RUN_TARGET = $(BIN_DIR)/evtol_test_simulator

all: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_OBJ_FILES_PREFIX)%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_TEST_BUILD) -c $< -o $@


$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_FILES) -o $(TARGET)

$(TEST_RUN_TARGET): $(TEST_OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(TEST_OBJ_FILES) -o $(TEST_RUN_TARGET)

# Clean all Simulator module obj, bin and test result dirctory
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)
	rm -rf $(RESULT_DIR)

# Clean and build simulation module.
rebuild: clean all

# Run simulator module bin
run: $(TARGET)
	@mkdir -p $(RESULT_DIR)
	./$(TARGET)

# Run test simulator module bin
test_run: $(TEST_RUN_TARGET)
	@mkdir -p $(RESULT_DIR)
	$(TEST_RUN_TARGET)

.PHONY: all clean rebuild run test_run
