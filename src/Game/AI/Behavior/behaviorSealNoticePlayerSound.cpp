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

void SealNoticePlayerSound::m8() {
    ++*mPlayerSoundSealRefCount_a;
}

void SealNoticePlayerSound::m9() {
    --*mPlayerSoundSealRefCount_a;
}

}  // namespace uking::behavior
