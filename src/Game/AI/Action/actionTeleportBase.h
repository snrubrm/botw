#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class TeleportBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TeleportBase, ksys::act::ai::Action)
public:
    explicit TeleportBase(const InitArg& arg);
    ~TeleportBase() override;

    // Saved physics state of the actor (filled / restored by sub_710072BB70 / sub_710072BEC4 around the
    // teleport; names and types of the fields are guesses).
    struct SavedState {
        u32 _0 = 1;
        u32 _4 = 0;
        bool _8 = false;
        bool _9 = true;
        bool _a = true;
    };

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // 0x71002955bc (out of line): the target position `mTargetPos_d` points to.
    const sead::Vector3f& sub_71002955BC() const;
    // 0x7100294f68: moves the actor towards `to` (a destination relative to the current position is
    // derived from both arguments; the character controller / main body velocity or transform is set)
    // and calls m38 with the direction to `target`.
    void sub_7100294F68(const sead::Vector3f& dest, const sead::Vector3f& target);

    virtual const sead::Vector3f& m32() { return sub_71002955BC(); }
    virtual sead::Vector3f& m33() { return *mTargetPos_d; }
    virtual const sead::Vector3f& m34() { return sub_71002955BC(); }
    virtual int m35() { return *mWaitTime_s; }
    virtual void m36() {}
    virtual void m37();
    virtual void m38(const sead::Vector3f& dir);
    virtual bool m39(const sead::Vector3f& in, sead::Vector3f* out) {
        out->set(in);
        return true;
    }

    // static_param at offset 0x20
    const int* mWaitTime_s{};
    // static_param at offset 0x28
    const int* mTimeRand_s{};
    // static_param at offset 0x30
    const bool* mIsUseChangePos_s{};
    // static_param at offset 0x38
    const bool* mIsLifeGageKeep_s{};
    // static_param at offset 0x40
    sead::SafeString mEffectName_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    ksys::Timer _58{0, 0};
    SavedState _64;
    u32 _70 = 0;  // state of the teleport (0-4)
};

KSYS_CHECK_SIZE_NX150(TeleportBase, 0x78);

}  // namespace uking::action
