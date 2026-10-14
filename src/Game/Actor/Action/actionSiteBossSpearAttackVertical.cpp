#include "Game/Actor/Action/actionSiteBossSpearAttackVertical.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"

namespace uking::action {

SiteBossSpearAttackVertical::SiteBossSpearAttackVertical(const InitArg& arg)
    : SiteBossSpearAttackBase(arg) {}

SiteBossSpearAttackVertical::~SiteBossSpearAttackVertical() = default;

bool SiteBossSpearAttackVertical::init_(sead::Heap* heap) {
    return SiteBossSpearAttackBase::init_(heap);
}

// Creates the (sleeping) shock wave actor in front of the boss; its attack power grows with the number of
// defeated Blights (3 / 4 in the later phases).
void SiteBossSpearAttackVertical::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossSpearAttackBase::enter_(params);
    sead::Matrix34f mtx = mActor->getMtx();
    const sead::Vector3f offset(0.0f, 0.75f, 0.0f);
    mtx.m[0][3] += offset.x;
    mtx.m[1][3] += offset.y;
    mtx.m[2][3] += offset.z;

    ksys::act::InstParamPack pack;
    pack->addMatrix(mtx);
    ksys::act::ActorCreator::addScale(pack, 15.0f);

    const s32 power = *mShockWaveAttackPower_s;
    s32 num = getNumberOfDeadBlights();
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        switch (boss->_1534 & ~3) {
        case 8:
            num = 4;
            break;
        case 4:
            num = 3;
            break;
        }
    }
    pack->add(power + *mAddAttackPower_s * num, "AttackPower");
    pack->add(15.0f, "ScaleTime");
    pack->add(0x102, "AttackAttr");
    pack->add(m34(), "AtMinDamage");
    sub_710073DB94("SiteBossSpearShockWave", &_f0, &pack,
                   ksys::act::ActorHeapUtil::instance()->getBaseProcHeap());
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
