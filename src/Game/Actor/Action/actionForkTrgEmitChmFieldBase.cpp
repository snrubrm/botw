#include "Game/Actor/Action/actionForkTrgEmitChmFieldBase.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::action {

ForkTrgEmitChmFieldBase::ForkTrgEmitChmFieldBase(const InitArg& arg) : ForkEmitExpandField(arg) {}

ForkTrgEmitChmFieldBase::~ForkTrgEmitChmFieldBase() = default;

bool ForkTrgEmitChmFieldBase::init_(sead::Heap* heap) {
    return ForkEmitExpandField::init_(heap);
}

void ForkTrgEmitChmFieldBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkEmitExpandField::enter_(params);
    _98 = false;
    _9c = ksys::Timer(0, 0);
}

void ForkTrgEmitChmFieldBase::leave_() {
    ForkEmitExpandField::leave_();
}

void ForkTrgEmitChmFieldBase::loadParams_() {
    ForkEmitExpandField::loadParams_();
    getStaticParam(&mEmitIntervalTime_s, "EmitIntervalTime");
}

void ForkTrgEmitChmFieldBase::calc_() {
    ForkEmitExpandField::calc_();
    if (*mEmitIntervalTime_s >= 0 && !(_9c.value <= 1.1920929e-7f))
        _9c.update();
    if (m33()) {
        sead::Matrix34f mtx;
        if (m34(&mtx))
            sub_710014E780(&mtx);
    }
}

// NON_MATCHING: the original keeps `tbz w19 / mov w0, #1` blocks for the sleeping test; ours folds `if (sleeping) return
// true; return false` into `and w0, w19, #1`
bool ForkTrgEmitChmFieldBase::m33() {
    if (*mEmitIntervalTime_s < 0) {
        if (_98)
            return false;
    } else if (!(_9c.value <= 1.1920929e-7f)) {
        return false;
    }
    auto& link = m32();
    if (!link.hasProc())
        return false;
    {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        if (accessor.isStateSleep())
            return true;
    }
    return false;
}

}  // namespace uking::action
