#include "Game/Actor/AI/aiBossBattleRoomRoot.h"
#include <aal/aalHandle.h>
#include <aal/aalSoundSource.h>
#include <container/seadPtrArray.h>
#include <math/seadQuat.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

// NON_MATCHING: Vector2 assignment and flag/handle stack allocation differ.
void BossBattleRoomRoot::sub_710033519C(const sead::Vector2f& direction) {
    if (_1e8->getMotionType() != ksys::phys::MotionType::Keyframed)
        _1e8->changeMotionType(ksys::phys::MotionType::Keyframed);
    if (_1e0->getMotionType() != ksys::phys::MotionType::Keyframed)
        _1e0->changeMotionType(ksys::phys::MotionType::Keyframed);
    _1e0->getTransform(&_80);
    _1b4.setBit(Flag(Flag::_0));
    _1b4.setBit(Flag(Flag::_4));
    _1b4.resetBit(Flag(Flag::_5));
    ksys::gdt::setFlag_FinalTrial_BossField_Rotate(true, false);
    _188 = direction;
    sub_710033529C();
    _1d0 = 0.0f;
    _208 = true;
    auto handle = ksys::eft::searchAndEmitSLink(mActor, "Start", false);
    sub_7100336B84(&handle);
}

// NON_MATCHING: SEAD_ENUM temporary stack slots differ.
void BossBattleRoomRoot::sub_71003355E8() {
    if (_1e8->getMotionType() != ksys::phys::MotionType::Keyframed)
        _1e8->changeMotionType(ksys::phys::MotionType::Keyframed);
    if (_1e0->getMotionType() != ksys::phys::MotionType::Keyframed)
        _1e0->changeMotionType(ksys::phys::MotionType::Keyframed);
    if (_1d4 == 0) {
        _1e0->getTransform(&_e0);
        _1d8 = (sead::GlobalRandom::instance()->getU32() & 2) - 1;
    }
    _1e0->getTransform(&_80);
    sub_7100335710();
    _1b4.setBit(Flag(Flag::_2));
    _1b4.setBit(Flag(Flag::_4));
    _1b4.resetBit(Flag(Flag::_3));
    _1b4.resetBit(Flag(Flag::_5));
    _1d0 = 0.0f;
    _208 = true;
    auto handle = ksys::eft::searchAndEmitSLink(mActor, "Start", false);
    sub_7100336B84(&handle);
}

// NON_MATCHING: vector load scheduling, float registers and final matrix stores differ.
void BossBattleRoomRoot::sub_710033529C() {
    sead::Vector3f direction(_188.x - mActor->getMtx().m[0][3], 0.0f,
                            _188.y - mActor->getMtx().m[2][3]);
    direction.normalize();
    sead::Vector3f axis = sead::Vector3f::ey.cross(direction);
    axis.normalize();
    sead::Quatf rotation;
    rotation.setAxisRadian(axis, *mParams.mTitleAngle_s);
    sead::Matrix33f matrix;
    matrix.fromQuat(rotation);
    sead::Vector3f up = sead::Vector3f::ey;
    up.mul(matrix);
    up.normalize();
    sead::Vector3f right = up.cross(sead::Vector3f::ez);
    right.normalize();
    sead::Vector3f forward = right.cross(up);
    forward.normalize();
    _b0.setBase(0, right);
    _b0.setBase(1, up);
    _b0.setBase(2, forward);
    _b0.setTranslation({_190, _194, _198});
}

// NON_MATCHING: basis loads, float registers and final matrix stores differ.
void BossBattleRoomRoot::sub_7100335710() {
    sead::Vector3f up = _e0.getBase(1);
    const sead::Vector3f forward = _e0.getBase(2);
    sead::Vector3f axis(_188.x - mActor->getMtx().m[0][3], 0.0f,
                       _188.y - mActor->getMtx().m[2][3]);
    axis.normalize();
    const f32 angle = *mParams.mRollAngle_s * static_cast<f32>(_1d8);
    sead::Quatf rotation;
    rotation.setAxisRadian(axis, (_1d4 & 1) ? angle : -angle);
    sead::Matrix33f matrix;
    matrix.fromQuat(rotation);
    up.mul(matrix);
    up.normalize();
    sead::Vector3f right = up.cross(forward);
    right.normalize();
    sead::Vector3f front = right.cross(up);
    front.normalize();
    _b0.setBase(0, right);
    _b0.setBase(1, up);
    _b0.setBase(2, front);
    _b0.setTranslation({_190, _194, _198});
}

