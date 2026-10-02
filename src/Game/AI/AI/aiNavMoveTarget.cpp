#include "Game/AI/AI/aiNavMoveTarget.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

// NON_MATCHING: lib/sead's FixedObjList puts its work buffer at an 8-aligned offset (0x80); the original's
// is at 0x7c (right after the ObjList), which shifts the free-list setup stores
NavMoveTarget::NavMoveTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NavMoveTarget::~NavMoveTarget() = default;

// NON_MATCHING: the original's three casts to the checker data branch (cbz / blr / tbz, `add x, #8` or
// null) instead of select and the first one stores through the unchecked object pointer
bool NavMoveTarget::init_(sead::Heap* heap) {
    sub_71005E2C58(mActor);
    if (*mVibrateCheckTime_s >= 1) {
        if (!_310.acquire(heap, static_cast<Unk_71025afb58**>(mRefPosVibrateCheckerForAI_a)))
            return false;
        _310.getData()->_84 = 3.0f;
        if (*mVibrateCheckTime_s >= 1)
            _310.getData()->_88 = *mVibrateCheckTime_s;
    }
    if (*mRotVibrateCheckTime_s >= 1) {
        if (!_318.acquire(heap, static_cast<Unk_71025afb58**>(mRefVelRotVibrateCheckerforAI_a)))
            return false;
        _318.getData()->sub_710071F494(*mRotVibrateCheckTime_s, 3.0f);
    }
    return true;
}

void NavMoveTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NavMoveTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

// NON_MATCHING: the original computes this + 0x320 (WeaponIdx) before the first call
void NavMoveTarget::loadParams_() {
    getStaticParam(&mVibrateCheckTime_s, "VibrateCheckTime");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mReachTargetArea_s, "ReachTargetArea");
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mTooFarDist_s, "TooFarDist");
    getStaticParam(&mUseCharacterRadius_s, "UseCharacterRadius");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getAITreeVariable(&mRefPosVibrateCheckerForAI_a, "RefPosVibrateCheckerForAI");
    getAITreeVariable(&mRefVelRotVibrateCheckerforAI_a, "RefVelRotVibrateCheckerforAI");
    getStaticParam(&mIsLastLineReachCheck_s, "IsLastLineReachCheck");
    getStaticParam(&mRotVibrateCheckTime_s, "RotVibrateCheckTime");
}

void NavMoveTarget::m35(sead::Vector3f* out) {
    if (out)
        out->set(*mTargetPos_d);
}

// NON_MATCHING: the original loads mActor for the call after the nav radius (scheduling)
bool NavMoveTarget::m36() {
    const sead::Vector3f pos = *m34();
    auto* nav = mActor->m45();
    return sub_710072CB78(mActor, pos, nullptr, nav ? nav->_2a8 * nav->_2ac : 0.0f, -1);
}

// NON_MATCHING: the original loads mActor for the call after the nav radius (scheduling)
bool NavMoveTarget::m37() {
    const sead::Vector3f pos = *m34();
    auto* nav = mActor->m45();
    return sub_710072F944(mActor, pos, nullptr, nav ? nav->_2a8 * nav->_2ac : 0.0f, 10.0f);
}

}  // namespace uking::ai
