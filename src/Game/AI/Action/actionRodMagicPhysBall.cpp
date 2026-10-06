#include "Game/AI/Action/actionRodMagicPhysBall.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

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

void RodMagicPhysBall::calc_() {
    ChemicalPhysBall::calc_();
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
