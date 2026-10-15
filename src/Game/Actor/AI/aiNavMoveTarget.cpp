#include "Game/Actor/AI/aiNavMoveTarget.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007320F0.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

// NON_MATCHING: only the position of the ObjList count store (`mCount = 0`, +0x60), which the original
// schedules after the vtable address load
NavMoveTarget::NavMoveTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NavMoveTarget::~NavMoveTarget() = default;

// NON_MATCHING: the original's three casts to the checker data branch (cbz / blr / tbz, `add x, #8` or
// null) instead of select and the first one stores through the unchecked object pointer
bool NavMoveTarget::init_(sead::Heap* heap) {
    sub_71005E2C58(mActor);
    if (*mParams.mVibrateCheckTime_s >= 1) {
        if (!_310.acquire(heap, static_cast<Unk_71025afb58**>(mRefPosVibrateCheckerForAI_a)))
            return false;
        _310.getData()->_84 = 3.0f;
        if (*mParams.mVibrateCheckTime_s >= 1)
            _310.getData()->_88 = *mParams.mVibrateCheckTime_s;
    }
    if (*mParams.mRotVibrateCheckTime_s >= 1) {
        if (!_318.acquire(heap, static_cast<Unk_71025afb58**>(mRefVelRotVibrateCheckerforAI_a)))
            return false;
        _318.getData()->sub_710071F494(*mParams.mRotVibrateCheckTime_s, 3.0f);
    }
    return true;
}

// NON_MATCHING: the radius parameter load is moved into the non-null movement branch.
void NavMoveTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71004B7C68();
    auto* actor = mActor;
    auto* nav = actor->m45();
    if (nav) {
        _368 = sub_71005E2BCC(actor);
        if (_368) {
            auto* current_nav = mActor->m45();
            if (current_nav && (current_nav->_2a4.load() & 0xffff) != 23) {
                _50.clear();
                if (!nav->_18)
                    ksys::phys::HavokAI::instance()->sub_7100F82BCC(nav);
                const bool use_character_radius = *mParams.mUseCharacterRadius_s;
                auto* movement = _368->_0;
                if (movement)
                    movement->sub_7100F7604C(use_character_radius ? movement->getRadiusMaybe() : 0.2f);
                sub_71004B7F80();
                return;
            }
        }
    }
    sub_71004B7E90();
}

// NON_MATCHING: the existing checker-data cast selects rather than branching.
void NavMoveTarget::sub_71004B7C68() {
    if (_310._0) {
        auto* checker = *_310._0;
        if (sead::IsDerivedFrom<Unk_71025b0578>(checker) &&
            static_cast<Unk_71025b0578*>(checker)->mRefCount > 0) {
            _310.getData()->reset();
        }
    }
    if (_318._0) {
        auto* checker = *_318._0;
        if (sead::IsDerivedFrom<Unk_71025b7688>(checker) &&
            static_cast<Unk_71025b7688*>(checker)->mRefCount > 0) {
            _318.getData()->sub_710071F47C();
        }
    }
}

// NON_MATCHING: query/output stack slots, timer store order and transition tail layout.
void NavMoveTarget::sub_71004B7F80() {
    auto* nav = mActor->m45();
    if (!nav || (nav->_2a4.load() & 0xffff) == 0x17) {
        sub_71004B7E90();
        return;
    }
    nav = mActor->m45();
    if (!nav) {
        sub_71004B7E90();
        return;
    }
    sead::Vector3f query_position;
    bool valid;
    {
        auto query = nav->sub_7100F760F0(&query_position, *m34(), 3.5f);
        valid = query.sub_7100F7EB40();
    }
    if (!valid) {
        sub_71004B7E90();
        return;
    }

    if (auto* current_nav = mActor->m45()) {
        u8 state;
        {
            auto lock = sead::makeScopedLock(current_nav->_1e0);
            state = current_nav->_294 | 1;
        }
        if (state == 5)
            current_nav->sub_7100F76790();
    }
    if (m37()) {
        if (isCurrentChild("直進")) {
            auto* child = getCurrentChild();
            if (!child->isFinished() && !child->isFailed()) {
                _370.reset(*mParams.mRepathTime_s);
                return;
            }
        }
        sub_71004B9984();
        return;
    }

    if (_368->_8 == 1) {
        if (auto* current_nav = mActor->m45()) {
            if (!current_nav->_194.isNan()) {
                const sead::Vector3f destination = current_nav->_194;
                bool can_move = true;
                if (auto* latest_nav = mActor->m45()) {
                    f32 distance;
                    {
                        auto lock = sead::makeScopedLock(latest_nav->_1e0);
                        distance = latest_nav->_2cc;
                    }
                    can_move = !(distance >= *mParams.mTooFarDist_s);
                }
                if (can_move) {
                    _368->_8 = -1;
                    _370.reset(*mParams.mRepathTime_s);
                    ksys::act::ai::InlineParamPack params;
                    params.addVec3(destination, "TargetPos", -1);
                    changeChild("移動", &params);
                    return;
                }
            }
        }
    }

    _370.reset(*mParams.mRepathTime_s);
    sub_71004B9590();
    if ((isCurrentChild("直進") || isCurrentChild("移動")) && !getCurrentChild()->isFailed())
        return;
    sub_71004B7E90();
}

