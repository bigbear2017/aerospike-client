#include "aerospike_client.h"

using namespace std;

int main (char ** argv, int argc) {
    ad::bs::AerospikeClient client;
    client.connectToAerospike("127.0.0.1", 3000, 3000);
    vector<string> values;
    values.push_back("value1");
    values.push_back("value2");
    client.writeRecord("keyStore", "testStore", "test1", values);
    values.clear();
    client.readRecord("keyStore","testStore", "test1", values);
    for(int i =0; i< values.size(); i++ ) {
        cout << values[i] << endl;
    }
    return 0;
}

