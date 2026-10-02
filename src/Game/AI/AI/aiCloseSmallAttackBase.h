#pragma once

#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CloseSmallAttackBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CloseSmallAttackBase, ksys::act::ai::Ai)
public:
    explicit CloseSmallAttackBase(const InitArg& arg);
    ~CloseSmallAttackBase() override = default;
    bool isFinished() const override {
        if (mFlags.isOn(Flag::Finished))
            return true;
        if (isCurrentChild(m35()))
            return getCurrentChild()->isFinished();
        return false;
    }
    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;

    virtual const char* m34() const = 0;
    virtual const char* m35() const = 0;
    virtual void m36() {}

protected:
    // static_param at offset 0x38
    const float* mCloseRadius_s{};
    // static_param at offset 0x40
    const int* mWeaponIdx_s{};
    // static_param at offset 0x48
    const bool* mIsIgnoreSmallHit_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    Unk_7102451ba0 _58;
    bool _80 = false;
};

}  // namespace uking::ai
