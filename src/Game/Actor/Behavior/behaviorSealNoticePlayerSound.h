#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SealNoticePlayerSound : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SealNoticePlayerSound, ksys::act::ai::Behavior)
public:
    explicit SealNoticePlayerSound(const InitArg& arg);
    ~SealNoticePlayerSound() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ int* mPlayerSoundSealRefCount_a{};
};
KSYS_CHECK_SIZE_NX150(SealNoticePlayerSound, 0x30);

}  // namespace uking::behavior
