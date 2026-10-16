#include "Game/Actor/Behavior/behaviorSealNoticePlayerSound.h"

namespace uking::behavior {

SealNoticePlayerSound::SealNoticePlayerSound(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SealNoticePlayerSound::~SealNoticePlayerSound() = default;

bool SealNoticePlayerSound::init_(sead::Heap* heap) {
    return true;
}

void SealNoticePlayerSound::calc() {}

void SealNoticePlayerSound::loadParams() {
    getAITreeVariable(&mPlayerSoundSealRefCount_a, "PlayerSoundSealRefCount");
}

void SealNoticePlayerSound::enter() {
    ++*mPlayerSoundSealRefCount_a;
}

void SealNoticePlayerSound::leave() {
    --*mPlayerSoundSealRefCount_a;
}

}  // namespace uking::behavior
