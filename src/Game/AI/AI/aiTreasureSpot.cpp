#include "Game/AI/AI/aiTreasureSpot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::ai {

TreasureSpot::TreasureSpot(const InitArg& arg) : CommonPickedItem(arg) {}

TreasureSpot::~TreasureSpot() = default;

bool TreasureSpot::init_(sead::Heap* heap) {
    return CommonPickedItem::init_(heap);
}

void TreasureSpot::enter_(ksys::act::ai::InlineParamPack* params) {
    CommonPickedItem::enter_(params);
}

// NON_MATCHING: the original keeps mObjects.size() and the buffer pointer in registers across the loop
// (bounds check kept); ours reloads both after each checkRevivalFlag call
void TreasureSpot::calc_() {
    auto* actor = mActor;
    auto* object = actor->getMapObject();
    if (object) {
        auto* link_data = object->getLinkData();
        if (link_data) {
            for (int i = 0; i < link_data->mObjects.size(); ++i) {
                auto* obj = link_data->mObjects[i];
                if (obj && obj->checkRevivalFlag(ksys::map::ActorData::Flag::RevivalForDrop)) {
                    ksys::act::disableAllAttClients(actor);
                    break;
                }
            }
        }
    }
    CommonPickedItem::calc_();
}

void TreasureSpot::leave_() {
    CommonPickedItem::leave_();
}

void TreasureSpot::loadParams_() {
    CommonPickedItem::loadParams_();
    getStaticParam(&mGetAttKeyForGuardian_s, "GetAttKeyForGuardian");
    getMapUnitParam(&mTresasureSpotType_m, "TresasureSpotType");
}

void TreasureSpot::m34() {
    auto* actor = mActor;
    ksys::act::disableAttClient(actor, mGetAttKeyName_s);
    ksys::act::disableAttClient(actor, mGetAttKeyForGuardian_s);
    CommonPickedItem::m34();
}

const sead::SafeString& TreasureSpot::m36() {
    switch (*mTresasureSpotType_m) {
    case 0:
        return mGetAttKeyName_s;
    case 1:
        return mGetAttKeyForGuardian_s;
    default:
        return sead::SafeString::cEmptyString;
    }
}

void TreasureSpot::m37() {
    auto* actor = mActor;
    if (!ksys::act::attentionStuff_0(actor) || *mTresasureSpotType_m == 1)
        ksys::act::disableAttClient(actor, "NoticeDo");
    else
        ksys::act::enableAttClient(actor, "NoticeDo");
}

}  // namespace uking::ai
