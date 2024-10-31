include_guard()

include(cmake/utils.cmake)

FetchContent_DeclareGitHubWithMirror(catch2
  catchorg/Catch2 v3.7.1
  SHA256=C991B247A1A0D7BB9C39AA35FAF0FE9E19764213F28FFBA3109388E62EE0269C
)

FetchContent_MakeAvailableWithArgs(catch2
  CATCH_INSTALL_DOCS=OFF
  CATCH_INSTALL_EXTRAS=OFF
  DO_NOT_USE_WMAIN=ON
)
