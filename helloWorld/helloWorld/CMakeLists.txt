# CMakeList.txt: helloWorld 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("helloWorld")

# 将源代码添加到此项目的可执行文件。
add_executable (Sales_data "main.cpp" "Sales_data.cpp" "Sales_data.h")
add_executable (helloInTest  "test/helloTest.cpp"   )
add_executable (mapAndset  "mapAndset/main.cpp"   )
add_executable (fileTransform "mapAndset/fileTransform.cpp"   )
add_executable (smartPointer "smartPointer/smartPointer.cpp"   )
add_executable (HasPtr "copyControl/HasPtr/HasPtr.cpp")
add_executable (HasPtrLikeValue "copyControl/HasPtrLikeValue/HasPtrLikeValue.cpp")
add_executable (MessageAndFolder "copyControl/MessageAndFolder/main.cpp")
add_executable (StrVec "copyControl/StrVec/main.cpp")
add_executable (StringSelf "copyControl/String/usingString.cpp" "copyControl/String/String.cpp")
add_executable (Quote  "OOP/usingQuote.cpp")


# TODO: 如有需要，请添加测试并安装目标。
