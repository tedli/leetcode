include_guard()

include(cmake/utils.cmake)

FetchContent_DeclareGitHubTarWithMirror(catch2
  catchorg/Catch2 v3.15.0
  SHA256=9650c55e497759cc39b977e45524bc8acb15256061c112080916ab6cb0b1ea66
)

FetchContent_MakeAvailableWithArgs(catch2
  CATCH_INSTALL_DOCS=OFF
  CATCH_INSTALL_EXTRAS=OFF
  DO_NOT_USE_WMAIN=ON
)
