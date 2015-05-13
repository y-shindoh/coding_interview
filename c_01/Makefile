# -*- tab-width: 4 -*-

SOURCE	:= $(sort $(wildcard *.cpp))
EXECUTE	:= $(patsubst %.cpp,%.exe,$(SOURCE))

CXX		:= clang++
CFLAGS	:= -Wall

%.exe : %.cpp
	# create: $@
	$(CXX) $(CFLAGS) $< -o $@

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
