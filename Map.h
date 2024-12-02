#include <map>
#include <string>
#include <vector>
using namespace std; 

class disasterMap {

private:
    vector<pair <pair<int, int>, pair<string, string> > > state_county; 
    map<vector<pair <int, int> >, vector<vector<int> > >index_to_disaster; // first vector: IDs of state and county, second vector: cost, type, other info for each FEMA grant
public:
    disasterMap() = default;

    void addRow(); 
    void 
};

