#include "Game/AI/AI/aiPriestBossPhaseFinish.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

// Declared only (placeholder names): the original calls two unnamed helpers (0x7100ffeb28 returns an object or null, 0x710100e0e0
// takes it).
void* sub_7100FFEB28();
void sub_710100E0E0(void* object);

namespace uking::ai {

PriestBossPhaseFinish::PriestBossPhaseFinish(const InitArg& arg) : PriestBossPhase(arg) {}

PriestBossPhaseFinish::~PriestBossPhaseFinish() = default;

bool PriestBossPhaseFinish::init_(sead::Heap* heap) {
    return PriestBossPhase::init_(heap);
}

void PriestBossPhaseFinish::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossPhase::enter_(params);
    _90.value = _90.previous_value = *mStartDemoDelayFrames_s;
    if (auto* object = sub_7100FFEB28())
        sub_710100E0E0(object);
}

void PriestBossPhaseFinish::calc_() {
    if (isFinished() || isFailed())
        return;

    _90.update();
    if (_90.value <= sead::Mathf::epsilon()) {
        if (ksys::gdt::getFlag_Defeated_Priest_Boss_Normal_Num() == 0)
            ksys::gdt::increaseFlag_Defeated_Priest_Boss_Normal_Num(1);
        mActor->emitBasicSigOn();
        setFinished();
        return;
    }

    if (_90.value <= 5.0f && !_9c) {
        sub_7100529AB0();
        _9c = true;
    }
}

void PriestBossPhaseFinish::sub_7100529AB0() {
    ksys::act::BaseProcLink link;
    if (!sub_7100525BC0(1, &link))
        return;

    auto* actor = sead::DynamicCast<ksys::act::Actor>(link.getProc(nullptr, nullptr));
    auto* enemy = sead::DynamicCast<act::Enemy>(actor);
    if (!enemy)
        return;

    for (auto it = enemy->_1128.mList.begin(); it != enemy->_1128.mList.end(); ++it) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&(*it)->mLink, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

void PriestBossPhaseFinish::leave_() {
    PriestBossPhase::leave_();
}

void PriestBossPhaseFinish::loadParams_() {
    PriestBossPhase::loadParams_();
    getStaticParam(&mStartDemoDelayFrames_s, "StartDemoDelayFrames");
    getMapUnitParam(&mPriestBossStartPhase_m, "PriestBossStartPhase");
}

}  // namespace uking::ai
