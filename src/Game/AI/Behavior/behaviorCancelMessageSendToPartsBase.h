#pragma once

#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

// CSV name: CancelMessageSendToParts (the base of that behavior).
class CancelMessageSendToPartsBase : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(CancelMessageSendToPartsBase, ksys::act::ai::Behavior)
public:
    explicit CancelMessageSendToPartsBase(const InitArg& arg);
    ~CancelMessageSendToPartsBase() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m11() override;
    virtual void m14() {}
    virtual Unk_7102357d20* m15() { return nullptr; }
    // 0x710062c280
    void sub_710062C280();

    /* 0x28 */ const bool* mIsEnter_s{};
    /* 0x30 */ const bool* mIsLeave_s{};
    /* 0x38 */ const bool* mIsChangeChild_s{};
    /* 0x40 */ sead::SafeString mPartsName_s{};
};

}  // namespace uking::behavior
