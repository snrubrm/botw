#include "Game/Actor/Player/Action/actionPlayerDiveMove.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"

namespace uking::action {

PlayerDiveMove::PlayerDiveMove(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDiveMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x400);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x2000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x2000000);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SwimWait", true, -1.0f);
    if (auto* controller = mActor->getCharacterController()) {
        controller->mFlags.set(0x8);
        controller->mFlags.set(0x20000);
    }
    _38 = 0;
}

void PlayerDiveMove::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->mFlags.reset(0x8);
        controller->mFlags.reset(0x20000);
    }
}

void PlayerDiveMove::loadParams_() {
    getStaticParam(&mAnmDrivenDist_s, "AnmDrivenDist");
    getStaticParam(&mFinishDist_s, "FinishDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: Player and target loads use different registers and scheduling.
void PlayerDiveMove::calc_() {
    if (_38 == 0) {
        auto* player = static_cast<ksys::act::Player*>(mActor);
        player->_20bc.value = 0;
        player->_20bc.prev_value = 0;
        player = static_cast<ksys::act::Player*>(mActor);
        const f32 dx = mTargetPos_d->x - player->_1770.x;
        const f32 dz = mTargetPos_d->z - player->_1770.z;
        ksys::act::Player::Unk1 target(sead::Mathf::atan2Idx(dx, dz));
        if (static_cast<ksys::act::Player*>(mActor)->sub_7100857014(-1.0f, &target, -1, 0x4000000)) {
            static_cast<ksys::act::Player*>(mActor)->_1800 = sead::Mathf::sqrt(dx * dx + dz * dz) /
                                                          *mAnmDrivenDist_s;
            static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SwimDash", true, -1.0f);
            _38 = 1;
        }
        static_cast<ksys::act::Player*>(mActor)->actionCommon();
    } else if (_38 == 1) {
        static_cast<ksys::act::Player*>(mActor)->sub_7100877BD8();
        auto* player = static_cast<ksys::act::Player*>(mActor);
        player->_20bc.value *= player->_1800;
        player->_20bc.prev_value = player->_20bc.value;
        static_cast<ksys::act::Player*>(mActor)->actionCommon();
        player = static_cast<ksys::act::Player*>(mActor);
        const f32 dx = mTargetPos_d->x - player->_1770.x;
        const f32 dz = mTargetPos_d->z - player->_1770.z;
        if (sead::Mathf::sqrt(dx * dx + dz * dz) <= *mFinishDist_s)
            setFinished();
        else if (mActor->getASList()->x_4(0, 0))
            setFailed();
    }

    if (auto* controller = mActor->getCharacterController()) {
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

bool PlayerDiveMove::isChangeable() const {
    return false;
}

}  // namespace uking::action
