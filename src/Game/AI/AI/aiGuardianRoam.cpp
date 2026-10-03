#include "Game/AI/AI/aiGuardianRoam.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

GuardianRoam::GuardianRoam(const InitArg& arg) : GuardianAI(arg) {}

GuardianRoam::~GuardianRoam() = default;

bool GuardianRoam::init_(sead::Heap* heap) {
    return GuardianAI::init_(heap);
}

void GuardianRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianAI::enter_(params);
    auto* guardian = sub_710040DA6C();
    if (!guardian) {
        setFailed();
        return;
    }

    sead::Vector3f home_pos;
    guardian->getHomePos(&home_pos);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(home_pos, "DynTargetPos", -1);
    pack.addVec3(mActor->getMtx().getTranslation(), "DynStartPos", -1);
    changeChild("移動", &pack);
    _48 = 0;
    _4c = 0;
}

void GuardianRoam::calc_() {
    GuardianAI::calc_();
    auto* guardian = sub_710040DA6C();
    if (!guardian) {
        setFailed();
        return;
    }

    const bool is_looking_around = isCurrentChild("見回す");
    sead::Vector3f pos;
    guardian->getMtx().getTranslation(pos);
    if (!is_looking_around && f32(*mMoveTime_s) < _4c) {
        sub_710040DDB0(1);
        changeChild("見回す");
        return;
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (is_looking_around) {
            sub_710042A774(pos);
            return;
        }
        sub_710040DDB0(1);
        changeChild("見回す");
    } else if (is_looking_around) {
        return;
    }
    ksys::Timer::update(&_4c, 1.0f);
}

void GuardianRoam::sub_710042A774(const sead::Vector3f& start_pos) {
    sead::Vector3f home_pos;
    mActor->getHomePos(&home_pos);
    sub_710040DDB0(0);

    _48 += (sead::GlobalRandom::instance()->getF32() + 0.5f) * sead::Mathf::pi();
    if (_48 > sead::Mathf::pi2())
        _48 -= sead::Mathf::pi2();

    sead::Vector3f target =
        sead::Vector3f{sead::Mathf::cos(_48), 0, sead::Mathf::sin(_48)} * *mMoveRadius_s + home_pos;
    if (auto* nav = mActor->m45()) {
        sead::Vector3f nav_pos;
        ksys::phys::Unk_7100f7e9f0 result = nav->sub_7100F76078(&nav_pos, target, *mMoveRadius_s);
        if (result.sub_7100F7EB40())
            target.set(nav_pos);
    }

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "DynTargetPos", -1);
    pack.addVec3(start_pos, "DynStartPos", -1);
    changeChild("移動", &pack);
    _4c = 0;
}

void GuardianRoam::leave_() {
    GuardianAI::leave_();
}

void GuardianRoam::loadParams_() {
    GuardianAI::loadParams_();
    getStaticParam(&mMoveTime_s, "MoveTime");
    getStaticParam(&mMoveRadius_s, "MoveRadius");
}

}  // namespace uking::ai
