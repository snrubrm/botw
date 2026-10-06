project(aal CXX ASM)

add_library(aal OBJECT
  include/aal/aalAssetInfo.h
  include/aal/aalDeviceType.h
  include/aal/aalEmitter.h
  include/aal/aalFadeCurveType.h
  include/aal/aalFxDelayParamSetter.h
  include/aal/aalFxParamSetter.h
  include/aal/aalGroup.h
  include/aal/aalGroupLimiter.h
  include/aal/aalGroupMgr.h
  include/aal/aalHandle.h
  include/aal/aalISpeakerBalanceSupplier.h
  include/aal/aalIUnifiable.h
  include/aal/aalNamedObj.h
  include/aal/aalSettings.h
  include/aal/aalShape.h
  include/aal/aalSoundController.h
  include/aal/aalSoundParam.h
  include/aal/aalSoundSource.h
  include/aal/aalSoundSourceUnifier.h
  include/aal/aalSpatialCalculator.h
  include/aal/aalSpatialSetting.h
  include/aal/aalSystem.h
  include/aal/aalSystemAccessor.h
  include/aal/aalTimedFader.h
  src/aalEmitter.cpp
  src/aalFxDelayParamSetter.cpp
  src/aalFxParamSetter.cpp
  src/aalGroup.cpp
  src/aalGroupFolder.cpp
  src/aalGroupLimiter.cpp
  src/aalGroupMgr.cpp
  src/aalSpatialCalculator.cpp
  src/aalHandle.cpp
  src/aalISpeakerBalanceSupplier.cpp
  src/aalNamedObj.cpp
  src/aalShape.cpp
  src/aalSoundGroup.cpp
  src/aalSimpleTimedFader.cpp
  src/aalPlayingStateController.cpp
  src/aalSoundController.cpp
  src/aalSoundParam.cpp
  src/aalSystem.cpp
  src/aalSoundSource.cpp
  src/aalSpatialSetting.cpp
  src/dummy.cpp
)

target_compile_options(aal PRIVATE -fno-exceptions)
target_compile_options(aal PRIVATE -fno-strict-aliasing)
target_compile_options(aal PRIVATE -Wno-invalid-offsetof)
target_include_directories(aal PUBLIC include/)

if(NOT TARGET sead)
  add_subdirectory(../sead)
endif()
target_link_libraries(aal PUBLIC sead)
