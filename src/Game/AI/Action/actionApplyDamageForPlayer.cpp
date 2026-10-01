#include "Game/AI/Action/actionApplyDamageForPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ApplyDamageForPlayer::ApplyDamageForPlayer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ApplyDamageForPlayer::~ApplyDamageForPlayer() = default;

bool ApplyDamageForPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool ApplyDamageForPlayer::oneShot_() {
    const s32* life_ptr = mActor->getLife();
    const s32 life = life_ptr ? *life_ptr : 1;
    const s32 damage = *mValue_d;
    *mActor->getLife() = life > damage ? life - damage : 0;
    return true;
}

void ApplyDamageForPlayer::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
}

}  // namespace uking::action
