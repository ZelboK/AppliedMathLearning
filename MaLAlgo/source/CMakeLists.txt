cxx_library(
        TARGET greeting
        FILENAME "greeting.cpp"
)

cxx_binary(
        TARGET main1
        FILENAME "main.cpp"
        LINK_TARGETS greeting
)

cxx_binary(
        TARGET main2
        FILENAMES "main.cpp" "greeting.cpp"
)
