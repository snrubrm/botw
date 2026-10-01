#include "Game/AI/AI/aiCommonPickedItem.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

CommonPickedItem::CommonPickedItem(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CommonPickedItem::~CommonPickedItem() {
    _d0.freeBuffer();
}

bool CommonPickedItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CommonPickedItem::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!_d0.getBufferPtr()) {
        _c8 = 1;
        _e0 = 1;
    }
    _88._34 = 0x1800029;
    _88.x();
    m34();
    m37();
    m38();
}

void CommonPickedItem::leave_() {
    ksys::act::disableAllAttClients(mActor);
}

void CommonPickedItem::loadParams_() {
    getStaticParam(&mCanGetOnBurning_s, "CanGetOnBurning");
    getStaticParam(&mIsControlNoticeDo_s, "IsControlNoticeDo");
    getStaticParam(&mGetAttKeyName_s, "GetAttKeyName");
    getMapUnitParam(&mIsPlayerPut_m, "IsPlayerPut");
    getMapUnitParam(&mDropTable_m, "DropTable");
    getMapUnitParam(&mDropActor_m, "DropActor");
    getAITreeVariable(&mGetNumLeft_a, "GetNumLeft");
}

void CommonPickedItem::m35() {
    ksys::act::disableAllAttClients(mActor);
}

void CommonPickedItem::m38() {
    _88.x();
    m34();
    changeChild("通常");
}

}  // namespace uking::ai
