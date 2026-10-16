#include "Game/Actor/Player/Action/actionPlayerWaterFall.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"

namespace uking::action {

PlayerWaterFall::PlayerWaterFall(const InitArg& arg) : PlayerAction(arg) {}

PlayerWaterFall::~PlayerWaterFall() = default;

void PlayerWaterFall::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x400);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4000);

    auto* player = static_cast<ksys::act::Player*>(mActor);
    const sead::Vector3f back = -*mFrontDir_d;
    player->sub_7100868D7C(2.0f, &back);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SwimWaterfallUp", true,
                                                                       -1.0f);

    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
        controller->mFlags.set(0x20000);
    }

    if (auto* rail = *mRailPtr_d) {
        _38.sub_7100EEBAE0(rail, 0.0f);
        _38.x(static_cast<ksys::act::Player*>(mActor)->_20f0 * 0.5f);
        while (_38._30.sub_7100EEB370().y < static_cast<ksys::act::Player*>(mActor)->_1770.y)
            _38.x(static_cast<ksys::act::Player*>(mActor)->_20f0 * 0.5f);
    } else {
        setFailed();
    }
}

void PlayerWaterFall::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
        controller->mFlags.reset(0x20000);
    }
}

void PlayerWaterFall::loadParams_() {
    getStaticParam(&mSpeedClimb_s, "SpeedClimb");
    getDynamicParam(&mRailPtr_d, "RailPtr");
    getDynamicParam(&mFrontDir_d, "FrontDir");
}

// NON_MATCHING: stack slot of the velocity vector (the original places it below the contact iterators).
void PlayerWaterFall::calc_() {
    if (!_38.sub_7100EEBB74()) {
        setFailed();
        return;
    }

    if ((_38._30.sub_7100EEB370() - static_cast<ksys::act::Player*>(mActor)->_1770).length() <
        static_cast<ksys::act::Player*>(mActor)->_20f0)
        _38.x(static_cast<ksys::act::Player*>(mActor)->_20f0 * 0.5f);

    sead::Vector3f dir = _38._30.sub_7100EEB370() - static_cast<ksys::act::Player*>(mActor)->_1770;
    dir.normalize();
    const sead::Vector3f velocity = dir * (*mSpeedClimb_s * 30.0f);

    if (_38.m3())
        setFinished();

    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F6FC(velocity);
        controller->sub_7100F5FC8C(static_cast<ksys::act::Player*>(mActor)->_1b18);
        if (auto* info = controller->sub_7100F635D8()) {
            if (info->getNumContactPoints() != 0 && !info->begin().isEnd()) {
                for (const auto* point : *info) {
                    auto* body = point->body_b;
                    if (body && (body->getContactLayer() == ksys::phys::ContactLayer::EntityObject ||
                                 body->getContactLayer() == ksys::phys::ContactLayer::EntityGroundObject ||
                                 body->getContactLayer() == ksys::phys::ContactLayer::EntityTree))
                        setFailed();
                }
            }
        }
    }
}

bool PlayerWaterFall::isChangeable() const {
    return false;
}

}  // namespace uking::action
