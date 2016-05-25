.PHONY: all

format:
	@astyle --options=.astylerc src/*/*.cpp src/*/*.hpp
