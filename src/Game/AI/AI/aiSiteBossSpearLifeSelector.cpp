#include "Game/AI/AI/aiSiteBossSpearLifeSelector.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/Actor/actSiteBoss.h"

namespace uking::ai {

SiteBossSpearLifeSelector::SiteBossSpearLifeSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossSpearLifeSelector::~SiteBossSpearLifeSelector() = default;

bool SiteBossSpearLifeSelector::init_(sead::Heap* heap) {
    _48 = 0;
    return true;
}

void SiteBossSpearLifeSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    if (_48 == 0) {
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
            if (boss->_1558.isOn(0x100)) {
                if (checkHpRate(mActor, *mPatternChangeLife3_s))
                    _48 = 3;
                else if (checkHpRate(mActor, *mPatternChangeLife2_s))
                    _48 = 2;
                else
                    _48 = 1;
                if (auto* current_boss = sead::DynamicCast<act::SiteBoss>(mActor))
                    current_boss->_1558.reset(0xc);
            }
        }
    }
    sub_710058C948();
}

void SiteBossSpearLifeSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossSpearLifeSelector::loadParams_() {
    getStaticParam(&mPatternChangeLife2_s, "PatternChangeLife2");
    getStaticParam(&mPatternChangeLife3_s, "PatternChangeLife3");
}

bool SiteBossSpearLifeSelector::isFailed() const {
    return getCurrentChild() && getCurrentChild()->isFailed();
}

bool SiteBossSpearLifeSelector::isFinished() const {
    return getCurrentChild() && getCurrentChild()->isFinished();
}

void SiteBossSpearLifeSelector::calc_() {
    if (getCurrentChild()) {
        if (getCurrentChild()->isFinished())
            setFinished();
        else if (getCurrentChild()->isFailed())
            setFailed();
    }
}

// 0x710058ced4
void SiteBossSpearLifeSelector::sub_710058CED4() {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_1558.reset(0x10000);
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "IsAttackPatternFixed", -1);
    changeChild("パターン1", &pack);
}

// 0x710058cd94
void SiteBossSpearLifeSelector::sub_710058CD94() {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_1558.reset(0x10000);
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "IsAttackPatternFixed", -1);
    changeChild("パターン2", &pack);
}

// 0x710058cc54
void SiteBossSpearLifeSelector::sub_710058CC54() {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_1558.reset(0x10000);
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "IsAttackPatternFixed", -1);
    changeChild("パターン3", &pack);
}

}  // namespace uking::ai
