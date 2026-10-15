#include "Game/Actor/AI/aiWolfLinkBattleRoot.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/actWolfLink.h"
#include "Game/Actor/aiAwarenessFilters.h"
#include "Game/Actor/aiUnk_7100742478.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWolfLink.h"

namespace uking::ai {

WolfLinkBattleRoot::WolfLinkBattleRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkBattleRoot::~WolfLinkBattleRoot() = default;

bool WolfLinkBattleRoot::init_(sead::Heap* heap) {
    _60 = sead::DynamicCast<act::WolfLink>(mActor);
    if (!_60)
        return false;

    const auto* params = mActor->getParam()->getRes().mGParamList->getWolfLink();
    const f32 min = params->mAttackCounterLength.ref();
    const f32 max = min + params->mAttackCounterRand.ref();
    const s32 time = sead::GlobalRandom::instance()->getF32Range(min, max);
    _60->_e68 = ksys::Timer(time, time);
    return true;
}

// NON_MATCHING: random singleton and parameter load scheduling differ.
void WolfLinkBattleRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    s32 life = 0;
    {
        const auto& link = _60->_c48._8;
        ksys::act::ActorLinkConstDataAccess accessor;
        if (link.hasProc() && ksys::act::acquireActor(&link, &accessor))
            life = accessor.getLife();
    }
    bool keep_target = false;
    if (life > 0) {
        const auto position = mActor->getMtx().getTranslation();
        const auto& target = sub_71005D9330(mActor);
        const f32 dx = position.x - target.x;
        const f32 dz = position.z - target.z;
        keep_target = dx * dx + dz * dz < *mKeepTargetRange_d * *mKeepTargetRange_d;
    }
    if (!keep_target && !_60->sub_71002F3234(*mKeepTargetRange_d, 1337, 1, 3)) {
        setFailed();
        return;
    }

    _68 = false;
    _69 = false;
    _60->_e68.rate = -1.0f;
    _60->sub_71002F2E78(act::WolfLink::Idx14f8::_6);
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("ダメージ後", &pack);
    } else {
        const auto* wolf_params = mActor->getParam()->getRes().mGParamList->getWolfLink();
        const f32 min = wolf_params->mAttackCounterLength.ref();
        const s32 time = sead::GlobalRandom::instance()->getF32Range(
            min, min + wolf_params->mAttackCounterRand.ref());
        _60->_e68 = ksys::Timer(time, time);
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("戦闘準備", &pack);
    }
}

// NON_MATCHING: parameter-pack frame layout and random-range arithmetic scheduling differ.
void WolfLinkBattleRoot::calc_() {
    if (!sub_7100601F84()) {
        setFinished();
        return;
    }
    if (!sub_7100602654() || !isCurrentChild("戦闘準備"))
        return;
    _60->sub_71002F3234(*mKeepTargetRange_d, 1337, 1, 3);
    if (!(_60->_e68.value <= sead::Mathf::epsilon()))
        return;
    if (sub_7100602CCC()) {
        if (sub_7100602E40()) {
            changeChild("戦闘連鎖攻撃", nullptr);
        } else {
            // The original constructs this actual pack despite passing no parameters.
            ksys::act::ai::InlineParamPack pack;
            changeChild("戦闘攻撃対地", nullptr);
        }
        return;
    }
    if (_60->sub_71002F420C())
        _5c += *mChanceToBarkOnAttackFail_s;
    if (sead::GlobalRandom::instance()->getF32Range(0.0f, 1.0f) <=
        *mChanceToBarkOnAttackFail_s + _5c) {
        _5c = 0;
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_60->_c48._18, "TargetPos", -1);
        changeChild("戦闘攻撃できない", &pack);
    } else {
        const auto* params = mActor->getParam()->getRes().mGParamList->getWolfLink();
        const f32 min = params->mAttackCounterLength.ref();
        const s32 time = sead::GlobalRandom::instance()->getF32Range(
            min, min + params->mAttackCounterRand.ref());
        _60->_e68.reset(time);
    }
}

void WolfLinkBattleRoot::leave_() {
    _60->_e68.rate = 0;
    using Idx = act::WolfLink::Idx14f8;
    _60->_14f8[Idx(Idx::_6)].rate = 0;
}

void WolfLinkBattleRoot::loadParams_() {
    if (getStaticParam(&mAttackIntiationRange_s, "AttackIntiationRange"))
        _58 = *mAttackIntiationRange_s * *mAttackIntiationRange_s;
    getStaticParam(&mChanceToBarkOnAttackFail_s, "ChanceToBarkOnAttackFail");
    getStaticParam(&mUseChainAttack_s, "UseChainAttack");
    getDynamicParam(&mKeepTargetRange_d, "KeepTargetRange");
}

