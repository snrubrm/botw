#include "Game/AI/Behavior/behaviorSealNoticePlayerSound.h"

namespace uking::behavior {

SealNoticePlayerSound::SealNoticePlayerSound(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SealNoticePlayerSound::~SealNoticePlayerSound() = default;

bool SealNoticePlayerSound::m6(sead::Heap* heap) {
    return true;
}

void SealNoticePlayerSound::m7() {}

void SealNoticePlayerSound::loadParams() {
    getAITreeVariable(&mPlayerSoundSealRefCount_a, "PlayerSoundSealRefCount");
}

}  // namespace uking::behavior
