#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include "gitint.h"

using namespace std;

/*********************** Messages to use for errors ***************************/
const std::string INVALID_COMMAND = "Invalid command";
const std::string INVALID_OPTION = "Invalid option";
const std::string INVALID_COMMIT_NUMBER = "Invalid commit number";
const std::string LOG_COMMIT_STARTER = "Commit: ";




// Class implementation

GitInt::GitInt() {

    map<string,int> temp;
    temp.insert(make_pair("",0));
    temp.insert(make_pair("",0));
    CommitObj dummy("dummy",temp, 0);
    CommitIdx dummyIdx = 0;
    commits_.insert(make_pair(dummyIdx,dummy));
    latestComm = 0;
    head_ = 0;
}

void GitInt::print_menu() const
{
    cout << "Menu:                          " << endl;
    cout << "===============================" << endl;
    cout << "create   filename int-value    " << endl;
    cout << "edit     filename int-value    " << endl;
    cout << "display  (filename)            " << endl;
    cout << "display  commit-num            " << endl;
    cout << "add      file1 (file2 ...)     " << endl;
    cout << "commit   \"log-message\"       " << endl;
    cout << "tag      (-a tag-name)         " << endl;
    cout << "log                            " << endl;
    cout << "checkout commit-num/tag-name   " << endl;
    cout << "diff                           " << endl;
    cout << "diff     commit                " << endl;
    cout << "diff     commit-n commit-m     " << endl;
}


bool GitInt::process_command(std::string cmd_line)
{
    bool quit = false;
    std::stringstream ss(cmd_line);
    std::string cmd;
    ss >> cmd;
    if (ss.fail()) throw std::runtime_error(INVALID_COMMAND);


    //for each command given to us (if valid), each command will have its exceptions that need to be
    //caught. This function executes each function according to the requirments it meets
    if (cmd == "quit") {
        quit = true;
    } else if (cmd == "create") {
        string filename;
        string value;
        int value1;
        ss >> filename;
        ss >> value;
        if(filename == "" || value == ""){
            throw std::runtime_error("Please enter filename/integer");
        } else if(files_.find(filename) != files_.end()) {
            throw invalid_argument("File already exists");
        } else {
            stringstream s1(value);
            s1 >> value1;
            create(filename, value1);
        }
    } else if(cmd == "edit") {
        string filename;
        string value;
        int value1;
        ss >> filename;
        ss >> value;
        if(filename == "" || value == ""){
            throw std::runtime_error("Please enter filename/integer");
        } else if(files_.find(filename) == files_.end()) {
            throw invalid_argument("File does not exist");
        } else {
            stringstream s1(value);
            s1 >> value1;
            edit(filename, value1);
        }
    } else if(cmd == "display") {
        string filename;
        ss >> filename;

        if(filename == "") {
            display_all();
        } else if(filename[0] > '0' && filename[0] <= '9') {
            stringstream s(filename);
            CommitIdx x = 0;
            s >> x;
                //does this work?????
                if(commits_.find(x) == commits_.end()) {
                    throw invalid_argument("Commit does not exist");
                } else {
                    display_commit(x);
                }
        } else {
            if(files_.find(filename) == files_.end()) {
                throw invalid_argument("File does not exist");
            } else {
                display(filename);
            }
        }
    } else if(cmd == "add") {
        string filename;
        ss >> filename;

        while(!(ss.fail())) {
            if(files_.find(filename) == files_.end()) {
                throw invalid_argument("File does not exist");
            } else {
                add(filename);
                ss >> filename;
            }
        }
    } else if(cmd == "commit") {
        char trash;
        char character;
        string message = "";
        ss >> trash;

        if(trash == '\"') {
            ss >> character;
            ss >> noskipws;
            while(character != '\"' || ss.fail()) {
                message += character;
                ss >> character;
                if(message.size() > 100) {
                    throw std::runtime_error("Please enter message enclosed in quotes");
                }
            }
        } else {
            throw std::runtime_error("Please enter message enclosed in quotes");
        }
        if(message != "") {
            commit(message);
        } else {
            throw std::runtime_error("Please enter message enclosed in quotes");
        }
    } else if(cmd == "tag") {
        string a = "";
        string tagName;
        ss >> a;
        ss >> tagName;

        if(a == "-a") {
            if(tagName != "") {
                create_tag(tagName, head_);
            } else {
                throw invalid_argument("Please enter a tag-name");
            }
        } else if(a == "") {
            tags();
        } else if(a != "-a") {
            throw std::runtime_error("Please enter -a before message");
        } else if(tagName == "") {
            throw std::runtime_error("Please enter message after -a");
        } 
    } else if(cmd == "log") {
        log();
    } else if(cmd == "checkout") {
        string tagName;
        ss >> tagName;
        if(tagName == "") {
            throw std::runtime_error("Please enter tag-name");
        } else if(tagName[0] > '0' && tagName[0] <= '9') {
            stringstream s(tagName);
            CommitIdx x = 0;
            s >> x;
            if(commits_.find(x) != commits_.end()) {
                checkout(x);
            } else {
                throw invalid_argument(INVALID_OPTION);
            }
        } else {
            if(tags_.find(tagName) != tags_.end()) {
                checkout(tagName);
            } else {
                throw invalid_argument(INVALID_OPTION);
            }
        }
    } else if(cmd == "diff") {
        string num1, num2;
        CommitIdx diff1, diff2;
        ss >> num1 >> num2;

        if(num1 < num2) {
            throw invalid_argument("from can't be less that to");
        } else if(num1 == "") {
            diff(head_);
            
        } else if(num2 == "") {
            stringstream s(num1);
            diff1 = 0;
            s >> diff1;
            if(commits_.find(diff1) == commits_.end()) {
                    throw invalid_argument("Commit does not exist");
            } else  {
                diff(diff1);
            }
        } else {
            stringstream s(num1);
            diff1 = 0;
            s >> diff1;
            stringstream s1(num2);
            s1 >> diff2;
            if(commits_.find(diff1) == commits_.end() || commits_.find(diff2) == commits_.end()) {
                throw invalid_argument("Commit does not exist");
            }
            diff(diff1, diff2);
        }

    } else {
        throw invalid_argument(INVALID_COMMAND);
    }
    
    return quit;
}

