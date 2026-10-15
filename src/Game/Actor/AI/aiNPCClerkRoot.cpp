#include "Game/Actor/AI/aiNPCClerkRoot.h"
#include "Game/UI/uiShopMgr.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceShop.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSystem.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

NPCClerkRoot::NPCClerkRoot(const InitArg& arg) : NPCRoot(arg) {}

NPCClerkRoot::~NPCClerkRoot() = default;

bool NPCClerkRoot::init_(sead::Heap* heap) {
    if (!NPCRoot::init_(heap))
        return false;
    _240.initWithName(mActor, mActor->getName(), "ClerkAsk");
    return true;
}

void NPCClerkRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCRoot::enter_(params);
    {
        ksys::act::ActorLinkConstDataAccess accessor;
        const bool grouping_item =
            ksys::act::hasTag(mActor, ksys::act::tags::GroupingDisplayItem);
        _238 = ksys::act::sub_7100EE2850(mActor, &accessor, grouping_item, nullptr, nullptr);
    }
    mActor->resetConnectedCalcChild(false);
    _239 = false;
    if (_240.mEventFlow)
        return;
    if (auto* object = mActor->getMapObject()) {
        if (auto* link_data = object->getLinkData()) {
            auto& links = link_data->mLinksToSelf.links;
            for (s32 i = 0; i < links.size(); ++i) {
                if (links[i].type == ksys::map::MapLinkDefType::ForSale) {
                    _240.loadEvent();
                    break;
                }
            }
        }
    }
}

void NPCClerkRoot::calc_() {
    NPCRoot::calc_();
    ksys::act::ActorLinkConstDataAccess accessor;
    const bool grouping_item =
        ksys::act::hasTag(mActor, ksys::act::tags::GroupingDisplayItem);
    _238 = ksys::act::sub_7100EE2850(mActor, &accessor, grouping_item, nullptr, nullptr);
}

void NPCClerkRoot::leave_() {
    NPCRoot::leave_();
    if (_240.mEventFlow && (isActorDeletedOrDeleting() || !isActorGoingBackToRootAi()))
        _240.unloadEvent();
    if (auto* mgr = ui::UiShopMgr::instance())
        mgr->sub_7100985508();
}

s32 NPCClerkRoot::sub_71004C402C(const sead::SafeString& name) {
    const auto* shop = mActor->getParam()->getRes().mShopData;
    if (!shop)
        return 0;
    const s32 index = shop->findTableIndexOrNormal("Market");
    if (index < 0)
        return 0;
    for (const auto& item : shop->getTables()[index].items) {
        if (item.name.ref() == name)
            return item.price_adjustment.ref();
    }
    return 0;
}

// NON_MATCHING: accessor, string and event-call stack slots differ.
bool NPCClerkRoot::handleMessage_(const ksys::Message* message) {
    if (NPCRoot::handleMessage_(message))
        return true;
    if (_239 || message->getType() != ksys::MessageType(0x8000070))
        return false;
    auto* item = static_cast<ksys::act::Actor*>(message->getUserData());
    if (!item)
        return false;
    sead::SafeString name(item->getName());
    if (ksys::act::hasTag(item, ksys::act::tags::Mannequin)) {
        const sead::SafeString same_group =
            item->getParam()->getRes().mGParamList->getSystem()->mSameGroupActorName.ref();
        if (!same_group.isEmpty())
            name = same_group;
    }
    ksys::act::ActorLinkConstDataAccess accessor(item);
    const s32 stock = getPlacedItemStockNum(mActor, accessor, nullptr, false);
    const s32 buying_price = ksys::act::getItemBuyingPrice(ksys::act::InfoData::instance(), name.cstr());
    const s32 price = buying_price + sub_71004C402C(name);
    ksys::gdt::setFlag_IsBuyPlacedItem(false, false);
    ksys::gdt::setFlag_IsOpenShopInfo_Demo(true, false);
    ksys::gdt::setFlag_ShopTradePrice(price, false);
    ksys::gdt::setFlag_Shop_PlacedItemStockNum(stock, false);
    ksys::gdt::setFlag_Shop_TradeItemNum(1, false);
    ksys::gdt::setStr64ByKey(item->getName().cstr(), "PlacedItemName", false);
    ksys::gdt::setS32ByKey(price, "PlacedItemPrice", false);
    bool called;
    {
        ksys::evt::Metadata metadata(mActor->getName().cstr(), "ClerkAsk", "");
        metadata.setCurrentActor(item);
        ksys::evt::CallArg arg;
        arg._31 = true;
        arg.metadata = &metadata;
        arg.proc = mActor;
        called = ksys::evt::sub_7100701AA8(arg);
    }
    _239 = called;
    if (called) {
        if (auto* shop = ui::UiShopMgr::instance())
            shop->sub_71009854FC(item);
    }
    return true;
}

void NPCClerkRoot::onPreDelete() {
    NPCRoot::onPreDelete();
    if (_240.mEventFlow)
        _240.unloadEvent();
}

void NPCClerkRoot::loadParams_() {
    NPCRoot::loadParams_();
}

}  // namespace uking::ai
