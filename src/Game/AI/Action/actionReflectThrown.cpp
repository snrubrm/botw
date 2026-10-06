#include "Game/AI/Action/actionReflectThrown.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>

namespace uking::action {

ReflectThrown::ReflectThrown(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ReflectThrown::~ReflectThrown() = default;

bool ReflectThrown::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original selects both the damage and the reaction arguments with csel on the sign of the
// reaction level (`csel w1, w9, w9`), ours branches around the clamp.
void ReflectThrown::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _49 = true;
    const f32 power = actor->getParam()->getRes().mGParamList->getAttack()->mPower.ref();
    const s32 level = *mReactionLevel_s;
    sub_71005DBC94(actor, s32(power),
                   level < 0 ? sead::Mathi::clamp((s32(power) - 1) / 4, 0, 2) : level, true, false,
                   false, false);
    if (auto* chemical = mActor->getChemicalStuff()) {
        _48 = (chemical->_c >> 6) & 1;
        chemical->sub_7100D91098(true);
    }
    sead::Vector3f velocity = *mTargetDir_d;
    const f32 speed = *mPower_d;
    velocity *= speed / f32(ksys::act::sub_7100EDD218(actor));
    ksys::act::sub_7100EE5980(actor, velocity);
    ksys::act::sub_7100EE5A14(
        actor, sead::Vector3f::ey * sead::GlobalRandom::instance()->getF32Range(
                                        sead::Mathf::deg2rad(2), sead::Mathf::deg2rad(8)));
    if (mIsReflectThrownBullet_a)
        *mIsReflectThrownBullet_a = true;
}

void ReflectThrown::leave_() {
    sub_71005DC02C(mActor);
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D91098(_48);
    if (mIsReflectThrownBullet_a)
        *mIsReflectThrownBullet_a = false;
}

void ReflectThrown::loadParams_() {
    getStaticParam(&mReactionLevel_s, "ReactionLevel");
    getStaticParam(&mFinishWaterDepth_s, "FinishWaterDepth");
    getDynamicParam(&mPower_d, "Power");
    getDynamicParam(&mTargetDir_d, "TargetDir");
    getAITreeVariable(&mIsReflectThrownBullet_a, "IsReflectThrownBullet");
}

void ReflectThrown::calc_() {
    if (isFinished()) {
        sub_71005DC02C(mActor);
        if (auto* chemical = mActor->getChemicalStuff())
            chemical->sub_7100D91098(_48);
        setFinished();
    }
    _49 = false;
}

bool ReflectThrown::isFinished() const {
    if (_49)
        return false;
    auto* actor = mActor;
    if (isLandedMaybe(actor, false) || isBgGroundHit(actor, false) ||
        sub_71007A4178(mActor, false)) {
        return true;
    }
    if (*mFinishWaterDepth_s >= 0.0f) {
        f32 depth;
        if (mActor->get68f()) {
            const f32 y = mActor->getMtx().m[1][3];
            depth = mActor->get6f0() - y;
        } else {
            depth = 0.0f;
        }
        if (depth >= *mFinishWaterDepth_s)
            return true;
    }
    if (auto* manager = sub_710072BA90(mActor))
        return sub_7100736BBC(manager->getField54());
    return false;
}

}  // namespace uking::action
