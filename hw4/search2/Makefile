all: search-shell

search-shell: search-shell.cpp searcheng.o searchui.o webpage.o combiners.o util.o txt_parser.o md_parser.o handler.o cmdhandler.o
	g++ -g -std=gnu++11 -Wall search-shell.cpp searcheng.o searchui.o webpage.o combiners.o util.o txt_parser.o md_parser.o handler.o cmdhandler.o -o search-shell

crawl: crawl.cpp util.o txt_parser.o md_parser.o webpage.o searcheng.o
	g++ -g -std=gnu++11 -Wall crawl.cpp util.o txt_parser.o md_parser.o webpage.o searcheng.o -o crawl

searcheng.o: searcheng.cpp searcheng.h webpage.h pageparser.h wpscombiner.h util.h
	g++ -g -std=gnu++11 -Wall -c searcheng.cpp -o searcheng.o

webpage.o: webpage.cpp webpage.h util.h
	g++ -g -std=gnu++11 -Wall -c webpage.cpp -o webpage.o

util.o: util.h util.cpp webpage.h
	g++ -g -std=gnu++11 -Wall -c util.cpp -o util.o

txt_parser.o: txt_parser.cpp txt_parser.h pageparser.h util.h 
	g++ -g -std=gnu++11 -Wall -c txt_parser.cpp -o txt_parser.o

searchui.o: searchui.cpp searchui.h util.h searcheng.h handler.h
	g++ -g -std=gnu++11 -Wall -c searchui.cpp -o searchui.o

md_parser.o: md_parser.cpp md_parser.h pageparser.h util.h
	g++ -g -std=gnu++11 -Wall -c md_parser.cpp -o md_parser.o

handler.o: searcheng.h handler.h handler.cpp
	g++ -g -std=gnu++11 -Wall -c handler.cpp -o handler.o

cmdhandler.o: handler.h searcheng.h cmdhandler.h cmdhandler.cpp util.h combiners.h
	g++ -g -std=gnu++11 -Wall -c cmdhandler.cpp -o cmdhandler.o

combiners.o: searcheng.h combiners.h combiners.cpp wpscombiner.h
	g++ -g -std=gnu++11 -Wall -c combiners.cpp -o combiners.o

clean:
	rm -f *.o crawl search-shell

