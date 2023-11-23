cmake_minimum_required(VERSION 3.26.4)
project(Bookshop_Management_System_Using_C_)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")


include_directories("C:/Program Files/MySQL/MySQL Server 8.0/include")
link_directories("C:/Program Files/MySQL/MySQL Server 8.0/lib")

add_executable(Bookshop_Management_System_Using_C_ main.cpp)
target_link_libraries(Bookshop_Management_System_Using_C_ "C:/Program Files/MySQL/MySQL Server 8.0/lib/libmysql.lib")

install(TARGETS Bookshop_Management_System_Using_C_ RUNTIME DESTINATION bin)
install(FILES "C:/Program Files/MySQL/MySQL Server 8.0/lib/libmysql.dll" DESTINATION bin)
install(FILES "C:/windows/system32/VCRUNTIME140.DLL" DESTINATION bin)
install(FILES "C:/windows/system32/LIBSSL-3-X64.DLL" DESTINATION bin)
install(FILES "C:/windows/system32/LIBCRYPTO-3-X64.DLL" DESTINATION bin)
install(FILES "C:/windows/system32/VCRUNTIME140_1.DLL" DESTINATION bin)
install(FILES "C:/windows/system32/MSVCP140.DLL" DESTINATION bin)


set(CPACK_PROJECT_NAME "Bookshop_Management_System_Using_C_")
set(CPACK_PROJECT_VERSION "0.0.2")
set(CPACK_GENERATOR "ZIP")
include(CPack)
