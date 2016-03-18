add_executable(fdb_microbench
               fdb_bench.cc
               ${PROJECT_SOURCE_DIR}/${FORESTDB_FILE_OPS}
               $<TARGET_OBJECTS:FDB_TOOLS_CORE>
               $<TARGET_OBJECTS:FDB_TOOLS_UTILS>
               $<TARGET_OBJECTS:TEST_STAT_AGG>)

if ((NOT WIN32) AND (NOT APPLE))
    target_link_libraries(fdb_microbench forestdb -lrt)
else ((NOT WIN32) AND (NOT APPLE))
    target_link_libraries(fdb_microbench forestdb)
endif ((NOT WIN32) AND (NOT APPLE))

# add test target
add_test(fdb_microbench fdb_microbench)
ADD_CUSTOM_TARGET(fdbench-micro
    COMMAND ctest
)
