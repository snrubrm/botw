#include "Game/Actor/AI/aiNPCGerudoQueenRoot.h"
#include "Game/Actor/aiUnk_710070435C.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
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

// 0x71004c97e0
void NPCGerudoQueenRoot::calc_() {
    NPCRoot::calc_();
    auto* schedule = mActor->getSchedule();
    if (!schedule)
        return;

    if (ksys::gdt::getBoolByKey(sUnk_710240b650[0])) {
        if (schedule->_68 == "Action1" && schedule->_88.isEmpty())
            ksys::gdt::setBoolByKey(true, sUnk_710240b650[1]);
        if (schedule->_68 == "Action4" && !schedule->_88.isEmpty()) {
            ksys::gdt::setBoolByKey(false, sUnk_710240b650[1]);
            ksys::gdt::setBoolByKey(true, sUnk_710240b650[2]);
        }
        if (!(schedule->_68 == "Action1") && !(schedule->_68 == "Action4") &&
            !(schedule->_68 == "Action5")) {
            if (ksys::gdt::getBoolByKey(sUnk_710240b650[1]))
                ksys::gdt::setBoolByKey(false, sUnk_710240b650[1]);
            if (ksys::gdt::getBoolByKey(sUnk_710240b650[2]))
                ksys::gdt::setBoolByKey(false, sUnk_710240b650[2]);
        }
    }

    if (mActor->getASList()->x(1, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
        ksys::act::setEnabledTalkAndLockOn(mActor, false);
        _248 = true;
    } else if (_248) {
        ksys::act::x_6(mActor);
    }

    const sead::SafeString anim = mActor->getASList()->x_1(0, 0);
    if (schedule->_88.isEmpty() && (anim == "Act_GdQueen_Sit" || anim == "Act_SitChair_Wait"))
        ksys::act::setEnabledTalkAndLockOn(mActor, false);
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