// NON_MATCHING: enum temporary stack slots and identity/translation store scheduling differ.
void BossBattleRoomRoot::sub_7100335A08(bool enable_contact) {
    if (_1e8->getMotionType() != ksys::phys::MotionType::Keyframed)
        _1e8->changeMotionType(ksys::phys::MotionType::Keyframed);
    if (_1e0->getMotionType() != ksys::phys::MotionType::Keyframed)
        _1e0->changeMotionType(ksys::phys::MotionType::Keyframed);
    _1e0->getTransform(&_80);
    _1b4.setBit(Flag(Flag::_1));
    _1b4.setBit(Flag(Flag::_4));
    _1b4.resetBit(Flag(Flag::_3));
    _1b4.resetBit(Flag(Flag::_2));
    _1b4.resetBit(Flag(Flag::_0));
    _1d4 = 0;
    _19c.previous_value = _19c.value = *mParams.mFramesDelayRoll_s;
    _b0.makeIdentity();
    _b0.setTranslation({_190, _194, _198});
    _1d0 = 0.0f;
    if (enable_contact) {
        _208 = false;
        _1e0->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    } else {
        _208 = true;
    }
    if (_208) {
        auto handle = ksys::eft::searchAndEmitSLink(mActor, "Start", false);
        sub_7100336B84(&handle);
    }
}

// NON_MATCHING: enum stack slots and the existing bool payload's flag test differ.
void BossBattleRoomRoot::sub_7100335EB0() {
    switch (Command(_140._34._8)) {
    case Command::_0:
        if (!_1b4.isOnBit(Flag(Flag::_0))) {
            _1b8 = _140._18;
            sub_710033519C(_140._34._0);
        }
        break;
    case Command::_1:
        if (!_1b4.isOnBit(Flag(Flag::_1)) && !_1b4.isOnBit(Flag(Flag::_5))) {
            _1b8 = _140._18;
            sub_7100335A08(_140._34._c);
        } else if (_1b4.isOnBit(Flag(Flag::_5))) {
            {
                sead::ScopedLock<sead::JobQueueLock> lock(&_110._18.mLock);
                _110._18._c = false;
                _110._18._8 = 5;
            }
            _110.sub_710070DBB0(_140._18, true);
        }
        break;
    case Command::_2:
        if (!_1b4.isOnBit(Flag(Flag::_2))) {
            _1b8 = _140._18;
            _19c.update();
            if (!(_19c.value <= sead::Mathf::epsilon()))
                return;
            sub_71003355E8();
        }
        break;
    }
    _140.x();
}

void BossBattleRoomRoot::sub_7100335B74() {
    if (_1e8->getMotionType() != ksys::phys::MotionType::Fixed)
        _1e8->changeMotionType(ksys::phys::MotionType::Fixed);
    if (_1e0->getMotionType() != ksys::phys::MotionType::Fixed)
        _1e0->changeMotionType(ksys::phys::MotionType::Fixed);
    _1b4.resetBit(Flag(Flag::_0));
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_110._18.mLock);
        _110._18._c = false;
        _110._18._8 = 3;
    }
    _110.sub_710070DBB0(_1b8, true);
}

// NON_MATCHING: SEAD_ENUM temporary stack slots and counter reset scheduling differ.
void BossBattleRoomRoot::sub_7100335C38() {
    if (_1e8->getMotionType() != ksys::phys::MotionType::Fixed)
        _1e8->changeMotionType(ksys::phys::MotionType::Fixed);
    if (_1e0->getMotionType() != ksys::phys::MotionType::Fixed)
        _1e0->changeMotionType(ksys::phys::MotionType::Fixed);
    _1b4.resetBit(Flag(Flag::_2));
    const s32 count = _1d4++;
    if (count >= *mParams.mNumTimesRoll_s) {
        _1d4 = 0;
        _1b4.resetBit(Flag(Flag::_3));
        _19c.previous_value = _19c.value = *mParams.mFramesDelayRoll_s;
        {
            sead::ScopedLock<sead::JobQueueLock> lock(&_110._18.mLock);
            _110._18._c = false;
            _110._18._8 = 6;
        }
        _110.sub_710070DBB0(_1b8, true);
    } else {
        const s32 frames =
            count == 0 ? *mParams.mFramesRollKeepFirst_s : *mParams.mFramesRollKeepSecond_s;
        _1a8.previous_value = _1a8.value = frames;
        _1b4.setBit(Flag(Flag::_3));
    }
}

