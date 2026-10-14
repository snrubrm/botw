#pragma once

#include <container/seadFreeList.h>
#include <container/seadPtrArray.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::phys {
class NavMeshCharacter;
}

namespace uking::action {

// Placeholder name: the list of positions that m32 appends to (a pointer array whose elements come from a free list;
// the original has no out-of-line copy of the code that appends to it: NPCEscape / NPCTargetMove / NpcSwimNavMove /
// DefRandomMoveAction::m32 all inline the same sequence).
struct RandomMovePoints {
    sead::PtrArray<sead::Vector3f> mPoints;
    sead::FreeList mFreeList;

    // inline-only in the original; name is a guess (the same sequence is inlined in the m32 of NPCEscape, NPCTargetMove,
    // NpcSwimNavMove and DefRandomMoveAction).
    void add(const sead::Vector3f& point) {
        if (mPoints.isFull())
            return;
        auto* p = static_cast<sead::Vector3f*>(mFreeList.alloc());
        p->set(point);
        mPoints.pushBack(p);
    }
};

class RandomMoveAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RandomMoveAction, ksys::act::ai::Action)
public:
    explicit RandomMoveAction(const InitArg& arg);
    // The original keeps this destructor out of line next to the subclasses' inlined copies, which a
    // defaulted destructor does not. Written like upstream's GameDataFlagSelector::~GameDataFlagSelector()
    // { ; } (commit 96101229).
    ~RandomMoveAction() override { ; }

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // inline in the original (emitted out of line in this TU); signature is a guess
    virtual s32 m32(RandomMovePoints* points) { return 0; }
    // The first parameter is unused; signature is a guess (0x7100d33e10).
    virtual void m33(void*, ksys::phys::NavMeshCharacter* nav);

    // static_param at offset 0x20
    const bool* mIsSuccessWhenGoalReached_s{};
    sead::Vector3f _28 = sead::Vector3f::zero;
    f32 _34 = 0;
};

KSYS_CHECK_SIZE_NX150(RandomMoveAction, 0x38);

}  // namespace uking::action
