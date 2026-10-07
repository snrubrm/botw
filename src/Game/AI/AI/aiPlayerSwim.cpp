#include "Game/AI/AI/aiPlayerSwim.h"
#include "Game/AI/aiUnk_7101e7c5d0.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

PlayerSwim::PlayerSwim(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerSwim::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerSwim::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerSwim::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PlayerSwim::loadParams_() {
    getStaticParam(&mCatchHeightL_s, "CatchHeightL");
    getStaticParam(&mCatchHeightH_s, "CatchHeightH");
    getStaticParam(&mEnableHeight_s, "EnableHeight");
}

bool PlayerSwim::isChangeable() const {
    if (getCurrentChild()->isChangeable()) {
        if (isCurrentChild("泳ぎ待機") || isCurrentChild("泳ぎ移動") || isCurrentChild("泳ぎダッシュ") ||
            isCurrentChild("スピンアタック")) {
            return true;
        }
    }
    return false;
}

// 0x71008452b8
// NON_MATCHING: same logic and `mActor` is re-read per use as in the original, but the original shares one `return false` block / epilogue
// between the paths and does not fold `&mActor` into a pre-indexed load (`ldr x0, [x19, #8]!`).
bool PlayerSwim::isFinished() const {
    using Player = ksys::act::Player;
    if (isCurrentChild("泳ぎジャンプ"))
        return false;

    if (static_cast<Player*>(mActor)->_cec.isOnBit(1))
        return static_cast<Player*>(mActor)->isSurfingOnGround();

    if (auto* controller = static_cast<Player*>(mActor)->getCharacterController()) {
        sead::Vector3f position;
        controller->sub_7100F5F6E0(&position);
        if (static_cast<Player*>(mActor)->_20d4 > position.y + sUnk_7101e7c5c8 + 0.05f)
            return false;
    }

    if (static_cast<Player*>(mActor)->_20d4 < static_cast<Player*>(mActor)->_1770.y)
        return true;
    if (!static_cast<Player*>(mActor)->isSurfingOnGround())
        return false;
    if (static_cast<Player*>(mActor)->sub_7100892098() && static_cast<Player*>(mActor)->_20bc.value == 0)
        return false;
    if (static_cast<Player*>(mActor)->_20d4 < static_cast<Player*>(mActor)->_1770.y + sUnk_7101e7c5c8)
        return true;
    return false;
}

}  // namespace uking::ai
