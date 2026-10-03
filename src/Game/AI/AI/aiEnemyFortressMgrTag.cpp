#include "Game/AI/AI/aiEnemyFortressMgrTag.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/Thread/MessageAck.h"

namespace uking::ai {

EnemyFortressMgrTag::EnemyFortressMgrTag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyFortressMgrTag::~EnemyFortressMgrTag() = default;

bool EnemyFortressMgrTag::init_(sead::Heap* heap) {
    *mRegistedActorUnit_a = &_50;
    _50._8.mOwner = mActor;
    _50._8.mSender._8 = &mActor->getMessageTransceiver();
    return true;
}

void EnemyFortressMgrTag::enter_(ksys::act::ai::InlineParamPack* params) {
    _50._8.sub_71006F0354(false);
    const f32 change_per = *mChangePer_s;
    const s32 interval = *mCheckInterval_s;
    _43c = interval;
    _448 = -1;
    _444 = false;
    _440 = s32(change_per);
    _438 = f32(interval);
    changeChild("待機");
}

// NON_MATCHING: only the load of _438 after Timer::update uses [this + 0x438] instead of the
// original's callee-saved copy of &_438 (x20).
void EnemyFortressMgrTag::calc_() {
    mActor->m107();
    _50._8.sub_71006F03D0();

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        _438 = f32(_43c);
        _444 = false;
        changeChild("待機");
        return;
    }

    if (child->isChangeable() && isCurrentChild("待機") && _444) {
        changeChild("会話");
        return;
    }

    if (isCurrentChild("待機") && !_444 && _440 >= 1) {
        ksys::Timer::update(&_438, -1.0f);
        if (_438 <= 0) {
            _444 = sead::GlobalRandom::instance()->getF32() * 100.0f < f32(_440);
            if (!_444)
                _438 = f32(_440);
        }
    }
}

void EnemyFortressMgrTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyFortressMgrTag::loadParams_() {
    getStaticParam(&mCheckInterval_s, "CheckInterval");
    getStaticParam(&mChangePer_s, "ChangePer");
    getAITreeVariable(&mRegistedActorUnit_a, "RegistedActorUnit");
}

bool EnemyFortressMgrTag::handleMessage_(const ksys::Message* message) {
    const auto type = message->getType();
    if (type == 0x8000006 || type == 0x8000017 || type == 0x80000c0)
        _50._8.sub_71006F0734(message->getType(), message->getUserData());
    return _50._8.sub_71006F0448(*message);
}

bool EnemyFortressMgrTag::handleAck_(const ksys::MessageAck* ack) {
    return _50._8.sub_71006F0604(*ack);
}

}  // namespace uking::ai
