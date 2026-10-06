#include "Game/AI/AI/aiSiteBossApproachRoot.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"

// Source namespace and reference spelling are inferred from the known caller interfaces.
bool sub_71002D2B5C(bool* side, ksys::act::Actor* actor, const gsys::BoneAccessKeyEx& key,
                  f32 angle, f32 scale);

namespace uking::ai {

SiteBossApproachRoot::SiteBossApproachRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {
    for (auto& ray_cast : mRayCasts)
        ray_cast = nullptr;
    for (auto& pos : _c8)
        pos.set(0, 0, 0);
}

SiteBossApproachRoot::~SiteBossApproachRoot() = default;

bool SiteBossApproachRoot::init_(sead::Heap* heap) {
    if (auto* model = mActor->getModel())
        _1f8.search(model, "Head");
    else
        _1f8.getKey().reset();
    return true;
}

void SiteBossApproachRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossApproachRoot::leave_() {
    for (auto*& ray_cast : mRayCasts) {
        if (ray_cast && !ray_cast->isRequestFinished()) {
            ray_cast->release();
            ray_cast = nullptr;
        }
    }
}

void SiteBossApproachRoot::loadParams_() {
    getStaticParam(&mCheckWallDist_s, "CheckWallDist");
    getStaticParam(&mApproachTime_s, "ApproachTime");
    getStaticParam(&mEndDist_s, "EndDist");
    getStaticParam(&mEndFarDist_s, "EndFarDist");
    getStaticParam(&mAttackStartDist_s, "AttackStartDist");
    getStaticParam(&mDoAttack_s, "DoAttack");
    getDynamicParam(&mIsMoveSide_d, "IsMoveSide");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool SiteBossApproachRoot::m34() {
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (!boss || !boss->sub_71002D33D0(90.0f))
        return false;
    bool side = false;
    return sub_71002D2B5C(&side, mActor, _1f8, 0.34906584f, 1.2f);
}

// 0x71005702d4
void SiteBossApproachRoot::sub_71005702D4(const sead::Vector3f& dst) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(dst, "MoveDstPos", -1);
    changeChild("移動", &pack);
}

// 0x7100570ca4
void SiteBossApproachRoot::sub_7100570CA4() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(_230, "MoveDstPos", -1);
    changeChild("遠距離攻撃移動", &pack);
}

}  // namespace uking::ai
