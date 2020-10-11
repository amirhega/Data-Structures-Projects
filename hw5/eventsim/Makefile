all: eventsim

eventsim: eventsim.cpp derived_events.o input_reader.o streetgrid.o
	g++ -g -std=gnu++11 -Wall eventsim.cpp input_reader.o derived_events.o streetgrid.o -o eventsim

derived_events.o: derived_events.cpp derived_events.h streetgrid.h vehicle.h event.h
	g++ -g -std=gnu++11 -Wall -c derived_events.cpp -o derived_events.o	

input_reader.o: input_reader.cpp input_reader.h derived_events.h streetgrid.h
	g++ -g -std=gnu++11 -Wall -c input_reader.cpp -o input_reader.o

streetgrid.o: streetgrid.cpp streetgrid.h event.h vehicle.h derived_events.h
	g++ -g -std=gnu++11 -Wall -c streetgrid.cpp -o 	streetgrid.o

clean:
	rm -f *.o eventsim


