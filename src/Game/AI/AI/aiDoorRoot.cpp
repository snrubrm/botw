#include "Game/AI/AI/aiDoorRoot.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

DoorRoot::DoorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DoorRoot::~DoorRoot() = default;

bool DoorRoot::init_(sead::Heap* heap) {
    *mIsOpenDoor_a = false;
    *mIsOpenToInside_a = false;
    return true;
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
