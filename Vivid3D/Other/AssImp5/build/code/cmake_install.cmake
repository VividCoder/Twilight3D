# Install script for directory: C:/Projects/Vivid3D/Other/AssImp5/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Assimp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Projects/Vivid3D/Other/AssImp5/build/code/Debug/assimp-vc142-mtd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Projects/Vivid3D/Other/AssImp5/build/code/Release/assimp-vc142-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Projects/Vivid3D/Other/AssImp5/build/code/MinSizeRel/assimp-vc142-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Projects/Vivid3D/Other/AssImp5/build/code/RelWithDebInfo/assimp-vc142-mt.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Projects/Vivid3D/Other/AssImp5/build/code/Debug/assimp-vc142-mtd.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Projects/Vivid3D/Other/AssImp5/build/code/Release/assimp-vc142-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Projects/Vivid3D/Other/AssImp5/build/code/MinSizeRel/assimp-vc142-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Projects/Vivid3D/Other/AssImp5/build/code/RelWithDebInfo/assimp-vc142-mt.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/anim.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/aabb.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/ai_assert.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/camera.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/color4.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/color4.inl"
    "C:/Projects/Vivid3D/Other/AssImp5/build/code/../include/assimp/config.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/defs.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/Defines.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/cfileio.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/light.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/material.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/material.inl"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/matrix3x3.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/matrix3x3.inl"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/matrix4x4.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/matrix4x4.inl"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/mesh.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/pbrmaterial.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/postprocess.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/quaternion.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/quaternion.inl"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/scene.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/metadata.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/texture.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/types.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/vector2.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/vector2.inl"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/vector3.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/vector3.inl"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/version.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/cimport.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/importerdesc.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/Importer.hpp"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/DefaultLogger.hpp"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/ProgressHandler.hpp"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/IOStream.hpp"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/IOSystem.hpp"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/Logger.hpp"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/LogStream.hpp"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/NullLogger.hpp"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/cexport.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/Exporter.hpp"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/DefaultIOStream.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/DefaultIOSystem.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/ZipArchiveIOSystem.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/SceneCombiner.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/fast_atof.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/qnan.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/BaseImporter.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/Hash.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/MemoryIOWrapper.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/ParsingUtils.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/StreamReader.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/StreamWriter.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/StringComparison.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/StringUtils.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/SGSpatialSort.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/GenericProperty.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/SpatialSort.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/SkeletonMeshBuilder.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/SmoothingGroups.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/SmoothingGroups.inl"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/StandardShapes.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/RemoveComments.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/Subdivision.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/Vertex.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/LineSplitter.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/TinyFormatter.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/Profiler.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/LogAux.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/Bitmap.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/XMLTools.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/IOStreamBuffer.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/CreateAnimMesh.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/irrXMLWrapper.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/BlobIOSystem.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/MathFunctions.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/Macros.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/Exceptional.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/ByteSwapper.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/Compiler/pushpack1.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/Compiler/poppack1.h"
    "C:/Projects/Vivid3D/Other/AssImp5/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

