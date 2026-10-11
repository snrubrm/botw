#include "Game/AI/Action/actionPlayerSitStart.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

PlayerSitStart::PlayerSitStart(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: vector extraction and normalization use different registers and stack slots.
void PlayerSitStart::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SitDownSt", true, -1.0f);
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EEB8(0.0f);
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::Attention::instance()->sub_7100D7482C(&accessor)) {
            const auto& mtx = accessor.getActorMtx();
            sead::Vector3f forward;
            sead::Vector3f position;
            mtx.getBase(forward, 2);
            mtx.getTranslation(position);
            forward.normalize();
            position += forward;
            controller->warpActorToPosition(position);
            static_cast<ksys::act::Player*>(mActor)->_1c68.value =
                sead::Mathf::atan2Idx(-forward.x, -forward.z);
            auto* player = static_cast<ksys::act::Player*>(mActor);
            const u32 angle = ksys::util::sUnk_7101EC6BA0 & (player->_1c68.value ^ 0x80000000u);
            player->sub_7100867FE0(ksys::util::angleDiff(angle, player->x_5()));
        }
    }
}

void PlayerSitStart::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5EEB8(1.0f);
}

void PlayerSitStart::calc_() {
    static_cast<ksys::act::Player*>(mActor)->sub_7100877F00(sead::Vector3f::zero);
    if (mActor->getASList()->x_4(0, 0))
        setFinished();
}

bool PlayerSitStart::isChangeable() const {
    return false;
}

}  // namespace uking::action
