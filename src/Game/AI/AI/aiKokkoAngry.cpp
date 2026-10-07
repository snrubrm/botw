#include "Game/AI/AI/aiKokkoAngry.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/AI/Action/actionSpotBgmTriggerAction.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

KokkoAngry::KokkoAngry(const InitArg& arg) : CreateActorWithTarget(arg) {}

KokkoAngry::~KokkoAngry() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (enemy->_e84.isOnBit(6)) {
            ksys::gdt::setBoolByKey(false, "Kokko_Event_Running", false);
            if (auto* mgr = sub_710FFD7CC())
                mgr->sub_710FFBEA8(false);
        }
    }
}

bool KokkoAngry::init_(sead::Heap* heap) {
    return CreateActorWithTarget::init_(heap);
}

// NON_MATCHING: the original derives the entry link address from &_d70 (+8) in x20 (same as calc_ / m35)
void KokkoAngry::enter_(ksys::act::ai::InlineParamPack* params) {
    CreateActorWithTarget::enter_(params);
    const ksys::act::BaseProcLink* target = &ksys::act::sUnk_71026505e0;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (!enemy->_d70.sub_71002DCCBC(-1))
            target = &enemy->_d70.mEntries[0].link;
    }
    if (!target->hasProc())
        setFailed();
}

void KokkoAngry::leave_() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.resetBit(6);
    ksys::gdt::setBoolByKey(false, "Kokko_Event_Running", false);
    if (auto* mgr = sub_710FFD7CC())
        mgr->sub_710FFBEA8(false);
    CreateActorWithTarget::leave_();
}

void KokkoAngry::loadParams_() {
    CreateActorWithTarget::loadParams_();
}

bool KokkoAngry::m36() {
    if (CreateActorWithTarget::m36() &&
        mActor->getASList()->x_7(0, 0, &ksys::as::ASList::Unk2::sub_7101162FE8)) {
        return true;
    }
    return false;
}

// NON_MATCHING: see getKokkoTargetLink (entry-0 address computed as enemy + 0xd78)
void KokkoAngry::calc_() {
    if (getKokkoTargetLink(mActor)->hasProc())
        CreateActorWithTarget::calc_();
    else
        setFinished();
}

// NON_MATCHING: see getKokkoTargetLink (entry-0 address computed as enemy + 0xd78)
sead::Vector3f KokkoAngry::m35() {
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(getKokkoTargetLink(mActor), &accessor))
        return accessor.getActorMtx().getTranslation();
    const auto& mtx = mActor->getMtx();
    return mtx.getTranslation() + mtx.getBase(2);
}

}  // namespace uking::ai
