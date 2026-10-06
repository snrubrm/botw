#include "Game/AI/AI/aiSignalFlowchartRootAI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Resource/resHandle.h"

namespace uking::ai {

// The resource handle of "EventFlow/SignalFlowchart.bfevfl" (placeholder name), created by loadResource.
ksys::res::Handle* sUnk_7102602228;

SignalFlowchartRootAI::SignalFlowchartRootAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {
    _178 = 0;
    _380 = 0;
    _3b8 = false;
    _3b9 = false;
    _3bc = 0;
    _3ba = false;
    _58 = nullptr;
    _60 = nullptr;
}

// NON_MATCHING: the original keeps `_3ba` and the handle test as two separate branches (the GOT load of the
// handle stays inside the first one); ours folds them into a ccmp.
SignalFlowchartRootAI::~SignalFlowchartRootAI() {
    if (_3ba) {
        if (sUnk_7102602228) {
            sUnk_7102602228->requestUnload2();
            delete sUnk_7102602228;
            sUnk_7102602228 = nullptr;
        }
    }
}

bool SignalFlowchartRootAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SignalFlowchartRootAI::enter_(ksys::act::ai::InlineParamPack* params) {
    _3b8 = false;
    _3b9 = false;
    _3bc = 0;
}

void SignalFlowchartRootAI::calc_() {
    if (mActor->checkBasicSig()) {
        if (!_3b8) {
            mContext.Start(nullptr);
            _3b8 = true;
        } else {
            mActionDoneHandler.Invoke();
        }
    } else if (_3bc == 0) {
        mActor->emitBasicSigOff();
    }

    if (mContext.GetNumAllocatedNodes() == 0)
        setFinished();
}

void SignalFlowchartRootAI::leave_() {
    mActionDoneHandler.Reset();
    mContext.Clear();
}

void SignalFlowchartRootAI::loadParams_() {
    getMapUnitParam(&mEventFlowName_m, "EventFlowName");
    getMapUnitParam(&mEventFlowEntryName_m, "EventFlowEntryName");
}

}  // namespace uking::ai
