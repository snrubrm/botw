#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "Game/Actor/AI/aiPriestBossPhase.h"
#include "Game/Actor/aiUnk_710071edf8.h"
#include "KingSystem/Event/evtBaseProcLinkForEvent.h"
#include "KingSystem/Event/evtMetadata.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/AI/aiPriestBossMetaAIRoot.h"
#include "KingSystem/Event/evtManager.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

// Declaration only; the original source namespace is unknown (as in aiPriestBossGiantEnemyRoot.cpp).
bool sub_710071E80C(ksys::act::Actor* actor, Unk_7102450fa8* unit);

namespace uking::ai {

// 0x7100528b5c: publish the next phase and its life threshold to the shared unit.
// NON_MATCHING: enum temporary stack placement and phase/threshold local layout differ.
void PriestBossPhase::sub_7100528B5C() {
    Flag phase = m38();
    if (_60.isOnBit(Flag(Flag::_0))) {
        switch (phase) {
        case Flag::_0:
            phase = Flag::_1;
            break;
        case Flag::_1:
            phase = Flag::_2;
            break;
        case Flag::_2:
            phase = Flag::_3;
            break;
        case Flag::_3:
            phase = Flag::_4;
            break;
        }
    }
    f32 percent;
    if (!m37(&percent))
        percent = sub_7100525A88()->_40;
    auto* unit = sub_7100525A88();
    unit->_3c = phase;
    unit->_40 = percent;
    if (unit->_38 == Flag::_4)
        unit->_38 = phase;
}

// NON_MATCHING: native string-comparison and loop cleanup scheduling differ.
// 0x7100528c48
bool PriestBossPhase::sub_7100528C48() {
    if (!mActor || !mActor->getAwareness())
        return false;
    auto& entries = mActor->getAwareness()->_8;
    const s32 count = entries.size();
    if (count < 1)
        return false;
    for (s32 i = 0; i < count; ++i) {
        auto* entry = i < entries.size() ? ksys::act::sub_7100D78E30(&entries, i) : nullptr;
        auto& link = entry->_0.mLink;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        if (accessor.getName() != "Item_Fruit_H" && accessor.getName() != "Item_Roast_11")
            continue;
        if (accessor.sub_7100D10E6C(30) || accessor.checkFlag25())
            continue;
        auto* unit = sub_7100525A88();
        if (link.hasProc())
            unit->_28 = link;
        return true;
    }
    return false;
}

// 0x7100528854
bool PriestBossPhase::sub_7100528854(const sead::SafeString& name, const sead::SafeString& entry) {
    if (m38() == Flag::_0 || m38() == Flag::_1) {
        ksys::act::acc::PlayerBase player;
        if (!ksys::act::acquireActor(&act::PlayerInfo::getSomeProcLink(), &player))
            return false;
        const f32 y = player.getActorMtx()(1, 3);
        if (!player.isGroundForEvent() || !(sead::Mathf::abs(y) <= 0.25f)) {
            _70.value = _70.previous_value = 5.0f;
            return false;
        }
        _70.update();
        if (!(_70.value <= sead::Mathf::epsilon()))
            return false;
    }
    auto* mgr = ksys::evt::Manager::instance();
    ksys::evt::Metadata metadata(name.cstr(), entry.cstr(), "");
    ksys::evt::CallArg arg;
    arg.metadata = &metadata;
    arg.proc = mActor;
    return mgr->callEvent(arg);
}

// 0x71005289c4
bool PriestBossPhase::sub_71005289C4() {
    auto* mgr = ksys::evt::Manager::instance();
    for (s32 i = 0; i < 4; ++i) {
        sead::FormatFixedSafeString<256> name("%s%s", sUnk_7102414930, sUnk_71025bb880[i].cstr());
        if (mgr->checkActiveContextEventName(name, sUnk_71025bb830[i]))
            return true;
    }
    return false;
}

// 0x710052902c
void PriestBossPhase::sub_710052902C() {
    sub_7100525A88()->resetFlag(Unk_7102450fa8::Flag::_1);
    ksys::act::ActorLinkConstDataAccess accessor;
    switch (m38()) {
    case Flag::_1:
        sub_7100525A88()->sub_71007194D4(2, &accessor);
        break;
    case Flag::_3:
        sub_7100525A88()->sub_71007194D4(1, &accessor);
        break;
    default:
        break;
    }
    if (!accessor.hasProc())
        return;
    ksys::act::BaseProcLink link;
    accessor.linkAcquire(&link);
    auto* actor = sead::DynamicCast<ksys::act::Actor>(link.getProc(nullptr, mActor));
    if (!sead::IsDerivedFrom<ksys::act::Actor>(actor))
        return;
    const Flag phase = m38();
    auto* unit = sub_7100525A88();
    if (phase == Flag::_1 ? sub_710071E64C(actor, unit) : sub_710071E80C(actor, unit))
        sub_7100525A88()->setFlag(Unk_7102450fa8::Flag::_1);
}

// 0x7100528f10
// NON_MATCHING: the orr operands of the flag 2 set are swapped
void PriestBossPhase::sub_7100528F10() {
    auto* unit = sub_7100525A88();
    if (!unit)
        return;
    if (unit->getPhaseFlags(m38())._0) {
        const auto& flags = unit->getPhaseFlags(m38());
        if (flags._0 && flags._1 && !flags._2)
            setFlag(Flag::_2);
    } else if (m36()) {
        m35();
        auto& flags = unit->_248[m38()];
        flags._0 = true;
        flags._1 = false;
        flags._2 = false;
    }
}

PriestBossPhase::PriestBossPhase(const InitArg& arg) : PriestBossMeta(arg) {}

PriestBossPhase::~PriestBossPhase() = default;

bool PriestBossPhase::init_(sead::Heap* heap) {
    return PriestBossMeta::init_(heap);
}

// NON_MATCHING: the original builds the two flag temporaries in the opposite stack slots and orrs the
// masks as (4, 3) (BitFlag16::setBit gives `orr mask, bits`), keeps m38()'s result in a register (no stack
// slot for a named Flag local) and stores _3c / _40 before the `_38 == 4` branch
void PriestBossPhase::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMeta::enter_(params);
    _60.makeAllZero();
    _60.setBit(Flag(Flag::_4));
    _60.setBit(Flag(Flag::_3));
    const Flag phase = m38();
    auto* unit = sub_7100525A88();
    if (unit->_38 == Flag::_4)
        unit->_38 = phase;
    unit->_3c = phase;
    unit->_40 = *mPercentLifePrevious_s;
    _70.value = _70.previous_value = 5.0f;
}

