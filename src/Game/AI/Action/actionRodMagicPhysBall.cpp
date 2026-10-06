#include "Game/AI/Action/actionRodMagicPhysBall.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

RodMagicPhysBall::RodMagicPhysBall(const InitArg& arg) : ChemicalPhysBall(arg) {}

RodMagicPhysBall::~RodMagicPhysBall() = default;

void RodMagicPhysBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ChemicalPhysBall::enter_(params);
    _d8.reset();
    _160 = false;
    _161 = false;
    _1a8._c = true;
    sub_710023B234(&_1a8);
}

void RodMagicPhysBall::leave_() {
    if (_160)
        mActor->sub_71011DA834(&_e8);
    ChemicalPhysBall::leave_();
}

void RodMagicPhysBall::loadParams_() {
    ChemicalPhysBall::loadParams_();
    getStaticParam(&mCreateActorName_s, "CreateActorName");
    getStaticParam(&mChemicalType_s, "ChemicalType");
    getStaticParam(&mBgCheckHeight_s, "BgCheckHeight");
}

// NON_MATCHING: the original loads the argument of `_e8.sub_7100D3C5E0(mActor)` as `ldr x1, [x19, #0x8]`; ours reuses
// the `&mActor` register (`ldr x1, [x20]`) of the neighbouring mActor loads. Nothing else differs.
void RodMagicPhysBall::calc_() {
    bool flag = false;
    if (sub_710023B458(&flag)) {
        if (flag && *mChemicalType_s == 0)
            xlinkSearchAndEmit(mActor, "Explode", 2, &_168[0]);
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
    if (mActor->get68f().load() || _d8.hasProc())
        sub_710023B7B4();
    ChemicalPhysBall::calc_();
    if (_160) {
        auto* actor = _e8.sub_7100D3C5E0(mActor);
        if (!actor || actor->getState() != ksys::act::BaseProc::State::Calc)
            mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    } else if (*mChemicalType_s == 0) {
        const bool hit = isBgGroundHit(mActor, false) || isLandedMaybe(mActor, false);
        if (hit && !_161)
            xlinkSearchAndEmit(mActor, "Rebound", 2, &_168[1]);
        _161 = hit;
    }
}

bool RodMagicPhysBall::m33() {
    return false;
}

f32 RodMagicPhysBall::m40() {
    f32 time = *mDeleteTime_s;
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor)) {
        if (bullet->_cf8 >= 0.0f)
            time = bullet->_cf8;
    }
    return time;
}

bool RodMagicPhysBall::sub_710023B234(Unk1a8* out) {
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor)) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&bullet->_ba0, &accessor);
        if (accessor.hasProc()) {
            accessor.getActorMtx().getTranslation(out->_0);
            return true;
        }
    }
    return false;
}

int RodMagicPhysBall::m36() {
    const int type = *mChemicalType_s;
    int flags = ChemicalAttackBall::m36();
    if (type == 1)
        flags |= 8;
    return flags;
}

}  // namespace uking::action
