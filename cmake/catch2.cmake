include_guard()

include(cmake/utils.cmake)

FetchContent_DeclareGitHubTarWithMirror(catch2
  catchorg/Catch2 v3.12.0
  SHA256=E077079F214AFC99FEE940D91C14CF1A8C1D378212226BB9F50EFFF75FE07B23
)

FetchContent_MakeAvailableWithArgs(catch2
  CATCH_INSTALL_DOCS=OFF
  CATCH_INSTALL_EXTRAS=OFF
  DO_NOT_USE_WMAIN=ON
)
