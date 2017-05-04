#pragma once

#include "goofit/DataSet.h"

#include <map>
#include <vector>
#include <initializer_list>

class UnbinnedDataSet : public DataSet {
    // Class for unbinned datasets.

public:
    using DataSet::addEvent;
    
    UnbinnedDataSet(Variable* var, std::string n = "");
    UnbinnedDataSet(std::vector<Variable*>& vars, std::string n = "");
    UnbinnedDataSet(std::set<Variable*>& vars, std::string n = "");
    UnbinnedDataSet(std::initializer_list<Variable*> vars, std::string n="");
    
    virtual ~UnbinnedDataSet();

    virtual void addEvent() override;
    
    /// This is an stand-in for the similarly named BinnedDataSet weighted events TODO: rename
    size_t getNumEvents() const {return numEvents();}
    
    /// Get the value at a specific variable and event number
    fptype getValue(Variable* var, size_t idx) const;
    
    /// Set all the variables to the current event values
    void loadEvent(size_t idx);
    
    /// Set all entries to a constant value (note: this is kind of ugly)
    void setValueForAllEvents(Variable* var);

private:
    std::vector<std::vector<fptype>> data;

};
