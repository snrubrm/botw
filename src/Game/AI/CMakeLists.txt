add_subdirectory(Action)
add_subdirectory(AI)
add_subdirectory(Query)

target_sources(uking PRIVATE
  aiActionFactories.cpp
  aiActionFactories.h
  aiAiFactories.cpp
  aiAiFactories.h
  aiQueryFactories.cpp
  aiQueryFactories.h
  aiUnk_71005D6D10.cpp
  aiUnk_71005D6D10.h
  aiUnk_710071edf8.cpp
  aiUnk_710071edf8.h
  aiUnk_7102357210.h
  aiUnk_7102357d20.cpp
  aiUnk_7102357d20.h
  aiUnk_7102450648.cpp
  aiUnk_71024507c8.cpp
  aiUnk_7102450828.cpp
  aiUnkDamageCallbacks.cpp
  aiUnkDamageCallbacks.h
  aiUnk_7102450af8.cpp
  aiUnk_7102450bb8.cpp
)
