//=========================================
//Includes
//
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>

#include <aerospike/aerospike.h>
#include <aerospike/aerospike_key.h>
#include <aerospike/as_error.h>
#include <aerospike/as_record.h>
#include <aerospike/as_status.h>

using namespace std;

#define MAX_HOST_SIZE 1024
#define MAX_KEY_STR_SIZE 1024

char aeroNameSpace[MAX_NAMESPACE_SIZE];
char aeroSet[MAX_SET_SIZE];
char aeroHost[MAX_HOST_SIZE];
int aeroPort;

void connectToAerospike( aerospike & as ); 

int main( int argc, char * argc [] ) { 
    aerospike as;
    connectToAerospike( &as );
}

void connectToAerospike( aerospike & tas ) {
    as_config config;
    as_config_init(&config);

    if( !as_config_add_hosts(&config, aeroHost, aeroPort) ) {
        cout << "Invalid host(s) : " << aeroHost << " and port : " << port << endl;
    }

    aerospike_init( as, &config );
    
    as_error err;

    if ( aerospike_connect(tas, &err ) != AEROSPIKE_ok ) {
        cout << "aerospike_connect() returned " << err.code << "-" << err.message << endl;
        aerospike_destroy( tas );
        exit( -1 );
    }

}
