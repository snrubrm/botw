project(gsys CXX ASM)

add_library(gsys OBJECT
  include/gsys/gsysLayer.h
  include/gsys/gsysLayer3D.h
  src/gsys/gsysLayer.cpp
  include/gsys/gsysModelRenderCache.h
  src/gsys/gsysModelRenderCache.cpp
  include/gsys/gsysGBuffer.h
  include/gsys/gsysRenderBufferContext.h
  include/gsys/gsysModelSceneBuffer.h
  include/gsys/gsysMaskedProjLight.h
  include/gsys/gsysMaskedProjLight.h
  include/gsys/gsysMaskedSpotLight.h
  include/gsys/gsysMemBuffer.h
  include/gsys/gsysModel.h
  include/gsys/gsysModelResource.h
  include/gsys/gsysModelDebugInfo.h
  include/gsys/gsysCameraAnimation.h
  include/gsys/gsysModelAutoAnimation.h
  include/gsys/gsysModelAccessKey.h
  include/gsys/gsysModelAnimation.h
  include/gsys/gsysModelDynamicEnvInfo.h
  include/gsys/gsysModelNW.h
  include/gsys/gsysModelDrawObj.h
  include/gsys/gsysModelRenderContext.h
  include/gsys/gsysModelRenderQueue.h
  include/gsys/gsysModelRenderUnitNodeArray.h
  include/gsys/gsysShaderContext.h
  include/gsys/gsysModelScene.h
  include/gsys/gsysModelSceneComponent.h
  include/gsys/gsysModelSceneEnv.h
  include/gsys/gsysModelSceneConfig.h
  include/gsys/gsysEffectModelDrawMgr.h
  include/gsys/gsysG3dResMaterialEx.h
  include/gsys/gsysG3dResModelEx.h
  include/gsys/gsysG3dResShapeEx.h
  include/gsys/gsysModelShaderProgram.h
  include/gsys/gsysModelShaderVariationKey.h
  include/gsys/gsysG3dResAnimationEx.h
  include/gsys/gsysPartialSkeletalAnm.h
  include/gsys/gsysIModelProcedural.h
  include/gsys/gsysModelRenderUnit.h
  include/gsys/gsysModelRenderUnitNW.h
  include/gsys/gsysModelUnit.h
  include/gsys/gsysModelUnitGroup.h
  include/gsys/gsysModelWorkBuffer.h
  include/gsys/gsysModelUnitDrawArray.h
  include/gsys/gsysOfxLensFlareRig.h
  include/gsys/gsysResourceEditor.h
  include/gsys/gsysORUtil.h
  include/gsys/gsysParticleMgr.h
  include/gsys/gsysParticleConfig.h
  include/gsys/gsysPointLight.h
  include/gsys/gsysSpotLight.h

  src/gsys/gsysMemBuffer.cpp
  src/gsys/gsysModel.cpp
  src/gsys/gsysRenderDisplay.cpp
  src/gsys/gsysModelRig.cpp
  src/gsys/gsysPointLight.cpp
  src/gsys/gsysMaskedLight.cpp
  src/gsys/gsysModelMgr.cpp
  src/gsys/gsysModelResource.cpp
  src/gsys/gsysG3dResMaterialEx.cpp
  src/gsys/gsysModelShaderProgram.cpp
  src/gsys/gsysG3dResModelEx.cpp
  src/gsys/gsysCameraAnimation.cpp
  src/gsys/gsysModelAccessKey.cpp
  src/gsys/gsysModelAnimation.cpp
  src/gsys/gsysModelAutoAnimation.cpp
  src/gsys/gsysModelNW.cpp
  src/gsys/gsysModelShaderVariationKey.cpp
  src/gsys/gsysG3dResAnimationEx.cpp
  src/gsys/gsysPartialSkeletalAnm.cpp
  src/gsys/gsysIModelProcedural.cpp
  src/gsys/gsysModelRenderUnit.cpp
  src/gsys/gsysModelRenderUnitNW.cpp
  src/gsys/gsysModelUnit.cpp
  src/gsys/gsysModelUnitGroup.cpp
  src/gsys/gsysModelWorkBuffer.cpp
  src/gsys/gsysModelUnitDrawArray.cpp
  src/gsys/gsysModelDrawObj.cpp
  src/gsys/gsysModelRenderContext.cpp
  src/gsys/gsysModelRenderQueue.cpp
  src/gsys/gsysModelRenderUnitNodeArray.cpp
  src/gsys/gsysShaderContext.cpp
  src/gsys/gsysModelSceneConfig.cpp
  src/gsys/gsysEffectModelDrawMgr.cpp
  src/gsys/gsysModelDynamicEnvInfo.cpp
  src/gsys/gsysModelScene.cpp
  src/gsys/gsysModelSceneComponent.cpp
  src/gsys/gsysModelSceneEnv.cpp
  src/gsys/gsysResourceEditor.cpp
  src/gsys/gsysParticleMgr.cpp
  src/gsys/gsysParticleConfig.cpp
  src/gsys/gsysORUtil.cpp
  src/gsys/gsysModelJobQueue.cpp
  src/gsys/gsysModelShaderHolder.cpp
  src/gsys/gsysViewer.cpp
  src/gsys/gsysDebugCtrl.cpp
  src/gsys/gsysShaderHolder.cpp
  src/gsys/gsysApplicationPackage.cpp
  src/gsys/gsysModelAssignRenderInfo.cpp
  src/gsys/gsysModelSceneBuffer.cpp
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
