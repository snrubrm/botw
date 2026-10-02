#include "Game/AI/Action/actionSiteBossSpearAttackVertical.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SiteBossSpearAttackVertical::SiteBossSpearAttackVertical(const InitArg& arg)
    : SiteBossSpearAttackBase(arg) {}

SiteBossSpearAttackVertical::~SiteBossSpearAttackVertical() = default;

bool SiteBossSpearAttackVertical::init_(sead::Heap* heap) {
    return SiteBossSpearAttackBase::init_(heap);
}

void SiteBossSpearAttackVertical::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossSpearAttackBase::enter_(params);
}

void SiteBossSpearAttackVertical::leave_() {
    SiteBossSpearAttackBase::leave_();
    if (_f0.isAllocatedOrFailed())
        _f0.deleteProc();
}

void SiteBossSpearAttackVertical::loadParams_() {
    SiteBossSpearAttackBase::loadParams_();
    getStaticParam(&mShockWaveAttackPower_s, "ShockWaveAttackPower");
}

// NON_MATCHING: instruction scheduling of the translation update (the original stores each row's
// result before loading the next row)
void SiteBossSpearAttackVertical::calc_() {
    SiteBossSpearAttackBase::calc_();

    ksys::as::ASList::Unk4 query;
    if (!sub_71005DD780(mActor, 81, &query, 0, 0))
        return;

    if (_f0.isAllocatedOrFailed() && _f0.isProcReady()) {
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(_f0.getProc())) {
            sead::Matrix34f mtx = mActor->getMtx();
            mtx.setTranslation(mtx * sead::Vector3f(0.0f, 0.75f, 1.0f));
            const sead::Vector3f scale(15.0f, 15.0f, 15.0f);
            actor->setMatrix(mtx, &scale);
        }
        _f0.releaseAndWakeProc();
    }
}

}  // namespace uking::action
