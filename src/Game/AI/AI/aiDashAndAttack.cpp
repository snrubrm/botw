#include "Game/AI/AI/aiDashAndAttack.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

// Declaration only (defined in the AI utility TU; same declaration as in aiSimpleEscapeFromTarget.cpp).
bool sub_710072F99C(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& to,
                    sead::Vector3f* out_pos, s32 a5, f32 a6, f32 a7);

namespace uking::ai {

DashAndAttack::DashAndAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DashAndAttack::~DashAndAttack() = default;

bool DashAndAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DashAndAttack::sub_710035B9E0(sead::Vector3f* target) {
    auto* actor = mActor;
    sead::Vector3f v = *mParams.mTargetPos_d;
    v -= actor->getMtx().getTranslation();
    v.y = 0.0f;
    v.normalize();
    v = sead::Vector3f(-v.z, 0.0f, v.x);
    v *= *mParams.mOffsetLR_s;
    v += *mParams.mTargetPos_d;
    if (sub_710072F99C(actor, *mParams.mTargetPos_d, v, target, -1, -1.0f, -1.0f))
        *target = v;
}

// NON_MATCHING: Target vector and parameter-pack stack placement differs.
void DashAndAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f target;
    sub_710035B9E0(&target);
    if (*mParams.mIsAbleSkipNear_s && sub_710035BB34()) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(target, "TargetPos", -1);
        changeChild("斬り付け", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(target, "TargetPos", -1);
        changeChild("駆け寄り", &pack);
    }
}

// NON_MATCHING: Target vector and parameter-pack stack placement differs.
void DashAndAttack::calc_() {
    sead::Vector3f target;
    sub_710035B9E0(&target);
    auto* child = getCurrentChild();
    child->setDynamicParam(target, "TargetPos");
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("駆け寄り")) {
            if (sub_710035BB34()) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(target, "TargetPos", -1);
                changeChild("斬り付け", &pack);
            } else {
                setFailed();
            }
        } else {
            setFinished();
        }
    } else if (child->isChangeable()) {
        if (sub_710035BB34()) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(target, "TargetPos", -1);
            changeChild("斬り付け", &pack);
        } else {
            auto* actor = mActor;
            sead::Vector3f direction = actor->getMtx().getTranslation() - *mParams.mTargetPos_d;
            const f32 length = direction.length();
            direction = -direction;
            if (length > 0)
                direction *= 1.0f / length;
            if (!(direction.dot(actor->getMtx().getBase(2)) >=
                  sead::Mathf::cos(*mParams.mTiredAngle_s))) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(target, "TargetPos", -1);
                changeChild("斬り付け", &pack);
            }
        }
    }
}

void DashAndAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DashAndAttack::loadParams_() {
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mAttackFrame_s, "AttackFrame");
    getStaticParam(&mParams.mOffsetLR_s, "OffsetLR");
    getStaticParam(&mParams.mAttackRange_s, "AttackRange");
    getStaticParam(&mParams.mTiredAngle_s, "TiredAngle");
    getStaticParam(&mParams.mTargetSpeedClampMax_s, "TargetSpeedClampMax");
    getStaticParam(&mParams.mIsAbleSkipNear_s, "IsAbleSkipNear");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getDynamicParam(&mParams.mTargetVel_d, "TargetVel");
}

}  // namespace uking::ai
