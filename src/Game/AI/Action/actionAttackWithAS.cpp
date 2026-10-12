#include "Game/AI/Action/actionAttackWithAS.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

AttackWithAS::AttackWithAS(const InitArg& arg) : TurnGiantAttack(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
AttackWithAS::~AttackWithAS() {
    ;
}

bool AttackWithAS::init_(sead::Heap* heap) {
    return TurnGiantAttack::init_(heap);
}

void AttackWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnGiantAttack::enter_(params);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

void AttackWithAS::leave_() {
    TurnGiantAttack::leave_();
}

void AttackWithAS::loadParams_() {
    TurnGiantAttack::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void AttackWithAS::calc_() {
    TurnGiantAttack::calc_();
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD66C(mActor, &query, 0, 0))
        m32(&query.name);
    if (sub_71005DD74C(mActor, nullptr, 0, 0))
        m33();
    if (isFinishedAS(0, 0))
        setFinished();
}

void AttackWithAS::m32(const sead::SafeString* name) {}

void AttackWithAS::m33() {}

}  // namespace uking::action
