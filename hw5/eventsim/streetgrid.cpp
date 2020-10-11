#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include "streetgrid.h"
#include "derived_events.h"

StreetGrid::StreetGrid(
    const std::vector<unsigned int> rowCapacities,
    const std::vector<unsigned int> colCapacities)
    : rowCapacities_(rowCapacities), colCapacities_(colCapacities)
{
    n = rowCapacities.size();
    m = colCapacities.size();
    expectedVehicles_ = 0;

    // TO BE COMPLETED

    //create number of row segment array and blocks
    rows = new size_t*[n];
    rowBlocks = new bool*[n];
    for(size_t i = 0; i < rowCapacities.size(); i++) {
        rows[i] = new size_t[m-1];
        rowBlocks[i] = new bool[m-1];
    }

    //intialize all to 0 because we start with 0 cars
    for(size_t i = 0; i < rowCapacities.size(); i++) {
        for(size_t j = 0; j < m - 1; j++) {
            rows[i][j] = 0;
            rowBlocks[i][j] = false;
        }
    }

    //create number of row segments
    columns = new size_t*[n-1];
    colBlocks = new bool*[n-1];
    for(size_t i = 0; i < n - 1; i++) {
        columns[i] = new size_t[m];
        colBlocks[i] = new bool[m];
    }

    //intialize all to 0 because we start with 0 cars
    for(size_t i = 0; i < n-1; i++) {
        for(size_t j = 0; j < m; j++) {
            columns[i][j] = 0;
            colBlocks[i][j] = false;
        }
    }


    //create intersection 2D array for ties
    ties = new bool*[n];
    for(size_t i = 0; i < n; i++) {
        ties[i] = new bool[m];
    }

    //intialize every tie to right row direction
    for(size_t i = 0; i < n; i++) {
        for(size_t j = 0; j < m; j++) {
            ties[i][j] = true;
        }
    }





    // Call monitor state to output starting state
    monitorState();
}

StreetGrid::~StreetGrid() {

    for(size_t i = 0; i < n; i++) {
        delete [] rows[i];
        delete [] rowBlocks[i];
        delete [] ties[i];
    }

    delete [] rows;
    rows = 0;
    delete [] rowBlocks;
    delete [] ties;


    for(size_t i = 0; i < n - 1; i++) {
        delete [] columns[i];
        delete [] colBlocks[i];
    }

    delete [] columns;
    delete [] colBlocks;

    grid.clear();

}

size_t StreetGrid::numRows() const
{
    return n;
}
size_t StreetGrid::numCols() const
{
    return m;
}
void StreetGrid::setExpected(size_t expectedVehicles)
{
    expectedVehicles_ = expectedVehicles;
}

void StreetGrid::outputCompletedVehicles(std::ostream& ostr) const
{
    for(auto v : completed_) {
         ostr << ((v.end == 0) ? (v.start) : v.end) << " " << v.id << std::endl;
    }
}

bool StreetGrid::allVehiclesArrived() const
{
    return completed_.size() == expectedVehicles_;
}

void StreetGrid::monitorState()
{
    std::cout << "State: " << std::endl;
    std::cout << std::setw(4) << " ";

    // Print header row with column capacities
    for(size_t cidx = 0; cidx < m; ++cidx) {
        std::cout <<  std::setw(4) << colCapacities_[cidx] << " " <<  std::setw(4) << " ";
    }
    std::cout << std::endl;
    std::cout << "    ";
    for(size_t cidx = 0; cidx < m; ++cidx) {
        std::cout <<  std::setw(4) << "====="  << "=====";
    }
    std::cout << std::endl;

    // Start printing grid data
    for(size_t ridx = 0; ridx < n; ++ridx) {
        // Print row capacity
        std::cout << std::setw(2) << rowCapacities_[ridx] << " |";
        // Print row occupancies
        for(size_t cidx = 0; cidx < m; ++cidx) {
            std::cout << std::setw(4) << "+" << " ";
            if(cidx < m-1) {
                if(isBlocked(ridx,cidx,true)) {
                    std::cout << std::setw(3) << getRowOccupancy(ridx,cidx);
                    std::cout << "B";
                }
                else {
                    std::cout << std::setw(4) << getRowOccupancy(ridx,cidx);
                }
            }
        }
        std::cout << std::endl;
        std::cout <<  "   |";
        // Print column occupancies
        if(ridx < n-1) {
            for(size_t cidx = 0; cidx < m; ++cidx) {
                if(isBlocked(ridx,cidx,false)) {
                    std::cout << std::setw(3) << getColOccupancy(ridx,cidx);
                    std::cout << "B";
                }
                else {
                    std::cout << std::setw(4) << getColOccupancy(ridx,cidx);
                }
                std::cout << std::setw(4) << " " << " " ;
            }
        }
        std::cout << std::endl;

    }
}

size_t StreetGrid::getRowOccupancy(size_t row, size_t col) const
{
    // TO BE COMPLETED
    return rows[row][col];


}

size_t StreetGrid::getColOccupancy(size_t row, size_t col) const
{
    // TO BE COMPLETED
    return columns[row][col];



}

bool StreetGrid::isBlocked(size_t row, size_t col, bool rowDir) const
{
    // TO BE COMPLETED

    //if rowDir == true, asks for row segments
    //if rowDir == false, asks for col segmentw occupancy
    if(rowDir) {
        return rowBlocks[row][col];
    } else {
        return colBlocks[row][col];
    }



}

