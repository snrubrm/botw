#include "Game/AI/AI/aiAssassinBossFirstBattleMove.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Map/mapObject.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

AssassinBossFirstBattleMove::AssassinBossFirstBattleMove(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
AssassinBossFirstBattleMove::~AssassinBossFirstBattleMove() {
    ;
}

bool AssassinBossFirstBattleMove::init_(sead::Heap* heap) {
    sub_7100316D50();
    _64 = 15;
    _68 = 15;
    return true;
}

// NON_MATCHING: target-coordinate loads and horizontal-distance arithmetic scheduling differ.
void AssassinBossFirstBattleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    const sead::Vector3f target = sub_71005D9330(mActor);
    sead::Vector3f direction = mActor->getMtx().getTranslation() - target;
    direction.y = 0.0f;
    direction.normalize();
    const f32 check_dist = *mCheckTargetDist_s;
    if (!(sead::Vector2f(_6c.x - (target.x + direction.x * check_dist),
                        _6c.z - (target.z + direction.z * check_dist)).length() >= *mDistXZ_s)) {
        sub_710031704C();
        return;
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("直線接近可能", &pack);
}

// The approach position: next to the target, perpendicular to the direction from the anchor `_6c`; moved to the other
// side if it is too near / too far from the anchor.
void AssassinBossFirstBattleMove::sub_7100317578(sead::Vector3f* out) {
    const sead::Vector3f target = sub_71005D9330(mActor);
    sead::Vector3f dir(target.x - _6c.x, 0.0f, target.z - _6c.z);
    dir.normalize();
    const sead::Vector3f side(-dir.z, 0.0f, dir.x);
    sead::Vector3f position = target + side * *mCheckTargetDist_s;
    const f32 distance = sead::Vector2f(position.x - _6c.x, position.z - _6c.z).length();
    if (distance < *mDistXZ_s || *mTooFarXZ_s < distance)
        position -= side * (*mCheckTargetDist_s + *mCheckTargetDist_s);
    *out = position;
}

bool AssassinBossFirstBattleMove::isChangeable() const {
    if (!getCurrentChild()->isChangeable())
        return false;
    if (isCurrentChild("直進接近不能"))
        return false;

    sub_71005D9330(mActor);
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const sead::Vector2f diff(pos.x - _6c.x, pos.z - _6c.z);
    return !(diff.length() <= *mDistXZ_s);
}

bool AssassinBossFirstBattleMove::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool AssassinBossFirstBattleMove::isFinished() const {
    return getCurrentChild()->isFinished();
}

void AssassinBossFirstBattleMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AssassinBossFirstBattleMove::loadParams_() {
    getStaticParam(&mDistXZ_s, "DistXZ");
    getStaticParam(&mCheckTargetDist_s, "CheckTargetDist");
    getStaticParam(&mTooFarXZ_s, "TooFarXZ");
    getStaticParam(&mAnchorName_s, "AnchorName");
}

void AssassinBossFirstBattleMove::sub_7100316D50() {
    if (auto* obj = mActor->getMapObject()) {
        if (auto* links = obj->getLinkData()) {
            auto objects = links->mObjects;
            for (s32 i = 0; i < objects.size(); ++i) {
                if (sead::SafeString(objects(i)->getUnitConfigName()) == mAnchorName_s) {
                    const sead::Vector3f translate = objects(i)->getTranslate();
                    _6c = translate;
                    return;
                }
            }
        }
    }
    mActor->getHomePos(&_6c);
}

void AssassinBossFirstBattleMove::sub_710031704C() {
    _60 = f32(_64 == _68 ? _64 : sead::GlobalRandom::instance()->getS32Range(_64, _68));
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f target;
    sub_7100317578(&target);
    pack.addVec3(target, "TargetPos", -1);
    changeChild("直線接近不能", &pack);
}

}  // namespace uking::ai
