#include "Game/AI/AI/aiNPCGerudoQueenRoot.h"
#include "Game/AI/aiUnk_710070435C.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"

namespace uking::ai {

// 0x710240b650
static const sead::SafeString sUnk_710240b650[] = {
    "Gerudo_Ch_Helmet_Finish",
    "Npc_oasis003_IntoFrontThrone",
    "Npc_oasis003_IntoThrone",
};

NPCGerudoQueenRoot::NPCGerudoQueenRoot(const InitArg& arg) : NPCRoot(arg) {}

NPCGerudoQueenRoot::~NPCGerudoQueenRoot() {
    if (_240) {
        mActor->sub_71011DA868(&_240[0]);
        mActor->sub_71011DA868(&_240[1]);
        mActor->sub_71011DA868(&_240[2]);
        delete[] _240;
    }
}

bool NPCGerudoQueenRoot::init_(sead::Heap* heap) {
    if (!NPCRoot::init_(heap))
        return false;
    _240 = new (heap, 8) ksys::act::BoneHandle[3];
    sub_710070435C(_240);
    mActor->boneHandleStuff(&_240[0], false);
    mActor->boneHandleStuff(&_240[1], false);
    mActor->boneHandleStuff(&_240[2], false);
    sub_710070439C(mActor->getModel(), _240, *mIsOnHelmet_m);
    return true;
}

void NPCGerudoQueenRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCRoot::enter_(params);
}

void NPCGerudoQueenRoot::leave_() {
    ksys::gdt::setBoolByKey(false, sUnk_710240b650[1]);
    ksys::gdt::setBoolByKey(false, sUnk_710240b650[2]);
    _248 = false;
    NPCRoot::leave_();
}

void NPCGerudoQueenRoot::loadParams_() {
    NPCRoot::loadParams_();
    getMapUnitParam(&mIsOnHelmet_m, "IsOnHelmet");
}

}  // namespace uking::ai
