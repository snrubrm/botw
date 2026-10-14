#include "Game/Actor/Action/actionDragonFollow.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DragonFollow::DragonFollow(const InitArg& arg) : AppearFollowChallenge(arg) {}

DragonFollow::~DragonFollow() = default;

bool DragonFollow::init_(sead::Heap* heap) {
    if (!AppearFollowChallenge::init_(heap))
        return false;
    sub_710004E2B4(false);
    sub_71000F4798();
    return true;
}

void DragonFollow::enter_(ksys::act::ai::InlineParamPack* params) {
    AppearFollowChallenge::enter_(params);
}

void DragonFollow::leave_() {
    AppearFollowChallenge::leave_();
    mActor->sub_71011DA834(&mBindInfo);
}

void DragonFollow::loadParams_() {
    AppearFollowChallenge::loadParams_();
    getStaticParam(&mDungeonName_s, "DungeonName");
}

void DragonFollow::calc_() {
    AppearFollowChallenge::calc_();
    const u32 delay = _c38;
    if (delay)
        --_c38;
    switch (_c48) {
    case 0: {
        if (!mBindInfo._18) {
            sub_710004E2B4(false);
            return;
        }
        auto* actor = mBindInfo.sub_7100D3C5E0(mActor);
        if (!actor) {
            sub_710004E2B4(false);
            return;
        }
        const auto position = actor->getMtx().getTranslation();
        const sead::Vector2f offset(position.x - mDungeonPosition.x,
                                   position.z - mDungeonPosition.z);
        if (!(offset.length() <= 300.0f)) {
            sub_710004E2B4(false);
            return;
        }
        _c48 = 1;
        break;
    }
    case 2:
        sub_710004E2B4(false);
        return;
    default:
        break;
    }
    if (!delay) {
        sub_710004E2B4(false);
        return;
    }
    if (_4b8) {
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    } else {
        sub_710004E2B4(true);
        if (sub_710004F8A4()) {
            sub_710004E2B4(false);
            _4b8 = true;
            sub_710004D9A4();
            sub_710004DFF4();
        } else if (m32()) {
            _c48 = 2;
        }
    }
    sub_710004E754();
}

}  // namespace uking::action
