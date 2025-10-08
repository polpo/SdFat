# SdFat.cmake - Configuration for SdFat library as external dependency

# Create the SdFat library from the submodule
add_library(SdFat STATIC
    # Core source files
    ${CMAKE_CURRENT_LIST_DIR}/src/ExFatLib/ExFatDbg.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ExFatLib/ExFatFile.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ExFatLib/ExFatFilePrint.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ExFatLib/ExFatFileWrite.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ExFatLib/ExFatFormatter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ExFatLib/ExFatName.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ExFatLib/ExFatPartition.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ExFatLib/ExFatVolume.cpp
    
    # FatLib source files
    ${CMAKE_CURRENT_LIST_DIR}/src/FatLib/FatDbg.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/FatLib/FatFile.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/FatLib/FatFileLFN.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/FatLib/FatFilePrint.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/FatLib/FatFileSFN.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/FatLib/FatFormatter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/FatLib/FatName.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/FatLib/FatPartition.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/FatLib/FatVolume.cpp
    
    # FsLib source files
    ${CMAKE_CURRENT_LIST_DIR}/src/FsLib/FsFile.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/FsLib/FsNew.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/FsLib/FsVolume.cpp
    
    # SdCard source files
    ${CMAKE_CURRENT_LIST_DIR}/src/SdCard/SdCardInfo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/SdCard/SdSpiCard/SdSpiCard.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/SdCard/SdSpiCard/SpiDriver/SdSpiChipSelect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/SdCard/PioSdio/PioSdioCard.cpp
    
    # Common source files
    ${CMAKE_CURRENT_LIST_DIR}/src/common/FmtNumber.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/common/FsCache.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/common/FsDateTime.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/common/FsName.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/common/FsStructs.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/common/FsUtf.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/common/PrintBasic.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/common/upcase.cpp
    
    # MinimumSerial
    ${CMAKE_CURRENT_LIST_DIR}/src/MinimumSerial.cpp
    
    # iostream
    ${CMAKE_CURRENT_LIST_DIR}/src/iostream/StdioStream.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/iostream/StreamBaseClass.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/iostream/istream.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/iostream/ostream.cpp
    
    ${CMAKE_CURRENT_LIST_DIR}/src/ArduinoCompat/ArduinoCompat.cpp
)

# Generate PIO header on the fly instead of using previously checked in version
pico_generate_pio_header(SdFat ${CMAKE_CURRENT_LIST_DIR}/src/SdCard/PioSdio/PioSdioCard.pio)

# Include directories
target_include_directories(SdFat PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/src/ArduinoCompat
)

# Platform-specific defines for Raspberry Pi Pico
target_compile_definitions(SdFat PUBLIC
    ENABLE_ARDUINO_FEATURES=0
    ENABLE_ARDUINO_SERIAL=0
    ENABLE_ARDUINO_STRING=0
    USE_RP2040_PICO_BOARD=1
    ARDUINO_ARCH_RP2040=1
    SPI_DRIVER_SELECT=3
    ENABLE_DEDICATED_SPI=1
    USE_BLOCK_DEVICE_INTERFACE=0
)

# Link with Pico SDK libraries
target_link_libraries(SdFat PUBLIC
    pico_stdlib
    hardware_spi
    hardware_pio
    hardware_dma
)

# Set C++ standard
set_target_properties(SdFat PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)

# Suppress warnings for third-party code
target_compile_options(SdFat PRIVATE
    -Wno-unused-parameter
    -Wno-unused-variable
    -Wno-sign-compare
)
