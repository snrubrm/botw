#include <gsys/gsysModelMgr.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelScene.h>
#include <utility/aglDevTools.h>
#include <gsys/gsysORUtil.h>

namespace gsys
{

// sInstance 0x71025fccf0, sStaticDisposer 0x71025fcce8, disposer vtable 0x71024ca078.
SEAD_SINGLETON_DISPOSER_IMPL(ModelMgr)

// 0x7100c030a8
void ModelMgr::createFFLTexturePerFrame(agl::DrawContext*) {}

// 0x7100c030ac
f32 ModelMgr::getMeterScale() const {
    return agl::utl::DevTools::getMeterScale();
}

// 0x7100c02d64
s32 ModelMgr::getXluZPrePassID() {
    return mXluZPrePassId++ & 0x7ff;
}

// 0x7100c01fd4
void ModelMgr::initialize(sead::Heap* heap, sead::Heap* debug_heap) {
    mArray30.allocBuffer(8, heap, 8);
    mArray40.allocBuffer(8, heap, 8);
    mScenes.allocBuffer(8, heap, 8);
    mGPUStressAnalyzer.initialize(heap);
    if (debug_heap)
        mArray1e8.allocBuffer(0x800, debug_heap, 8);
    ORUtil::setNodeMeta(this, ORUtil::Category::_6, debug_heap);
    ORUtil::setNodeMeta(&mNode1e0, ORUtil::Category::_3, debug_heap);
}

// 0x7100c02a80
void ModelMgr::editAll() {
    mCS.lock();
    for (auto it = mModelList.begin(); it != mModelList.end(); ++it)
        it->edit_(nullptr);
    mCS.unlock();
}

// 0x7100c02b00
void ModelMgr::editAll(const G3dResModelEx* res_model) {
    mCS.lock();
    for (auto it = mModelList.begin(); it != mModelList.end(); ++it)
        it->edit_(res_model);
    mCS.unlock();
}

// 0x7100c02d80
void ModelMgr::add_(ModelScene* scene, sead::Heap* heap, sead::Heap*) {
    mSceneCS.lock();
    mArray40.pushBack(scene);
    mSceneCS.unlock();

    if (mModelMgrCallback)
        mModelMgrCallback->onAddModelScene(scene, heap);
}

// 0x7100c02ee4
void ModelMgr::add_(Model* model, bool append_or, sead::Heap* heap) {
    mCS.lock();
    model->mModelIndex = mModelCounter++;
    if (append_or)
        appendOR_(model);
    mModelList.pushBack(model);
    if (mModelMgrCallback)
        mModelMgrCallback->onAddModel(model, heap);
    mCS.unlock();
}

// 0x7100c02cc8
void ModelMgr::rebindModelScene(const ModelScene* scene) {
    mCS.lock();
    for (auto it = mModelList.begin(); it != mModelList.end(); ++it) {
        if (it->getScene() == scene)
            it->bindToModelScene();
    }
    mCS.unlock();
}

// 0x7100c027b4
void ModelMgr::calcModel(sead::WorkerMgr* wm) {
    for (auto it = mScenes.begin(); it != mScenes.end(); ++it)
        it->update(wm);
}

// 0x7100c0288c
void ModelMgr::sortQueue(sead::WorkerMgr* wm) {
    sead::WorkerMgr* work = (mFlags & 2) && (mFlags & 1) ? wm : nullptr;
    for (auto it = mScenes.begin(); it != mScenes.end(); ++it)
        it->sortQueue_(work);
}

// 0x7100c028f0
void ModelMgr::calcWorld(sead::WorkerMgr* wm) {
    sead::WorkerMgr* work = (mFlags & 2) && (mFlags & 1) ? wm : nullptr;
    for (auto it = mScenes.begin(); it != mScenes.end(); ++it)
        it->calcWorld_(work);
}

// 0x7100c02954
void ModelMgr::calcRenderView(sead::WorkerMgr* wm) {
    sead::WorkerMgr* work = (mFlags & 8) && (mFlags & 1) ? wm : nullptr;
    for (auto it = mScenes.begin(); it != mScenes.end(); ++it)
        it->calcRenderView_(work);
}

// 0x7100c029b8
void ModelMgr::calcDrawBackGround(sead::WorkerMgr* wm) {
    sead::WorkerMgr* work = (mFlags & 0x10) && (mFlags & 1) ? wm : nullptr;
    for (auto it = mScenes.begin(); it != mScenes.end(); ++it)
        it->calcDrawBackGround_(work);
}

// 0x7100c02a1c
void ModelMgr::calcGPU(sead::WorkerMgr* wm) {
    sead::WorkerMgr* work = (mFlags & 0x40) && (mFlags & 1) ? wm : nullptr;
    for (auto it = mScenes.begin(); it != mScenes.end(); ++it)
        it->calcGPU_(work);
}

}  // namespace gsys
