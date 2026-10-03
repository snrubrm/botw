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

// NON_MATCHING: see getKokkoTargetLink (entry-0 address computed as enemy + 0xd78)
void KokkoAngry::enter_(ksys::act::ai::InlineParamPack* params) {
    CreateActorWithTarget::enter_(params);
    if (!getKokkoTargetLink(mActor)->hasProc())
        setFailed();
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
