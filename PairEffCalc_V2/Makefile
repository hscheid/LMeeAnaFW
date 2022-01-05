CXX = g++
# CXX = clang++

# If script runs on own pc, check if you have an c++11 compliant compiler

# DEBUG MODE
# CXXFLAGS = -ggdb -Wall -Werror -Wextra -std=c++11 -I`root-config --incdir`
# CXXFLAGS = -ggdb -Wall -Werror -Wextra -I`root-config --incdir`

# RELEASE MODE
# CXXFLAGS = -O2 -std=c++11 -I`root-config --incdir`
CXXFLAGS = -Og -ggdb -I`root-config --incdir` -std=c++14

# LINKER FLAGS
LDFLAGS = `root-config --libs` -lEG

main.exe: obj/main.o obj/PairEfficiency.o obj/LmHelper.o obj/LmRebinner.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS)

obj/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/PairEfficiency.o: src/PairEfficiency.cpp src/PairEfficiency.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/LmHelper.o: ../PlottingFW/src/LmHelper.cpp ../PlottingFW/src/LmHelper.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/LmRebinner.o: ../PlottingFW/src/LmRebinner.cpp ../PlottingFW/src/LmRebinner.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm obj/*.o
	rm main.exe
