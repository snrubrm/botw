#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SoundStateLoad : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SoundStateLoad, ksys::act::ai::Behavior)
public:
    explicit SoundStateLoad(const InitArg& arg);
    void m8() override;

};
KSYS_CHECK_SIZE_NX150(SoundStateLoad, 0x28);

}  // namespace uking::behavior
