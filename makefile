build:
	g++ -std=c++26 -O3 -Wall -Wextra -Werror -Wno-missing-braces \
		main.cpp -o jacks

debug:
	g++ -std=c++26 -g -Wall -Wextra -Werror -Wno-missing-braces \
		main.cpp -o jacks

test:
	g++ -std=c++26 -Wall -Wextra -Werror -Wno-missing-braces \
		tests/tests.cpp tests/TestDeckOfCards.cpp tests/TestGameState.cpp \
		-o jacks_tests && ./jacks_tests

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