#include "Game/AI/AI/aiAssassinBossEscapeFromTarget.h"
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

bool AssassinBossEscapeFromTarget::isChangeable() const {
    return false;
}

void AssassinBossEscapeFromTarget::leave_() {
    SimpleEscapeFromTarget::leave_();
}

void AssassinBossEscapeFromTarget::loadParams_() {
    SimpleEscapeFromTarget::loadParams_();
    getStaticParam(&mAnchorName_s, "AnchorName");
    getStaticParam(&mCheckDist_s, "CheckDist");
}

// NON_MATCHING: the original copies the position as 8 + 4 bytes in x, z order (ours: z first)
void AssassinBossEscapeFromTarget::sub_7100315244() {
    if (auto* obj = mActor->getMapObject()) {
        if (auto* links = obj->getLinkData()) {
            const auto objects = links->mObjects;
            for (s32 i = 0; i < objects.size(); ++i) {
                if (sead::SafeString(objects(i)->getUnitConfigName()) == mAnchorName_s) {
                    _80.set(objects(i)->getTranslate());
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

}  // namespace uking::ai
