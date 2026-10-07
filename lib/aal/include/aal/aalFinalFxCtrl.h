#pragma once

#include <hostio/seadHostIONode.h>
#include <container/seadOffsetList.h>
#include <thread/seadCriticalSection.h>
#include "aal/aalDeviceType.h"

namespace aal {

/// The control of the final effects of a device. TODO: incomplete.
class FinalFxCtrl : public sead::hostio::Node {
public:
    // The list element is polymorphic; clearFinalFx calls slot 7. Other slots
    // are placeholders until their interfaces are recovered.
    class Element {
    public:
        virtual void m0() = 0;
        virtual void m1() = 0;
        virtual void m2() = 0;
        virtual void m3() = 0;
        virtual void m4() = 0;
        virtual void m5() = 0;
        virtual void m6() = 0;
        virtual void m7() = 0;
        sead::ListNode mNode;
    };

    explicit FinalFxCtrl(DeviceType device);
    virtual ~FinalFxCtrl();
    void clearFinalFx();

private:
    DeviceType mDevice;
    sead::OffsetList<Element> mEffects;
    sead::CriticalSection mCriticalSection;
};
static_assert(sizeof(FinalFxCtrl) == 0x68, "aal::FinalFxCtrl size mismatch");

}  // namespace aal
