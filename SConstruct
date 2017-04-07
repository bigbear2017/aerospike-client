Src = Split(Glob('./src/main/*.cpp'))

Libs = Split('aerospike')

IncludePath = Split('./src/include')

LibPath = Split('./lib')

CCFlags = Split('-g -O2 -Wall')

Program(target='test_write', source='./src/main/test_write.cc', LIBS=Libs, LIBPATH=LibPath, CPPPATH=IncludePath, CCFLAGS=CCFlags)
