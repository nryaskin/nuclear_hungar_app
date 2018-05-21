#ifndef HANGAR_H
#define HANGAR_H
#include <vector>

namespace model {

using namespace std;
class Hangar{

public:
    void addBox(int x, int y, int z);
    void removeBox(int x, int y, int z);
    constexpr const vector<Box>& boxes() const;
private:
    vector<Box> v_box;

};

inline constexpr const Hangar::vector<Box>& boxes() const {return v_box;}

}

#endif // HANGAR_H
