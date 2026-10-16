#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class BossBgmDamaged : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(BossBgmDamaged, ksys::act::ai::Behavior)
public:
    explicit BossBgmDamaged(const InitArg& arg);
    ~BossBgmDamaged() override;
    bool init_(sead::Heap* heap) override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void onChangeChild() override {}
    virtual bool m14() { return false; }
    void calc() override;

    /* 0x28 */ const int* mDieType_s{};
};
KSYS_CHECK_SIZE_NX150(BossBgmDamaged, 0x30);

}  // namespace uking::behavior
