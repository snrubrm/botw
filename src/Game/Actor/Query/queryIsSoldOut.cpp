#include "Game/Actor/Query/queryIsSoldOut.h"
#include <evfl/Query.h>
#include "Game/Actor/actNPC.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"

namespace uking::query {

IsSoldOut::IsSoldOut(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsSoldOut::~IsSoldOut() = default;

int IsSoldOut::doQuery() {
    if (mTableName == "Current" || mTableName.isEmpty())
        return ui::sub_7100A982A4();
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor)) {
        if (npc->_f88.giveItem(mActor->getParam()->getRes().mShopData, mActor->getName(),
                               mTableName, false))
            return npc->_f88.sub_710091D4C8();
    }
    return false;
}

void IsSoldOut::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "TableName");
}

void IsSoldOut::loadParams() {
    getDynamicParam(&mTableName, "TableName");
}

}  // namespace uking::query
