#pragma once

#include "Game/AI/Action/actionWillBallAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

// Placeholder name (the singleton at 0x710260de68; declared only): the method at 0x7100f85eb8 (700 B) is a line query from
// `from` to `to` (`radius` 3 here) that answers whether something is in the way.
class Unk_710260de68 {
public:
    static Unk_710260de68* instance() { return sInstance; }
    bool sub_7100F85EB8(f32 radius, const sead::Vector3f* from, const sead::Vector3f* to, void* unused);

private:
    static Unk_710260de68* sInstance;
};

class WillBallAvoidCenterDist : public WillBallAction {
    SEAD_RTTI_OVERRIDE(WillBallAvoidCenterDist, WillBallAction)
public:
    explicit WillBallAvoidCenterDist(const InitArg& arg);
    ~WillBallAvoidCenterDist() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32(sead::Vector3f* direction, f32* distance, f32* progress) override;

    // static_param at offset 0x98
    const float* mDist_s{};
    // static_param at offset 0xa0
    const float* mMaxDist_s{};
    // static_param at offset 0xa8
    const float* mMiddleDist_s{};
    // dynamic_param at offset 0xb0
    sead::Vector3f* mCenterPos_d{};
};

}  // namespace uking::action
