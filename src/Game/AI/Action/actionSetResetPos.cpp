#include "Game/AI/Action/actionSetResetPos.h"
#include <math/seadMathCalcCommon.h>
#include "Game/gamePlayerResetPosMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::action {

SetResetPos::SetResetPos(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetResetPos::~SetResetPos() = default;

bool SetResetPos::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: translation snapshot loads and stores are combined differently.
void SetResetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    const sead::Vector3f position = actor->getMtx().getTranslation();
    f32 yaw = 0.0f;
    if (auto* object = actor->getMapObject())
        yaw = sead::Mathf::rad2deg(object->getRotate().y);
    PlayerResetPosMgr::instance()->setResetPos(position, yaw, actor);
}

void SetResetPos::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetResetPos::loadParams_() {}

void SetResetPos::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
