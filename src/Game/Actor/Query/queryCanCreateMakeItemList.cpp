#include "Game/Actor/Query/queryCanCreateMakeItemList.h"
#include <evfl/Query.h>
#include "Game/gameNpcShopData.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"

namespace uking::query {

CanCreateMakeItemList::CanCreateMakeItemList(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CanCreateMakeItemList::~CanCreateMakeItemList() = default;

static const char* const sShopTypeNames[] = {"Cooking", "Jewelry", "Compound", "Ancient"};

int CanCreateMakeItemList::doQuery() {
    return NpcShopData::sub_710091D8E4(mActor->getParam()->getRes().mShopData,
                                       sShopTypeNames[*mShopType], *mIncludePorchMainMat,
                                       *mIncludePorchSubMat);
}

void CanCreateMakeItemList::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "ShopType");
    loadBool(arg.param_accessor, "IncludePorchMainMat");
    loadBool(arg.param_accessor, "IncludePorchSubMat");
}

void CanCreateMakeItemList::loadParams() {
    getDynamicParam(&mShopType, "ShopType");
    getDynamicParam(&mIncludePorchMainMat, "IncludePorchMainMat");
    getDynamicParam(&mIncludePorchSubMat, "IncludePorchSubMat");
}

}  // namespace uking::query
