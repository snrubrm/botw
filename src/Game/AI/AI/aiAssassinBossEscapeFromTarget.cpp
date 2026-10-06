#include "Game/AI/AI/aiAssassinBossEscapeFromTarget.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::ai {

AssassinBossEscapeFromTarget::AssassinBossEscapeFromTarget(const InitArg& arg)
    : SimpleEscapeFromTarget(arg) {}

// The SafeString member makes the original keep the vtable store that a defaulted destructor drops;
// written as upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
AssassinBossEscapeFromTarget::~AssassinBossEscapeFromTarget() { ; }

bool AssassinBossEscapeFromTarget::init_(sead::Heap* heap) {
    return SimpleEscapeFromTarget::init_(heap);
}

void AssassinBossEscapeFromTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100315244();
    SimpleEscapeFromTarget::enter_(params);
}

void AssassinBossEscapeFromTarget::calc_() {
    auto* child = getCurrentChild();
    if (!child) {
        setFailed();
        return;
    }
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("後退移動完了")) {
            if (child->isFinished())
                setFinished();
            else
                setFailed();
        } else if (sub_710056D24C()) {
            if (isCurrentChild("後退不能移動")) {
                setFinished();
                return;
            }
        } else if (isCurrentChild("後退不能移動")) {
            sub_710056CF84();
            return;
        }
    } else {
        child->isChangeable();
    }
    if (!isCurrentChild("後退移動完了"))
        SimpleEscapeFromTarget::calc_();
}

bool AssassinBossEscapeFromTarget::isChangeable() const {
    return false;
}

void AssassinBossEscapeFromTarget::leave_() {
    SimpleEscapeFromTarget::leave_();
}

void AssassinBossEscapeFromTarget::loadParams_() {
    SimpleEscapeFromTarget::loadParams_();
    getStaticParam(&mParams.mAnchorName_s, "AnchorName");
    getStaticParam(&mParams.mCheckDist_s, "CheckDist");
}

void AssassinBossEscapeFromTarget::sub_7100315244() {
    if (auto* obj = mActor->getMapObject()) {
        if (auto* links = obj->getLinkData()) {
            auto objects = links->mObjects;
            for (s32 i = 0; i < objects.size(); ++i) {
                if (sead::SafeString(objects(i)->getUnitConfigName()) == mParams.mAnchorName_s) {
                    const sead::Vector3f translate = objects(i)->getTranslate();
                    _80 = translate;
                    return;
                }
            }
        }
    }
    mActor->getHomePos(&_80);
}

bool AssassinBossEscapeFromTarget::m34() {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("後退不能移動", &params);
    return true;
}

void AssassinBossEscapeFromTarget::m35(bool finished) {
    if (!isCurrentChild("後退移動"))
        return;
    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("後退移動完了", &params);
}

void AssassinBossEscapeFromTarget::m37() {
    if (isCurrentChild("後退不能移動") || isCurrentChild("後退移動完了"))
        getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    else
        SimpleEscapeFromTarget::m37();
}

void AssassinBossEscapeFromTarget::m38(sead::Vector3f* dir, s32 idx) {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    const sead::Vector3f target = *dir;
    sead::Vector3f hit;
    if (sub_710072FD0C(mActor, pos, target, &hit, -1, *mParams.mCheckDist_s, -1.0f, -1.0f, -1.0f))
        return;

    sead::Vector3f to_anchor = _80;
    to_anchor -= pos;
    to_anchor.normalize();
    s32 sign = dir->dot(to_anchor) > 0.0f ? 1 : -1;
    if (sead::Vector2f(_80.x - hit.x, _80.z - hit.z).squaredLength() >
        sead::Vector2f(_80.x - pos.x, _80.z - pos.z).squaredLength()) {
        sign = -sign;
    }
    const f32 angle = sead::Mathf::deg2rad(f32(sign * idx) * 10.0f);
    sead::Matrix34f rot;
    rot.makeR({0.0f, angle, 0.0f});
    dir->rotate(rot);
}

bool AssassinBossEscapeFromTarget::m39(const sead::Vector3f& dir) {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    return sub_710072FD0C(mActor, pos, dir, nullptr, -1, *mParams.mCheckDist_s, -1.0f, -1.0f, -1.0f);
}

}  // namespace uking::ai
