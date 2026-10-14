#pragma once

#include <cmath>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

class SandwormFindTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SandwormFindTarget, ksys::act::ai::Ai)
public:
    explicit SandwormFindTarget(const InitArg& arg);
    ~SandwormFindTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710055a3dc: activates the attack sensor and changes to the "移動" child with the target position
    void sub_710055A3DC();
    // 0x710055a530: changes to the "威嚇" child with the target position
    void sub_710055A530();
    // inline-only in the original; names are guesses (enter_ and calc_ both inline the navmesh reachability test
    // (sub_710072F944) and the lost test (LostVMin / LostVMax / LostRange, sub_71005D9F4C))
    bool isTargetReachable() const {
        auto* actor = mActor;
        const sead::Vector3f pos = sub_71005D9330(actor);
        auto* nav = actor->m45();
        return sub_710072F944(actor, pos, nullptr, nav ? nav->getRadiusMaybe() : 0.0f, 3.0f);
    }
    bool isTargetLost() const {
        auto* actor = mActor;
        const sead::Vector3f pos = sub_71005D9330(actor);
        const sead::Vector3f diff = pos - actor->getMtx().getTranslation();
        if (diff.y < *mLostVMin_s || *mLostVMax_s < diff.y)
            return true;
        if (std::sqrt(diff.x * diff.x + diff.z * diff.z) > *mLostRange_s)
            return true;
        return sub_71005D9F4C(pos);
    }
    // 0x710055a614 (CSV sandwormFindTarget): changes to the "戦闘" child with the target position
    void sub_710055A614();
    // static_param at offset 0x38
    const int* mLostTimer_s{};
    // static_param at offset 0x40
    const float* mLostVMin_s{};
    // static_param at offset 0x48
    const float* mLostVMax_s{};
    // static_param at offset 0x50
    const float* mLostRange_s{};
    // static_param at offset 0x58
    const float* mAttackRange_s{};
    u32 _60 = 0;
    u32 _64 = 0;
    u32 _68 = 0;
};
KSYS_CHECK_SIZE_NX150(SandwormFindTarget, 0x70);

}  // namespace uking::ai
