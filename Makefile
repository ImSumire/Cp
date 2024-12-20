# Styling
RED := \033[31m
BLUE := \033[34m
MAGENTA := \033[35m
UNDERLINE := \033[4m
RESET := \033[0m

# Paths
SRC_DIR := src
TESTS_DIR := tests
TARGET_DIR := target
EXAMPLES_DIR := examples

# Targets
SRC_FILES := $(wildcard $(SRC_DIR)/*)

ifeq ($(target), release)  # make ... target=release
	CFLAGS := -O3
	TARGET := release
else
	CFLAGS := -Og -Wall -Wno-return-type
	TARGET := debug
endif

ifeq ($(MAKECMDGOALS), check)  # make check ...
	DEBUG_INFO := -g
else
	DEBUG_INFO :=
endif

FULL_TARGET := $(TARGET_DIR)/$(TARGET)

# Default
.PHONY: help
help:
	@printf "C+'s Basic Makefile\n\n"

	@printf "$(MAGENTA)Usage: $(BLUE)make [cmd]\n"
	@printf "  $(BLUE)Use target=release to built the release\n\n"

	@printf "$(MAGENTA)Commands:$(RESET)\n"
		@printf "  $(BLUE)build           $(RESET)Compile the project\n"
		@printf "  $(BLUE)check           $(RESET)Check the project w/ Valgrind\n"
		@printf "  $(BLUE)clean           $(RESET)Clean the target\n"
		@printf "  $(BLUE)help            $(RESET)Print help\n"
		@printf "  $(BLUE)run             $(RESET)Run the project\n"
		@printf "  $(BLUE)test            $(RESET)Run tests\n"

$(FULL_TARGET): $(SRC_FILES)
	@printf "$(BLUE)  Compiling $(RESET)($(TARGET)) $(UNDERLINE)$(SRC_DIR)/*$(RESET)\n"
	@mkdir -p $(TARGET_DIR)
	@start_time=$$(date +%s.%N); \
	if ! gcc $(CFLAGS) $(DEBUG_INFO) $(SRC_FILES) -o $(TARGET_DIR)/$(TARGET); then \
		printf "$(RED)Compilation failed$(RESET)\n"; \
		rm -f $(FULL_TARGET); \
	else \
		end_time=$$(date +%s.%N); \
		elapsed_time=$$(echo "$$end_time - $$start_time" | bc); \
		printf "$(BLUE)   Finished $(RESET)$(UNDERLINE)$(FULL_TARGET)$(RESET) in %.2f seconds\n" $$elapsed_time; \
	fi
	
.PHONY: build
build: $(FULL_TARGET)

.PHONY: run
run: $(FULL_TARGET)
	@if [ -f "$(FULL_TARGET)" ]; then \
		printf "$(BLUE)    Running $(RESET)$(UNDERLINE)$(FULL_TARGET)$(RESET)\n"; \
		$(FULL_TARGET); \
	fi

.PHONY: check
check: $(FULL_TARGET)
	@if [ -f "$(FULL_TARGET)" ]; then \
		# Check if valgrind is installed \
		if ! command -v valgrind > /dev/null 2>&1; then \
			printf "$(RED)Valgrind is not installed. Please install Valgrind to perform memory checks.$(RESET)\n"; \
		else \
			printf "$(BLUE)    Running $(RESET)valgrind ($(TARGET))\n"; \
			valgrind --log-file="$(TARGET_DIR)/check.valgrind" --leak-check=full --show-leak-kinds=all $(FULL_TARGET); \
			printf "$(BLUE)   Finished $(RESET)$(UNDERLINE)$(TARGET_DIR)/check.valgrind$(RESET)\n"; \
		fi; \
		# Check if cppcheck is installed \
		if ! command -v cppcheck > /dev/null 2>&1; then \
			printf "$(RED)cppcheck is not installed. Please install cppcheck to perform static analysis.$(RESET)\n"; \
		else \
			printf "$(BLUE)    Running $(RESET)cppcheck\n"; \
			cppcheck --enable=all --suppress=unusedFunction --suppress=missingIncludeSystem --inconclusive --force $(SRC_DIR); \
		fi; \
	fi

.PHONY: test
test:
	@printf "$(BLUE)    Running $(RESET)tests in $(UNDERLINE)$(TESTS_DIR)/$(RESET)\n"
	@mkdir -p $(TARGET_DIR)/tests
	
	@for test_file in $(wildcard $(TESTS_DIR)/*.c); do \
		test_name=$$(basename $$test_file .c); \
		output_file=$(TARGET_DIR)/tests/$$test_name; \
		printf "$(BLUE)  Compiling $(RESET)$(UNDERLINE)$$test_file$(RESET)\n"; \
		if gcc $(CFLAGS) $(DEBUG_INFO) $$test_file -o $$output_file; then \
			printf "$(BLUE)    Running $(RESET)$(UNDERLINE)$$output_file$(RESET)\n"; \
			$$output_file; \
		else \
			printf "$(RED)  Compilation failed for test $(RESET)$(UNDERLINE)$$test_file$(RESET)\n"; \
		fi; \
	done

.PHONY: clean
clean:
	@printf "$(BLUE)   Cleaning $(RESET)$(UNDERLINE)$(TARGET_DIR)$(RESET)\n"
	@rm -rf $(TARGET_DIR)
