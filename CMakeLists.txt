cmake_minimum_required(VERSION 3.10) # Проверка версии CMake.
								# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.
project(MyProject VERSION 1.0)
if (UNIX)
    message("Builf for UNIX")
	message("source ${CMAKE_SOURCE_DIR}")
endif (UNIX)

# Определение стандартов C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указываем директорию с заголовочными файлами, чтобы они были видны во всех компонентах проекта
include_directories(${CMAKE_SOURCE_DIR}/include)

# Автоматически собираем все файлы с расширением .cpp в папке src
file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Создаем исполняемый файл, добавляя все .cpp файлы
add_executable(MyApp ${SRC_FILES})

# Поиск библиотеки Eigen
# Включаем директорию с Eigen
include_directories(${CMAKE_SOURCE_DIR}/external/eigen)
include_directories(${CMAKE_SOURCE_DIR}/external/spectra/include/Spectra)

# Создаем библиотеку из файлов foo.cpp и foo.h
# add_library(foo src/foo.cpp)
# add_library(foo2 src/foo2.cpp)

# target_include_directories(foo2 PUBLIC CMAKE_SOURCE_DIR}/include)


# Связываем сновное приложение с библиотекой foo
# Добавляем основной исполняемый файл
# target_link_libraries(MyProject PRIVATE foo)

# target_link_libraries(MyProject PRIVATE foo2)