bool StreetGrid::shouldChooseRow(size_t row, size_t col)
{
    // TO BE COMPLETED
 
    bool chooseRow;

    //checks boundaries
    //if on edge for rows, we cant go down column, must go row
    //if on edge for cols, we cant go right row, must go down column
    if(row >= (n-1)) {
        return true;
    } else if(col >= (m-1)) {
        return false;
    } 

    //if row segment blocked, go down column
    if(isBlocked(row, col, true)) {
        return false;
    }

    //if column segment blocked, go down column
    if(isBlocked(row, col, false)) {
        return true;
    } 

    //check if time for row segment and column segment are equal or which is quick
    if(timeDelay(row, col, true) == timeDelay(row, col, false)) {
        //find last car direction from intersection
        chooseRow = ties[row][col];
        ties[row][col] = !chooseRow;
    } else if(timeDelay(row, col, true) < timeDelay(row, col, false)) {
        chooseRow = true;
    } else {
        chooseRow = false;
    }

    return chooseRow;

}

void StreetGrid::setBlockage(size_t row, size_t col, bool rowDir, bool val)
{
    // TO BE COMPLETED
    // if(row >= (n-1)) {
    //     throw std::logic_error("Can't place blockage because there is no road segment there");
    // } else if(col >= (m-1)) {
    //     throw std::logic_error("Can't place blockage because there is no road segment there");
    // } 

    //if rowDir == true, asks for row segments blockage
    //if rowDir == false, asks for col segmentw blockage
    if(rowDir) {
        rowBlocks[row][col] = val;
        std::cout << "BlockageEvent::process()" << std::endl;
        std::cout << "Blocking row at " << row << "," << col << std::endl << std::endl;
    } else {
        colBlocks[row][col] = val;
        std::cout << "BlockageEvent::process()" << std::endl;
        std::cout << "Blocking col at " << row << "," << col << std::endl << std::endl;
    }



}

EventList StreetGrid::processArrival(const std::string& vehicleID, const TimeStamp& ts)
{
    // TO BE COMPLETED
    if(vehicles_.find(vehicleID) == vehicles_.end()) {
        throw std::logic_error("No Vehicle exists to process arrival");
    } 

    std::vector<Event*> generatedEvents;
    std::map<std::string, Vehicle>::iterator v = vehicles_.find(vehicleID);
    //change vehicles start time at the beginning of the proccess
    v->second.start = ts;


    //if its coming from row or col direction
    if(grid.find(vehicleID)->second) {
        rows[v->second.rowIndex][v->second.colIndex]--;
        v->second.colIndex++;
    } else {
        columns[v->second.rowIndex][v->second.colIndex]--;
        v->second.rowIndex++;
    } 

    //if at finish
    if((v->second.rowIndex == (n - 1)) && (v->second.colIndex == (m - 1))) {
        v->second.end = ts;
        Vehicle temp = (v->second);
        completed_.push_back(temp);
        vehicles_.erase(vehicleID);
    } else {
        //pick route it goes down and update vehicle members
        bool rightRoute = shouldChooseRow(v->second.rowIndex, v->second.colIndex);
        v->second.rowDir = rightRoute;
        v->second.end = v->second.start + timeDelay(v->second.rowIndex, v->second.colIndex, rightRoute);
        grid.find(vehicleID)->second = rightRoute;
        Event *route = new ArrivalEvent(v->second.end, *this, v->second.id);

        
        //add to the correct segment
        if(rightRoute) {
            rows[v->second.rowIndex][v->second.colIndex]++;
        } else {
            columns[v->second.rowIndex][v->second.colIndex]++;
        }

        //create arrival event and add to eventlist
        //ArrivalEvent route(v->second.start, *this, v->second.id);
        generatedEvents.push_back(route);
    }

    return generatedEvents;

}

EventList StreetGrid::addVehicle(const Vehicle& v)
{
    // TO BE COMPLETED

    std::vector<Event*> generatedEvents;
    //checks if vechile already exists
    if(vehicles_.find(v.id) == vehicles_.end()) {
        
        //check if in terminal. if so add to terminal
        if((v.rowIndex == (n - 1)) && (v.colIndex == (m - 1))) {
            completed_.push_back(v);
        } else {
            //create a vehicle
            vehicles_.insert(std::make_pair(v.id, v));

            bool rightRoute = shouldChooseRow(v.rowIndex, v.colIndex);
            grid.insert(make_pair(v.id, rightRoute));

            std::cout << "StreetGrid::AddVehicle - vehicle " << v.id << " now at " << v.rowIndex << "," << v.colIndex << std::endl;
            std::cout << "StreetGrid::AddVehicle - vehicle " << v.id << " will go " 
                      << ((rightRoute) ? "row " : "col ") <<  timeDelay(v.rowIndex, v.colIndex, rightRoute) << std::endl;
            //create arrival event and add to eventlist
            Event *route = new ArrivalEvent((v.start+timeDelay(v.rowIndex, v.colIndex, rightRoute)), *this, v.id);
                    
            //add to the correct segment
            if(rightRoute) {
                rows[v.rowIndex][v.colIndex]++;
            } else {
                columns[v.rowIndex][v.colIndex]++;
            }


            generatedEvents.push_back(route);

        }

    } else {
        throw std::logic_error("Vehicle already exists");
    }

   
    return generatedEvents;
}



//mine
size_t StreetGrid::timeDelay(size_t row, size_t col, bool rowDir) {

    size_t time;
    double temp = SCALE_FACTOR;
    //if rowDir == true, asks for row time delay
    //if rowDir == false, asks for col segment time delay
    if(rowDir) {
        double rowOcc = 1.0 + getRowOccupancy(row,col);
        double rowCap = rowCapacities_[row];
        double tempRow = (rowOcc / rowCap);
        time = (size_t)(std::max(1.0, tempRow) * temp);
    } else {
        double colOcc = 1.0 + getColOccupancy(row,col);
        double colCap = colCapacities_[col];
        double tempCol = colOcc / colCap;
        time = (size_t)(std::max(1.0, tempCol) * temp);
    }

    return time;
}

