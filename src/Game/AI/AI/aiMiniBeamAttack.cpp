#include "Game/AI/AI/aiMiniBeamAttack.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "Game/Actor/actEnemy.h"
#include "Game/gameUnk_71024739d0.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

MiniBeamAttack::MiniBeamAttack(const InitArg& arg) : BreathAttackEnemyBattle(arg), _230() {}

MiniBeamAttack::~MiniBeamAttack() = default;

bool MiniBeamAttack::init_(sead::Heap* heap) {
    return BreathAttackEnemyBattle::init_(heap);
}

void MiniBeamAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    BreathAttackEnemyBattle::enter_(params);
    if (isCurrentChild("戦闘準備")) {
        if (*mIsValidGuide_s) {
            const s32 fluctuation_time = m45();
            // The original evaluates the Enemy cast of the actor and drops the result (discarded call: logged).
            sead::DynamicCast<act::Enemy>(mActor);
            _100.init(mActor, "Target", "Laser", "", "BeamSightSearch", "BeamSightLocking",
                      "BeamSightLocked", *mFluctuationRange_s, *mFluctuationSpan_s,
                      f32(fluctuation_time), *mTargetOffsetY_s, sub_71005D9330(mActor), mNodeName_s,
                      sead::Vector3f::zero);
        }
        startAimEffect();
    }
    if (*mIsIgnoreSmallHit_s)
        setDamageCallbackTiming(mActor, 4, &_1f8);
}

void MiniBeamAttack::startAimEffect() {
    if (mAimEffectName_s.isEmpty())
        return;
    _230.mELink.kill();
    xlinkSearchAndEmit(mActor, mAimEffectName_s.cstr(), 2, &_230);
}

void MiniBeamAttack::calc_() {
    BreathAttackEnemyBattle::calc_();
    if (isCurrentChild("戦闘準備")) {
        if (*mIsValidGuide_s)
            sub_710042CFA4(sub_71005D960C(mActor));
    } else if (isCurrentChild("戦闘攻撃")) {
        const sead::Vector3f target = _220;
        sub_71005DB1D8(mActor, target);
        getCurrentChild()->setDynamicParam(_220, "TargetPos");
    }
}

// NON_MATCHING: the original builds the actor-position fallback of the start point's x / y with a vector lane insert
// (`ld1 {v0.s}[1]`, one 8-byte store); ours loads / stores two words. (`(&query)->worldRayCast()` is a real vtable call
// like in the original; the plain `query.worldRayCast()` is devirtualized.)
void MiniBeamAttack::sub_710042CFA4(const sead::Vector3f& target) {
    auto* model = mActor->getModel();
    sead::Vector3f start;
    bool found = false;
    if (!mNodeName_s.isEmpty() && model) {
        const auto key = model->searchBone(mNodeName_s);
        if (key.isValid()) {
            sead::Matrix34f mtx;
            model->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->getBoneWorldMatrix(
                &mtx, key.bone_index);
            mtx.getTranslation(start);
            found = true;
        }
    }
    if (!found)
        mActor->getMtx().getTranslation(start);

    sead::Vector3f end = sead::Vector3f::ey * *mTargetOffsetY_s + target;
    uking::Unk_71024739d0 query(ksys::phys::GroundHit::HitAll);
    query.sub_710090D8A4();
    query.setStart(start);
    query.setEnd(end);
    // called through a pointer in the original (not devirtualised)
    if ((&query)->worldRayCast()) {
        query.getHitPosition(&end);
        end -= sead::Vector3f::ey * *mTargetOffsetY_s;
        _100.update(end);
    } else {
        _100.update(target);
    }
}

void MiniBeamAttack::leave_() {
    BreathAttackEnemyBattle::leave_();
    if (*mIsValidGuide_s)
        _100.sub_71006F2D08();
    _230.fadeXLink();
    sub_71005DA114(mActor, &_1f8);
}

void MiniBeamAttack::loadParams_() {
    BreathAttackEnemyBattle::loadParams_();
    getStaticParam(&mFluctuationRange_s, "FluctuationRange");
    getStaticParam(&mFluctuationSpan_s, "FluctuationSpan");
    getStaticParam(&mTargetOffsetY_s, "TargetOffsetY");
    getStaticParam(&mNodeName_s, "NodeName");
    getStaticParam(&mIsValidGuide_s, "IsValidGuide");
    getStaticParam(&mIsIgnoreSmallHit_s, "IsIgnoreSmallHit");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mAimEffectName_s, "AimEffectName");
}

bool MiniBeamAttack::isChangeable() const {
    if (!*mIsChangeable_s)
        return false;
    return ksys::act::ai::Ai::isChangeable();
}

const sead::Vector3f* MiniBeamAttack::m35() {
    return &sub_71005D9330(mActor);
}

void MiniBeamAttack::m37() {
    _220 = *m35();
    BreathAttackEnemyBattle::m37();
}

void MiniBeamAttack::m41() {
    if (*mIsValidGuide_s)
        _100.end("Target_End");
    _230.fadeXLink();
}

s32 MiniBeamAttack::m45() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        return enemy->_e68.value;
    return 100;
}

}  // namespace uking::ai