// 0x71005293ec
// NON_MATCHING: sub_7100528B5C is inlined at the end here (the original calls it); the m37 output slot and two orr
// operand orders differ
void PriestBossPhase::calc_() {
    if (isFlagOn(Flag::_3)) {
        resetFlag(Flag::_3);
        return;
    }
    if (isFlagOn(Flag::_2)) {
        if (isFlagOn(Flag::_0)) {
            const bool started = isFlagOn(Flag::_1);
            const bool active = sub_71005289C4();
            if (started) {
                if (!active)
                    setFinished();
            } else if (active) {
                setFlag(Flag::_1);
            }
        } else {
            m39();
            if (sUnk_71025bb880[m38()].isEmpty()) {
                setFlag(Flag::_0);
                setFlag(Flag::_1);
            } else {
                sead::FormatFixedSafeString<256> name("%s%s", sUnk_7102414930, sUnk_71025bb880[m38()].cstr());
                changeFlag(Flag::_0, sub_7100528854(name, sUnk_71025bb830[m38()]));
            }
        }
    } else {
        sub_7100528F10();
        sub_710052902C();
        f32 x;
        if (m37(&x)) {
            const f32 max_life = *mMetaAIMaxLife_a;
            const s32 low = max_life * *mPercentLifeTransition_s;
            const f32 high_f = max_life * *mPercentLifePrevious_s;
            const s32 high = high_f;
            *mMetaAILife_a = low + high_f * x / high_f * (high - low);
        }
        m40();
        sub_7100525A88()->sub_710071A258();
        sub_7100525A88()->sub_710071A2E8();
    }
    sub_7100528B5C();
}

void PriestBossPhase::leave_() {
    PriestBossMeta::leave_();
    _60.resetBit(Flag(Flag::_4));
}

void PriestBossPhase::loadParams_() {
    PriestBossMeta::loadParams_();
    getStaticParam(&mPercentLifeTransition_s, "PercentLifeTransition");
    getStaticParam(&mPercentLifePrevious_s, "PercentLifePrevious");
}

void PriestBossPhase::m40() {
    _64.update();
    if (_64.value <= sead::Mathf::epsilon()) {
        _64.value = 30.0f;
        _64.previous_value = 30.0f;
        sub_7100525A88()->_2b0.copy(sUnk_7102450f80[sead::GlobalRandom::instance()->getU32(3)]);
    }
}

bool PriestBossPhase::m36() {
    return *mMetaAILife_a <= int(float(*mMetaAIMaxLife_a) * *mPercentLifeTransition_s);
}

}  // namespace uking::ai
