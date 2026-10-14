#include "Game/Actor/Player/Action/actionPlayerGrabReady.h"
#include <algorithm>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerGrabReady::PlayerGrabReady(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGrabReady::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(1);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x20);
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
    static_cast<ksys::act::Player*>(mActor)->sub_710088755C();

    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::Attention::instance()->sub_7100D7482C(&accessor);
    sead::Vector3f pos;
    accessor.getMtxPos(&pos);
    sead::Vector3f min;
    sead::Vector3f max;
    accessor.getAabb(&min, &max);
    f32 half = std::max(max.x - min.x, max.y - min.y);
    half = std::max(half, max.z - min.z) * 0.5f;
    half *= accessor.sub_7100D12100();

    const sead::Vector3f start = pos;
    sead::Vector3f end = pos;
    end.y -= half + 0.1f;
    if (!static_cast<ksys::act::Player*>(mActor)->sub_710087F360(start, end, &pos, nullptr))
        pos.y -= half;

    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->getASList()->x_6(0x10, 0, pos.y - player->_1770.y);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("GrabReady", true, -1.0f);
}

void PlayerGrabReady::leave_() {}

void PlayerGrabReady::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_17f0) {
        if (!player->getConnectedCalcChild())
            setFailed();
    } else {
        player->_17f0 = 1;
    }
    if (mActor->getASList()->x_4(0, 0))
        setFinished();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerGrabReady::isChangeable() const {
    return false;
}

}  // namespace uking::action
