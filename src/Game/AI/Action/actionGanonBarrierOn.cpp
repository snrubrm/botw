#include "Game/AI/Action/actionGanonBarrierOn.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include "Game/Actor/actLastBoss.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

GanonBarrierOn::GanonBarrierOn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonBarrierOn::~GanonBarrierOn() = default;

bool GanonBarrierOn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonBarrierOn::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    bool in_event = mActor->get1a0() != nullptr;
    if (!in_event) {
        auto* obj = mActor->getMapObject();
        in_event = obj && obj->getFlags0().isOn(ksys::map::Object::Flag0::_20000);
    }
    if (in_event) {
        sub_71005DB3EC(mActor);
        sub_7100739900(mActor);
    }
    mFlags.reset(Flag::Changeable);
}

void GanonBarrierOn::leave_() {
    sub_7100739918(mActor);
    if (auto* boss = sead::DynamicCast<uking::act::LastBoss>(mActor))
        boss->stunEnd();
}

void GanonBarrierOn::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
}

void GanonBarrierOn::calc_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD780(mActor, 59, &query, 0, 0)) {
        if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor)) {
            boss->_14e8.set(2);
            boss->_14f8._30.set(2);
            if (!boss->_14e8.isOn(4))
                boss->_14e8.set(4);
            boss->_14f8._30.set(1);
            boss->stunEnd();
            boss->x();
        }
    }
    if (isFinishedAS(1, 0)) {
        if (auto* as_list = mActor->getASList()) {
            if (as_list->x_1(1, 0) == "Damage")
                as_list->startAnimationMaybe(-1.0f, -1.0f, "Wait_Battle_Material", 1, 0, true);
        }
    }
    if (isFinishedAS(0, 0))
        setFinished();
}

bool GanonBarrierOn::isFinished() const {
    return isFinishedAS(0, 0);
}

}  // namespace uking::action
