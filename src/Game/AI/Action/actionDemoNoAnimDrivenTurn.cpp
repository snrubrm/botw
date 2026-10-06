#include "Game/AI/Action/actionDemoNoAnimDrivenTurn.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::action {

DemoNoAnimDrivenTurn::DemoNoAnimDrivenTurn(const InitArg& arg) : ForkTurn(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
DemoNoAnimDrivenTurn::~DemoNoAnimDrivenTurn() {
    ;
}

bool DemoNoAnimDrivenTurn::init_(sead::Heap* heap) {
    return ForkTurn::init_(heap);
}

void DemoNoAnimDrivenTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkTurn::enter_(params);
}

void DemoNoAnimDrivenTurn::leave_() {
    ForkTurn::leave_();
}

void DemoNoAnimDrivenTurn::loadParams_() {
    ForkTurn::loadParams_();
    getDynamicParam(&mObjectId_d, "ObjectId");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
}

void DemoNoAnimDrivenTurn::calc_() {
    ForkTurn::calc_();
}

void DemoNoAnimDrivenTurn::m36(sead::Vector3f* target) {
    switch (*mObjectId_d) {
    case 1: {
        ksys::act::acc::PlayerBase accessor;
        accessor.getPlayerFromPlayerInfo();
        accessor.getActorMtx().getTranslation(*target);
        break;
    }
    case 4: {
        ksys::act::ActorConstDataAccess accessor;
        if (auto* obj = ksys::act::findLinkReferenceObj(mActor, mActorName_d, mUniqueName_d,
                                                        nullptr)) {
            obj->getActorWithAccessor(accessor);
            if (accessor.hasProc())
                accessor.getActorMtx().getTranslation(*target);
            else {
                const sead::Vector3f translate = obj->getTranslate();
                *target = translate;
            }
        }
        break;
    }
    default:
        setFinished();
        break;
    }
}

}  // namespace uking::action
