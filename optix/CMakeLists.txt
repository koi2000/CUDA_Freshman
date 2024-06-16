if(POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)
if (POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()

project(optix8course VERSION 1.0.1)

cmake_minimum_required(VERSION 2.8)
if (NOT WIN32)
# visual studio doesn't like these (not need them):
set (CMAKE_CXX_FLAGS "--std=c++11")
set (CUDA_PROPAGATE_HOST_FLAGS ON)
endif()

set(gdt_dir ${PROJECT_SOURCE_DIR}/common/gdt/)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${gdt_dir}/cmake/")
include(${gdt_dir}/cmake/configure_build_type.cmake)
include(${gdt_dir}/cmake/configure_optix.cmake)

mark_as_advanced(CUDA_SDK_ROOT_DIR)

# ------------------------------------------------------------------
# import gdt submodule
# ------------------------------------------------------------------
include_directories(${gdt_dir})
add_subdirectory(${gdt_dir} EXCLUDE_FROM_ALL)

# ------------------------------------------------------------------
# build glfw
# ------------------------------------------------------------------
set(OpenGL_GL_PREFERENCE LEGACY)
if (WIN32)
#  set(glfw_dir ${PROJECT_SOURCE_DIR}/submodules/glfw/)
  set(glfw_dir ${PROJECT_SOURCE_DIR}/common/3rdParty/glfw/)
  include_directories(${glfw_dir}/include)
  add_subdirectory(${glfw_dir} EXCLUDE_FROM_ALL)
else()
  find_package(glfw3 REQUIRED)
endif()
include_directories(common)
add_subdirectory(common/glfWindow EXCLUDE_FROM_ALL)


# ------------------------------------------------------------------
# and final build rules for the project
# ------------------------------------------------------------------

set(optix_LIBRARY "")

# a first, simple, hello-world applicaion that creates a context, and
# says hello...
add_subdirectory(example01_helloOptix)

# the first example that sets up an entire optix 7 pipeline, renders a
# test image, and saves that in a png file.
add_subdirectory(example02_pipelineAndRayGen)

# the same rendering example, but in a glfwindow with continuous
# rendering
add_subdirectory(example03_inGLFWindow)

add_subdirectory(example04_firstTriangleMesh)
add_subdirectory(example05_firstSBTData)
add_subdirectory(example06_multipleObjects)
add_subdirectory(example07_firstRealModel)
add_subdirectory(example08_addingTextures)
add_subdirectory(example09_shadowRays)
add_subdirectory(example10_softShadows)
add_subdirectory(example11_denoiseColorOnly)
add_subdirectory(example12_denoiseSeparateChannels)