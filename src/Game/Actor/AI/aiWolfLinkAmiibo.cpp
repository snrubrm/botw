#include "Game/Actor/AI/aiWolfLinkAmiibo.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/actWolfLink.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameAmiiboMgr.h"
#include "Game/gameWolfLinkMgr.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::ai {

namespace {
// 0x71024320f8: constant-initialised into .data in the original, right before the WolfLinkAmiibo
// vtable. The amiibo name used while no amiibo is registered.
const sead::SafeString sUnk_71024320f8(sead::SafeString::ConstInitTag{}, "default");
}  // namespace

WolfLinkAmiibo::WolfLinkAmiibo(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkAmiibo::~WolfLinkAmiibo() {
    if (_60)
        ksys::phys::HavokAI::instance()->destroyQuery(_60);
}

// 0x7100600a6c (placeholder name): allocates the navmesh position query from the request pool's
// heap, starts it at the current amiibo position and submits it.
// NON_MATCHING: the two parameter loads are scheduled after the destination member reload (same
// instructions otherwise).
void WolfLinkAmiibo::sub_7100600A6C() {
    if (_60)
        return;

    void* memory = ksys::phys::HavokAI::instance()->_40->mHeap->tryAlloc(
        sizeof(Unk_71024ed6a0), 8);
    if (!memory) {
        _60 = nullptr;
        setFailed();
        return;
    }

    _60 = new (memory) Unk_71024ed6a0;
    _60->_18 = AmiiboMgr::instance()->_9c;
    _60->_24 = *mAreaSearchRadius_s;
    _60->_28 = *mAreaSearchCharacterRadius_s;
    _60->_2c = 0;
    _60->_30 = 2.0f;
    _60->_3c = *mAreaThreshold_s;
    _60->_34 = ksys::phys::NavMeshCharacterType::WolfLink;
    ksys::phys::HavokAI::instance()->submitQuery(_60);
}

bool WolfLinkAmiibo::havokQueryFinished() {
    auto* query = _60;
    if (!query || query->_8 != 2)
        return false;

    if (query->_38 >= query->_3c) {
        const sead::Vector3f pos = query->_40;
        ksys::phys::RayCastBodyQuery ray(nullptr, ksys::phys::GroundHit::HitAll);
        ray.enableLayer(ksys::phys::ContactLayer::EntityGround);
        ray.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
        ray.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);

        {
            const sead::Vector3f start(pos.x, pos.y + 2.0f, pos.z);
            ray.setStart(start);
        }
        {
            const sead::Vector3f end(pos.x, pos.y - 2.0f, pos.z);
            ray.setEnd(end);
        }

        if (ray.worldRayCast(ksys::phys::ContactLayerType::Entity))
            ray.getHitPosition(&_50);
        else
            setFlag(Flag::_5);
    } else {
        setFlag(Flag::_5);
    }

    ksys::phys::HavokAI::instance()->destroyQuery(_60);
    _60 = nullptr;
    return true;
}

bool WolfLinkAmiibo::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WolfLinkAmiibo::enter_(ksys::act::ai::InlineParamPack* params) {
    _5c.makeAllZero();
    if (cannotUseWolfLinkAmiibo()) {
        ui::showInfoOverlay(26);
        setFailed();
        return;
    }
    sub_7100600A6C();
}

void WolfLinkAmiibo::calc_() {
    if (isFinishedOrFailed())
        return;

    if (_68) {
        auto* child = getCurrentChild();
        if (!child->isFinishedOrFailed())
            return;

        if (child->isFinished()) {
            if (auto* amiibo = AmiiboMgr::instance()) {
                AmiiboInfo info;
                const AmiiboInfo& src = AmiiboMgr::instance()->_148.mInfo;
                info._0 = src._0;
                info._4 = src._4;
                memcpy(&info._8, &src._8, sizeof(info._8));
                info.mName = src.mName;
                amiibo->registerAmiibo(info);
            }
            setFinished();
        } else {
            isCurrentChild("登録");
            ui::showInfoOverlay(25);
            setFailed();
        }
    } else {
        _68 = havokQueryFinished();
        if (_68) {
            checkAndUpdateFlags();
            sub_71006013D4();
        }
    }
}

void WolfLinkAmiibo::leave_() {
    ksys::act::ai::Ai::leave_();
}

