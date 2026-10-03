#include "Game/AI/AI/aiSwitchWheel.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "Game/AI/aiXlinkHandle.h"

namespace uking::ai {

SwitchWheel::SwitchWheel(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwitchWheel::~SwitchWheel() {
    if (_90) {
        delete _90;
        _90 = nullptr;
    }
}

bool SwitchWheel::init_(sead::Heap* heap) {
    _90 = new (heap, 8) xlink2::HandleSLink;
    return true;
}

// NON_MATCHING: the original copies the 3x3 part with three vector loads of the actor's matrix rows (q0/q1/q2 + lane
// shuffles); the element-wise copy of sead's Matrix33(const Mtx34&) is not vectorized here
void SwitchWheel::enter_(ksys::act::ai::InlineParamPack* params) {
    _68 = sead::Matrix33f(mActor->getHomeMtxRaw());
    sead::Matrix33CalcCommon<f32>::inverse(_68, _68);
    changeChild("待機");
}

void SwitchWheel::calc_() {
    auto* actor = mActor;
    sead::Vector3f angular_velocity = sead::Vector3f::zero;
    if (auto* body = actor->getMainBody())
        body->getAngularVelocity(&angular_velocity);
    angular_velocity.mul(_68);

    f32 value;
    switch (*mRotAxis_m) {
    case 0:
        value = angular_velocity.x;
        break;
    case 1:
        value = angular_velocity.y;
        break;
    case 2:
        value = angular_velocity.z;
        break;
    default:
        value = 0.0f;
        break;
    }

    if (!*mIsAbleToReverse_s) {
        if (value >= *mRotateStartRad_s) {
            if (!isCurrentChild("回転")) {
                changeChild("回転");
                return;
            }
        } else if (value <= *mRotateEndRad_s) {
            if (!isCurrentChild("待機")) {
                changeChild("待機");
                return;
            }
        }
    } else if (!isCurrentChild("待機")) {
        if ((isCurrentChild("回転") && value <= *mRotateEndRad_s) ||
            (isCurrentChild("逆回転") && value >= *mReverseEndRad_s)) {
            changeChild("待機");
            return;
        }
    } else if (value >= *mRotateStartRad_s) {
        changeChild("回転");
        return;
    } else if (value <= *mReverseStartRad_s) {
        changeChild("逆回転");
        return;
    }

    if (_90) {
        const f32 magnitude = value > 0.0f ? value : -value;
        if (magnitude > 0.0f) {
            auto* event = _90->getEvent();
            if (!event || event->getCreateId() != u32(_90->getCreateId()))
                ksys::eft::sub_710105DDB8(actor, "Roll", _90);
        } else {
            xlink::fade(*_90, -1);
        }
    }
}

void SwitchWheel::leave_() {
    if (_90)
        xlink::fade(*_90, -1);
}

void SwitchWheel::loadParams_() {
    getStaticParam(&mRotateStartRad_s, "RotateStartRad");
    getStaticParam(&mRotateEndRad_s, "RotateEndRad");
    getStaticParam(&mReverseEndRad_s, "ReverseEndRad");
    getStaticParam(&mReverseStartRad_s, "ReverseStartRad");
    getStaticParam(&mIsAbleToReverse_s, "IsAbleToReverse");
    getMapUnitParam(&mRotAxis_m, "RotAxis");
}

bool SwitchWheel::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000003 && !isCurrentChild("待機")) {
        changeChild("待機");
        return true;
    }
    return false;
}

}  // namespace uking::ai
