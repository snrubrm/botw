#pragma once

#include <prim/seadSafeString.h>
#include "Game/Actor/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

// CSV name: CancelMessageSendToParts (the base of that behavior).
class CancelMessageSendToPartsBase : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(CancelMessageSendToPartsBase, ksys::act::ai::Behavior)
public:
    explicit CancelMessageSendToPartsBase(const InitArg& arg);
    ~CancelMessageSendToPartsBase() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void onChangeChild() override;
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
