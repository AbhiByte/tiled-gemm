cmake_minimum_required(VERSION 3.15)

project(tiled_gemm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GEMM_WARNINGS
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>
)

add_executable(verify_gemm verify_gemm.cpp matrix_math.cpp)
target_compile_options(verify_gemm PRIVATE ${GEMM_WARNINGS})

add_executable(main main.cpp matrix_math.cpp)
target_compile_options(main PRIVATE ${GEMM_WARNINGS})

add_dependencies(main verify_gemm)
add_custom_command(
  TARGET main
  PRE_BUILD
  COMMAND $<TARGET_FILE:verify_gemm>
  COMMENT "GEMM correctness check (naive vs tiled)"
  VERBATIM
)
