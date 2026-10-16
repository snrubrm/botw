#include "Game/Actor/AI/aiPriestBossLineFormationFall.h"
#include "Game/Actor/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include <random/seadGlobalRandom.h>
#include <cmath>

namespace uking::ai {

PriestBossLineFormationFall::PriestBossLineFormationFall(const InitArg& arg)
    : PriestBossFormation(arg) {}

PriestBossLineFormationFall::~PriestBossLineFormationFall() = default;

bool PriestBossLineFormationFall::init_(sead::Heap* heap) {
    return PriestBossFormation::init_(heap);
}

void PriestBossLineFormationFall::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossFormation::enter_(params);
    m43();
    _94 = false;
}

// NON_MATCHING: appearance-position component loads and stores are combined and scheduled differently.
void PriestBossLineFormationFall::calc_() {
    PriestBossFormation::calc_();
    if (!isCurrentChild("攻撃"))
        return;
    if (sub_710072B6C8() || sub_710072B660()) {
        auto* unit = sead::DynamicCast<Unk_7102450fa8>(
            *static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
        const f32 angle = static_cast<f32>(unit->sub_7100719534(mActor)) *
                          (sead::Mathf::pi2() / 9.0f);
        const f32 radius = sead::GlobalRandom::instance()->getF32Range(0.0f, 3.0f) + 3.0f;
        _88.set(std::cos(angle) * radius, 0.0f, std::sin(angle) * radius);
    }
    auto* child = getCurrentChild();
    const sead::Vector3f target = sub_7100523708();
    const sead::Vector3f appear = {target.x + _88.x,
                                 target.y + *mWarpHightOffset_s + _88.y,
                                 target.z + _88.z};
    child->setDynamicParam(appear, "AppearPosition");
    child->setDynamicParam(target, "TargetPos");
}

// NON_MATCHING: the Y component stays in a floating-point register rather than an integer register.
sead::Vector3f PriestBossLineFormationFall::sub_7100523708() {
    sead::Vector3f target = sub_71005D9330(mActor);
    if (sead::DynamicCast<Unk_7102450fa8>(
            *static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a))) {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (sead::DynamicCast<Unk_7102450fa8>(
                *static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a))
                ->sub_71007194CC(&accessor)) {
            target.y = accessor.getActorMtx().m[1][3];
        }
    }
    return target;
}

void PriestBossLineFormationFall::m39() {
    ksys::act::ai::InlineParamPack params;
    const sead::Vector3f target = sub_7100523708();
    _88.set(sead::Vector3f::zero);
    params.addVec3(target, "TargetPos", -1);
    const sead::Vector3f appear = {target.x, target.y + *mWarpHightOffset_s, target.z};
    params.addVec3(appear, "AppearPosition", -1);
    changeChild("攻撃", &params);
}

void PriestBossLineFormationFall::leave_() {
    PriestBossFormation::leave_();
}

void PriestBossLineFormationFall::loadParams_() {
    PriestBossFormation::loadParams_();
    getStaticParam(&mWarpHightOffset_s, "WarpHightOffset");
}

void PriestBossLineFormationFall::m34(Unk_7102450fa8* unit) {
    if (!unit)
        return;
    unit->sub_7100719534(mActor);
    PriestBossFormation::m34(unit);
}

void PriestBossLineFormationFall::m42() {
    sead::FixedSafeString<16> name;
    name.format("%d", sub_7100518B50());
    mActor->getASList()->goLimpFromHeadShotMaybe(0x2f, name, 0);
    changeChild("攻撃前");
}

void PriestBossLineFormationFall::m43() {
    if (!isCurrentChild("攻撃"))
        changeChild("待機");
}

}  // namespace uking::ai
