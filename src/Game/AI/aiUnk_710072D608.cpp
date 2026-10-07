#include "Game/AI/aiUnk_710072D608.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGiantArmorSlot.h"

// 0x710072d608
// NON_MATCHING: each arm emits the param-address add and the value add separately; the original folds
// them into a single add (jump table, checked GParam lookup, dereference and default all match).
const sead::SafeString* sub_710072D608(ksys::act::Actor* actor, int index) {
    switch (index) {
    case 0:
        return &actor->getParam()->getRes().mGParamList->getGiantArmorSlot()->mSlot0Node.ref();
    case 1:
        return &actor->getParam()->getRes().mGParamList->getGiantArmorSlot()->mSlot1Node.ref();
    case 2:
        return &actor->getParam()->getRes().mGParamList->getGiantArmorSlot()->mSlot2Node.ref();
    case 3:
        return &actor->getParam()->getRes().mGParamList->getGiantArmorSlot()->mSlot3Node.ref();
    default:
        return &sead::SafeString::cEmptyString;
    }
}
