#include "Game/AI/aiUnk_7100EDD26C.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGrab.h"

// 0x7100edd26c
// NON_MATCHING: each arm emits the param-address add and the value add separately; the original folds
// them into a single add (same shape as sub_710072D608 and sub_710072D53C).
const sead::SafeString* sub_7100EDD26C(ksys::act::Actor* actor, int index) {
    const auto* list = actor->getParam()->getRes().mGParamList;
    if (!list)
        return &sead::SafeString::cEmptyString;
    const auto* grab = static_cast<const ksys::res::GParamListObjectGrab*>(
        list->getObject(ksys::res::GParamListObjType::Grab));
    if (!grab)
        return &sead::SafeString::cEmptyString;
    switch (index) {
    case 0:
        return &grab->mSlot0PodNode.ref();
    case 1:
        return &grab->mSlot1PodNode.ref();
    case 2:
        return &grab->mSlot2PodNode.ref();
    case 3:
        return &grab->mSlot3PodNode.ref();
    case 4:
        return &grab->mSlot4PodNode.ref();
    case 5:
        return &grab->mSlot5PodNode.ref();
    default:
        return &sead::SafeString::cEmptyString;
    }
}
