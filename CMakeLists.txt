cmake_minimum_required(VERSION 3.26.4)
project(Bookshop_Management_System_Using_C_)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
set(CMAKE_CURRENT_SOURCE_DIR "C:/Users/romak/OneDrive/Desktop/Archive/Programming/Bookshop-Management-System-Using-C-")


include_directories("C:/Program Files/MySQL/MySQL Server 8.0/include")
link_directories("C:/Program Files/MySQL/MySQL Server 8.0/lib")

add_executable(Bookshop_Management_System_Using_C_ main.cpp app.rc
        config.h)
target_link_libraries(Bookshop_Management_System_Using_C_ "C:/Program Files/MySQL/MySQL Server 8.0/lib/libmysql.lib")

install(TARGETS Bookshop_Management_System_Using_C_ RUNTIME DESTINATION .)
install(FILES "C:/Program Files/MySQL/MySQL Server 8.0/lib/libmysql.dll" DESTINATION .)
install(FILES "C:/windows/system32/VCRUNTIME140.DLL" DESTINATION .)
install(FILES "C:/windows/system32/LIBSSL-3-X64.DLL" DESTINATION .)
install(FILES "C:/windows/system32/LIBCRYPTO-3-X64.DLL" DESTINATION .)
install(FILES "C:/windows/system32/VCRUNTIME140_1.DLL" DESTINATION .)
install(FILES "C:/windows/system32/MSVCP140.DLL" DESTINATION .)


set(CPACK_GENERATOR "NSIS")
set(CPACK_PROJECT_NAME "Bookshop_Management_System_Using_C_")
set(CPACK_PACKAGE_NAME "Bookshop_Management_System_Using_C_")
set(CPACK_PACKAGE_VENDOR "Roman Kuryliuk")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "2")
set(CPACK_PACKAGE_VERSION_PATCH "3")

set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)

set(CPACK_NSIS_CREATE_ICONS_EXTRA
        "CreateShortCut '\$DESKTOP\\\\${CPACK_PACKAGE_NAME}.lnk' '\$INSTDIR\\\\${PROJECT_NAME}.exe'"
)

include(CPack)

