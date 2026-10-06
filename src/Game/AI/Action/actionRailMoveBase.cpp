#include "Game/AI/Action/actionRailMoveBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

RailMoveBase::RailMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RailMoveBase::~RailMoveBase() = default;

bool RailMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RailMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
    if (!mASName_d.isEmpty())
        playAS(mASName_d.cstr(), *mIsIgnoreSame_d, *mASSlot_d, *mSequenceBank_d, -1.0f);
}

void RailMoveBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void RailMoveBase::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getDynamicParam(&mASSlot_d, "ASSlot");
    getDynamicParam(&mSequenceBank_d, "SequenceBank");
    getDynamicParam(&mIsIgnoreSame_d, "IsIgnoreSame");
    getDynamicParam(&mASName_d, "ASName");
}

void RailMoveBase::calc_() {
    m32();
    auto* as_list = mActor->getASList();
    auto* controller = mActor->getCharacterController();
    if (!as_list || !controller) {
        setFailed();
    } else {
        sead::Vector3f dir = _1c;
        dir.normalize();
        controller->sub_7100F5EDBC(dir);
        controller->sub_7100F5FDF0(dir);
        controller->sub_7100F5E7F0(*mSpeed_s * 30.0f);
        controller->sub_7100F60E98();
        const f32 length_xz = sead::Mathf::sqrt(_1c.x * _1c.x + _1c.z * _1c.z);
        if (!sead::Mathf::equalsEpsilon(length_xz, 0.0f, 0.1f))
            return;
        setFinished();
    }
    mFlags.set(Flag::Changeable);
}

void RailMoveBase::m32() {}

}  // namespace uking::action
