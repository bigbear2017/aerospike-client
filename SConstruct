Src = Split(Glob('./src/main/*.cpp'))


Libs = [File('lib/libaerospike.a')]

Libs += Split('ssl crypto pthread rt dl z')

IncludePath = Split('./src/include')

LibPath = Split('./lib/')

CCFlags = Split('-g -O2 -Wall')

Program(target='test_write', source=Split('./src/main/test_write.cc'), LIBS=Libs, LIBPATH=LibPath, CPPPATH=IncludePath, CCFLAGS=CCFlags)
