#include <map>
#include <string>
#include <vector>
using namespace std; 

class disasterMap {

private:
    map<pair<string, string>, pair<int, int> >  state_county_string; // used to convert between state/county names and state/county IDs
    map<pair<int, int>, pair<string, string> >  state_county; // first pair: IDs of state and county, second vector: names of state and county
    map<pair <int, int> , vector<vector<int> > >index_to_disaster; // first vector: IDs of state and county, second vector: cost, type, other info for each FEMA grant
public:
    disasterMap(); 

    void addRow(); 
    void sort_index_to_disaster(string county, string state); 
};

