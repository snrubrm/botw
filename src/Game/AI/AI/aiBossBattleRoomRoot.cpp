#include "Game/AI/AI/aiBossBattleRoomRoot.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

// NON_MATCHING: regalloc (ours keeps &_80 in a callee-saved register across the memset)
BossBattleRoomRoot::BossBattleRoomRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BossBattleRoomRoot::~BossBattleRoomRoot() = default;

bool BossBattleRoomRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BossBattleRoomRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (_1e8 && _1e0) {
        if (_1e8->getMotionType() != ksys::phys::MotionType::Fixed)
            _1e8->changeMotionType(ksys::phys::MotionType::Fixed);
        if (_1e0->getMotionType() != ksys::phys::MotionType::Fixed)
            _1e0->changeMotionType(ksys::phys::MotionType::Fixed);
        _1e0->getTransform(&_80);
        _190 = _80.m[0][3];
        _194 = _80.m[1][3];
        _198 = _80.m[2][3];
        _1d0 = 0;
        _1b4.makeAllZero();
        _1e8->addToWorld();
        _1e8->setContactAll();
        _1e8->disableContactLayer(ksys::phys::ContactLayer::EntityNPC);
        _1e8->setFlag200();
        _19c.previous_value = _19c.value = *mFramesDelayRoll_s;
        _208 = true;
        _1b4.setBit(Flag(Flag::_5));
    }
}

bool BossBattleRoomRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x80000d7 && _140._30) {
        auto* payload = static_cast<Unk_71023dbd40_Payload*>(message->getUserData());
        const Command command(payload->_8);
        switch (command) {
        case Command::_1:
            _140.x();
            break;
        default:
            return false;
        }
    }
    if (!_140._30 && _140.m2(*message))
        return true;
    return false;
}

void BossBattleRoomRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BossBattleRoomRoot::loadParams_() {
    getStaticParam(&mFramesRollKeepSecond_s, "FramesRollKeepSecond");
    getStaticParam(&mNumTimesRoll_s, "NumTimesRoll");
    getStaticParam(&mTitleAngle_s, "TitleAngle");
    getStaticParam(&mRollAngle_s, "RollAngle");
    getStaticParam(&mFramesRotate_s, "FramesRotate");
    getStaticParam(&mFramesReset_s, "FramesReset");
    getStaticParam(&mFramesRoll_s, "FramesRoll");
    getStaticParam(&mFramesDelayRoll_s, "FramesDelayRoll");
    getStaticParam(&mFramesRollKeepFirst_s, "FramesRollKeepFirst");
}

}  // namespace uking::ai
