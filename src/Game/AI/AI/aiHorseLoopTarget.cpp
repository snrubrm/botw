#include "Game/AI/AI/aiHorseLoopTarget.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapRail.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

HorseLoopTarget::HorseLoopTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseLoopTarget::~HorseLoopTarget() = default;

void HorseLoopTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _50.clear();
    _160 = 0;
    _164 = 1;
    sub_710127FB74();
    if (auto* nav = mActor->m45()) {
        nav->sub_7100F7605C(2.0f);
        nav->sub_7100F7604C(nav->getRadiusMaybe());
    }
    changeChild("待機", nullptr);
}

void HorseLoopTarget::sub_710127FB74() {
    _168 = m34();
    _160 = 0;
    if (!_168)
        return;

    const f32 x = mActor->getMtx().m[0][3];
    const f32 z = mActor->getMtx().m[2][3];
    f32 min_dist = 0.0f;
    for (s32 i = 0; i < _168->getNumPoints(); ++i) {
        const sead::Vector3f& point = _168->getPointTranslate(i);
        const f32 dx = point.x - x;
        const f32 dz = point.z - z;
        const f32 dist = dx * dx + dz * dz;
        if (i == 0 || dist < min_dist) {
            _160 = i;
            min_dist = dist;
        }
    }
    _160 -= 1;
    if (_160 < 0)
        _160 += _168->getNumPoints();
}

void HorseLoopTarget::sub_710127FF2C() {
    auto* rail = _168;
    const s32 next = _164 + _160;
    _160 = next;
    if (next < rail->getNumPoints()) {
        if (_160 >= 0)
            return;
        if (!_168->isClosed() && *mIsFlip_s) {
            _164 = -_164;
            _160 = 1;
            return;
        }
        _160 = _168->getNumPoints() - 1;
    } else {
        if (_168->isClosed()) {
            _160 = 0;
            return;
        }
        if (!*mIsFlip_s) {
            _160 = 0;
            return;
        }
        _164 = -_164;
        _160 = _168->getNumPoints() - 1;
    }
}

// NON_MATCHING: scheduling only: the original loads the 8-byte x/y pair of the rail point before its z (and
// stores z after the SafeString key); ours loads z first (all three inlined copies of the block)
void HorseLoopTarget::calc_() {
    if (!_168)
        return;
    if (isCurrentChild("待機")) {
        sub_710127FF2C();
        ksys::act::ai::InlineParamPack pack;
        const sead::Vector3f pos = _168->getPointTranslate(_160);
        pack.addVec3(pos, "TargetPos", -1);
        changeChild("指定位置に移動", &pack);
    } else if (isCurrentChild("指定位置に移動")) {
        if (!getCurrentChild()->isFinished()) {
            if (getCurrentChild()->isFailed()) {
                sub_710127FF2C();
                ksys::act::ai::InlineParamPack pack;
                const sead::Vector3f pos = _168->getPointTranslate(_160);
                pack.addVec3(pos, "TargetPos", -1);
                changeChild("指定位置に移動", &pack);
            }
        } else {
            sub_710127FF2C();
            ksys::act::ai::InlineParamPack pack;
            const sead::Vector3f pos = _168->getPointTranslate(_160);
            pack.addVec3(pos, "TargetPos", -1);
            changeChild("指定位置に移動", &pack);
        }
    }
}

ksys::map::Rail* HorseLoopTarget::m34() {
    auto* object = mActor->getMapObject();
    if (!object)
        return nullptr;
    if (!object->getRails_0())
        return nullptr;
    return *object->getRails_0();
}

void HorseLoopTarget::loadParams_() {
    getStaticParam(&mTargetName_s, "TargetName");
    getStaticParam(&mIsFlip_s, "IsFlip");
}

sead::Vector3f HorseLoopTarget::sub_710127FFD8() {
    return _168->getPointTranslate(_160);
}

}  // namespace uking::ai
