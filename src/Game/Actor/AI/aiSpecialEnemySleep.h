#pragma once

#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class SpecialEnemySleep : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SpecialEnemySleep, ksys::act::ai::Ai)
public:
    explicit SpecialEnemySleep(const InitArg& arg);
    ~SpecialEnemySleep() override;

    bool isChangeable() const override;
    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34() { changeChild("起き上がる"); }
    virtual void m35();
    virtual bool m36() { return false; }
    // Returns an awareness-related object (type unknown); x receives an index.
    virtual ksys::act::Unk_7100d78e50* m37(int* x);
    virtual void m38(int x, ksys::act::Unk_7100d78e50* entry) {}
    virtual bool m39(sead::Vector3f* pos) { return false; }

protected:
    // static_param at offset 0x38
    const float* mAwakeDelayTime_s{};
    // static_param at offset 0x40
    const bool* mIsAwakenByHearing_s{};
    // static_param at offset 0x48
    const bool* mIsWaitAfterAwaken_s{};
    bool _50{};
    bool _51{};
    bool _52{};
    ksys::Timer _54;
};

}  // namespace uking::ai
