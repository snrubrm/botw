#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadDelegate.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

// Placeholder name and namespace (CSV: MCMgr::createInstance 0x7100dcb390, ctor 0x7100dcb418, init 0x7100dcb5f0, dtor
// 0x7100dcb924; instance pointer at 0x7102590f10 (GOT 0x2590f10); size 0x1c50, singleton disposer at +8). The
// per-frame coordinator that submits the actor / effect / sound updates to the worker support threads (it owns 18
// sead::FixedSizeJQ at +0x28 stride 0xa0 and two task delegates at +0x1c10 / +0x1c30). Only the small functions are
// defined so far.
class MCMgr : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(MCMgr)
    MCMgr();
    virtual ~MCMgr();

public:
    // 0x7100dcb8a8 (CSV invoked2; the delegate target at ... returns true): calls the unnamed 0x7100f3ed50.
    bool invoked2(void* arg);
    // 0x7100dcb8c0 (CSV invoked3_calcEffectMostLikely): the effect manager's two calc steps.
    bool invoked3(void* arg);
    // 0x7100dcb8fc (CSV invoked4): the sound manager's calc2.
    bool invoked4(void* arg);

    // 0x7100dcd4ac (CSV processAllBaseProcMgrJobsType3): runs the extra jobs of type 3 of the BaseProcMgr until it has
    // no more.
    void processAllBaseProcMgrJobsType3();
    // 0x7100dcd510 / 0x7100dcd544 (CSV calc / postCalc): wait for the worker task 3 / 4.
    void calc();
    void postCalc();
    // 0x7100dcd524: submits invoked3 as worker request 4.
    void requestInvoker3();
    // 0x7100dcd558: calls the sound calc2 directly while the worker threads are paused, else submits invoked4 as
    // worker request 6.
    void requestInvoker4OrSound();

private:
    u8 _28[0x1c10 - 0x28];
    sead::Delegate1R<MCMgr, void*, bool> mInvoker3{this, &MCMgr::invoked3};
    sead::Delegate1R<MCMgr, void*, bool> mInvoker4{this, &MCMgr::invoked4};
};
KSYS_CHECK_SIZE_NX150(MCMgr, 0x1c50);

}  // namespace ksys
