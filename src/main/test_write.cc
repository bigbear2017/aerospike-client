//=========================================
//Includes
//
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
#include <sstream>

#include <aerospike/aerospike.h>
#include <aerospike/aerospike_key.h>
#include <aerospike/as_error.h>
#include <aerospike/as_record.h>
#include <aerospike/as_status.h>
#include <aerospike/as_operations.h>
#include <aerospike/as_key.h>
#include <aerospike/as_record_iterator.h>
#include <aerospike/as_config.h>

using namespace std;

#define MAX_HOST_SIZE 1024
#define MAX_KEY_STR_SIZE 1024
#define MAX_SET_SIZE 100
#define MAX_NAMESPACE_SIZE 100

char aeroNameSpace[MAX_NAMESPACE_SIZE] = "keyStore";
char aeroSet[MAX_SET_SIZE] = "testStore";
char aeroHost[MAX_HOST_SIZE] = "127.0.0.1";
char aeroKeyStr[MAX_KEY_STR_SIZE] = "aeroTestKey";
int aeroPort = 3000;
as_key aeroKey;

//void connectToAerospike( aerospike & as ); 
//void dumpRecord( as_record & pRec );
//void initKey( as_key & key );

void initKey( as_key & key, const string & keyValue) {
    as_key_init_str( &aeroKey, aeroNameSpace, aeroSet, keyValue.c_str());
}

void connectToAerospike( aerospike & tas ) {
    as_config config;
    as_config_init(&config);

    if( !as_config_add_hosts(&config, aeroHost, aeroPort) ) {
        cout << "Invalid host(s) : " << aeroHost << " and port : " << aeroPort << endl;
    }

    aerospike_init( &tas, &config );
    
    as_error err;

    if ( aerospike_connect(&tas, &err ) != AEROSPIKE_OK ) {
        cout << "aerospike_connect() returned " << err.code << "-" << err.message << endl;
        aerospike_destroy( &tas );
        exit( -1 );
    }

}

void dumpRecord( const as_record * pRec ) {
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
            char * valAsStr = as_val_tostring( as_bin_get_value( pBin ) );
            cout << "Bin Name : " << as_bin_get_name( pBin) << " Bin Value: " << valAsStr << endl;
            free( valAsStr );
        }
    }

    as_record_iterator_destroy( &iter );
}
int main( int argc, char * argv [] ) { 
    aerospike as;
    connectToAerospike( as ); //first connect to aerospike
    as_error err; 
	
    clock_t start = clock();
    for( int i = 0; i < 100000; i++ ) {
    as_record record; //create record 
    as_record_init( &record, 2 );
    as_record_set_int64( &record, "bin1", 1234 );
    as_record_set_int64( &record, "bin2", 1234 );
    as_record_set_int64( &record, "bin3", 1234 );
    as_record_set_int64( &record, "bin4", 1234 );
    as_record_set_int64( &record, "bin5", 1234 );
    as_record_set_int64( &record, "bin6", 1234 );
    as_record_set_int64( &record, "bin7", 1234 );
    as_record_set_int64( &record, "bin8", 1234 );
    as_record_set_int64( &record, "bin9", 1234 );
    as_record_set_int64( &record, "bin10", 1234 );
    as_record_set_str( &record, "bin11", "bin2-data");
    as_record_set_str( &record, "bin12", "bin2-data");
    as_record_set_str( &record, "bin13", "bin2-data");
    as_record_set_str( &record, "bin14", "bin2-data");
    as_record_set_str( &record, "bin15", "bin2-data");

    //dumpRecord( &record );

    stringstream ss ;
    ss << aeroKeyStr << i;
    
    initKey( aeroKey, ss.str() );

    if( aerospike_key_put( &as, &err, NULL, &aeroKey, &record ) != AEROSPIKE_OK ) {
        cout << "there is some problems, I can not put record into aerospike!" << endl;
        //aerospikeCleanUp(& as);
        exit(-1);
    }

    as_record * pRec = NULL;
    if( aerospike_key_get( &as, &err, NULL, &aeroKey, &pRec ) != AEROSPIKE_OK ) {
        cout << "there is some problems, I can not read record from aerospike!" << endl;
        //aerospikeCleanUp( &as );
        exit( -1 );
    }

    //dumpRecord( pRec );

    as_record_destroy( pRec );
    }
    clock_t end = clock();
    double elapsed = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
    cout << "Time is : " << elapsed << " ms for 10w records" <<endl; 

    return 0;
}

