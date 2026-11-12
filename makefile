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