bool WolfLinkBattleRoot::sub_7100602CCC() {
    if (_60->_1698 & 4)
        return false;
    s32 life = 0;
    {
        const auto& link = _60->_c48._8;
        ksys::act::ActorLinkConstDataAccess accessor;
        if (link.hasProc() && ksys::act::acquireActor(&link, &accessor))
            life = accessor.getLife();
    }
    if (life < 1 || !sub_71006030BC())
        return false;
    const auto position = mActor->getMtx().getTranslation();
    const auto& target = sub_71005D9330(mActor);
    const f32 dx = position.x - target.x;
    const f32 dz = position.z - target.z;
    if (!(dx * dx + dz * dz < _58) || !(_60->_1698 & 0x2000))
        return false;
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return false;
    auto* sensor = awareness->_260[0];
    const u32 count = sensor ? sensor->_8.size() : 0;
    for (u32 i = 0; i < count; ++i) {
        ksys::act::Unk_7100d78e50* entry = nullptr;
        if (auto* current_sensor = awareness->_260[0]) {
            if (current_sensor->_8.size() > s32(i))
                entry = ksys::act::sub_7100D78E30(&current_sensor->_8, i);
        }
        if (auto* link = sub_71005D9050(mActor)) {
            if (*link == entry->_0.mLink)
                return true;
        }
    }
    return false;
}

// NON_MATCHING: random singleton and parameter load scheduling differ.
bool WolfLinkBattleRoot::sub_7100602654() {
    auto* child = getCurrentChild();
    if (!child)
        return false;
    if (!child->isFinished() && !child->isFailed())
        return true;

    if (isCurrentChild("ダメージ後")) {
        setRootAiFlag(ksys::act::ai::RootAiFlag::_0);
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("戦闘準備", &pack);
        return false;
    }

    if (isCurrentChild("戦闘準備") && child->isFailed()) {
        if (!_60->sub_71002F3234(*mKeepTargetRange_d, 1337, 1, 3)) {
            setFailed();
            return false;
        }
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("戦闘準備", &pack);
    }

    isCurrentChild("戦闘連鎖攻撃");
    const auto* params = mActor->getParam()->getRes().mGParamList->getWolfLink();
    const f32 min = params->mAttackCounterLength.ref();
    const s32 time = sead::GlobalRandom::instance()->getF32Range(
        min, min + params->mAttackCounterRand.ref());
    _60->_e68 = ksys::Timer(time, time);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("戦闘準備", &pack);
    return false;
}

// NON_MATCHING: accessor initialization and position component stores are reordered.
bool WolfLinkBattleRoot::sub_7100602E40() {
    if (!*mUseChainAttack_s || _60->_1688 < 100.0f)
        return false;
    auto* life = mActor->getLife();
    if ((life ? *life : 1) != mActor->getMaxLife() || !mActor->getAwareness())
        return false;

    Unk_7102451830 filter;
    auto* awareness = _60->getAwareness();
    if (!awareness || !awareness->_260[0] || awareness->_260[0]->_8.size() < 1)
        return false;
    const s32 count = awareness->_260[0]->_8.size();
    const auto& target_link = _60->_c48._8;
    ksys::act::ActorLinkConstDataAccess target;
    if (!ksys::act::acquireActor(&target_link, &target) || target.hasTag(0xd8efc0bb))
        return false;

    f32 x = _60->_c48._18.x;
    f32 z = _60->_c48._18.z;
    s32 num_reachable = 0;
    for (s32 i = 0; i < count; ++i) {
        auto* sensor = awareness->_260[0];
        if (!sensor)
            break;
        auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter);
        if (!entry)
            break;
        ksys::act::ActorLinkConstDataAccess accessor;
        if (!ksys::act::acquireActor(&entry->_0.mLink, &accessor) ||
            entry->_0.mLink == target_link || accessor.getLife() < 1 ||
            accessor.hasTag(0xd8efc0bb))
            continue;
        const sead::Vector3f position = accessor.getActorMtx().getTranslation();
        const f32 dx = x - position.x;
        const f32 dz = z - position.z;
        if (s32(dz * dz + dx * dx) > 400)
            continue;
        if (sub_7100742588(nullptr, mActor->m45(), &position, 10.0f)) {
            x = position.x;
            z = position.z;
            ++num_reachable;
        }
    }
    return num_reachable > 1;
}

// NON_MATCHING: position stores merge and the final bool negation uses an integer tail.
bool WolfLinkBattleRoot::sub_71006030BC() {
    auto* link = sub_71005D9050(mActor);
    ksys::act::ActorLinkConstDataAccess accessor;
    if (!link || !ksys::act::acquireActor(link, &accessor) || accessor.hasTag(0x2bc52291))
        return false;
    if (accessor.isBgGroundHit())
        return true;
    if (accessor.hasTag(0xd3231bed)) {
        const sead::Vector3f position = accessor.getActorMtx().getTranslation();
        const auto& bounds = accessor.sub_7100D0FD54();
        return sub_7100742334(
            &position, mActor->getParam()->getRes().mGParamList->getWolfLink()->mMaxHeightAttackable.ref() +
                           bounds.getSizeY() * 0.5f);
    }
    return !accessor.hasTag(0xff2ecb67);
}

}  // namespace uking::ai
