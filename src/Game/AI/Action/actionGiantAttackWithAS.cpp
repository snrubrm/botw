#include "Game/AI/Action/actionGiantAttackWithAS.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

GiantAttackWithAS::GiantAttackWithAS(const InitArg& arg) : GiantAttack(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
GiantAttackWithAS::~GiantAttackWithAS() {
    ;
}

bool GiantAttackWithAS::init_(sead::Heap* heap) {
    return GiantAttack::init_(heap);
}

void GiantAttackWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantAttack::enter_(params);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

void GiantAttackWithAS::leave_() {
    GiantAttack::leave_();
}

void GiantAttackWithAS::loadParams_() {
    GiantAttack::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void GiantAttackWithAS::calc_() {
    GiantAttack::calc_();
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD66C(mActor, &query, 0, 0))
        m32(&query.name);
    if (sub_71005DD74C(mActor, nullptr, 0, 0))
        m33();
    if (isFinishedAS(0, 0))
        setFinished();
}

void GiantAttackWithAS::m32(const sead::SafeString* name) {}

void GiantAttackWithAS::m33() {}

}  // namespace uking::action