// NON_MATCHING: SEAD_ENUM temporary stack slots differ.
void BossBattleRoomRoot::sub_7100335DA8() {
    if (_1e8->getMotionType() != ksys::phys::MotionType::Fixed)
        _1e8->changeMotionType(ksys::phys::MotionType::Fixed);
    if (_1e0->getMotionType() != ksys::phys::MotionType::Fixed)
        _1e0->changeMotionType(ksys::phys::MotionType::Fixed);
    _1b4.setBit(Flag(Flag::_5));
    _1b4.resetBit(Flag(Flag::_1));
    _1b4.resetBit(Flag(Flag::_4));
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_110._18.mLock);
        _110._18._c = false;
        _110._18._8 = 5;
    }
    _110.sub_710070DBB0(_1b8, true);
    ksys::gdt::setFlag_FinalTrial_BossField_Rotate(false, false);
    _1d4 = 0;
    _1e0->setContactNone();
}

void BossBattleRoomRoot::sub_7100336B84(xlink2::HandleSLink* handle) {
    if (handle && handle->isActive()) {
        sead::FixedPtrArray<aal::Handle, 8> handles;
        if (handle->isActive()) {
            const u32 count = static_cast<xlink2::EventSLink*>(handle->getEvent())->getSoundHandle(&handles);
            for (u32 i = 0; i < count; ++i) {
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

// NON_MATCHING: SEAD_ENUM temporary stack slot, quaternion slerp / matrix float scheduling.
void BossBattleRoomRoot::calc_() {
    if (!_1e0)
        return;

    if (_140._30)
        sub_7100335EB0();

    if (_1b4.isOnBit(Flag(Flag::_3))) {
        _1a8.update();
        if (_1a8.value <= sead::Mathf::epsilon()) {
            if (_1d4 < *mParams.mNumTimesRoll_s)
                sub_71003355E8();
            else
                sub_7100335C38();
        }
    }

    if (!_1b4.isOnBit(Flag(Flag::_0)) && !_1b4.isOnBit(Flag(Flag::_1)) &&
        !_1b4.isOnBit(Flag(Flag::_2))) {
        _1e0->setAngularVelocity(sead::Vector3f::zero);
        _1e8->setAngularVelocity(sead::Vector3f::zero);
        _1f8.fade();
        return;
    }

    sead::Quatf from;
    sead::Quatf to;
    _80.toQuat(from);
    _b0.toQuat(to);

    f32 t;
    const bool rotate = _1b4.isOnBit(Flag(Flag::_0));
    if (1.0f - _1d0 <= sead::Mathf::epsilon()) {
        if (rotate)
            sub_7100335B74();
        else if (_1b4.isOnBit(Flag(Flag::_2)))
            sub_7100335C38();
        else if (_1b4.isOnBit(Flag(Flag::_1)))
            sub_7100335DA8();
        _1d0 = 1.0f;
        t = 1.0f;
        if (_208) {
            auto handle = ksys::eft::searchAndEmitSLink(mActor, "Stop", false);
            sub_7100336B84(&handle);
        }
    } else {
        f32 frames;
        if (rotate)
            frames = *mParams.mFramesRotate_s;
        else if (_1b4.isOnBit(Flag(Flag::_2)))
            frames = *mParams.mFramesRoll_s;
        else
            frames = *mParams.mFramesReset_s;
        _1d0 += (1.0f / frames) * ksys::VFR::instance()->getDeltaFrame();
        t = _1d0 * _1d0 * (_1d0 * -2.0f + 3.0f);
    }

    from.slerpTo(from, to, t);
    sead::Matrix34f mtx;
    mtx.makeQT(from, {_190, _194, _198});
    _1e0->changeRotation(mtx);
    _1e8->changeRotation(mtx);

    if (_208) {
        if (!_1f8.isActive())
            _1f8 = ksys::eft::searchAndEmitSLink(mActor, "Move", false);
        sub_7100336B84(&_1f8);
    }

    if (_1f0) {
        sead::Matrix34f shape_mtx = mtx;
        shape_mtx.setTranslation(mActor->getMtx().getTranslation());
        _1f0->setActorMatrix(shape_mtx);
    }
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
