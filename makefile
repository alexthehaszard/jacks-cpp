build:
	clang++ -std=c++26 -Wall -Wextra -Werror -Wno-missing-braces main.cpp -o jacks

debug:
	clang++ -std=c++26 -g -Wall -Wextra -Werror -Wno-missing-braces main.cpp -o jacks

test:
	clang++ -std=c++26 -Wall -Wextra -Werror -Wno-missing-braces tests.cpp -o tests && ./tests