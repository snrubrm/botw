#include "Game/Actor/Player/AI/aiPlayerWaterFall.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapRail.h"
#include <cmath>
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

PlayerWaterFall::PlayerWaterFall(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PlayerWaterFall::~PlayerWaterFall() = default;

bool PlayerWaterFall::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: transform stores, normalization and child-selection scheduling differ.
void PlayerWaterFall::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_c48.resetBit(24);
    player->x_8(false, false);
    if (player->_2550._8.isOnBit(2)) {
        // called through a pointer in the original (not devirtualised)
        (&player->_2550)->m13(2);
    }
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::Attention::instance()->sub_7100D7482C(&accessor);
    if (!accessor.hasProc()) {
        setFailed();
        return;
    }
    if (const auto* object = accessor.getMapObject()) {
        if (auto* rails = object->getRails_0()) {
            _88 = rails[0];
            if (!_88) {
                setFailed();
                return;
            }
        }
    }
    const auto end = _88->calcTranslate(static_cast<f32>(_88->getNumPoints() - 1));
    player->_e58 = end.y - player->_1770.y + 20.0f;
    const auto& mtx = accessor.getActorMtx();
    _7c = mtx.getTranslation();
    _70 = mtx.getBase(2);
    _70.normalize();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_7c, "TargetPos", -1);
    if (auto* controller = mActor->getCharacterController()) {
        _90 = controller->_150;
        controller->_150 = 0;
        controller->mFlags.reset(8);
    }
    if (!handlePendingChildChange())
        changeChild(player->m193() ? "ゾーラ跳ね上げ" : "潜水移動", &pack);
}

// NON_MATCHING: vector stores, parameter-pack stack slots and branch scheduling differ.
void PlayerWaterFall::calc_() {
    if (handlePendingChildChange())
        return;
    if (getCurrentChild()->isChangeable() && isCurrentChild("ゾーラ跳ね上げ")) {
        auto* player = static_cast<ksys::act::Player*>(mActor);
        const f32 dx = player->_1770.x - _7c.x;
        const f32 dz = player->_1770.z - _7c.z;
        if (std::sqrt(dx * dx + dz * dz) < player->_20bc.value * player->_20f0) {
            ksys::act::ai::InlineParamPack pack;
            pack.addPointer(_88, "RailPtr", ksys::AIDefParamType::Rail, -1);
            pack.addVec3(_70, "FrontDir", -1);
            changeChild("登り", &pack);
            return;
        }
    }
    auto* child = getCurrentChild();
    if (child->isFailed() || child->isFinished()) {
        if (isCurrentChild("潜水移動")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addPointer(_88, "RailPtr", ksys::AIDefParamType::Rail, -1);
            pack.addVec3(_70, "FrontDir", -1);
            changeChild("登り", &pack);
        } else if (isCurrentChild("登り")) {
            changeChild("ジャンプ", nullptr);
        }
    }
}

void PlayerWaterFall::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->_150 = _90;
        controller->mFlags.set(0x8);
    }
}

void PlayerWaterFall::loadParams_() {}

bool PlayerWaterFall::isFinished() const {
    if (isCurrentChild("ジャンプ")) {
        if (getCurrentChild()->isFinished())
            return true;
    }
    return false;
}

bool PlayerWaterFall::isFailed() const {
    if (getCurrentChild()->isFailed())
        return true;
    if (!static_cast<ksys::act::Player*>(mActor)->_207f) {
        if (isCurrentChild("潜水移動") || isCurrentChild("登り"))
            return true;
    }
    return false;
}

}  // namespace uking::ai
