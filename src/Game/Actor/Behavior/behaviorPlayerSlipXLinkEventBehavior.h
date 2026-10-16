#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::behavior {

class PlayerSlipXLinkEventBehavior : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(PlayerSlipXLinkEventBehavior, ksys::act::ai::Behavior)
public:
    explicit PlayerSlipXLinkEventBehavior(const InitArg& arg);
    ~PlayerSlipXLinkEventBehavior() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ Unk_71012419b4 _28;
    /* 0x48 */ u32 _48 = 0;
    /* 0x4c */ u32 _4c = 0;
    /* 0x50 */ u8 _50 = 0;
    /* 0x51 */ bool _51 = false;
};
KSYS_CHECK_SIZE_NX150(PlayerSlipXLinkEventBehavior, 0x58);

}  // namespace uking::behavior
