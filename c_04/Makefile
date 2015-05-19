# -*- tab-width: 4 -*-

SOURCE	:= $(sort $(wildcard *.c) $(wildcard *.cpp))
EXECUTE	:= $(patsubst %.cpp,%.exe,$(patsubst %.c,%.exe,$(SOURCE)))

CC			:= clang
CXX			:= clang++
CFLAGS		:= -Wall -std=c99
CXXFLAGS	:= -Wall -std=c++98

%.exe : %.c $(wildcard *.h)
	# create: $@
	$(CC) $(CFLAGS) $< -o $@

%.exe : %.cpp $(wildcard *.hpp)
	# create: $@
	$(CXX) $(CXXFLAGS) $< -o $@

check: $(EXECUTE)
	@for e in $^ ; do \
		if [ -e $${e} ]; then \
			printf "# execute: $${e}\n"; \
			./$${e}; \
		fi \
	done

clean:
	rm -f $(EXECUTE)
	find . -name '*~' -print0 | xargs -0 rm -f

.PHONY: check clean