void GitInt::display_commit(CommitIdx commit) const
{

    if ( false == valid_commit(commit) ) {
        throw std::invalid_argument(INVALID_COMMIT_NUMBER);
    }
    map<CommitIdx, CommitObj>::const_iterator it = commits_.find(commit);
    display_helper(it->second.diffs_);
}


void GitInt::display_helper(const std::map<std::string, int>& dat) const
{

    for (std::map<std::string, int>::const_iterator cit = dat.begin();
            cit != dat.end();
            ++cit) {
        std::cout << cit->first << " : " << cit->second << std::endl;
    }
}


void GitInt::log_helper(CommitIdx commit_num, const std::string& log_message) const
{
    std::cout << LOG_COMMIT_STARTER << commit_num << std::endl;
    std::cout << log_message << std::endl << std::endl;

}

void GitInt::create(const string& filename, int value) {
    //adds to files map
    files_.insert(make_pair(filename, value));
}


void GitInt::edit(const string& filename, int value) {
    map<string, int>::iterator it = files_.find(filename);

    //edits file name if found
    if(it != files_.end()) {
        it->second = value;
    }
}

void GitInt::display(const string& filename) const {
    map<string, int>::const_iterator it = files_.find(filename);

    //displays filename if found
    if(it != files_.end()) {
        cout << it->first << " : " << it->second << endl;
    }
}

void GitInt::display_all() const {
    map<string, int>::const_iterator it;
    //goes through each file
    for(it = files_.begin(); it != files_.end(); it++) {
        //don't display files that are 0
        if (it->second != 0) {
            cout << it->first << " : " << it->second << endl;
        }
    }
}

void GitInt::add(string filename) {
    map<string,int>::iterator it = files_.find(filename);

    //adds file to set if found
    if(it != files_.end()) {
        add_.insert(it->first);
    }
}


void GitInt::commit(string message) {

    map<string, int> diffs;
    set<string>::iterator it;
    map<CommitIdx, CommitObj>::iterator it2;

    //goes through each file in add
    for(it = add_.begin(); it != add_.end(); it++) {
        int totalDiff = 0;
        it2 = commits_.find(head_); //goes to the current commit we are on
        CommitIdx parent = head_;

        //while not equal to the dummy variable
        while(parent != 0) {
            //if commits is found
            if(it2 != commits_.end()) {
                //if not equal to the dummy commit which should be ignored
                if(it2->second.msg_ != "dummy" || it2 != commits_.end()) {
                    //if add file is found in the diffs of our commit object
                    if(it2->second.diffs_.find(*it) != it2->second.diffs_.end()) {
                        //gets total difference to give us our number
                        totalDiff += it2->second.diffs_.find(*it)->second;
                    }
                }

                parent = commits_.find(parent)->second.parent_;
                it2 = commits_.find(parent);
            }
        }
        diffs.insert(make_pair(*it, (files_.find(*it)->second - totalDiff)));
    }







    latestComm++;
    CommitObj temp(message, diffs, head_);
    commits_.insert(make_pair(latestComm, temp));
    add_.clear();
    head_ = latestComm;
}

