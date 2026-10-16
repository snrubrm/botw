#pragma once

#include <prim/seadSafeString.h>
#include "Game/Actor/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class DisableWeakPointActor : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(DisableWeakPointActor, ksys::act::ai::Behavior)
public:
    explicit DisableWeakPointActor(const InitArg& arg);
    ~DisableWeakPointActor() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void loadParams() override;
    void enter() override;
    void leave() override;

    /* 0x28 */ sead::SafeString mWeakPointKey_s{};
    /* 0x38 */ Unk_7102357d48 _38{mActor, 0x800002f};
    /* 0x50 */ Unk_7102357d70 _50{mActor, 0x8000030};
};
KSYS_CHECK_SIZE_NX150(DisableWeakPointActor, 0x68);

}  // namespace uking::behavior
