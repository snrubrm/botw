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

void SetResetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    sead::Vector3f position;
    actor->getMtx().getTranslation(position);
    f32 yaw = 0.0f;
    if (auto* object = actor->getMapObject())
        yaw = sead::Mathf::rad2deg(object->getRotate().y);
    PlayerResetPosMgr::instance()->setResetPos(position, yaw, actor);
}

// NON_MATCHING: singleton and actor argument loads are scheduled differently.
void SetResetPos::leave_() {
    PlayerResetPosMgr::instance()->sub_71007A6620(mActor);
}

void SetResetPos::loadParams_() {}

void SetResetPos::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
