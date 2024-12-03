#include <map>
#include <string>
#include <vector>
#include <iostream>
using namespace std; 

class MapIncident {

private:
public:
    int cost; 
    string disasterType; 
    string date; 
    string damageCategory; 
    MapIncident(int _cost, string _disasterType, string _date, string _damageCategory)
    {
        cost = _cost; 
        disasterType = _disasterType; 
        date = _date; 
        damageCategory = _damageCategory; 
    }

    void printIncident()
    {
        cout << "Type: " << disasterType << "Date: " << date << "Damage Category: " << damageCategory << "Cost: " << cost; 
    }

    bool operator<(const MapIncident& other) const {
        return cost < other.cost; // Compare by cost
    }


};
