#include "Game/AI/Action/actionSiteBossSwordAfterImageMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

SiteBossSwordAfterImageMove::SiteBossSwordAfterImageMove(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossSwordAfterImageMove::~SiteBossSwordAfterImageMove() {
    auto* slot = static_cast<Unk_71025afb58**>(mSiteBossSwordAfterImageUnit_a);
    if (slot && *slot == &_60)
        *slot = nullptr;
}

bool SiteBossSwordAfterImageMove::init_(sead::Heap* heap) {
    *static_cast<Unk_71025afb58**>(mSiteBossSwordAfterImageUnit_a) = &_60;
    return true;
}

void SiteBossSwordAfterImageMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _5c = false;
    _5d = true;
    _5e = false;

    switch (*mPatternID_m) {
    case 0:
    case 1:
    case 5:
    case 6:
        setFinished();
        return;
    case 10:
        setFinished();
        return;
    default:
        break;
    }

    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    mActor->getXLink()->_cc.reset(0x80000);
    _38.reset(*mMoveFrame_s);
    mActor->getMtx().getTranslation(_44);
}

void SiteBossSwordAfterImageMove::leave_() {
    if (_5d)
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
}

void SiteBossSwordAfterImageMove::loadParams_() {
    getStaticParam(&mMoveFrame_s, "MoveFrame");
    getMapUnitParam(&mPatternID_m, "PatternID");
    getAITreeVariable(&mSiteBossSwordAfterImageUnit_a, "SiteBossSwordAfterImageUnit");
}

namespace {
// Placeholder name: the user data of message 0x800004d (sent by the SiteBossSwordApproach AI classes).
struct Unk_800004d_Payload {
    u32 _0;
    u32 _4;
    sead::Vector3f _8;
    u32 _14;
    bool _18;
    bool _19;
    bool _1a;
    bool _1b;
};
}  // namespace

bool SiteBossSwordAfterImageMove::handleMessage_(const ksys::Message* message) {
    if (message && message->getBrokerId() == u32(-1) && message->getType() == 0x800004d) {
        if (message->getUserData()) {
            const auto* data = static_cast<const Unk_800004d_Payload*>(message->getUserData());
            if (data) {
                _50 = data->_8;
                _38.reset(5.0f);
                _5c = true;
                _5f = true;
                _5d = data->_18;
                _5e = data->_19;
                _60._8 = data->_1a;
                _60._9 = data->_1b;
                return true;
            }
        }
    }
    return false;
}

// NON_MATCHING: the original keeps the target position in float registers (loaded with `ldp s0, s1` before the
// `_38.value > 1` test, one `stp` to the stack after the branch); ours materialises `pos` on the stack first.
void SiteBossSwordAfterImageMove::calc_() {
    if (!_5c)
        return;

    if (_5f) {
        const bool repair = _5e;
        _5f = false;
        if (repair)
            playAS("Shield_Repair", false, 0, 0, -1.0f);
        else
            playAS("Shield_Break", false, 0, 0, -1.0f);
    }

    sead::Vector3f pos(_50.x, _50.y, _50.z);
    if (!(_38.value <= 1.0f)) {
        sead::Vector3f dir = _50 - _44;
        const f32 length = dir.length();
        if (length > 0.0f)
            dir *= 1.0f / length;
        pos = _44 + dir * (length * ((*mMoveFrame_s - _38.value) / *mMoveFrame_s));
    }

    if (auto* body = mActor->getMainBody())
        body->changePosition(pos, ksys::phys::KeepAngularVelocity{true});

    _38.update();
    if (_38.value <= sead::Mathf::epsilon())
        setFinished();
}

}  // namespace uking::action
