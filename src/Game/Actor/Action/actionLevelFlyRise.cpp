#include "Game/Actor/Action/actionLevelFlyRise.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

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
    _8c.reset(8.0f);
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

// NON_MATCHING: timer, vector normalization and movement scheduling.
void LevelFlyRise::calc_() {
    auto* actor = mActor;
    const f32 height = actor->getMtx().m[1][3];
    const f32 target_height = *mHeight_s;
    const f32 remaining = target_height < 0.0f ? height - _80.y - target_height :
                                               target_height - (height - _80.y);
    if (remaining <= 0.0f) {
        setFinished();
        return;
    }
    const f32 height_change = height - _98;
    if (height_change <= 0.001f && height_change >= -0.001f) {
        if (_8c.value <= sead::Mathf::epsilon()) {
            setFailed();
            return;
        }
        _8c.update();
    } else {
        _98 = height;
        _8c.value = _8c.previous_value = 8.0f;
    }
    _50.chase(*mSpeed_s, *mSpeed_s * 0.1f);
    _50.updateStats();
    auto* controller = actor->getCharacterController();
    if (!controller)
        return;
    sead::Vector3f velocity;
    controller->sub_7100F5F598(&velocity);
    if (sead::Vector2f(velocity.x, velocity.z).length() > 0.0f)
        sub_7100737C0C(controller, *mPosReduceRatio_s, -sead::Vector3f::ey);

    sead::Vector3f direction = sead::Vector3f::ey;
    if (auto* cc = mActor->getCharacterController()) {
        direction = getUpDir(cc->get70());
        if (*mHeight_s < 0.0f)
            direction = -direction;
        direction.normalize();
    }
    sub_7100737710(controller, direction * _50.value);

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    front.y = 0.0f;
    front.normalize();
    const sead::Vector3f up = getUpDir(controller->get70());
    sub_710073FA94(&_5c, actor);
    sub_710074006C(&_5c, front, up, true, *mRotRatio_s, sead::Mathf::pi2(), 0.0f);
    sub_7100740E04(_5c, controller);
}

}  // namespace uking::action
