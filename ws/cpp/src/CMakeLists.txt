cmake_minimum_required (VERSION 2.6) 
project (LAB1231_ECG_PRJ) 

add_subdirectory (main)
add_subdirectory (pre)
add_subdirectory (util)
add_subdirectory (array-const)
add_subdirectory (norm)
add_subdirectory (spiht)





find_package( PkgConfig REQUIRED)
pkg_check_modules( gsl REQUIRED gsl )


find_package( PkgConfig REQUIRED)
pkg_check_modules( fftw3 REQUIRED fftw3 )



## add the install targets
#set(CMAKE_INSTALL_PREFIX /home/tor/tmp) # used to determine the root of where the files will be installed.
#install (TARGETS Tutorial DESTINATION bin)
#install (FILES "${LAB1231_ECG_PRJ_BINARY_DIR}/TutorialConfig.h" DESTINATION include)

## Print out all accessible variables in a script, 
## see http://stackoverflow.com/questions/9298278/cmake-print-out-all-accessible-variables-in-a-script
#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
    #message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

