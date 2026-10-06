#include <prim/seadScopedLock.h>
#include "aal/aalCone.h"

namespace aal {

SEAD_SINGLETON_DISPOSER_IMPL(ConeFactory)

// 0x7100b8e0b0 / 0x7100b8e160
ConeFactory::~ConeFactory() {
    mCones.freeBuffer();
}

// 0x7100b8e218
void ConeFactory::initialize(s32 num, sead::Heap* heap) {
    mCones.allocBuffer(num, heap);
}

// NON_MATCHING: inlined ObjList::emplaceBack stores the (zeroed) list node before computing the list address
// 0x7100b8e2e0
Cone* ConeFactory::create() {
    if (!mCones.isBufferReady())
        return nullptr;
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    return mCones.emplaceBack();
}

// 0x7100b8e37c
void ConeFactory::destroy(Cone* cone) {
    if (!mCones.isBufferReady())
        return;
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    if (mCones.indexOf(cone) >= 0)
        mCones.erase(cone);
}

}  // namespace aal
