build:
	g++ -std=c++26 -O3 -Wall -Wextra -Werror -Wno-missing-braces \
		main.cpp -o jacks

debug:
	g++ -std=c++26 -g -Wall -Wextra -Werror -Wno-missing-braces \
		main.cpp -o jacks

build-test:
	/opt/local/bin/clang++-mp-23 -std=c++26 -Wall -Wextra -Werror -Wno-missing-braces \
		-fprofile-instr-generate -fcoverage-mapping \
		tests/tests.cpp tests/TestDeckOfCards.cpp tests/TestGameState.cpp \
		-o jacks_tests

test-run:
	make build-test && \
	LLVM_PROFILE_FILE="jacks_tests.profraw" ./jacks_tests &&

test:
	make test-run && \
	llvm-profdata merge -sparse jacks_tests.profraw -o jacks_tests.profdata && \
	llvm-cov show --format=html ./jacks_tests -instr-profile=jacks_tests.profdata \
		-output-dir=./coverage_report -ignore-filename-regex=tests.*

format:
	clang-format -i ./*.hpp ./*.cpp ./**/*.hpp ./**/*.cpp

test-format:
	clang-format --Werror --dry-run ./*.hpp ./*.cpp ./**/*.hpp ./**/*.cpp

tidy:
	clang-tidy --fix -fix-errors -header-filter=.* \
		-checks='bugprone-*,clang-analyzer-*,clang-diagnostic-*,cppcoreguidelines-*,performance-*,readability-*' \
		./main.cpp ./tests/tests.cpp

test-tidy:
	clang-tidy -header-filter=.* \
		-checks='bugprone-*,clang-analyzer-*,clang-diagnostic-*,cppcoreguidelines-*,performance-*,readability-*' \
		--warnings-as-errors='bugprone-*,clang-analyzer-*,clang-diagnostic-*,cppcoreguidelines-*,performance-*,readability-*' \
		./main.cpp ./tests/tests.cpp

