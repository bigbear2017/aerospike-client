#include "aerospike_client.h"

AerospikeClient::AerospikeClient() {
}


bool AerospikeClient::connectToAerospike(const char *ip, int port, int timeout) {
    as_config config;
    as_config_init(&config);

    if( !as_config_add_hosts(&config, ip, port) ) {
        cout << "Invalid host(s) : " << aeroHost << " and port : " << aeroPort << endl;
    }

    aerospike_init( &tas, &config );
    
    as_error err;

    if ( aerospike_connect(&tas, &err ) != AEROSPIKE_OK ) {
        cout << "aerospike_connect() returned " << err.code << "-" << err.message << endl;
        aerospike_destroy( &tas );
        return false;
    }
    return true;
}

bool AerospikeClient::writeRecord(const string & aeroNamespace, const string & aeroSet, const string & key, vector<string> & values ) {
    as_record record; //create record 
    as_record_init( &record, values.size() );
    int size = values.size();
    for( int i = 0; i < size; i++ ) {
        char [MAX_BIN_SIZE] binName = "bin";
        strcpy( binName + sizeof(char) * 3, itoa(i) );
        as_record_set_str( &record, binName, values[i].c_str());
    }
    
    as_key aeroKey;

    as_key_init_str( &aeroKey, aeroNameSpace.c_str(), aeroSet.c_str(), keyValue.c_str());

    if( aerospike_key_put( &tas, &err, NULL, &aeroKey, &record ) != AEROSPIKE_OK ) {
        cout << "there is some problems, I can not put record into aerospike!" << endl;
        //aerospikeCleanUp(& as);
        return false;
    }
    //destroy key?
    return true;
}


bool AerospikeClient::readRecordToVector(const string & aeroNamespace, const string & aeroSet, const string & key, vector<string> & values) {
    as_record * pRec = NULL;
    as_key aeroKey;

    as_key_init_str( &aeroKey, aeroNameSpace.c_str(), aeroSet.c_str(), keyValue.c_str());
    if( aerospike_key_get( &tas, &err, NULL, &aeroKey, &pRec ) != AEROSPIKE_OK ) {
        cout << "there is some problems, I can not read record from aerospike!" << endl;
        //aerospikeCleanUp( &as );
        return false;
    }

        if( ! pRec ) {
        cout << "The pointer is NULL" << endl;
        return;
    }

    if( pRec->key.valuep ) {
        char * keyValueStr = as_val_tostring( pRec -> key.valuep );
        cout << "Key : " << keyValueStr << endl;
        free( keyValueStr );
    }

    uint16_t numBins = as_record_numbins( pRec );

    cout << "Generation :" << pRec->gen << " TTL: " << pRec->ttl << " NumBins: " << numBins << endl;

    as_record_iterator iter;
    as_record_iterator_init( &iter, pRec );
    while( as_record_iterator_has_next( &iter ) ) {
        as_bin * pBin = as_record_iterator_next( &iter );
        if( ! pBin ) {
            cout << "The bin is null " << endl;
        } else {
            string valstr = string( as_val_tostring( as_bin_get_value( pBin ) ) );
            values.push_back( valstr );
            //cout << "Bin Name : " << as_bin_get_name( pBin) << " Bin Value: " << valAsStr << endl;
            //free( valAsStr );
        }
    }

    as_record_iterator_destroy( &iter );

    return true;
}

