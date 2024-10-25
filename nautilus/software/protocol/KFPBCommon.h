



#define PB_ERROR_FUNCTION_CPP \
 inline string GetErrorString() const \
{ \
    return string( fCmd->error_string); \
};\
\
inline void SetErrorString(const string id ) \
 { \
     SetString( fCmd->error_string, sizeof( this->fCmd->error_string), id.c_str() ); \
     fCmd->has_error_string = true; \
 }; 


#define PB_ERROR_FUNCTION_C \
inline  void \
GetErrorString(char *id, const size_t max_size ) const \
{ \
 int n = max_size < sizeof( fCmd->error_string ) ? max_size : sizeof( fCmd->error_string); \
    strncpy( id, (const char *)fCmd->error_string, n ); \
 \
}; \
 \
 \
inline void \
SetErrorString(const char *id, const size_t max_size ) \
{ \
    auto n = max_size < sizeof( fCmd->error_string) ? max_size : sizeof( fCmd->error_string); \
    strncpy( fCmd->error_string, id, n ); \
      fCmd->has_error_string = true; \
};  \
\
inline bool \
HasErrorString() const \
{ \
    return fCmd->has_error_string; \
}; 

