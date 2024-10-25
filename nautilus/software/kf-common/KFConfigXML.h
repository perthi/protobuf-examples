

#include <map>


#include <string>
using std::string;

#include <memory>

struct KFEntityDevice;
struct KFEntityHMI;


struct KFConfigXML
{
    std::map<string, std::shared_ptr< KFEntityDevice > >  fEntitiesDevices;
    std::map<string, std::shared_ptr< KFEntityHMI > >  fEntitiesHMI;    
};
