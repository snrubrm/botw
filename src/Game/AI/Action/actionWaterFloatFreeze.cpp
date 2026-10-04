#include "Game/AI/Action/actionWaterFloatFreeze.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"

namespace uking::action {

WaterFloatFreeze::WaterFloatFreeze(const InitArg& arg) : WaterFloatImmobile(arg) {}

WaterFloatFreeze::~WaterFloatFreeze() = default;

void WaterFloatFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatImmobile::enter_(params);
    if (auto* as_list = mActor->getASList())
        as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
    if (auto* physics = mActor->getPhysics()) {
        physics->getFlags().set(ksys::phys::InstanceSet::Flag::_20000);
        physics->sub_7100FBDD40(true);
    }
    if (auto* xlink = mActor->getXLink())
        xlink->_cc.set(0x800);
    if (auto* bone_control = mActor->getBoneControl())
        bone_control->sub_7100D82FB4();
}

void WaterFloatFreeze::leave_() {
    WaterFloatImmobile::leave_();
    if (*mIsKeepFreeze_a) {
        *mIsKeepFreeze_a = false;
        return;
    }
    if (auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor))
        actor->m149(3);
    if (auto* as_list = mActor->getASList())
        as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
    if (auto* physics = mActor->getPhysics()) {
        physics->getFlags().reset(ksys::phys::InstanceSet::Flag::_20000);
        physics->sub_7100FBDD40(false);
    }
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F6321C(false);
    if (auto* xlink = mActor->getXLink())
        xlink->_cc.reset(0x800);
    if (auto* bone_control = mActor->getBoneControl())
        bone_control->sub_7100D82FC4();
}

void WaterFloatFreeze::loadParams_() {
    WaterFloatImmobile::loadParams_();
    getAITreeVariable(&mIsKeepFreeze_a, "IsKeepFreeze");
}

void WaterFloatFreeze::calc_() {
    WaterFloatImmobile::calc_();
    auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
    if (actor && !actor->m151(3))
        setFinished();
}

}  // namespace uking::action
