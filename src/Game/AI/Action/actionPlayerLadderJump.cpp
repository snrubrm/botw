#include "Game/AI/Action/actionPlayerLadderJump.h"
#include <cmath>
#include "Game/AI/aiUnk_7101e7c5d0.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PlayerLadderJump::PlayerLadderJump(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: operand order of the final `speed * offset` product (the original multiplies speed by the
// ladder offset, ours swaps the operands)
void PlayerLadderJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x80);

    auto* player = static_cast<ksys::act::Player*>(mActor);
    const f32 height = player->_1810.y - player->_181c.y;
    const f32 offset = sUnk_7101e7c5d0;
    player->_1800 = 0;
    const f32 ratio = height / offset;
    if (ratio > 0.01f) {
        if (ratio > 0.5f) {
            static_cast<ksys::act::Player*>(mActor)->_1800 = ratio - 1.0f;
            if (static_cast<ksys::act::Player*>(mActor)->_1800 > 0.0f)
                static_cast<ksys::act::Player*>(mActor)->_1800 = 0.0f;
        } else {
            static_cast<ksys::act::Player*>(mActor)->_1800 = ratio;
        }
    }

    f32 speed = 6.0f;
    if (static_cast<ksys::act::Player*>(mActor)->_1800 <= 0.0f) {
        if (mActor->getASList()->x_1(0, 0) == "LadderUp")
            speed = 5.0f;
    }
    static_cast<ksys::act::Player*>(mActor)->_1810.y += speed * sUnk_7101e7c5d0;
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("LadderJump", true, -1.0f);
    static_cast<ksys::act::Player*>(mActor)->m371(*mEnergyJump_s);
}

void PlayerLadderJump::leave_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_181c = player->_1810;
}

void PlayerLadderJump::loadParams_() {
    getStaticParam(&mEnergyJump_s, "EnergyJump");
}

void PlayerLadderJump::calc_() {
    sead::Vector3f move{0, 0, 0};
    ksys::act::Player* player;
    if (mActor->getASList()->x_4(0, 0)) {
        setFinished();
        player = static_cast<ksys::act::Player*>(mActor);
    } else {
        const auto& mtx = static_cast<ksys::act::Player*>(mActor)->_1b18;
        sead::Vector3f dir;
        mtx.getBase(dir, 2);
        dir.normalize();
        const f32 angle = std::atan2(dir.x, dir.z);
        move = mActor->getASList()->sub_710115D2D4();
        ksys::util::sub_71011EF010(&move, angle);
        player = static_cast<ksys::act::Player*>(mActor);
        move *= player->_1800 / 6.0f + 1.0f;
    }
    player->_181c += move * ksys::VFR::instance()->getDeltaFrame();
    player = static_cast<ksys::act::Player*>(mActor);
    player->sub_7100892100(player->_181c);
}

bool PlayerLadderJump::isChangeable() const {
    return true;
}

}  // namespace uking::action