void NavMoveTarget::sub_71004B7E90() {
    sub_71004B7C68();
    const sead::Vector3f pos = *m34();
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    changeChild("見まわす", &params);
}

// NON_MATCHING: the original loads the three translation floats and the three target floats before the
// first subtraction; we interleave one subtraction after the translation loads.
bool NavMoveTarget::sub_71004B9388() {
    const sead::Vector3f& target = *m34();
    sead::Vector3f diff = target - mActor->getMtx().getTranslation();
    if (isCurrentChild("直進"))
        diff.y = 0;
    const f32 dist = diff.length();
    return dist <= *mParams.mReachTargetArea_s + sub_71007320F0(mActor, *mParams.mWeaponIdx_s) ||
           _368->_8 == 3;
}

// NON_MATCHING: query/output stack slots and horizontal component load scheduling.
bool NavMoveTarget::sub_71004B9590() {
    const sead::Vector3f target = *m34();
    auto* nav = mActor->m45();
    if (!nav)
        return false;

    sead::Vector3f position;
    bool valid;
    {
        auto query = nav->sub_7100F76078(&position, target, 3.0f);
        valid = query.sub_7100F7EB40();
    }
    if (!valid)
        return false;

    sead::Vector3f direction = position - *mParams.mTargetPos_d;
    direction.y = 0.0f;
    if (sead::Mathf::sqrt(direction.x * direction.x + direction.z * direction.z) >= 0.5f) {
        direction.normalize();
        position += direction;
    }
    auto* state = _368;
    if (state->_0) {
        state->_0->sub_7100F75F8C(position);
        state->_8 = 0;
    }
    return true;
}

void NavMoveTarget::sub_71004B9984() {
    _368->_8 = -1;
    if (auto* nav = _368->_0)
        nav->inlineReset();
    const f32 repath_time = *mParams.mRepathTime_s;
    _370 = ksys::Timer(repath_time, repath_time);
    const sead::Vector3f target = *m34();
    ksys::act::ai::InlineParamPack params;
    params.addVec3(target, "TargetPos", -1);
    changeChild("直進", &params);
}

void NavMoveTarget::leave_() {
    if (_368) {
        if (_368->_0)
            _368->_0->inlineReset();
        _368->_8 = -1;
    }
}

void NavMoveTarget::loadParams_() {
    getStaticParam(&mParams.mVibrateCheckTime_s, "VibrateCheckTime");
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mReachTargetArea_s, "ReachTargetArea");
    getStaticParam(&mParams.mRepathTime_s, "RepathTime");
    getStaticParam(&mParams.mTooFarDist_s, "TooFarDist");
    getStaticParam(&mParams.mUseCharacterRadius_s, "UseCharacterRadius");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getAITreeVariable(&mRefPosVibrateCheckerForAI_a, "RefPosVibrateCheckerForAI");
    getAITreeVariable(&mRefVelRotVibrateCheckerforAI_a, "RefVelRotVibrateCheckerforAI");
    getStaticParam(&mParams.mIsLastLineReachCheck_s, "IsLastLineReachCheck");
    getStaticParam(&mParams.mRotVibrateCheckTime_s, "RotVibrateCheckTime");
}

void NavMoveTarget::m35(sead::Vector3f* out) {
    if (out)
        out->set(*mParams.mTargetPos_d);
}

bool NavMoveTarget::m36() {
    const sead::Vector3f pos = *m34();
    auto* nav = mActor->m45();
    const f32 radius = nav ? nav->getRadiusMaybe() : 0.0f;
    return sub_710072CB78(mActor, pos, nullptr, radius, -1);
}

bool NavMoveTarget::m37() {
    const sead::Vector3f pos = *m34();
    auto* nav = mActor->m45();
    const f32 radius = nav ? nav->getRadiusMaybe() : 0.0f;
    return sub_710072F944(mActor, pos, nullptr, radius, 10.0f);
}

}  // namespace uking::ai
