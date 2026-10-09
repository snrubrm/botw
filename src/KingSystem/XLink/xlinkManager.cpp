#include "KingSystem/XLink/xlinkManager.h"
#include <prim/seadScopedLock.h>
#include <xlink2/xlink2SystemELink.h>
#include <xlink2/xlink2SystemSLink.h>
#include "KingSystem/XLink/xlinkXLink.h"

namespace ksys::xlink {

Manager* Manager::sInstance;

void Manager::setGlobalProperty(u32 property, f32 value) {
    xlink2::SystemELink::instance()->setGlobalPropertyValue(property, value);
    xlink2::SystemSLink::instance()->setGlobalPropertyValue(property, value);
}

void Manager::queueSleep(XLink* xlink) {
    sead::ScopedLock<sead::CriticalSection> lock(&mSleepLock);
    if (!xlink->mSleepNode.isLinked())
        mSleepQueue.pushBack(xlink);
}

void Manager::removeSleep(XLink* xlink) {
    sead::ScopedLock<sead::CriticalSection> lock(&mSleepLock);
    if (xlink->mSleepNode.isLinked())
        mSleepQueue.erase(xlink);
}

// NON_MATCHING: the saved entry avoids the native repeated count/index lookup; copy scheduling differs.
void Manager::queueTransform(XLink* xlink, const sead::Matrix34f& matrix, bool flag) {
    sead::ScopedLock<sead::CriticalSection> lock(&mTransformLock);
    if (mNumTransformRequests > 62)
        return;
    auto& request = mTransformRequests[mNumTransformRequests];
    request.xlink = xlink;
    request.matrix = matrix;
    request.flag = flag;
    ++mNumTransformRequests;
}

void Manager::removeTransform(XLink* xlink) {
    sead::ScopedLock<sead::CriticalSection> lock(&mTransformLock);
    for (u32 i = 0; i < mNumTransformRequests; ++i) {
        if (mTransformRequests[i].xlink == xlink)
            mTransformRequests[i].xlink = nullptr;
    }
}

}  // namespace ksys::xlink
