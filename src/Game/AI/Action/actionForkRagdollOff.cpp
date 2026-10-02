#include "Game/AI/Action/actionForkRagdollOff.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"

namespace uking::action {

ForkRagdollOff::ForkRagdollOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkRagdollOff::~ForkRagdollOff() = default;

bool ForkRagdollOff::init_(sead::Heap* heap) {
    _30.acquire(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_30._0)) {
        if (!(unit->_b0 & 1)) {
            unit->_8.setName("Skl_Root");
            unit->_8._68 = sead::Matrix34f::ident;
            unit->_b4 = 0;
            unit->_b0 |= 1;
        }
    }
    _30.sub_7100137A28(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
    _30.x();
    return true;
}

void ForkRagdollOff::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    if (*mOffTiming_s != 0)
        return;

    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor))
        actor->sub_71006DD92C(true);
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_30.mSlot))
        unit->_8._68 = sead::Matrix34f::ident;
}

void ForkRagdollOff::leave_() {
    if (*mOffTiming_s != 1)
        return;

    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor))
        actor->sub_71006DD92C(true);
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_30.mSlot))
        unit->_8._68 = sead::Matrix34f::ident;
}

void ForkRagdollOff::loadParams_() {
    getStaticParam(&mOffTiming_s, "OffTiming");
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

void ForkRagdollOff::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
