#include <iostream>
#include <fstream>
#include "searcheng.h"
#include "searchui.h"
#include "md_parser.h"
#include "txt_parser.h"
#include "cmdhandler.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Must provide an index file" << endl;
        return 1;
    }

    // Declare the search engine
    SearchEng seng(new TXTParser);

    // ---------------------- [TO BE COMPLETED] -------------------------------
    // Create and register appropriate parsers for .md and .txt files


    // Create the SearchUI object


    // Create and add appropriate Command Handlers to the SearchUI



    // ------------------------------------------------------------------------
    PageParser* txt = new TXTParser();
    seng.register_parser("txt", txt);

    PageParser* md = new MDParser();
    seng.register_parser("md", md);

    SearchUI ui(&seng);
    Handler* quitHandler = new QuitHandler();
    ui.add_handler(quitHandler);
    Handler* printHandler = new PrintHandler();
    ui.add_handler(printHandler);
    Handler* incomingHandler = new IncomingHandler();
    ui.add_handler(incomingHandler);
    Handler* outgoingHandler = new OutgoingHandler();
    ui.add_handler(outgoingHandler);
    Handler* andHandler = new AndHandler();
    ui.add_handler(andHandler);
    Handler* orHandler = new OrHandler();
    ui.add_handler(orHandler);
    Handler* diffHandler = new DiffHandler();
    ui.add_handler(diffHandler);
    Handler* prandHandler = new PRAndHandler();
    ui.add_handler(prandHandler);
    Handler* prorHandler = new PROrHandler();
    ui.add_handler(prorHandler);




    try {
        seng.read_pages_from_index(argv[1]);
    }
    catch (std::exception& e) {
        cout << e.what() << endl;
        return 1;
    }

    bool result;
    if (argc == 2)
    {
        result = ui.run(cin, cout);

    }
    else if (argc == 3) {
        ifstream in_file(argv[2]);
        result = ui.run(in_file, cout);
    }
    else  {
        ifstream in_file(argv[2]);
        ofstream out_file(argv[3]);
        result = ui.run(in_file, out_file);
    }
    // You may add cleanup code here though you likely do not
    // need to.

    return result;
}
