#include "Game/AI/AI/aiNPCTravel.h"
#include "Game/Actor/actNPC.h"
#include "Game/AI/aiUnk_71007130BC.h"
#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::ai {

NPCTravel::NPCTravel(const InitArg& arg) : NPCTravelBase(arg) {}

NPCTravel::~NPCTravel() = default;

void NPCTravel::onPreDelete() {
    if (_88 && _88->_840 == &_1f8)
        _88->_840 = nullptr;
    if (_f8.isRegistered()) {
        mActor->sendMessage(_f8, ksys::MessageType(0x8000076), nullptr, true);
        if (_88)
            _88->_fe8 &= ~0x40000;
    }
}

bool NPCTravel::init_(sead::Heap* heap) {
    return NPCTravelBase::init_(heap);
}

void NPCTravel::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCTravelBase::enter_(params);
}

void NPCTravel::leave_() {}

// NON_MATCHING: same control flow; the original computes the row addresses of the copied matrix
// (_c8 + 0x10 / + 0x20) before the message source call and reuses them for the three translation
// loads (two more callee-saved registers, frame 0x60 instead of 0x50)
bool NPCTravel::handleMessage_(const ksys::Message* message) {
    if (message) {
        if (message->getType() == 0x8000075 &&
            (isCurrentChild("急いで指定位置に移動") ||
             (isCurrentChild("指定位置に移動") && wm::callIsRainingOrSnowingOrThunderStorm(true) &&
              !wm::callIsRainingOrSnowingOrThunderStorm(false)))) {
            auto* mtx = static_cast<sead::Matrix34f*>(message->getUserData());
            if (!mtx)
                return false;
            _c8 = *mtx;
            _c6 = true;
            if (_88)
                _88->_fe8 |= 0x40000;
            _f8 = message->getSource();

            ksys::act::ai::InlineParamPack params;
            sead::Vector3f pos;
            if (_c6) {
                pos.set(_c8.m[0][3], _c8.m[1][3], _c8.m[2][3]);
            } else if (auto* rail = static_cast<Unk_71024f15c0*>(_88->_840);
                       rail && rail->sub_7100EEBB74()) {
                pos = static_cast<Unk_71024f15c0*>(_88->_840)->_30.sub_7100EEB370();
            } else {
                auto& actor_mtx = mActor->getMtx();
                pos.set(actor_mtx.m[0][3], actor_mtx.m[1][3], actor_mtx.m[2][3]);
            }
            params.addVec3(pos, "TargetPos", -1);
            params.addString(wm::callIsRainingOrSnowingOrThunderStorm(false) ? "Run_Rain" : "Walk",
                             "DynASKeyName", -1);
            changeChild("雨宿り地点に移動", &params);
            return true;
        }
        if (message->getType() == 0x3800028)
            sub_71004E3B10(0.0f, true);
    }
    return false;
}

void NPCTravel::sub_71004E3B10(f32 value, bool onProcessingThread) {
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&_88->_f70, &accessor)) {
        _110.mLock.lock();
        _110.mLink.acquire(mActor, false);
        _110._50 = value;
        if (onProcessingThread) {
            mActor->sendMessageOnProcessingThread(*accessor.getMessageTransceiverId(),
                                                  ksys::MessageType(0x3800008), &_110, true);
        } else {
            sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3800008), &_110);
        }
        _110.mLock.unlock();
    }
}

// NON_MATCHING: XZ target/actor position loads use different registers and scheduling.
bool NPCTravel::sub_71004E5824() {
    if (auto* nav = mActor->m45()) {
        nav->_1e0.lock();
        const u8 state = nav->_294;
        nav->_1e0.unlock();
        if (state == 2)
            return true;
    }
    auto* rail = static_cast<Unk_71024f15c0*>(_88->_840);
    if (!rail || !rail->sub_7100EEBB74())
        return false;
    const auto& target = static_cast<Unk_71024f15c0*>(_88->_840)->_30.sub_7100EEB370();
    const auto& mtx = mActor->getMtx();
    return sead::Vector2f(target.x - mtx.m[0][3], target.z - mtx.m[2][3]).length() < 5.0f;
}

// NON_MATCHING: flag temporary stack placement and speed/threshold scheduling differ.
bool NPCTravel::sub_71004E58FC() {
    auto* rail = static_cast<Unk_71024f15c0*>(_88->_840);
    if (!rail || !rail->sub_7100EEBB74())
        return false;
    const auto& motion = mActor->getASList()->sub_710115D2D4();
    sead::Vector2f distance(motion.x, motion.z);
    if (mActor->sub_71011C7A98())
        distance *= mActor->get830();
    const f32 speed = distance.length();
    u32 flags = 0;
    static_cast<Unk_71024f15c0*>(_88->_840)->m4(
        speed < sead::Mathf::epsilon() ? 0.75f : speed * 15.0f, nullptr, &flags);
    return (flags & 0x30) != 0;
}

void NPCTravel::sub_71004E59D4() {
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&_88->_f70, &accessor)) {
        const sead::Vector3f other_pos = accessor.getActorMtx().getTranslation();
        const sead::Vector3f diff = mActor->getMtx().getTranslation() - other_pos;
        if (diff.length() < 2.0f) {
            mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3800007),
                                nullptr, true);
        }
    }
}

void NPCTravel::loadParams_() {
    NPCTravelBase::loadParams_();
    getStaticParam(&mWaitHorseReturnDist_s, "WaitHorseReturnDist");
    getStaticParam(&mGiveUpWaitHorseTime_s, "GiveUpWaitHorseTime");
}

}  // namespace uking::ai
