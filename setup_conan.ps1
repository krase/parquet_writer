
$env:CONAN_USER_HOME="${env:LIBRARIES_ROOT}\conan_home"

~\.virtualenvs\resimpython\Scripts\Activate.ps1

conan install . -r conan-center --output-folder=build -if=build -oarrow/*:parquet=True

mkdir -p build
cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Release

make && ./parquet_writer 

