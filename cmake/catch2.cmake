include_guard()

include(cmake/utils.cmake)

FetchContent_DeclareGitHubTarWithMirror(catch2
  catchorg/Catch2 v3.15.3
  SHA256=b0299ae552918220a7a6e21e7de5b714777f4e8c883fb70c4bb23fe01df8c6e3
)

FetchContent_MakeAvailableWithArgs(catch2
  CATCH_INSTALL_DOCS=OFF
  CATCH_INSTALL_EXTRAS=OFF
  DO_NOT_USE_WMAIN=ON
)
