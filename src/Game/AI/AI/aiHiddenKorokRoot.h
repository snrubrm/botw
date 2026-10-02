#pragma once

#include <prim/seadDelegate.h>
#include "Game/AI/aiMessage3DText.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::phys {
class CollisionInfo;
}

namespace uking::ai {

class HiddenKorokRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HiddenKorokRoot, ksys::act::ai::Ai)
public:
    explicit HiddenKorokRoot(const InitArg& arg);
    ~HiddenKorokRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    void invokedTalk();
    void invokedExamine();
    void callHiddenKorokFoundDemo();

protected:
    // static_param at offset 0x38
    const float* mPainTalkHitSpeed_s{};
    // static_param at offset 0x40
    const float* mPainTalkDistance_s{};
    // map_unit_param at offset 0x48
    const int* mKorokEventStartWaitFrame_m{};
    // map_unit_param at offset 0x50
    const bool* mIsAppearCheck_m{};
    // map_unit_param at offset 0x58
    sead::SafeString mPlacementType_m{};
    // map_unit_param at offset 0x68
    const bool* mIsHiddenKorokLiftAppear_m{};
    // map_unit_param at offset 0x70
    const bool* mIsInvisibleKorok_m{};
    ksys::phys::CollisionInfo* _78{};
    bool _80{};
    bool _81{};
    bool _82{};
    // Zeroed by the constructor (8 + 4 bytes each); not used by this class's functions.
    void* _88{};
    u32 _90{};
    void* _98{};
    u32 _a0{};
    Message3DText _a8;
    sead::Delegate<HiddenKorokRoot> _180{this, &HiddenKorokRoot::invokedTalk};
    sead::Delegate<HiddenKorokRoot> _1a0{this, &HiddenKorokRoot::invokedExamine};
};
KSYS_CHECK_SIZE_NX150(HiddenKorokRoot, 0x1c0);

}  // namespace uking::ai
