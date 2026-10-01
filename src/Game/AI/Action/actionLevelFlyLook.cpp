#include "Game/AI/Action/actionLevelFlyLook.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

LevelFlyLook::LevelFlyLook(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LevelFlyLook::~LevelFlyLook() = default;

bool LevelFlyLook::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LevelFlyLook::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    auto* actor = mActor;
    _60 = actor->getVelocity().y;
    _64 = actor->getAngVelocity().y;
    sub_7100741034(&_68, actor);
    actor->getMtx().getTranslation(_8c);
    _98 = ksys::Timer(8.0f, 8.0f);
    _a4 = _8c.y;
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
}

void LevelFlyLook::leave_() {
    ksys::act::ai::Action::leave_();
}

void LevelFlyLook::loadParams_() {
    getStaticParam(&mHeight_s, "Height");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void LevelFlyLook::calc_() {
    ksys::act::ai::Action::calc_();
}

float LevelFlyLook::m32() {
    return _8c.y + *mHeight_s;
}

bool LevelFlyLook::m33(float x) {
    return false;
}

}  // namespace uking::action
