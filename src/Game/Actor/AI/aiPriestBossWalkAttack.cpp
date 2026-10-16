#include "Game/Actor/AI/aiPriestBossWalkAttack.h"
#include <cmath>
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"

namespace uking::ai {


PriestBossWalkAttack::PriestBossWalkAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossWalkAttack::~PriestBossWalkAttack() = default;

bool PriestBossWalkAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original's NaN / zero tests of `dir` go z, y, x (ours x, y, z), which swaps the registers of
// dir.x / dir.z; the acos clamp is laid out min-first with a different register choice
void PriestBossWalkAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* nav = mActor->m45();
    if (!nav) {
        setFailed();
        return;
    }

    nav->inlineReset();
    nav->sub_7100F75F8C(*mTargetPos_d);
    nav->sub_7100F7604C(*mGoalDistanceTolerance_s);

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f dir = *mTargetPos_d - pos;
    dir.y = 0.0f;
    dir.normalize();
    if (dir.isNan() || dir == sead::Vector3f(0, 0, 0))
        dir = front;

    const f32 angle = sead::Mathf::acos(sead::Mathf::clamp(front.dot(dir), -1.0f, 1.0f));
    if (angle > *mAngleNeedTurn_s) {
        ksys::act::ai::InlineParamPack child_params;
        child_params.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("回転", &child_params);
    } else {
        ksys::act::ai::InlineParamPack child_params;
        child_params.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("待機", &child_params);
    }
    _98 = false;
}

// NON_MATCHING: the original keeps both path state reads in stack slots (str / ldr, like a SEAD_ENUM value; a
// SEAD_ENUM helper did not reproduce it) and lays out the "移動" state branches the other way round
// Walks to TargetPos ("移動"), turning first ("回転") when the target is too far to the side, and attacks with the
// AS-driven attack sensor; finishes when the nav mesh path ends (state 2 / 3).
void PriestBossWalkAttack::calc_() {
    auto* child = getCurrentChild();
    auto* nav = mActor->m45();
    if (!child || !nav)
        return;

    child->setDynamicParam(*mTargetPos_d, "TargetPos");
    if (isCurrentChild("待機")) {
        if (!_98) {
            nav->_1e0.lock();
            const u8 state = nav->_294;
            nav->_1e0.unlock();
            if (state == 2 || state == 3) {
                setFinished();
            } else if (state == 1) {
                sub_7100531900();
                _98 = true;
            }
        }
    } else if (isCurrentChild("移動")) {
        nav->sub_7100F75F8C(*mTargetPos_d);
        if (auto* as_list = mActor->getASList();
            as_list && as_list->x(0x2e, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
            const sead::Vector3f pos = mActor->getMtx().getTranslation();
            const sead::Vector3f& player_pos = getPlayerPosition();
            const f32 dx = pos.x - player_pos.x;
            const f32 dz = pos.z - player_pos.z;
            mActor->getASList()->x_6(0x10, 0, std::sqrt(dx * dx + dz * dz));
        }
        nav->_1e0.lock();
        const u8 state = nav->_294;
        nav->_1e0.unlock();
        if (state == 2 || state == 3) {
            setFinished();
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("待機", &pack);
        } else if (state < 2) {
            sead::Vector3f front;
            mActor->getMtx().getBase(front, 2);
            const sead::Vector3f pos = mActor->getMtx().getTranslation();
            sead::Vector3f dir = *mTargetPos_d - pos;
            dir.y = 0.0f;
            dir.normalize();
            if (dir.isNan() || dir == sead::Vector3f(0, 0, 0))
                dir = front;
            const f32 angle = sead::Mathf::acos(sead::Mathf::clamp(front.dot(dir), -1.0f, 1.0f));
            if (angle > *mAngleNeedTurn_s) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(*mTargetPos_d, "TargetPos", -1);
                changeChild("回転", &pack);
            }
        }
    }

    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("回転")) {
            sub_7100531900();
        } else if (isCurrentChild("移動")) {
            setFinished();
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("待機", &pack);
        }
    }

    ksys::as::ASList::Unk4 query;
    if (mActor->getASList() &&
        mActor->getASList()->x(3, &query, 0, 0, &ksys::as::ASList::Unk2::sub_710116383C, true)) {
        const sead::SafeString name = query.name;
        sub_71007A2C30(mActor, name, &mActor->getMtx());
        getActorAttackSensor(mActor)->activateAttackSensor(
            *mAtType_s, *mAtAttr_s, *mAtDamage_s, *mAtPower_s, static_cast<f32>(*mAtImpact_s), *mAtPowerReduce_s,
            *mAtShieldBreakPower_s, *mAtDirType_s, false, 1, -1);
    }
    if (mActor->getASList() &&
        mActor->getASList()->x(3, &query, 0, 0, &ksys::as::ASList::Unk2::sub_710116388C, true)) {
        const sead::SafeString name = query.name;
        sub_71007A2D7C(mActor, name);
    }
}

void PriestBossWalkAttack::leave_() {
    sub_71007A2E04(mActor);
}

void PriestBossWalkAttack::loadParams_() {
    getStaticParam(&mAtDirType_s, "AtDirType");
    getStaticParam(&mAtAttr_s, "AtAttr");
    getStaticParam(&mAtType_s, "AtType");
    getStaticParam(&mAtShieldBreakPower_s, "AtShieldBreakPower");
    getStaticParam(&mAtImpact_s, "AtImpact");
    getStaticParam(&mAtPowerReduce_s, "AtPowerReduce");
    getStaticParam(&mAtPower_s, "AtPower");
    getStaticParam(&mAtDamage_s, "AtDamage");
    getStaticParam(&mGoalDistanceTolerance_s, "GoalDistanceTolerance");
    getStaticParam(&mAngleNeedTurn_s, "AngleNeedTurn");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

// 0x7100531900
void PriestBossWalkAttack::sub_7100531900() {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const sead::Vector3f& player_pos = getPlayerPosition();
    const f32 dx = pos.x - player_pos.x;
    const f32 dz = pos.z - player_pos.z;
    const f32 distance = std::sqrt(dx * dx + dz * dz);
    mActor->getASList()->x_6(0x10, 0, distance);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("移動", &pack);
}

}  // namespace uking::ai
