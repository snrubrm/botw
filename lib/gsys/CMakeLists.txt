project(gsys CXX ASM)

add_library(gsys OBJECT
  include/gsys/gsysMaskedProjLight.h
  include/gsys/gsysMaskedProjLight.h
  include/gsys/gsysMaskedSpotLight.h
  include/gsys/gsysMemBuffer.h
  include/gsys/gsysModel.h
  include/gsys/gsysModelResource.h
  include/gsys/gsysCameraAnimation.h
  include/gsys/gsysModelAutoAnimation.h
  include/gsys/gsysModelAccessKey.h
  include/gsys/gsysModelAnimation.h
  include/gsys/gsysModelDynamicEnvInfo.h
  include/gsys/gsysModelNW.h
  include/gsys/gsysModelScene.h
  include/gsys/gsysModelSceneComponent.h
  include/gsys/gsysModelSceneEnv.h
  include/gsys/gsysModelSceneConfig.h
  include/gsys/gsysG3dResAnimationEx.h
  include/gsys/gsysPartialSkeletalAnm.h
  include/gsys/gsysModelUnit.h
  include/gsys/gsysModelUnitGroup.h
  include/gsys/gsysModelUnitDrawArray.h
  include/gsys/gsysOfxLensFlareRig.h
  include/gsys/gsysORUtil.h
  include/gsys/gsysParticleConfig.h
  include/gsys/gsysPointLight.h
  include/gsys/gsysSpotLight.h

  src/gsys/gsysMemBuffer.cpp
  src/gsys/gsysModel.cpp
  src/gsys/gsysModelResource.cpp
  src/gsys/gsysCameraAnimation.cpp
  src/gsys/gsysModelAccessKey.cpp
  src/gsys/gsysModelAnimation.cpp
  src/gsys/gsysModelAutoAnimation.cpp
  src/gsys/gsysModelNW.cpp
  src/gsys/gsysG3dResAnimationEx.cpp
  src/gsys/gsysPartialSkeletalAnm.cpp
  src/gsys/gsysModelUnit.cpp
  src/gsys/gsysModelUnitGroup.cpp
  src/gsys/gsysModelSceneConfig.cpp
  src/gsys/gsysParticleConfig.cpp
)

target_compile_options(gsys PRIVATE -fno-exceptions)
target_compile_options(gsys PRIVATE -fno-strict-aliasing)
target_compile_options(gsys PRIVATE -Wno-invalid-offsetof)
target_include_directories(gsys PUBLIC include/)

if(NOT TARGET sead)
  add_subdirectory(../sead)
endif()
target_link_libraries(gsys PUBLIC sead)

if(NOT TARGET agl)
  add_subdirectory(../agl)
endif()
target_link_libraries(gsys PUBLIC agl)
