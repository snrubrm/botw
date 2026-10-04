#include "Game/AI/Action/actionChemicalElectricWaterBall.h"
#include <gsys/gsysModel.h>
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLimiter.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

namespace uking::action {

ChemicalElectricWaterBall::ChemicalElectricWaterBall(const InitArg& arg)
    : ChemicalAttackBall(arg) {}

ChemicalElectricWaterBall::~ChemicalElectricWaterBall() = default;

bool ChemicalElectricWaterBall::init_(sead::Heap* heap) {
    if (!ChemicalAttackBall::init_(heap))
        return false;
    *static_cast<Unk_71025afb58**>(mChemicalBulletBindActor_a) = &_138;
    return true;
}

// NON_MATCHING: model-versus-actor matrix selection uses different registers.
void ChemicalElectricWaterBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ChemicalAttackBall::enter_(params);
    _b0.reset(*mDeleteTime_s);
    _bc = false;
    if (auto* link = sead::DynamicCast<Unk_7102370e70>(
            *static_cast<Unk_71025afb58**>(mChemicalBulletBindActor_a))) {
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(link->mLink.getProc(nullptr, nullptr))) {
            _c0.x(actor);
            sead::Matrix34f matrix;
            matrix = actor->getModel() ? actor->getModel()->getMatrix() : actor->getMtx();
            sead::Matrix34f inverse;
            inverse.setInverse(matrix);
            _c0._28.setMul(inverse, mActor->getMtx());
            mActor->sub_71011DA824(&_c0);
            _bc = true;
        }
    }
    if (auto* chemical = mActor->sub_71011D8A44(0)) {
        chemical->_190 = 1.0f;
        chemical->sub_7100D90CD8(true);
        _150 = false;
    }
    if (*mDeleteTime_s >= 0 && !_151) {
        ksys::act::ActorLimiter::instance()->get(ksys::act::ActorLimiter::Category::_7).addActor(mActor, true);
        _151 = true;
    }
}

void ChemicalElectricWaterBall::leave_() {
    mActor->sub_71011DA834(&_c0);
    ChemicalAttackBall::leave_();
}

void ChemicalElectricWaterBall::loadParams_() {
    ChemicalAttackBall::loadParams_();
    getStaticParam(&mDeleteTime_s, "DeleteTime");
    getStaticParam(&mTargetScale_s, "TargetScale");
    getStaticParam(&mScaleKeep_s, "ScaleKeep");
    getAITreeVariable(&mChemicalBulletBindActor_a, "ChemicalBulletBindActor");
}

// NON_MATCHING: bullet flag mask register allocation differs.
void ChemicalElectricWaterBall::calc_() {
    const bool hit_player = sub_71000DBC74();
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor)) {
        if (hit_player)
            bullet->_cf4 |= 0x20;
        else
            bullet->_cf4 &= ~0x20;
    }
    if (*mDeleteTime_s >= 0) {
        _b0.update();
        if (_b0.value <= sead::Mathf::epsilon())
            mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
    if (_bc) {
        auto* actor = _c0.sub_7100D3C5E0(mActor);
        if (!actor || actor->getState() != ksys::act::BaseProc::State::Calc)
            mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
    if (!_150) {
        if (auto* chemical = mActor->sub_71011D8A44(0))
            chemical->sub_7100D91978(chemical->_1b8 * *mTargetScale_s);
        _150 = true;
    }
    if (*mScaleKeep_s) {
        if (auto* chemical = mActor->sub_71011D8A44(0))
            chemical->_190 = 1.0f;
    }
}

bool ChemicalElectricWaterBall::sub_71000DBC74() {
    auto* actor = mActor;
    if (actor && hasAttackInfo(actor)) {
        const s32 count = getNumAttackInfoMaybe(actor);
        for (s32 index = 0; index < count; ++index) {
            auto* info = getAttackInfo(actor, index);
            if (info && ksys::act::isPlayerProfile(&info->_50)) {
                ksys::act::acc::PlayerBase accessor;
                ksys::act::acquireActor(&info->_50, &accessor);
                return accessor.x_12();
            }
        }
    }
    return false;
}

int ChemicalElectricWaterBall::m36() {
    return ChemicalAttackBall::m36() | 8;
}

int ChemicalElectricWaterBall::m37() {
    return mActor->getParam()->getRes().mGParamList->getAttack()->mPower.ref();
}

int ChemicalElectricWaterBall::m38() {
    return mActor->getParam()->getRes().mGParamList->getAttack()->mPowerForPlayer.ref();
}

}  // namespace uking::action
