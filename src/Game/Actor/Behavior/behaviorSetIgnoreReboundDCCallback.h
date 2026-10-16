#pragma once

#include "Game/Actor/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetIgnoreReboundDCCallback : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetIgnoreReboundDCCallback, ksys::act::ai::Behavior)
public:
    explicit SetIgnoreReboundDCCallback(const InitArg& arg);
    ~SetIgnoreReboundDCCallback() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    struct Params {
        const bool* mEnableRebound_s{};
        const bool* mEnableReboundStrong_s{};
        const bool* mEnableReboundSuper_s{};
    };
    /* 0x28 */ Params mParams;
    /* 0x40 */ Unk_7102451b68 _40;
};
KSYS_CHECK_SIZE_NX150(SetIgnoreReboundDCCallback, 0x68);

}  // namespace uking::behavior