void GitInt::create_tag(const std::string& tagname, CommitIdx commit) {

    tags_.insert(make_pair(tagname, commit));
    displayTags_.push_back(tagname);

}

void GitInt::tags() const {

    //for each tag in our vector
    for(int i = displayTags_.size() - 1; i >= 0; i--) {
        cout << displayTags_[i] << endl;
    }
}

bool GitInt::checkout(CommitIdx commitIndex) {

    map<string, int>::iterator it;
    map<CommitIdx, CommitObj>::iterator it2;


    //same logic as commit function for each of these statement
    for(it = files_.begin(); it != files_.end(); it++) {
        int totalDiff = 0;
        it2 = commits_.find(commitIndex);
       // bool run = true;
        CommitIdx parent = commitIndex;
        
        while(parent != 0) {
            if(it2 != commits_.end()) {
                if(it2->second.msg_ != "dummy" || it2 != commits_.end()) {
                    if(it2->second.diffs_.find(it->first) != it2->second.diffs_.end()) {
                        totalDiff += it2->second.diffs_.find(it->first)->second;

                    }
                }

                parent = commits_.find(parent)->second.parent_;
                it2 = commits_.find(parent);
            }
        }
        it->second = totalDiff;
    }
    head_ = commitIndex; //our current commit is the one checkout

    return true;
}

bool GitInt::checkout(std::string tag) {

    //find commit number of tag
    if(tags_.find(tag) != tags_.end()) {
        checkout(tags_.find(tag)->second);
    }
    return true;
}


void GitInt::log() const {

    CommitIdx parent = head_;

    //while not equal to the dummy
    while(parent != 0) {
        log_helper(parent, commits_.find(parent)->second.msg_);
        parent = commits_.find(parent)->second.parent_;

    }

}

void GitInt::diff(CommitIdx to) const {

    map<string, int>::const_iterator it;
    map<CommitIdx, CommitObj>::const_iterator it2;

    //same logic as commit and checkout functions
    for(it = files_.begin(); it != files_.end(); it++) {
        int totalDiff = 0;
        it2 = commits_.find(to); //starts from the index given
        CommitIdx parent = to;

        while(parent != 0) {
            if(it2 != commits_.end()) {
                if(it2->second.msg_ != "dummy" || it2 != commits_.end()) {
                    if(it2->second.diffs_.find(it->first) != it2->second.diffs_.end()) {
                        totalDiff += it2->second.diffs_.find(it->first)->second;
                    }
                }

                parent = commits_.find(parent)->second.parent_;
                it2 = commits_.find(parent);
            }
        }
       
        //dont display diffs of 0
        if((it->second - totalDiff) != 0) {
            cout << it->first << " : " << (it->second - totalDiff) << endl;
        }
       
    }

}


void GitInt::diff(CommitIdx from, CommitIdx to) const {

    map<string, int>::const_iterator it;
    map<CommitIdx, CommitObj>::const_iterator it2;
    map<CommitIdx, CommitObj>::const_iterator it3;


    //same logic inside as commits and checkout
    for(it = files_.begin(); it != files_.end(); it++) {
        int fromDiff = 0;
        it2 = commits_.find(from);
        CommitIdx parent = from;

        while(parent != 0) {
            if(it2 != commits_.end()) {
                if(it2->second.msg_ != "dummy" || it2 != commits_.end()) {
                    if(it2->second.diffs_.find(it->first) != it2->second.diffs_.end()) {
                        fromDiff += it2->second.diffs_.find(it->first)->second;
                    }
                }

                parent = commits_.find(parent)->second.parent_;
                it2 = commits_.find(parent);
            }
        }
        

        it3 = commits_.find(to);
        parent = to;
        int toDiff = 0;

        while(parent != 0) {
            if(it3 != commits_.end()) {
                if(it3->second.msg_ != "dummy" || it3 != commits_.end()) {
                    if(it3->second.diffs_.find(it->first) != it3->second.diffs_.end()) {
                        toDiff += it3->second.diffs_.find(it->first)->second;
                    }
                }

                parent = commits_.find(parent)->second.parent_;
                it3 = commits_.find(parent);
            }
        }

        //dont display diffs of 0
        if((fromDiff - toDiff) != 0) {
            cout << it->first << " : " << (fromDiff - toDiff) << endl;
        }
       
    }
}

bool GitInt::valid_commit(CommitIdx commit) const {
    if (commit >= 1 && commit <= latestComm) {
        return true;
    }
    return false;
}