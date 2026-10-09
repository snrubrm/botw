#pragma once

#include "Game/AI/AI/aiSimpleWildlifeRoot.h"
#include <container/seadBuffer.h>
#include <gsys/gsysModelAccessKey.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::phys {
class RayCastForRequest;
}

namespace uking::ai {

// Placeholder name: the 0xe8-byte element of FishRoot::_1d0 (a bone key and data that is not recovered yet); its
// destructor removes the bone key first.
struct FishRootBoneEntry {
    ~FishRootBoneEntry() {
        if (_0.isValid())
            _0.remove();
    }

    gsys::BoneAccessKeyEx _0;
    u8 _38[0xe8 - 0x38];
};
KSYS_CHECK_SIZE_NX150(FishRootBoneEntry, 0xe8);

class FishRoot : public SimpleWildlifeRoot {
    SEAD_RTTI_OVERRIDE(FishRoot, SimpleWildlifeRoot)
public:
    explicit FishRoot(const InitArg& arg);
    ~FishRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m34() override;
    bool m35() override;
    bool m36() override;
    void m40() override;
    void m41() override;
    void m39() override;

protected:
    // Declaration only; original method names and void returns are inferred.
    void sub_71003CC69C();
    void sub_71003CC878();
    // Full native tail helper updates the owned animation values; called only by sub_71003CC878.
    void sub_71003CD268();
    // 0x71003ce608 (placeholder name): submits a downward ground ray cast from `start` as tall as the actor.
    bool sub_71003CE608(const sead::Vector3f& start);
    void sub_71003CCA34();
    // 0x71003cd730 (placeholder name)
    void changeToReturn();
    // 0x71003cde1c (placeholder name)
    void changeToDiscoverInterest();
    // 0x71003cd81c (placeholder name)
    void changeToReturnToInitialPlacement(bool is_escape);

    // Aggregate parameter initialization follows the original contiguous parameter block.
    struct Params {
        // static_param at offset 0xf8
        const float* mInWaterDepth_s{};
        // static_param at offset 0x100
        const float* mOnGroundDepth_s{};
        // static_param at offset 0x108
        const float* mNextJumpTimeBase_s{};
        // static_param at offset 0x110
        const float* mNextJumpTimeRand_s{};
        // static_param at offset 0x118
        const float* mAllowReturnThreatDist_s{};
        // static_param at offset 0x120
        const float* mFrameUntilOutOfWater_s{};
        // static_param at offset 0x128
        const float* mDistRunFromPlayerOnReturn_s{};
        // static_param at offset 0x130
        const float* mIgnoreFoodBase_s{};
        // static_param at offset 0x138
        const float* mIgnoreFoodRand_s{};
        // static_param at offset 0x140
        const float* mIgnoreFoodAfterSuccessBase_s{};
        // static_param at offset 0x148
        const float* mIgnoreFoodAfterSuccessRand_s{};
    };
    Params mParams{};
    // 0x160 .. 0x1b4: vector / counters (not decompiled)
    ksys::act::BaseProcLink _150;  // the target of interest
    u8 _160[0x184 - 0x160]{};
    sead::Vector3f _184{};
    sead::Vector3f _190{};
    u8 _19c[4]{};
    f32 _1a0{};
    f32 _1a4{};
    u8 _1a8[0x1b0 - 0x1a8]{};
    s32 _1b0{};
    u8 _1b4[0x1b8 - 0x1b4];
    ksys::phys::RayCastForRequest* _1b8{};
    ksys::phys::RayCastForRequest* _1c0{};
    bool _1c8{};
    bool _1c9{};
    bool _1ca{};
    u8 _1cb[0x1d0 - 0x1cb];
    sead::Buffer<FishRootBoneEntry> _1d0;
    // Placeholder callback: vtable 0x71023ee000; m2 is the large bone-buffer processing routine.
    class Unk_71023ee000 {
    public:
        explicit Unk_71023ee000(sead::Buffer<FishRootBoneEntry>* buffer) : _8(buffer) {}
        virtual void m0() {}
        virtual void m1() {}
        virtual void m2(void* model);
        virtual void m3() {}

        sead::Buffer<FishRootBoneEntry>* _8;
        f32 _10 = 1.0f;
        f32 _14 = 0.5f;
        f32 _18 = 0.52359879f;
        bool _1c = false;
    };
    Unk_71023ee000 _1e0{&_1d0};
};

}  // namespace uking::ai
