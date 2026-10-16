#include "Game/Actor/AI/aiAssassinBossBattle.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/aiRootAi.h"

namespace uking::ai {

AssassinBossBattle::AssassinBossBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
AssassinBossBattle::~AssassinBossBattle() {
    ;
}

bool AssassinBossBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the anchor position shares the param pack slot in the original; register numbering.
void AssassinBossBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (!testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0)) {
        if (auto* enemy = static_cast<act::Enemy*>(mActor))
            enemy->startAttackInterval(*mIntervalIntensity_s);
    }

    auto* self = mActor;
    auto* life = self->getLife();
    const s32 current_life = life ? *life : 1;
    const bool dying = f32(current_life) < f32(self->getMaxLife()) * *mDyingLifeRatio_s ||
                       (current_life <= 0 && *mDyingLifeRatio_s < 0.0f);
    sead::Vector3f anchor;
    sub_71005DF270(&anchor, self, mAnchorName_s, dying ? *mBattleDist_s : *mBattleDistSecond_s);

    const sead::Vector3f& pos = actor->getMtx().getTranslation();
    if (sead::Vector2f(anchor.x - pos.x, anchor.z - pos.z).length() > *mHomeDist_s) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(anchor, "TargetPos", -1);
        changeChild("移動", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("様子見", &pack);
    }
}

void AssassinBossBattle::calcAnchorPos(sead::Vector3f* out) {
    auto* self = mActor;
    auto* life = self->getLife();
    const s32 current_life = life ? *life : 1;
    const bool dying = f32(current_life) < f32(self->getMaxLife()) * *mDyingLifeRatio_s ||
                       (current_life <= 0 && *mDyingLifeRatio_s < 0.0f);
    sub_71005DF270(out, self, mAnchorName_s, dying ? *mBattleDist_s : *mBattleDistSecond_s);
}

// NON_MATCHING: stack slots (as in enter_, the anchor position shares the param pack slot in the original)
void AssassinBossBattle::calc_() {
    if (auto* enemy = static_cast<act::Enemy*>(mActor))
        enemy->_e68.rate = -1.0f;

    const auto isFar = [this](const sead::Vector3f& anchor) {
        const sead::Vector3f& pos = mActor->getMtx().getTranslation();
        return sead::Vector2f(anchor.x - pos.x, anchor.z - pos.z).length() > *mHomeDist_s ||
               sead::Mathf::abs(anchor.y - pos.y) > *mReturnHeight_s;
    };

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("攻撃")) {
            if (auto* enemy = static_cast<act::Enemy*>(mActor))
                enemy->startAttackInterval(*mIntervalIntensity_s);
            sead::Vector3f anchor;
            calcAnchorPos(&anchor);
            if (isFar(anchor)) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(anchor, "TargetPos", -1);
                changeChild("移動", &pack);
            } else {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("様子見", &pack);
            }
            return;
        }
        if (isCurrentChild("様子見")) {
            sead::Vector3f anchor;
            calcAnchorPos(&anchor);
            if (isFar(anchor)) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(anchor, "TargetPos", -1);
                changeChild("移動", &pack);
            } else {
                setFailed();
            }
        } else {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("様子見", &pack);
        }
    } else if (child->isChangeable() && !isCurrentChild("攻撃") && isCurrentChild("様子見")) {
        auto* enemy = static_cast<act::Enemy*>(mActor);
        if (enemy && enemy->_e68.value <= sead::Mathf::epsilon()) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("攻撃", &pack);
            return;
        }
    }

    if (isCurrentChild("移動")) {
        sead::Vector3f anchor;
        calcAnchorPos(&anchor);
        getCurrentChild()->setDynamicParam(anchor, "TargetPos");
    } else {
        getCurrentChild()->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
    }
}

bool AssassinBossBattle::handleMessage_(const ksys::Message* message) {
    return false;
}

void AssassinBossBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AssassinBossBattle::loadParams_() {
    getStaticParam(&mRetFrmDmgAtkTimer_s, "RetFrmDmgAtkTimer");
    getStaticParam(&mIntervalIntensity_s, "IntervalIntensity");
    getStaticParam(&mHomeDist_s, "HomeDist");
    getStaticParam(&mBattleDist_s, "BattleDist");
    getStaticParam(&mDyingLifeRatio_s, "DyingLifeRatio");
    getStaticParam(&mBattleDistSecond_s, "BattleDistSecond");
    getStaticParam(&mAnchorName_s, "AnchorName");
    getStaticParam(&mReturnHeight_s, "ReturnHeight");
}

}  // namespace uking::ai
