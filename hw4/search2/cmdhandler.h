#ifndef CMDHANDLER_H
#define CMDHANDLER_H
#include "handler.h"
#include "searcheng.h"
#include "combiners.h"
#include <sstream>

/**
 * Handles the QUIT command - COMPLETED in cmdhandler.cpp
 */
class QuitHandler : public Handler
{
public:
    QuitHandler();
    QuitHandler(Handler* next);

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
};

/*********** OTHER CLASSES WILL NEED TO BE COMPLETED IN cmdhandler.cpp *******/
/***********  You will also need to declare the classes for handling   *******/
/***********          the AND, OR, and DIFF command handlers           *******/

/**
 * Handles the PRINT command
 */
class PrintHandler : public Handler
{
public:
    PrintHandler();
    PrintHandler(Handler* next);

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
};

/**
 * Handles the INCOMING command
 */
class IncomingHandler : public Handler
{
public:
    IncomingHandler();
    IncomingHandler(Handler* next);

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
};

/**
 * Handles the OUTGOING command
 */
class OutgoingHandler : public Handler
{
public:
    OutgoingHandler();
    OutgoingHandler(Handler* next);

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
};

/****************************************************************************/
/* Declare the handler classes for AND, OR, and DIFF here                   */
/****************************************************************************/

class AndHandler : public Handler {
public:
        AndHandler();
        AndHandler(Handler* _next);
protected:
    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
    ANDWebPageSetCombiner combiner_;
};


class OrHandler : public Handler {
public:
        OrHandler();
        OrHandler(Handler* _next);
protected:
    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
    ORWebPageSetCombiner combiner_;
};

class DiffHandler : public Handler {
public:
        DiffHandler();
        DiffHandler(Handler* _next);
protected:
    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
    DiffWebPageSetCombiner combiner_;
};


class PRAndHandler : public Handler {
public:
        PRAndHandler();
        PRAndHandler(Handler* _next);
protected:
    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
    ANDWebPageSetCombiner combiner_;
};

class PROrHandler : public Handler {
public:
        PROrHandler();
        PROrHandler(Handler* _next);
protected:
    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
    ORWebPageSetCombiner combiner_;
};

//comparator that sorts pased on pagerank value
struct LargeToSmall {
    bool operator()(std::pair<WebPage*, double> val, std::pair<WebPage*, double> val1) {
        return val.second >= val1.second;
    }
};

//comparator that sorts based on alphabetical order
struct Alphabetical {
    bool operator()(std::pair<WebPage*, double> val, std::pair<WebPage*, double> val1) {
        std::string one = val.first->filename();
        std::string two = val1.first->filename();
        return one <= two;
    }
};





#endif
