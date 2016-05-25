.PHONY: all

format:
	@astyle --options=.astylerc src/*/*.cpp src/*/*.hpp

cloc:
	@cloc src/converter  src/data  src/dirtytesting  src/generator  src/genetic  src/net  src/simplega  src/utils
