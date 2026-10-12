#include "Game/AI/Action/actionOnEnterSwapDropTable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Resource/Actor/resResourceDrop.h"

namespace uking::action {

OnEnterSwapDropTable::OnEnterSwapDropTable(const InitArg& arg)
    : OnEnterSwapActorBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
OnEnterSwapDropTable::~OnEnterSwapDropTable() {
    ;
}

bool OnEnterSwapDropTable::init_(sead::Heap* heap) {
    return OnEnterSwapActorBase::init_(heap);
}

void OnEnterSwapDropTable::enter_(ksys::act::ai::InlineParamPack* params) {
    OnEnterSwapActorBase::enter_(params);
}

void OnEnterSwapDropTable::leave_() {
    OnEnterSwapActorBase::leave_();
}

void OnEnterSwapDropTable::loadParams_() {
    OnEnterSwapActorBase::loadParams_();
    getStaticParam(&mTableName_s, "TableName");
}

void OnEnterSwapDropTable::calc_() {
    OnEnterSwapActorBase::calc_();
}

bool OnEnterSwapDropTable::m32(sead::BufferedSafeString* name) {
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
