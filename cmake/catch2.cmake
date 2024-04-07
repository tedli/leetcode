include_guard()

include(cmake/utils.cmake)

FetchContent_DeclareGitHubWithMirror(catch2
  catchorg/Catch2 v3.5.3
  SHA256=8D723B0535C94860EF8CF6231580FA47D67A3416757ECB10639E40D748AB6C71
)

FetchContent_MakeAvailableWithArgs(catch2
  CATCH_INSTALL_DOCS=OFF
  CATCH_INSTALL_EXTRAS=OFF
  DO_NOT_USE_WMAIN=ON
)
