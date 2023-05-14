set(source_files experiment.cpp)
set(headers bounds.h constants.h analytical.h integrator.h Distribution.h utility.h)
add_library(Source ${source_files} ${headers})