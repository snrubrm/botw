#include "Game/AI/AI/aiCommonPickedItem.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"
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

void CommonPickedItem::m34() {
    auto* actor = mActor;
    if (actor->getFadeOutDeleteType() != 0)
        return;
    ksys::act::enableAttClient(actor, "NameBalloon");
    ksys::act::enableAttClient(actor, "AutoAim");
    if (ksys::act::itemIsForSale(actor)) {
        ksys::act::enableAttClient(actor, "Buy");
        ksys::act::disableAttClient(actor, m36());
    } else {
        ksys::act::enableAttClient(actor, m36());
        ksys::act::disableAttClient(actor, "Buy");
    }
}

void CommonPickedItem::m37() {
    auto* actor = mActor;
    if (*mCanGetOnBurning_s) {
        ksys::act::enableAttClient(actor, "NoticeDo");
        return;
    }

    auto* chemical = actor->sub_71011D8A44(0);
    if (!chemical)
        return;

    if (chemical->_c0 == 2) {
        m35();
        ksys::act::disableAttClient(actor, "NoticeDo");
    } else {
        m34();
        if (*mIsControlNoticeDo_s)
            ksys::act::enableAttClient(actor, "NoticeDo");
    }
}

}  // namespace uking::ai
