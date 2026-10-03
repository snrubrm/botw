#include "Game/AI/Action/actionKick.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

Kick::Kick(const InitArg& arg) : ActionEx(arg) {}

Kick::~Kick() = default;

bool Kick::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

void Kick::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS("Kick", false, 0, 0, -1.0f);
    _50 = false;
    _54 = 0;
    const f32 speed = mActor->getAngVelocity().length();
    _7c.value = speed;
    _7c.prev_value = speed;
    sub_710073FA90(&_58, mActor);
}

void Kick::loadParams_() {
    getStaticParam(&mPower_s, "Power");
    getStaticParam(&mUpRate_s, "UpRate");
    getStaticParam(&mDirAngle_s, "DirAngle");
    getStaticParam(&mCanKickArea_s, "CanKickArea");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void Kick::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
