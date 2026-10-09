#pragma once

#include <container/seadOffsetList.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <math/seadMatrix.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::xlink {

class XLink;

// Name is a guess for the game singleton at 2653168. Factory 123DE44 allocates 0x52e8;
// constructor 123DECC installs the destructor-only vtable 25169F0 and initializes the queues.
class Manager {
    SEAD_SINGLETON_DISPOSER(Manager)
    Manager();
    virtual ~Manager();

public:
    void queueSleep(XLink* xlink);
    void removeSleep(XLink* xlink);
    void queueTransform(XLink* xlink, const sead::Matrix34f& matrix, bool flag);
    void removeTransform(XLink* xlink);

private:
    struct TransformRequest {
        XLink* xlink;
        sead::Matrix34f matrix;
        bool flag;
    };
    static_assert(sizeof(TransformRequest) == 0x40);

    /* 0x0028 */ u8 _28[0x1d0 - 0x28];
    /* 0x01d0 */ sead::OffsetList<XLink> mSleepQueue;
    /* 0x01e8 */ sead::CriticalSection mSleepLock;
    /* 0x0228 */ sead::SafeArray<TransformRequest, 64> mTransformRequests;
    /* 0x1228 */ s32 mNumTransformRequests;
    /* 0x1230 */ sead::CriticalSection mTransformLock;
    /* 0x1270 */ u8 _1270[0x52e8 - 0x1270];
};
KSYS_CHECK_SIZE_NX150(Manager, 0x52e8);

}  // namespace ksys::xlink
