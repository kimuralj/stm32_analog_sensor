create:
	mkdir targets
	cp mock_main.h targets/main.h
	cp ../Core/Src/PotSensor.c targets/PotSensor.c
	cp ../Core/Src/PotSensor.h targets/PotSensor.h
	cp ../Core/Src/Button.c targets/Button.c
	cp ../Core/Src/Button.h targets/Button.h
	cp ../Core/Src/Communication.c targets/Communication.c
	cp ../Core/Src/Communication.h targets/Communication.h
build:
	rm -f targets/main_test
	g++ -o targets/main_test main.cpp tests.cpp hal_mock.cpp targets/PotSensor.c targets/Communication.c targets/Button.c -lgtest -lgtest_main -pthread
clean:
	rm -rf targets
run:
	./targets/main_test