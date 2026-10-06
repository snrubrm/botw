#include "Game/AI/AI/aiBossBattleRoomRoot.h"
#include <aal/aalHandle.h>
#include <aal/aalSoundSource.h>
#include <container/seadPtrArray.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

// NON_MATCHING: the original keeps the loop index as a 32-bit value (`sxtw` at the access, `cbz` on the count) instead of
// a widened 64-bit induction variable.
void BossBattleRoomRoot::sub_7100336B84(xlink2::HandleSLink* handle) {
    if (handle && handle->isActive()) {
        sead::FixedPtrArray<aal::Handle, 8> handles;
        if (handle->isActive()) {
            const s32 count = static_cast<xlink2::EventSLink*>(handle->getEvent())->getSoundHandle(&handles);
            for (s32 i = 0; i < count; ++i) {
                if (auto* source = handles[i]->getSoundSource()) {
                    if (source->mState <= 2)
                        source->mSpatialSetting.setShape(_1f0);
                }
            }
        }
    }
}

BossBattleRoomRoot::BossBattleRoomRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BossBattleRoomRoot::~BossBattleRoomRoot() {
    if (_1f0) {
        _1f0->destroy();
        _1f0 = nullptr;
    }
}

bool BossBattleRoomRoot::init_(sead::Heap* heap) {
    if (!_1f0) {
        _1f0 = aal::ShapeCylinder::create("BossBattleRoom", heap);
        if (_1f0) {
            _1f0->setPosition(mActor->getMtx().getTranslation());
            _1f0->mFlags.resetBit(aal::Shape::KeepPosition);
            _1f0->mFlags.resetBit(aal::Shape::KeepRotation);
            _1f0->setRadius(50.0f);
            _1f0->setVector(sead::Vector3f::ey * -25.0f);
        }
    }
    _208 = true;
    _1e8 = mActor->findPhysicsBodyByName("BodyParts_00", "AirFloor");
    if (_1e8)
        _1e0 = mActor->getMainBody();
    return true;
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
        _19c.previous_value = _19c.value = *mParams.mFramesDelayRoll_s;
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
    _1f8.fade();
    if (_1e8)
        _1e8->removeFromWorld();
}

void BossBattleRoomRoot::loadParams_() {
    getStaticParam(&mParams.mFramesRollKeepSecond_s, "FramesRollKeepSecond");
    getStaticParam(&mParams.mNumTimesRoll_s, "NumTimesRoll");
    getStaticParam(&mParams.mTitleAngle_s, "TitleAngle");
    getStaticParam(&mParams.mRollAngle_s, "RollAngle");
    getStaticParam(&mParams.mFramesRotate_s, "FramesRotate");
    getStaticParam(&mParams.mFramesReset_s, "FramesReset");
    getStaticParam(&mParams.mFramesRoll_s, "FramesRoll");
    getStaticParam(&mParams.mFramesDelayRoll_s, "FramesDelayRoll");
    getStaticParam(&mParams.mFramesRollKeepFirst_s, "FramesRollKeepFirst");
}

}  // namespace uking::ai
