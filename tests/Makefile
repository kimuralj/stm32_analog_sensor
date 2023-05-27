create:
	mkdir targets
	cp mock_main.h targets/main.h
	cp ../Core/Src/PotSensor.c targets/PotSensor.c
	cp ../Core/Src/PotSensor.c targets/PotSensor.h
	cp ../Core/Src/Button.c targets/Button.c
	cp ../Core/Src/Button.c targets/Button.h
	cp ../Core/Src/Communication.c targets/Communication.c
	cp ../Core/Src/Communication.c targets/Communication.h
build:
	g++ -o targets/main_test main.cpp tests.cpp hal_mock.cpp targets/PotSensor.c -lgtest -lgtest_main -pthread
clean:
	rm -rf targets
	rm -rf main_test

run:
	./targets/main_test