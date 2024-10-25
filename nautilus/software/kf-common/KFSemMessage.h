

#include <string>

using std::string;

#include <memory>

#include <utilities/GPrintable.h>

class KFSemMessage
{
 public:
    inline KFSemMessage(const string id, const string msg  ) : fDeviceID(id), fProtobufMessage(msg) {};
    
    inline static std::shared_ptr<KFSemMessage> Spawn( const string  id, const string  msg )
    {
        shared_ptr<KFSemMessage> ptr =  std::make_shared<KFSemMessage>(id, msg);
        return ptr;
        //      return nullptr;
    }

    inline  string GetDeviceID() const    { return     fDeviceID;  };
    inline  string GetProtobufMessage() const { return  fProtobufMessage; };
    
 private:
    string fDeviceID = "";
    string fProtobufMessage = "";
    
    
};

