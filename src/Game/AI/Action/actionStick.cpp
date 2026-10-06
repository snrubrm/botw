#include "Game/AI/Action/actionStick.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

Stick::Stick(const InitArg& arg) : ActionEx(arg) {}

Stick::~Stick() = default;

void Stick::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void Stick::leave_() {
    auto* actor = mActor;
    if (_160 == 3)
        actor->sub_71011DA834(&_c0);
    else
        actor->sub_71011DA834(&_48);
}

void Stick::loadParams_() {
    if (!mActor->getParam())
        return;
    getDynamicParam(&mStickPos_d, "StickPos");
    getDynamicParam(&mStickPosDiv_d, "StickPosDiv");
    getDynamicParam(&mStickActor_d, "StickActor");
    getDynamicParam(&mStickBodyName_d, "StickBodyName");
}

// NON_MATCHING: the original makes a real vtable call for the bind's m10 (ours devirtualises the empty ActorBind::m10).
bool Stick::sub_710027D3AC() {
    if (!mStickActor_d)
        return false;
    if (mStickActor_d->isAccessingSpecifiedProcUnsafe(nullptr))
        return false;
    auto* actor = sead::DynamicCast<ksys::act::Actor>(mStickActor_d->getProc(nullptr, nullptr));
    if (!actor)
        return false;
    auto& parent_link = actor->getParentLinkMaybe();
    if (!parent_link.hasProc())
        return false;
    if (!parent_link.isAccessingSpecifiedProcUnsafe(nullptr))
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&parent_link, &accessor);
    if (accessor.isStateCalc()) {
        _48._58 = parent_link;
        _48._8.acquire(nullptr, false);
        _48.m10(&_48._8);
        return true;
    }
    return false;
}

void Stick::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
