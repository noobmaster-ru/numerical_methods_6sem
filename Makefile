plot:
	python parse_constants.py
	clang++ -std=c++11 -isystem /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1 main.cpp -o main
	./main
	python make_plot.py
stability:
	clang++ -std=c++11 -isystem /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1 stability.cpp -o main
	./main
	python stability.py