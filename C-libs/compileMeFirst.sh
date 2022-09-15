#!/bin/bash
# [Multi-Platform] This code requires gcc with openMP!
# Please check the available documentation to correctly configure and run the compilation
# Default configuration: UNIX OS (LINUX, MAX) -- Comment/Uncomment lines (12,13) and (23,24) for WINDOWS OS

# Cleaning-up the folder from existing compiled files (*.o)
for i in *.o; do
	rm $i
done

# Cleaning-up the folder from existing Shared Libraries (*.so, *.dll) 
rm *.so # << Comment/Uncomment here for: Windows/Unix (Linux and Mac) OS
# rm *.dll # << Uncomment/Comment here for: Windows/Unix (Linux and Mac) OS

# Compiling the software
# Set the gcc version (e.g. gcc-6 or gcc-10) correctly configured with OpenMP
# e.g. replace 'gcc' with '/mySW/.../bin/gcc' in case gcc is not the pre-defined compiler 
for i in *.c; do
    gcc -c -Wall -Werror -fpic -fopenmp $i
done

# Building the Shared Library
gcc -fopenmp -shared -o libmpMuelMat.so *.o ## << Comment/Uncomment here for: Windows/Unix (Linux and Mac) OS
# gcc -fopenmp -shared -o libmpMuelMat.dll *.o ## << Uncomment/Comment here for: Windows/Unix (Linux and Mac) OS

# Remember to add the gcc compiler shared libraries to the PATHS of the System! 
