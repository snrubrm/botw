#include "Game/Actor/AI/aiAnimalEscapeAI.h"
#include "Game/Actor/actRideable.h"
#include <limits>
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

AnimalEscapeAI::AnimalEscapeAI(const InitArg& arg) : AnimalRndMove(arg) {}

AnimalEscapeAI::~AnimalEscapeAI() = default;

bool AnimalEscapeAI::init_(sead::Heap* heap) {
    return AnimalRndMove::init_(heap);
}

// NON_MATCHING: finite checks, atomic updates and navigation-reset stores use different scheduling.
void AnimalEscapeAI::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalRndMove::enter_(params);
    auto* nav = mActor->m45();
    if (!nav) {
        setFailed();
        return;
    }
    _130.value = _130.previous_value = 150.0f;
    _13c.reset(120.0f);
    _14c = 0;
    _120.set(0.0f, 0.0f, 0.0f);
    _148 = *mShouldEscapeDistance_s +
           *mShouldEscapeDistanceRand_s * sead::GlobalRandom::instance()->getF32();
    _108 = mActor->getMtx().getTranslation();
    _150 = true;
    {
        auto lock = sead::makeScopedLock(nav->_1e0);
        _120 = nav->_284;
    }
    const f32 penalty = *mPenaltyScale_s;
    if (!sead::Mathf::isNan(penalty) && sead::Mathf::abs(penalty) <= sead::Mathf::maxNumber()) {
        auto lock = sead::makeScopedLock(nav->_1e0);
        nav->_2b0 = penalty;
        nav->_220 |= 0x20;
    }
    sub_71003051C0();
    _12c = nav->_2ac;
    const f32 radius_scale = *mNavMeshRadiusScale_s;
    if (!sead::Mathf::isNan(radius_scale) &&
        sead::Mathf::abs(radius_scale) <= sead::Mathf::maxNumber() && nav->_2ac != radius_scale) {
        auto lock = sead::makeScopedLock(nav->_1e0);
        nav->_2ac = radius_scale;
        nav->_220 |= 0x10;
    }
    nav->inlineReset();
    nav->sub_7100F7604C(0.0f);
    if (*mIsUseBeforeAction_s)
        m36();
    else
        changeToEscape();
    if (sub_710030B070(_108)) {
        sead::Vector3f home;
        const auto position = mActor->getMtx().getTranslation();
        mActor->getHomePos(&home);
        const auto direction = home - position;
        m34(&direction);
    } else {
        m34(nullptr);
    }
}

// NON_MATCHING: Finite radius comparison uses a different equivalent branch after the NaN check.
void AnimalEscapeAI::leave_() {
    AnimalRndMove::leave_();
    if (auto* nav = mActor->m45()) {
        {
            auto lock = sead::makeScopedLock(nav->_1e0);
            nav->_2b0 = 1.0f;
            nav->_220 |= 0x20;
        }
        if (!_120.isNan()) {
            auto lock = sead::makeScopedLock(nav->_1e0);
            nav->_284 = _120;
        }
        const f32 radius_scale = _12c;
        if (!sead::Mathf::isNan(radius_scale) &&
            sead::Mathf::abs(radius_scale) <= sead::Mathf::maxNumber() &&
            nav->_2ac != radius_scale) {
            auto lock = sead::makeScopedLock(nav->_1e0);
            nav->_2ac = radius_scale;
            nav->_220 |= 0x10;
        }
    }
}

