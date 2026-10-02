#include "Game/AI/Behavior/behaviorCreateEaselBase.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"

namespace uking::behavior {

CreateEaselBase::CreateEaselBase(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
CreateEaselBase::~CreateEaselBase() {
    ;
}

bool CreateEaselBase::m6(sead::Heap* heap) {
    ksys::act::InstParamPack pack;
    const char* name = m14();
    if (*name != sead::SafeString::cNullChar) {
        ksys::act::ActorCreator::instance()->requestCreateActor(
            name, ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_48, &pack, nullptr,
            1);
    }
    return true;
}

void CreateEaselBase::m8() {}

void CreateEaselBase::m9() {}

void CreateEaselBase::loadParams() {
    getStaticParam(&mIsNoSystemDelete_s, "IsNoSystemDelete");
    getStaticParam(&mActorName_s, "ActorName");
    getStaticParam(&mOffset_s, "Offset");
}

const char* CreateEaselBase::m14() {
    return mActorName_s.cstr();
}

}  // namespace uking::behavior
