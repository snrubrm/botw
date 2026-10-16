#include "Game/Actor/AI/aiViewWaitRiskAvoid.h"
#include <math/seadMathCalcCommon.h>
#include <math/seadVector.h>
#include <cmath>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"

namespace uking::ai {

ViewWaitRiskAvoid::ViewWaitRiskAvoid(const InitArg& arg) : ViewWait(arg) {}

ViewWaitRiskAvoid::~ViewWaitRiskAvoid() = default;

bool ViewWaitRiskAvoid::init_(sead::Heap* heap) {
    return ViewWait::init_(heap);
}

void ViewWaitRiskAvoid::enter_(ksys::act::ai::InlineParamPack* params) {
    ViewWait::enter_(params);
}

void ViewWaitRiskAvoid::calc_() {
    ViewWait::calc_();
}

void ViewWaitRiskAvoid::leave_() {
    ViewWait::leave_();
}

void ViewWaitRiskAvoid::loadParams_() {
    ViewWait::loadParams_();
    getStaticParam(&mAvoidFrame_s, "AvoidFrame");
    getStaticParam(&mFrontAngle_s, "FrontAngle");
    getStaticParam(&mSpaceAngle_s, "SpaceAngle");
    getStaticParam(&mSpaceDist_s, "SpaceDist");
}

void ViewWaitRiskAvoid::m40() {
    _5c = false;
    if (isCurrentChild("後ずさり回避")) {
        getCurrentChild()->setDynamicParam(m34(), "TargetPos");
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(m34(), "TargetPos", -1);
        changeChild("後ずさり回避", &pack);
    }
}

bool ViewWaitRiskAvoid::m35() {
    if (m42()) {
        _80 = ksys::Timer(*mAvoidFrame_s, *mAvoidFrame_s);
        return true;
    }

    if (isCurrentChild("横移動回避") || isCurrentChild("後ずさり回避")) {
        _80.update();
        if (_80.value <= sead::Mathf::epsilon()) {
            m36();
            return true;
        }
    }
    return ViewWait::m35();
}

// NON_MATCHING: float register allocation (the original keeps the constant 0 and the front vector in fewer
// registers: one saved d register less)
// 0x71005e6b84
bool ViewWaitRiskAvoid::sub_71005E6B84(const sead::Vector3f& target) {
    const sead::Matrix34f& mtx = mActor->getMtx();
    sead::Vector3f dir = target - mtx.getTranslation();
    dir.y = 0;
    dir.normalize();
    sead::Vector3f front;
    mtx.getBase(front, 2);
    front.y = 0;
    front.normalize();
    sead::Vector3f cross;
    cross.setCross(front, dir);
    return std::atan2(cross.length(), dir.dot(front)) < *mFrontAngle_s;
}

// NON_MATCHING: stack slots / registers (the original keeps two stack copies of the target position) and the first
// loop's size test (cmp 0 / b.le)
// Starts a sideways avoid move away from a burning fire (m43) or from the nearby awareness entries (sensor 2, then
// enemies), weighting each by sub_71005E6D10.
bool ViewWaitRiskAvoid::m42() {
    auto* actor = mActor;
    const sead::Vector3f pos = actor->getMtx().getTranslation();
    const sead::Vector3f target = sub_71005D9330(actor);
    sead::Vector3f dir = target - pos;
    dir.y = 0.0f;
    const f32 dist = dir.normalize();

    sead::Vector3f fire;
    if (m43(&fire)) {
        if (sub_71005E6B84(fire)) {
            m40();
            return true;
        }
        const sead::Vector3f& self = sub_71005D9330(mActor);
        sead::Vector3f away{self.x - fire.x, 0.0f, self.z - fire.z};
        away.normalize();
        m41(away.cross(dir).y >= 0.0f ? 1 : -1);
        return true;
    }

    if (*mSpaceAngle_s <= 0.0f)
        return false;

    f32 side = 0.0f;
    auto* awareness = actor->getAwareness();
    for (s32 i = 0; i < 5; ++i) {
        auto* sensor = awareness->_260[2];
        if (!sensor || sensor->_8.size() <= i)
            break;
        auto* entry = ksys::act::sub_7100D78E30(&sensor->_8, i);
        if (!entry)
            break;
        sub_71005E6D10(&side, dir, entry->_58, false, 4.0f, dist);
    }
    for (s32 i = 0; i < 10; ++i) {
        if (awareness->_8.size() <= i)
            break;
        auto* entry = ksys::act::sub_7100D78E30(&awareness->_8, i);
        if (!entry || !ksys::act::isEnemyProfile(&entry->_0.mLink))
            break;
        sub_71005E6D10(&side, dir, entry->_58, false, 2.0f, dist);
    }

    if (sead::Mathf::abs(side) < 0.7f)
        return false;

    const s8 rot = side <= 0.0f ? 1 : -1;
    sead::Vector3f perp{-(target.z - pos.z), 0.0f, target.x - pos.x};
    perp.normalize();
    const sead::Vector3f goal = pos + perp * (*mSpaceDist_s * rot);
    if (!sub_710072FAB0(actor, goal, nullptr, -1, -1.0f, -1.0f))
        return false;
    m41(rot);
    return true;
}

// NON_MATCHING: scheduling / registers, and the original tests `force` with eor + tbnz
void ViewWaitRiskAvoid::sub_71005E6D10(f32* side, const sead::Vector3f& dir, const sead::Matrix34f& mtx, bool force,
                                       f32 amount, f32 dist) {
    const sead::Vector3f trans = mtx.getTranslation();
    const sead::Vector3f& pos = sub_71005D9330(mActor);
    sead::Vector3f to{pos.x - trans.x, 0.0f, pos.z - trans.z};
    const f32 len = to.normalize();
    if (len > dist + 1.0f && !force)
        return;

    const f32 angle = std::acos(sead::Mathf::clamp(to.dot(dir), -0.999f, 0.999f));
    const f32 space = *mSpaceAngle_s;
    if (to.cross(dir).y < 0.0f) {
        if (angle > space)
            amount *= sead::Mathf::clamp((angle - space) * -3.0f / space + 1.0f, 0.0f, 1.0f);
        *side += amount;
    } else {
        if (angle > space)
            amount *= sead::Mathf::clamp((angle - space) * -3.0f / space + 1.0f, 0.0f, 1.0f);
        *side -= amount;
    }
}

bool ViewWaitRiskAvoid::m43(sead::Vector3f* out) {
    auto* actor = mActor;
    auto* chemical = actor->getChemicalStuff();
    if (!chemical)
        return false;
    const auto* damage_param = actor->getParam()->getRes().mDamageParam;
    if (!damage_param || !damage_param->mBurnable.ref())
        return false;
    auto* holder = chemical->_90->_0;
    if (!holder)
        return false;
    *out = holder->sub_7100D8D1E0();
    return true;
}

void ViewWaitRiskAvoid::m41(s8 dir) {
    _5c = false;
    if (isCurrentChild("横移動回避")) {
        getCurrentChild()->setDynamicParam(m34(), "TargetPos");
        getCurrentChild()->setDynamicParam(s32(dir), "RotDir");
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(m34(), "TargetPos", -1);
        pack.addInt(dir, "RotDir", -1);
        changeChild("横移動回避", &pack);
    }
}

}  // namespace uking::ai
