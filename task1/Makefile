all:
	clang++ -std=c++11 -isystem /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1 main.cpp -o main
	./main
	python3 make_plot.py
clean:
	rm -r data.txt main report.aux report.log report.out report.toc report.synctex.gz report.fls report.fdb_latexmk 