void AnimalEscapeAI::changeToEscape() {
    sead::Vector3f target;
    if (*mIsSendGoalPos_s) {
        if (m35()) {
            auto* nav = mActor->m45();
            auto lock = sead::makeScopedLock(nav->_1e0);
            target.set(nav->_194);
        } else {
            const sead::Vector3f position = mActor->getMtx().getTranslation();
            sead::Vector3f direction = position - *mTargetPos_d;
            const f32 distance = _148;
            const f32 length = direction.length();
            if (length > 0.0f)
                direction *= distance / length;
            target = position + direction;
        }
    } else {
        target = {std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
                  std::numeric_limits<f32>::quiet_NaN()};
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    m38(&pack);
    changeChild("逃走", &pack);
}

// NON_MATCHING: instruction scheduling of the hit position (the original interleaves the loads of the forward axis
// and the translation differently).
void AnimalEscapeAI::changeToStuckOnTerrain() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f target;
    sead::Vector3f forward;
    mActor->getMtx().getBase(forward, 2);
    const sead::BoundBox3f& aabb = mActor->getAabb();
    sead::Vector3f hit_position;
    hit_position.setScaleAdd((aabb.getMax().z - aabb.getMin().z) * 0.5f, forward, mActor->getMtx().getTranslation());
    {
        auto* nav = mActor->m45();
        auto lock = sead::makeScopedLock(nav->_1e0);
        target = nav->_194;
    }
    pack.addVec3(target, "TargetPos", -1);
    pack.addVec3(hit_position, "HitPos", -1);
    changeChild("地形嵌り", &pack);
}

// NON_MATCHING: the original loads mActor into a callee-saved register before the velocity query and the
// NavMeshCharacter speed limit before the IsStuckOnTerrain test, and computes the half depth before testing
// `*mIsStuckOnTerrain_a` (instruction order and block layout only).
void AnimalEscapeAI::sub_71003051C0() {
    if (!*mIsDynamicallyOffsetNavChar_s)
        return;
    auto* nav = mActor->m45();
    auto* controller = mActor->getCharacterController();
    if (!nav || !controller)
        return;
    sead::Vector3f velocity;
    controller->sub_7100F5F598(&velocity);
    const f32 speed = sead::Mathf::sqrt(velocity.x * velocity.x + velocity.z * velocity.z);
    const sead::BoundBox3f& aabb = mActor->getAabb();
    f32 offset;
    if (mIsStuckOnTerrain_a && *mIsStuckOnTerrain_a)
        offset = -((aabb.getMax().z - aabb.getMin().z) * 0.5f);
    else
        offset = speed / nav->_8->_6c * ((aabb.getMax().z - aabb.getMin().z) * 0.5f) + 0.0f;
    const sead::Vector3f value{
        0, 0,
        sead::Mathf::clamp(offset, (aabb.getMax().z - aabb.getMin().z) * -0.5f,
                           (aabb.getMax().z - aabb.getMin().z) * 0.5f)};
    if (!value.isNan()) {
        auto lock = sead::makeScopedLock(nav->_1e0);
        nav->_284 = value;
    }
}

void AnimalEscapeAI::loadParams_() {
    AnimalRndMove::loadParams_();
    getStaticParam(&mNumTimesAllowStuck_s, "NumTimesAllowStuck");
    getStaticParam(&mContinueDistance_s, "ContinueDistance");
    getStaticParam(&mShouldEscapeDistance_s, "ShouldEscapeDistance");
    getStaticParam(&mShouldEscapeDistanceRand_s, "ShouldEscapeDistanceRand");
    getStaticParam(&mPenaltyScale_s, "PenaltyScale");
    getStaticParam(&mNavMeshRadiusScale_s, "NavMeshRadiusScale");
    getStaticParam(&mFramesStuckOnTerrainAction_s, "FramesStuckOnTerrainAction");
    getStaticParam(&mIsSendGoalPos_s, "IsSendGoalPos");
    getStaticParam(&mIsUseBeforeAction_s, "IsUseBeforeAction");
    getStaticParam(&mIsDynamicallyOffsetNavChar_s, "IsDynamicallyOffsetNavChar");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getAITreeVariable(&mIsUseTerritory_a, "IsUseTerritory");
}

// NON_MATCHING: register allocation and spills differ (the original keeps the position on the stack
// and the normalised axis in float registers); same calls and arithmetic.
bool AnimalEscapeAI::sub_7100306890(sead::Vector3f* out_dir) {
    const auto& mtx = mActor->getMtx();
    sead::Vector3f side(mtx(0, 0), 0.0f, mtx(2, 0));
    side.normalize();
    sead::Vector3f pos;
    mtx.getTranslation(pos);
    const u32 roll = sead::GlobalRandom::instance()->getU32(100);
    sead::Vector3f dir = roll < 50 ? side : -side;
    sead::Vector3f target = pos + dir * 7.0f;
    if (!sub_710072FAB0(mActor, target, nullptr, -1, -1.0f, -1.0f)) {
        dir = roll < 50 ? -side : side;
        target = pos + dir * 7.0f;
        if (!sub_710072FAB0(mActor, target, nullptr, -1, -1.0f, -1.0f))
            return false;
    }
    if (out_dir)
        *out_dir = dir;
    return true;
}

