
#include <stdio.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "kf.pb.h"


//#include <ostream>


// bool encode_payload(pb_ostream_t *ostream, const pb_field_t *field, void * const  * arg);
// bool decode_payload(pb_istream_t *istream, const pb_field_t *field, void **arg);


typedef struct
{
    int numbers_decoded;
} DecodingState;


int main()
{
    // uint8_t buffer[128];
    // size_t message_length;

    //  bool status;
    
    {
        /*
        SEMCommand message_sendt = SEMCommand_init_zero;
        pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

        float *arr = message_sendt.param_f;
        message_sendt.param_f_count = 5;
        
        /// Setting some arbritrary parameters
        for(int i=0; i <  message_sendt.param_f_count; i++ )
        {
            arr[i] = (i+1)*66.77;
        }
        
        message_sendt.cmd_id = 14;


        /// Encoding the message 
        status = pb_encode(&stream, SEMCommand_fields, &message_sendt);
        
        
        printf("status = %s\n", status == true ? "TRUE" : "FALSE" );
        message_length = stream.bytes_written;
        printf("message length = %ld\n",  message_length );
        
        if (!status)
        {
            printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
            return 1;
        }
        */
    }

    /*************************************
     *** sending over TCP/IP ..... etc *** 
    **************************************/

    /* Decoding the message*/
    {
        /*
        SEMCommand message_rcvd = SEMCommand_init_zero;
        pb_istream_t stream = pb_istream_from_buffer(buffer, message_length);
        status = pb_decode(&stream, SEMCommand_fields, &message_rcvd);
        float *arr_rcvd = message_rcvd.param_f;
        
        if (!status)
        {
            printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
            return 1;
        }
        

        printf("cmd_id =\t%d!\n",  message_rcvd.cmd_id );
        printf("printing recived data\n");
        
        for(int i=0; i <   message_rcvd.param_f_count; i++ )
        {
            printf("arr2[%d] = %f\n", i, arr_rcvd[i]);
            
        }
        */
    }
    return 0;
}





// bool encode_payload(pb_ostream_t *ostream, const pb_field_t *field, void *  const * arg )
// {
//     printf("Encoding callback not implemented:\n");
//     return true;
// }




// bool decode_payload(pb_istream_t *istream, const pb_field_t *field, void **arg)
// {
//     printf("Decoding message");
//     DecodingState *state = (DecodingState*)(*arg);

//     uint32_t value;
//     if (!pb_decode_varint32(istream, &value))
//     {
//         const char * error = PB_GET_ERROR(istream);
//         printf("Protobuf error: %s", error);
//         return false;
//     }

//     printf("Decoded successfully: %d", value);
//     state->numbers_decoded++;
//     return true;
// }









