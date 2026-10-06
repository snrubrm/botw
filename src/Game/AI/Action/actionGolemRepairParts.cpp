#include "Game/AI/Action/actionGolemRepairParts.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Damage/dmgDamageCallback.h"

namespace uking::action {

GolemRepairParts::GolemRepairParts(const InitArg& arg) : ActionWithAS(arg) {
    _e8._18.y(mActor);
}

GolemRepairParts::~GolemRepairParts() = default;

bool GolemRepairParts::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void GolemRepairParts::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    setDamageCallbackTiming(mActor, 4, &_118);
    mFlags.reset(Flag::Changeable);
    sub_710018CED4();
}

void GolemRepairParts::leave_() {
    sub_71005DA114(mActor, &_118);
    ActionWithAS::leave_();
}

void GolemRepairParts::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mTgtBodyName_s, "TgtBodyName");
    getStaticParam(&mChmObjectName_s, "ChmObjectName");
    _60.sub_71005E1BE8(this, 0);
    _a0.sub_71005E1BE8(this, 1);
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

void GolemRepairParts::calc_() {
    ActionWithAS::calc_();
    if (auto* as_list = mActor->getASList()) {
        if (as_list->x(69, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true))
            sub_710018D09C();
    }
    if (isFinishedAS(0, 0))
        setFinished();
}

// NON_MATCHING: regalloc only (the original keeps &_e8 in the register freed by the Enemy pointer and
// &_1128 in a new one).
void GolemRepairParts::sub_710018CED4() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        {
            auto& link = enemy->_1128.getActorPartsActor(_60._0);
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            if (accessor.hasProc() && accessor.isStateCalc())
                _e8.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
        }
        {
            auto& link = enemy->_1128.getActorPartsActor(_a0._0);
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            if (accessor.hasProc() && accessor.isStateCalc())
                _e8.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
        }
    }
}

}  // namespace uking::action
