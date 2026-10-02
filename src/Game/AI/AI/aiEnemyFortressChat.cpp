#include "Game/AI/AI/aiEnemyFortressChat.h"

namespace uking::ai {

EnemyFortressChat::EnemyFortressChat(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyFortressChat::~EnemyFortressChat() = default;

bool EnemyFortressChat::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyFortressChat::enter_(ksys::act::ai::InlineParamPack* params) {
    _48.reset();
    sub_710038E110();
}

void EnemyFortressChat::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyFortressChat::loadParams_() {
    getStaticParam(&mNextPer_s, "NextPer");
    getAITreeVariable(&mRegistedActorUnit_a, "RegistedActorUnit");
}

}  // namespace uking::ai
