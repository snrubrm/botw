#include "Game/AI/Action/actionForkOnEnterSwapDropTableActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Resource/Actor/resResourceDrop.h"

namespace uking::action {

ForkOnEnterSwapDropTableActor::ForkOnEnterSwapDropTableActor(const InitArg& arg)
    : ForkOnEnterSwapDropTableActorBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ForkOnEnterSwapDropTableActor::~ForkOnEnterSwapDropTableActor() {
    ;
}

bool ForkOnEnterSwapDropTableActor::init_(sead::Heap* heap) {
    return ForkOnEnterSwapDropTableActorBase::init_(heap);
}

void ForkOnEnterSwapDropTableActor::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkOnEnterSwapDropTableActorBase::enter_(params);
}

void ForkOnEnterSwapDropTableActor::leave_() {
    ForkOnEnterSwapDropTableActorBase::leave_();
}

void ForkOnEnterSwapDropTableActor::loadParams_() {
    ForkOnEnterSwapDropTableActorBase::loadParams_();
    getStaticParam(&mTableName_s, "TableName");
}

void ForkOnEnterSwapDropTableActor::calc_() {
    ForkOnEnterSwapDropTableActorBase::calc_();
}

bool ForkOnEnterSwapDropTableActor::m32(sead::BufferedSafeString* name) {
    auto* drop = mActor->getParam()->getRes().mDropTable;
    if (!drop)
        return false;
    const s32 table_idx = drop->findTableIndex(mTableName_s);
    if (table_idx < 0)
        return false;
    const sead::SafeString& drop_name = drop->getRandomDropFromTable(table_idx);
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    ksys::eco::getEcosystemActorName(name, drop_name, pos);
    return true;
}

}  // namespace uking::action
