#include "Game/AI/AI/aiDoorRoot.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiAwarenessFilters.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

DoorRoot::DoorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DoorRoot::~DoorRoot() = default;

bool DoorRoot::init_(sead::Heap* heap) {
    *mIsOpenDoor_a = false;
    *mIsOpenToInside_a = false;
    return true;
}

// Returns true when nothing is inside the awareness range of the door (the door may close).
bool DoorRoot::sub_7100366D0C() {
    if (isCurrentChild("Open"))
        return false;
    if (!*mIsOpenDoor_a)
        return false;
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return false;

    Unk_71024515b0 filter;
    auto* actor = mActor;
    const f32 radius = awareness->_2f4;
    const sead::Vector3f pos = actor->getMtx().getTranslation();
    const sead::Matrix34f mtx = actor->getMtx();
    sead::Matrix34f inv;
    sead::Matrix34CalcCommon<f32>::inverse(inv, mtx);
    while (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&entry->_0.mLink, &accessor);
        const sead::Vector3f entry_pos = accessor.getActorMtx().getTranslation();
        const sead::Vector3f diff = pos - entry_pos;
        if (radius >= std::sqrt(diff.x * diff.x + diff.z * diff.z)) {
            if (*mIsCheckBack_s &&
                diff.x * inv(0, 0) + diff.y * inv(0, 1) + diff.z * inv(0, 2) < 0.0f)
                continue;
            return false;
        }
    }
    return true;
}

void DoorRoot::sub_7100366B9C(const ksys::act::BaseProcLink& link, const sead::SafeString& as_name) {
    _a8.x();
    auto* actor = mActor;
    actor->getPhysics()->sub_7100FC01B0();
    ksys::act::disableAttClient(actor, "Open");
    *mIsOpenDoor_a = true;
    ksys::act::ai::InlineParamPack pack;
    pack.addActor(link, "DynOwner", -1);
    pack.addString(as_name, "DynASKey", -1);
    changeChild("Open", &pack);
}

void DoorRoot::sub_7100366ED0(const ksys::act::BaseProcLink& link, const sead::SafeString& as_name) {
    mActor->getPhysics()->sub_7100FC01B0();
    *mIsOpenDoor_a = false;
    ksys::act::ai::InlineParamPack pack;
    pack.addActor(link, "DynOwner", -1);
    pack.addString(as_name, "DynASKey", -1);
    changeChild("Close", &pack);
}

void DoorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* awareness = mActor->getAwareness())
        awareness->enable();
    auto* actor = mActor;
    if (*mIsOpenDoor_a) {
        _e8 = ksys::Timer(*mCloseWaitFrame_s, *mCloseWaitFrame_s);
        actor->getPhysics()->sub_7100FC012C(nullptr);
    } else {
        actor->getPhysics()->sub_7100FC01B0();
        ksys::act::enableAttClient(actor, "Open");
    }
    changeChild("Wait");
}

// NON_MATCHING: The dot-product loads and empty string initialization are scheduled differently.
void DoorRoot::calc_() {
    auto* actor = mActor;
    auto* child = getCurrentChild();
    mActor->setFlag(ksys::act::Actor::ActorFlag::_2d, true);
    if (_a8._30) {
        ksys::act::ActorConstDataAccess accessor;
        if (!_a8._8.hasProc())
            return;
        ksys::act::acquireActor(&_a8._8, &accessor);
        const f32 side = (accessor.getActorMtx().getTranslation() -
                          actor->getMtx().getTranslation()).dot(actor->getMtx().getBase(2));
        const bool player = ksys::act::isPlayerProfile(&_a8._8);
        sead::SafeString as_name;
        if (side >= 0.0f) {
            as_name = mOpen_L_AS_s;
            *mIsOpenToInside_a = true;
        } else {
            as_name = mOpen_R_AS_s;
            *mIsOpenToInside_a = false;
        }
        if (!ksys::act::isPlayerProfile(&_a8._8))
            ksys::act::isNPCProfile(&_a8._8);
        if (ksys::act::isNPCProfile(&_a8._8) && !mNpcCanOpenFlag_m.isEmpty() &&
            !ksys::gdt::getBoolByKey(mNpcCanOpenFlag_m, false)) {
            _a8.x();
            return;
        }
        sub_7100366B9C(player ? ksys::act::PlayerInfo::getSomeProcLink() :
                             ksys::act::getDummyBaseProcLink(), as_name);
        return;
    }
    if (child->isChangeable()) {
        if (sub_7100366D0C()) {
            _e8.update();
            if (_e8.value <= sead::Mathf::epsilon()) {
                sead::SafeString as_name;
                if (*mIsOpenToInside_a)
                    as_name = mClose_R_AS_s;
                else
                    as_name = mClose_L_AS_s;
                sub_7100366ED0(ksys::act::getDummyBaseProcLink(), as_name);
            }
        } else {
            mActor->setFlag(ksys::act::Actor::ActorFlag::_2d, false);
            _e8.reset(*mCloseWaitFrame_s);
        }
    } else if (child->isFinished() || child->isFailed()) {
        auto* current_actor = mActor;
        if (*mIsOpenDoor_a) {
            _e8.reset(*mCloseWaitFrame_s);
            current_actor->getPhysics()->sub_7100FC012C(nullptr);
        } else {
            current_actor->getPhysics()->sub_7100FC01B0();
            ksys::act::enableAttClient(current_actor, "Open");
        }
        changeChild("Wait");
    }
}

void DoorRoot::leave_() {
    if (auto* awareness = mActor->getAwareness())
        awareness->disable();
}

void DoorRoot::loadParams_() {
    getStaticParam(&mCloseWaitFrame_s, "CloseWaitFrame");
    getStaticParam(&mIsCheckBack_s, "IsCheckBack");
    getStaticParam(&mOpen_L_AS_s, "Open_L_AS");
    getStaticParam(&mOpen_R_AS_s, "Open_R_AS");
    getStaticParam(&mClose_L_AS_s, "Close_L_AS");
    getStaticParam(&mClose_R_AS_s, "Close_R_AS");
    getMapUnitParam(&mNpcCanOpenFlag_m, "NpcCanOpenFlag");
    getAITreeVariable(&mIsOpenDoor_a, "IsOpenDoor");
    getAITreeVariable(&mIsOpenToInside_a, "IsOpenToInside");
}

bool DoorRoot::handleMessage_(const ksys::Message* message) {
    if (_a8._30)
        return false;
    if (isCurrentChild("Wait") && !*mIsOpenDoor_a)
        return _a8.m2(*message);
    return false;
}

}  // namespace uking::ai
