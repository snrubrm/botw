#include "Game/AI/Action/actionLevelFlyRise.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "Game/AI/aiUnk_710073fa90.h"

namespace uking::action {

LevelFlyRise::LevelFlyRise(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LevelFlyRise::~LevelFlyRise() = default;

bool LevelFlyRise::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LevelFlyRise::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    auto* cc = mActor->getCharacterController();
    if (!cc)
        return;
    _9c.changeMotionType(cc, ksys::act::MotionType::Hover);
    auto* actor = mActor;
    _50.value = actor->getVelocity().y;
    _50.prev_value = actor->getVelocity().y;
    sub_710073FA90(&_5c, actor);
    actor->getMtx().getTranslation(_80);
    _8c = 8.0f;
    _90 = 8.0f;
    _94 = -1.0f;
    _98 = _80.y;
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
}

void LevelFlyRise::leave_() {
    _9c.resetMotionType(mActor->getCharacterController());
}

void LevelFlyRise::loadParams_() {
    getStaticParam(&mHeight_s, "Height");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mASName_s, "ASName");
}

void LevelFlyRise::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
