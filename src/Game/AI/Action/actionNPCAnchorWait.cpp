#include "Game/AI/Action/actionNPCAnchorWait.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::action {

NPCAnchorWait::NPCAnchorWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCAnchorWait::~NPCAnchorWait() = default;

bool NPCAnchorWait::init_(sead::Heap* heap) {
    _40 = sead::DynamicCast<uking::act::NPC>(mActor);
    return true;
}

void NPCAnchorWait::enter_(ksys::act::ai::InlineParamPack* params) {
    if (_40 && *mIsRainAnchor_d)
        _40->_8b9 = true;
    _48 = false;
    bool start_same_as = *mIsStartSameAS_d;
    if (auto* schedule = mActor->getSchedule()) {
        const sead::SafeString current_as(mActor->getASList()->sub_710115ECF4(0x37, 1));
        if (!current_as.isEmpty() &&
            current_as != sead::SafeString((*mIsRainAnchor_d ? schedule->_258 : schedule->_248)
                                               .getStringTop()))
            start_same_as = true;
    }
    playAS(m32(), !start_same_as, 0, 0, -1.0f);
    if (auto* navmesh = mActor->m45())
        navmesh->sub_7100F76778();
}

void NPCAnchorWait::leave_() {
    _48 = false;
    if (auto* navmesh = mActor->m45())
        navmesh->sub_7100F76790();
}

void NPCAnchorWait::loadParams_() {
    getDynamicParam(&mIsRainAnchor_d, "IsRainAnchor");
    getDynamicParam(&mIsStartSameAS_d, "IsStartSameAS");
    getDynamicParam(&mASName_d, "ASName");
}

void NPCAnchorWait::sub_71001F3AE8() {
    if (!_40 || !(_40->_fe8 & 0x20000) || _48)
        return;
    ksys::act::ActorConstDataAccess accessor;
    if (!ksys::act::acquireActor(&_40->_f70, &accessor))
        return;
    auto* horse = static_cast<uking::act::RideableBase*>(accessor.getHorseOptions());
    if (!horse || !(horse->_8.load() & 0x200000))
        return;
    auto* actor = mActor;
    _48 = true;
    _50.mPos = actor->getMtx().getBase(2);
    actor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3800005), &_50,
                       true);
}

// NON_MATCHING: the original copies velocity.x / velocity.z through registers (z first) before storing
// _10a8 into velocity.y; here the redundant copies are dropped. The "Sleep" comparison is also a different
// inline loop (no length bound, no pointer fast path).
void NPCAnchorWait::calc_() {
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
    if (uking::act::NPC::isZora(mActor)) {
        if (auto* controller = mActor->getCharacterController()) {
            if (_40 && (_40->_fe8 & 0x8000000)) {
                sead::Vector3f velocity;
                controller->sub_7100F5F598(&velocity);
                velocity.set(velocity.x, _40->_10a8, velocity.z);
                controller->sub_7100F5F6FC(velocity);
            }
            if (auto* schedule = mActor->getSchedule()) {
                if (sead::SafeString(schedule->_88.getStringTop()) == "Sleep" && controller->mFlags.isOnBit(16)) {
                    const ksys::act::MotionType type = controller->sub_7100F5F0E4();
                    if (type != ksys::act::MotionType::Hover) {
                        sead::Vector3f gravity = getGravity(mActor);
                        gravity *= 0.29891199f;
                        controller->sub_7100F5F6FC(gravity);
                    }
                }
            }
        }
    }
    sub_71001F3AE8();
}

bool NPCAnchorWait::handleMessage_(const ksys::Message* message) {
    return false;
}


}  // namespace uking::action