// NON_MATCHING: normalized-vector storage and reachability-query scheduling differ.
bool AnimalEscapeAI::sub_7100305C58() {
    if (!*mIsUseBeforeAction_s || _150 || !m35())
        return false;
    auto* nav = mActor->m45();
    if (!nav)
        return false;
    const auto position = mActor->getMtx().getTranslation();
    sead::Vector3f direction;
    {
        auto lock = sead::makeScopedLock(nav->_1e0);
        direction.set(nav->_194.x - position.x, 0.0f, nav->_194.z - position.z);
    }
    direction.normalize();
    sead::Vector3f forward;
    mActor->getMtx().getBase(forward, 2);
    if (sub_710072FAB0(mActor, position + forward * 7.0f, nullptr, -1, -1.0f, -1.0f))
        return false;
    if (sub_710072FAB0(mActor, position + direction * 7.0f, nullptr, -1, -1.0f, -1.0f)) {
        if (!(forward.dot(direction) < 0.8660253882408142f))
            return false;
    } else if (!sub_7100306890(&direction)) {
        direction = *mTargetPos_d - position;
    }
    sub_7100306664(direction);
    _150 = true;
    return true;
}

// NON_MATCHING: distance argument evaluation and normalized-vector registers differ.
void AnimalEscapeAI::m36() {
    sead::Vector3f direction = _108 - *mTargetPos_d;
    direction.y = 0.0f;
    direction.normalize();
    _114.set(0.0f, 0.0f, 0.0f);
    sub_71007428DC(*mShouldEscapeDistance_s, 10.0f, &_114, mActor->m45(), &direction, 8);
    if (!_114.isNan()) {
        direction = _114 - _108;
        direction.y = 0.0f;
        direction.normalize();
    }
    sub_7100306664(direction);
}

// NON_MATCHING: normalized-vector registers, NaN check order and position stack allocation differ.
void AnimalEscapeAI::sub_7100306664(const sead::Vector3f& direction) {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    sead::Vector3f horizontal(direction.x, 0.0f, direction.z);
    horizontal.normalize();
    if (horizontal.isNan() || horizontal == sead::Vector3f(0.0f, 0.0f, 0.0f))
        horizontal = controller->get64();
    sead::Vector3f position;
    controller->sub_7100F5F6E0(&position);
    const sead::Vector3f target = position + horizontal * 5.0f;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    changeChild("逃走前", &pack);
}

// NON_MATCHING: the final store of the rideable direction (the original stores x / y per branch and z once).
bool AnimalEscapeAI::m34(const sead::Vector3f* pos) {
    auto* rideable = mActor->m132();
    sead::Vector3f dir = mActor->getMtx().getTranslation() - *mTargetPos_d;

    if (!(_114.isNan() || _114 == sead::Vector3f(0.0f, 0.0f, 0.0f))) {
        if (rideable) {
            dir = _114 - mActor->getMtx().getTranslation();
            dir.normalize();
            rideable->_148 = dir;
        }
        mActor->m45()->sub_7100F75F8C(_114);
        _114 = sead::Vector3f(0.0f, 0.0f, 0.0f);
        return true;
    }

    if (pos && !(pos->isNan() || *pos == sead::Vector3f(0.0f, 0.0f, 0.0f)))
        dir = *pos;

    if (rideable) {
        dir.normalize();
        const bool invalid = dir.isNan() || dir == sead::Vector3f(0.0f, 0.0f, 0.0f);
        rideable->_148 = invalid ? sead::Vector3f::zero : dir;
    }
    return AnimalRndMove::m34(&dir);
}

bool AnimalEscapeAI::m37() {
    return isCurrentChild("逃走前");
}

}  // namespace uking::ai
