Src = Split(Glob('./src/main/*.cpp'))

Libs = Split('aerospike')

IncludePATH = Split('./src/include')

LibPATH = Split('./lib')

CCFlags = Split('-g -O2 -Wall')

Program(target='test_write', source='./src/main/test_write.cc', LIBS=Libs, LIBPATH=LibPath, CPPPATH=IncludePATH, CCFLAGS=CCFlags)
