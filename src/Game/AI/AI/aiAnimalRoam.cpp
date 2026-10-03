#include "Game/AI/AI/aiAnimalRoam.h"
#include <cmath>
#include <limits>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_7100742478.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

AnimalRoam::AnimalRoam(const InitArg& arg) : AnimalRoamBase(arg) {}

AnimalRoam::~AnimalRoam() = default;

bool AnimalRoam::init_(sead::Heap* heap) {
    return AnimalRoamBase::init_(heap);
}

void AnimalRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalRoamBase::enter_(params);
    auto* nav = mActor->m45();
    if (!nav) {
        setFailed();
        return;
    }
    mActor->getMtx().getTranslation(_e0);
    nav->inlineReset();
    m36();
}

void AnimalRoam::calc_() {
    AnimalRoamBase::calc_();
    if (m38())
        m34(nullptr);
    if (!(_ec.value <= sead::Mathf::epsilon()))
        _ec.update();

    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed()) {
        child->isChangeable();
        return;
    }

    if (!m39()) {
        m36();
        return;
    }

    if (sead::GlobalRandom::instance()->getF32() < *mParams.mChangeWaitRate_s)
        m36();
    else
        m37();
    _a0 = 0;
}

bool AnimalRoam::m35() {
    if (!AnimalRoamBase::m35())
        return false;
    if (!*mParams.mCheckLOS_s)
        return true;
    auto* nav = mActor->m45();
    return sub_7100742588(nullptr, nav, &mActor->m45()->_194, 10.0f);
}

void AnimalRoam::leave_() {
    AnimalRoamBase::leave_();
}

void AnimalRoam::loadParams_() {
    AnimalRoamBase::loadParams_();
    getStaticParam(&mParams.mFinishChangeCount_s, "FinishChangeCount");
    getStaticParam(&mParams.mLimitRadius_s, "LimitRadius");
    getStaticParam(&mParams.mChangeWaitRate_s, "ChangeWaitRate");
    getStaticParam(&mParams.mFramesStuckOnTerrainAction_s, "FramesStuckOnTerrainAction");
    getStaticParam(&mParams.mIsSendGoalPos_s, "IsSendGoalPos");
    getStaticParam(&mParams.mCheckValidStartPos_s, "CheckValidStartPos");
    getStaticParam(&mParams.mCheckLOS_s, "CheckLOS");
}

// NON_MATCHING: operand order of the multiplications in the second rotation; scheduling of the
// stores of the initial direction copy
bool AnimalRoam::m34(const sead::Vector3f* pos) {
    auto* rideable = mActor->m132();
    sead::Vector3f dir;
    mActor->getMtx().getBase(dir, 2);
    const sead::Vector3f my_pos = mActor->getMtx().getTranslation();

    const sead::Vector2f diff(_e0.x - my_pos.x, _e0.z - my_pos.z);
    const f32 dist = diff.length();

    if (dist > *mParams.mLimitRadius_s * 0.9f) {
        dir = _e0 - my_pos;
        dir.y = 0.0f;
        dir.normalize();
    } else if (dist > *mParams.mLimitRadius_s * 0.55f) {
        dir = _e0 - my_pos;
        sead::Vector3f to_center(dir.x, 0.0f, dir.z);
        to_center.normalize();
        sead::Vector3f front;
        mActor->getMtx().getBase(front, 2);
        dir = to_center + front;
        dir.y = 0.0f;
        dir.normalize();
        if (dir.isNan() || (dir.x == 0.0f && dir.z == 0.0f)) {
            const f32 range = (_a0 * 15.0f + 45.0f) * sead::Mathf::deg2rad(1);
            const f32 angle = sead::GlobalRandom::instance()->getF32Range(-range, range);
            sead::Matrix34f rot;
            rot.makeR({0.0f, angle, 0.0f});
            dir.setRotated(rot, to_center);
            dir.normalize();
        }
    } else {
        const f32 range = (_a0 * 30.0f + 60.0f) * sead::Mathf::deg2rad(1);
        const f32 angle = sead::GlobalRandom::instance()->getF32Range(-range, range);
        sead::Matrix34f rot;
        rot.makeR({0.0f, angle, 0.0f});
        dir.rotate(rot);
        dir.normalize();
    }

    if (rideable)
        rideable->_148 = dir;

    auto* nav = mActor->m45();
    const f32 time = (nav && (nav->_2a4 & 0xffff) != 0x17) ? 10.0f : 150.0f;
    _ec = ksys::Timer(time, time);
    return AnimalRoamBase::m34(&dir);
}

void AnimalRoam::m36() {
    auto* nav = mActor->m45();
    auto* nav2 = mActor->m45();
    const f32 time = (nav2 && (nav2->_2a4 & 0xffff) != 0x17) ? 10.0f : 150.0f;
    _ec = ksys::Timer(time, time);
    if (!m35() || *mParams.mIsSendGoalPos_s)
        nav->inlineReset();
    changeChild("待機", nullptr);
}

bool AnimalRoam::m38() {
    auto* nav = mActor->m45();
    if (!nav || !(_ec.value <= sead::Mathf::epsilon()))
        return false;
    if (!m35() && !(nav->_220 & 0x41000) && isCurrentChild("待機"))
        return true;
    const f32 frames = mFramesStuckOnTerrain_a ? *mFramesStuckOnTerrain_a : -1.0f;
    if (!(frames >= *mParams.mFramesStuckOnTerrainAction_s))
        return false;
    nav->inlineReset();
    return true;
}

void AnimalRoam::m37() {
    sead::Vector3f pos;
    if (*mParams.mIsSendGoalPos_s) {
        m40(&pos);
    } else {
        pos = {std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
               std::numeric_limits<f32>::quiet_NaN()};
    }

    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    changeChild("移動", &params);
}

bool AnimalRoam::m40(sead::Vector3f* pos) {
    if (!pos)
        return false;
    auto* nav = mActor->m45();
    if (!nav)
        return false;
    nav->_1e0.lock();
    pos->set(nav->_194);
    nav->_1e0.unlock();
    return true;
}

bool AnimalRoam::m39() {
    if (isCurrentChild("待機") && m35()) {
        if (!*mParams.mCheckValidStartPos_s)
            return true;
        if (auto* nav = mActor->m45()) {
            const sead::Vector3f pos = mActor->getMtx().getTranslation();
            return sub_7100742278(nav->_2a8 * nav->_2ac, nullptr, nav, &pos);
        }
    }
    return false;
}

}  // namespace uking::ai