// 0x7100600d28 (CSV placeholder name: AI_AI_WolfLinkAmiibo::checkAndUpdateFlags): refreshes the
// spawn flag byte from the WolfLink game-data flags and the last amiibo's data.
// NON_MATCHING: same size and call set; the isFlagOn mask/byte `and` operands are swapped
// (commutative), and the `&info.mName` address is spilled, shifting the frame by 0x10.
void WolfLinkAmiibo::checkAndUpdateFlags() {
    if (isFlagOn(Flag::_5))
        return;

    auto* wolf_link = WolfLinkMgr::instance();
    auto* amiibo = AmiiboMgr::instance();
    auto* gdt = ksys::gdt::Manager::instance();
    if (!wolf_link || !amiibo || !gdt) {
        ui::showInfoOverlay(15);
        setFailed();
        return;
    }

    AmiiboInfo info;
    const AmiiboInfo& src = AmiiboMgr::instance()->_148.mInfo;
    info._0 = src._0;
    info._4 = src._4;
    memcpy(&info._8, &src._8, sizeof(info._8));
    info.mName = src.mName;

    s32 value = s32(info._8._100);
    if (value == 0)
        setFlag(Flag::_4);
    else
        value = info._8._12;

    f32 hearts = 0.0f;
    if (value >= 0)
        hearts = f32(sead::Mathi::min(value, 80));

    if (!gdt->setBool(true, sWolfLink_HasBeenUsed)) {
        ui::showInfoOverlay(25);
        setFailed();
    }

    const s32 count = s32(hearts);

    if (AmiiboMgr::instance()->oneDayHasPassed()) {
        if (gdt->resetS32(sWolfLink_CurrentLife) && gdt->resetS32(sWolfLink_MaxLife) &&
            gdt->resetS32(sWolfLink_LastRecordedHearts) && gdt->resetVec3f(sWolfLink_CurrentPos) &&
            gdt->resetStr64(sWolfLink_TodayFirstDetectedUID))
            gdt->resetBool(sWolfLink_DiedToday);
        setFlag(Flag::_7);
        setFlag(Flag::_1);
    } else if (!amiibo->queryHistoryTodayWithWorldMgrCheck(info, 1)) {
        setFlag(Flag::_1);
    }

    if (isFlagOn(Flag::_1)) {
        if (!gdt->setS32(count, sWolfLink_LastRecordedHearts) ||
            !gdt->setBool(false, sWolfLink_DiedToday) ||
            !gdt->setStr64(info.mName.cstr(), sWolfLink_TodayFirstDetectedUID)) {
            ui::showInfoOverlay(25);
            setFailed();
        }
        return;
    }

    const char* uid = nullptr;
    if (!gdt->getParam().get().getStr64(&uid, sWolfLink_TodayFirstDetectedUID)) {
        ui::showInfoOverlay(25);
        setFailed();
        return;
    }

    if (info.mName != uid) {
        if (info.mName == sUnk_71024320f8) {
            ui::showInfoOverlay(25);
            setFailed();
            return;
        }
        setFlag(Flag::_6);
    }

    s32 recorded;
    if (!gdt->getParam().get().getS32(&recorded, sWolfLink_LastRecordedHearts)) {
        ui::showInfoOverlay(25);
        setFailed();
        return;
    }

    if (count != recorded && !isFlagOn(Flag::_6)) {
        setFlag(Flag::_2);
        if (!gdt->setS32(count, sWolfLink_LastRecordedHearts) ||
            !gdt->setBool(false, sWolfLink_DiedToday)) {
            ui::showInfoOverlay(25);
            setFailed();
            return;
        }
    }

    if (wolf_link->_60 == 2)
        setFlag(Flag::_0);

    if (isFlagOn(Flag::_2))
        return;

    bool died = false;
    if (!gdt->getParam().get().getBool(&died, sWolfLink_DiedToday) || !died)
        return;

    setFlag(Flag::_3);
}

// NON_MATCHING: the five flag tests differ only in the commutative `and` operand order (ours puts the
// mask first). The natural isOnBit form also loads _5c before the mask; a one-use mask local fixes that
// scheduling but not the operand order.
void WolfLinkAmiibo::sub_71006013D4() {
    if (!AmiiboMgr::instance() || !ksys::gdt::Manager::instance()) {
        ui::showInfoOverlay(15);
        setFailed();
        return;
    }

    if (isFlagOn(Flag::_5)) {
        ui::showInfoOverlay(26);
        setFailed();
        return;
    }

    if (isFlagOn(Flag::_0) && !isFlagOn(Flag::_2)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_50, "TargetPos", -1);
        changeChild("ワープ", &pack);
        return;
    }

    if (isFlagOn(Flag::_1)) {
        sub_7100601594();
        return;
    }

    if (isFlagOn(Flag::_3)) {
        ui::showInfoOverlay(25);
        setFailed();
        return;
    }

    sub_7100601594();
}

void WolfLinkAmiibo::sub_7100601594() {
    ksys::act::ai::InlineParamPack pack;
    pack.addInt(_5c.getDirect(), "SpawnFlags", -1);
    pack.addVec3(_50, "TargetPos", -1);
    changeChild("登録", &pack);
}

void WolfLinkAmiibo::loadParams_() {
    getStaticParam(&mAreaSearchCharacterRadius_s, "AreaSearchCharacterRadius");
    getStaticParam(&mAreaThreshold_s, "AreaThreshold");
    getStaticParam(&mAreaSearchRadius_s, "AreaSearchRadius");
}

}  // namespace uking::ai
