#include "Game/AI/AI/aiKokkoAngry.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

KokkoAngry::KokkoAngry(const InitArg& arg) : CreateActorWithTarget(arg) {}

KokkoAngry::~KokkoAngry() = default;

bool KokkoAngry::init_(sead::Heap* heap) {
    return CreateActorWithTarget::init_(heap);
}

void KokkoAngry::enter_(ksys::act::ai::InlineParamPack* params) {
    CreateActorWithTarget::enter_(params);
}

void KokkoAngry::leave_() {
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

// NON_MATCHING: the original passes -1 as a full 32-bit value to sub_71002DCCBC (its parameter is
// probably not u16) and keeps &_d70 in x20
void KokkoAngry::calc_() {
    const ksys::act::BaseProcLink* target = &ksys::act::sUnk_71026505e0;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        auto& targets = enemy->_d70;
        target = targets.sub_71002DCCBC(0xffff) ? &ksys::act::sUnk_71026505e0 :
                                                  &targets.mEntries[0].link;
    }

    if (target->hasProc())
        CreateActorWithTarget::calc_();
    else
        setFinished();
}

// NON_MATCHING: the original derives the entry link address from &_d70 (+8) (regalloc follows)
sead::Vector3f KokkoAngry::m35() {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::BaseProcLink* link = &ksys::act::sUnk_71026505e0;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (!enemy->_d70.sub_71002DCCBC(-1))
            link = &enemy->_d70.mEntries[0].link;
    }
    if (ksys::act::acquireActor(link, &accessor))
        return accessor.getActorMtx().getTranslation();
    const auto& mtx = mActor->getMtx();
    return mtx.getTranslation() + mtx.getBase(2);
}

}  // namespace uking::ai
