#ifndef __BS_AEROSPIKE_CLIENT_H__
#define __BS_AEROSPIKE_CLIENT_H__
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>

#include <aerospike/aerospike.h>
#include <aerospike/aerospike_key.h>
#include <aerospike/as_error.h>
#include <aerospike/as_record.h>
#include <aerospike/as_status.h>
#include <aerospike/as_operations.h>
#include <aerospike/as_key.h>
#include <aerospike/as_record_iterator.h>
#include <aerospike/as_config.h>

#define MAX_HOST_SIZE 1024
#define MAX_KEY_STR_SIZE 1024
#define MAX_SET_SIZE 100
#define MAX_NAMESPACE_SIZE 100
#define MAX_BIN_SIZE 50

namespace ad { namespace bs {

class AerospikeClient {
    public:
        AerospikeClient();
        bool connectToAerospike(const char *ip, int port, int timeout);
        bool writeRecord(const string & aeroNamespace, const string & aeroSet, const string & key, vector<string> & values );//write key and values to record
        bool readRecordToVector(const string & aeroNamespace, const string & aeroSet, const string & key, vector<string> & values); //read all values to values
        ~AerospikeClient();

    private : 
        //void initAsKey(as_key & asKey, const char* aeroSet, const char* key);
        //void initRecord(as_record &  asRecord, vector<string> & values);
        //void dumpRecord(as_record  & asRecord);

    private:
        aerospike tas;
};

} //end bs
} //end ad


#endif 
