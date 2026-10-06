#include "Game/AI/Action/actionForkEmitExpandFieldWithCreate.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/Actor/actUnk_7100d3cd74.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkEmitExpandFieldWithCreate::ForkEmitExpandFieldWithCreate(const InitArg& arg)
    : ForkEmitExpandField(arg) {}

ForkEmitExpandFieldWithCreate::~ForkEmitExpandFieldWithCreate() {
    auto* parts = mActor->m101();
    if (*mIsSetPartsLink_s && parts) {
        parts->sub_7100D3CFEC(mPartsKey_s);
    } else if (_a8.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_a8, &accessor);
        if (accessor.isStateSleep())
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

bool ForkEmitExpandFieldWithCreate::init_(sead::Heap* heap) {
    return ForkEmitExpandField::init_(heap);
}

void ForkEmitExpandFieldWithCreate::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkEmitExpandField::enter_(params);
    sub_710014E780(&mActor->getMtx());
}

void ForkEmitExpandFieldWithCreate::leave_() {
    ForkEmitExpandField::leave_();
}

void ForkEmitExpandFieldWithCreate::loadParams_() {
    ForkEmitExpandField::loadParams_();
    getStaticParam(&mScaleTime_s, "ScaleTime");
    getStaticParam(&mIsReuseActor_s, "IsReuseActor");
    getStaticParam(&mIsSetPartsLink_s, "IsSetPartsLink");
}

void ForkEmitExpandFieldWithCreate::calc_() {
    ForkEmitExpandField::calc_();
}

ksys::act::BaseProcLink& ForkEmitExpandFieldWithCreate::m32() {
    auto* parts = mActor->m101();
    if (*mIsSetPartsLink_s && parts)
        return parts->getActorPartsActor(mPartsKey_s);
    return _a8;
}

}  // namespace uking::action
