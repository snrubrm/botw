#include "Game/AI/AI/aiMagnetglove.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

Magnetglove::Magnetglove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

Magnetglove::~Magnetglove() = default;

bool Magnetglove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void Magnetglove::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* player = sead::DynamicCast<ksys::act::PlayerBase>(sead::DynamicCast<ksys::act::Actor>(
        ksys::act::PlayerInfo::getSomeProcLink().getProc(nullptr, mActor)));
    if (player && player->_cf0.isOnBit(22))
        changeChild("マグネフォース発生");
    else
        changeChild("所持");
}

void Magnetglove::calc_() {
    if (isCurrentChild("消滅"))
        return;

    auto* player = sead::DynamicCast<ksys::act::PlayerBase>(sead::DynamicCast<ksys::act::Actor>(
        ksys::act::PlayerInfo::getSomeProcLink().getProc(nullptr, mActor)));
    if (!player) {
        setFailed();
        return;
    }

    _38.x(player);
    _38._28 = "Weapon_R";
    _38._30.getKey().reset();
    mActor->sub_71011DA824(&_38);
    if (auto* body = mActor->getMainBody())
        body->setTransform(mActor->getMtx());

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("所持")) {
            if (player->_cf0.isOnBit(22))
                changeChild("マグネフォース発生");
        }
    } else if (child->isChangeable()) {
        if (isCurrentChild("所持")) {
            if (player->_cf0.isOnBit(22)) {
                changeChild("マグネフォース発生");
            } else {
                mActor->sub_71011DA834(&_38);
                changeChild("消滅");
            }
        } else if (isCurrentChild("マグネフォース発生")) {
            if (!player->_cf0.isOnBit(22)) {
                mActor->sub_71011DA834(&_38);
                changeChild("消滅");
            }
        }
    }
}

void Magnetglove::leave_() {
    mActor->sub_71011DA834(&_38);
}

void Magnetglove::loadParams_() {}

}  // namespace uking::ai
