#include "Game/gameHorseColorInfoMgr.h"

SEAD_SINGLETON_DISPOSER_IMPL(HorseColorInfoMgr)

// NON_MATCHING: createInstance inlines this constructor; the original zeroes +0x28..+0x48 with three
// 8-byte stores and one 4-byte store (ours merges them into two 16-byte stores) and stores
// SingletonDisposer_::sStaticDisposer before the instance's vptr (ours after it).
HorseColorInfoMgr::HorseColorInfoMgr()
    : _28(0), _29(0), _2a{}, _2c(0), mHeap(nullptr), mModel(nullptr), mTextureModel(nullptr),
      mLoadTask(sead::IDisposer::HeapNullOption::DoNotAppendDisposerIfNoHeapSpecified) {
    mLoadDelegate.bind(this, &HorseColorInfoMgr::loadResources);
}

HorseColorInfoMgr::~HorseColorInfoMgr() {
    sub_710094C810();
}

void HorseColorInfoMgr::sub_710094C810() {
    _28 &= ~2;
    _29 = 0;
    mLoadTask.removeFromQueue();
    if (mModel) {
        gsys::Model::sub_7100BF69F8(mModel);
        mModel = nullptr;
    }
    if (mTextureModel) {
        gsys::Model::sub_7100BF69F8(mTextureModel);
        mTextureModel = nullptr;
    }
    if (mHeap) {
        mHeap->destroy();
        mHeap = nullptr;
    }
    if (mModelRes.requestedLoad())
        mModelRes.requestUnload();
    if (mTextureRes.requestedLoad())
        mTextureRes.requestUnload();
    if (mAnimRes.requestedLoad())
        mAnimRes.requestUnload();
    _2c = 0;
}

void HorseColorInfoMgr::sub_710094C638() {
    _28 = 0;
}

void HorseColorInfoMgr::sub_710094D0F8() {
    if (_2c == 2)
        _28 |= 1;
}
