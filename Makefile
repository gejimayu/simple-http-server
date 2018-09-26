run-500b:
	valgrind --tool=massif --time-unit=ms ./server index500b.html

run-20KB:
	valgrind --tool=massif --time-unit=ms ./server index20KB.html