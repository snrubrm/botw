#include "Game/gameAmiiboMgr.h"
#include <nn/time.h>
#include <time/seadDateTime.h>
#include "Game/AI/aiXlinkHandle.h"
#include "Game/gameNFP.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Physics/RigidBody/Shape/Cylinder/physCylinderRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Cylinder/physCylinderShape.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"
#include "KingSystem/World/worldManager.h"

// Declarations of nn::time functions that lib/NintendoSDK lacks (PLT imports in the original).
namespace nn::time {
struct SteadyClockTimePoint {
    s64 value;
    u8 clockSourceId[16];
};
class StandardSteadyClock {
public:
    static Result GetCurrentTimePoint(SteadyClockTimePoint* out);
};
Result GetSpanBetween(s64* out_seconds, const SteadyClockTimePoint& from,
                      const SteadyClockTimePoint& to);
Result Finalize();
}  // namespace nn::time

namespace uking {

// TU-local statics. In the original they are part of one merged block of the TU's statics based at
// 0x71025bf390 (0x71025bf3b8 = block + 0x28, 0x71025bf500 = +0x170, 0x71025bf518 = +0x188; the rest
// of the block, set up by the static initialiser sinitAmiiboMgrDates 0x710064c550, is not known), so
// createInstance, the constructor, the destructors, init and oneDayHasPassed address them
// differently from the original (one `add` more / fewer): NON_MATCHING (m) for those.
static sead::DateTime sUnk_71025bf3b8;
// Set by the TU's static initialiser (sinitAmiiboMgrDates, not decompiled: the index of the amiibo id
// 0x24f in the amiibo id enum table).
static s32 sUnk_71025bf500;
static nn::time::SteadyClockTimePoint sUnk_71025bf518;

// Initialised (non-const) data at 0x710243b7a0: the radius of the marker cylinder (AmiiboMgr::init).
static f32 sUnk_710243b7a0 = 2.0f;

// NON_MATCHING: createInstance (inlined constructor) references sUnk_71025bf500 through the merged
// statics block, see above.
SEAD_SINGLETON_DISPOSER_IMPL(AmiiboMgr)

namespace {
// The current date as yyyymmdd (the value of the AmiiboLastTouchDate flag).
s32 getTodayNumber() {
    sead::DateTime date;
    date.setNow();
    sead::CalendarTime time;
    date.getCalendarTime(&time);
    const auto d = time.getDate();
    return d.mYear.getValue() * 10000 + d.mMonth.getValueOneOrigin() * 100 + d.mDay.getValue();
}
}  // namespace

AmiiboMgr::AmiiboMgr() {
    NFP::instance()->sub_F45E1C(&sUnk_71025bf500);
}

// NON_MATCHING: the destructors (D1, the two thunks, D0) use sUnk_71025bf500, see above; the two
// vtable address computations are also scheduled in the other order.
AmiiboMgr::~AmiiboMgr() {
    NFP::instance()->sub_F45E24(&sUnk_71025bf500);
    if (_138) {
        delete _138;
        _138 = nullptr;
    }
    if (_140) {
        ksys::phys::QueryContactPointInfo::free(_140);
        _140 = nullptr;
    }
    nn::time::Finalize();
}

// NON_MATCHING: sUnk_71025bf3b8 / sUnk_71025bf518 are addressed through the merged statics block.
bool AmiiboMgr::oneDayHasPassed() {
    {
        nn::time::SteadyClockTimePoint now;
        nn::time::StandardSteadyClock::GetCurrentTimePoint(&now);
        sead::DateTime date;
        date.setNow();

        s64 span;
        const auto result = nn::time::GetSpanBetween(&span, sUnk_71025bf518, now);
        if (span <= 86400 && result.IsSuccess()) {
            // The system clock must agree with the steady clock to within 5 minutes.
            const s64 diff = (sUnk_71025bf3b8 + sead::DateSpan(span)).diff(date).getSpan();
            const s64 abs_diff = diff < 0 ? -diff : diff;
            if (abs_diff > span || abs_diff >= 301)
                return false;
        }
    }

    nn::time::StandardSteadyClock::GetCurrentTimePoint(&sUnk_71025bf518);
    sUnk_71025bf3b8.setNow();

    auto* gdm = ksys::gdt::Manager::instance();
    if (!gdm)
        return false;

    const s32 today = getTodayNumber();
    s32 last_touch = -1;
    return gdm->getParam().get().getS32(&last_touch, "AmiiboLastTouchDate") &&
           today != last_touch;
}

void AmiiboMgr::registerAmiibo(const AmiiboInfo& info) {
    auto* gdm = ksys::gdt::Manager::instance();
    if (!gdm)
        return;

    addAmiiboToHistory(info, "AmiiboTouchHistory", oneDayHasPassed());
    addAmiiboToHistory(info, "AmiiboTouchHistoryTotal", false);
    gdm->setS32(getTodayNumber(), "AmiiboLastTouchDate");
}

int AmiiboMgr::queryHistoryToday(const AmiiboInfo& info, u32 mode) {
    return queryHistory(info, "AmiiboTouchHistory", mode);
}

bool AmiiboMgr::queryHistoryTodayWithWorldMgrCheck(const AmiiboInfo& info, u32 mode) {
    if (auto* world = ksys::world::Manager::instance(); world && world->isDemo())
        return false;
    return queryHistoryToday(info, mode) > 0;
}

int AmiiboMgr::queryHistoryTotal(const AmiiboInfo& info, u32 mode) {
    return queryHistory(info, "AmiiboTouchHistoryTotal", mode);
}

bool AmiiboMgr::guaranteedBigHits() const {
    return false;
}

bool AmiiboMgr::guaranteedGreatHits() const {
    return false;
}

bool AmiiboMgr::guaranteedEpona() const {
    return false;
}

bool AmiiboMgr::noAmiiboUseLimit() const {
    return false;
}

// NON_MATCHING: the statics are addressed through the merged statics block; the original also loads
// the cylinder radius from the initialised data at 0x710243b7a0 (a non-const TU-local float, clang
// folds the never-written static here), and stores the vertex z coordinates earlier.
bool AmiiboMgr::init(sead::Heap* heap) {
    nn::time::Initialize();
    nn::time::StandardSteadyClock::GetCurrentTimePoint(&sUnk_71025bf518);
    sUnk_71025bf3b8.setNow();
    _134 &= ~0x40;

    // The marker collision: a cylinder around the amiibo marker position.
    ksys::phys::CylinderParam param;
    param.vertex_a = {0, 0, 0};
    param.vertex_b = {0, 0.1f, 0};
    param.radius = sUnk_710243b7a0;
    param.toi = true;
    param.contact_layer = ksys::phys::ContactLayer::EntityGroundObject;
    param.motion_type = ksys::phys::MotionType::Keyframed;
    param.mass = 1.0f;
    _138 = ksys::phys::CylinderRigidBody::make(&param, heap);
    if (!_138)
        return false;

    _140 = ksys::phys::QueryContactPointInfo::make(heap, 0x100, "AmiiboMgr", 0, 0);
    _140->subscribeLayer(ksys::phys::ContactLayer::EntityObject);
    _140->subscribeLayer(ksys::phys::ContactLayer::EntityGroundObject);
    _140->subscribeLayer(ksys::phys::ContactLayer::EntityGround);
    _140->subscribeLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    _140->subscribeLayer(ksys::phys::ContactLayer::EntityTree);
    return true;
}

void AmiiboMgr::sub_7100649F94() {
    _b0.fadeXLink();
    _a8 = 0;
    _134 &= ~2;
    _90.set(sead::Vector3f::zero);
    xlink::fade(_2b8, -1);
}

void AmiiboMgr::sub_710064A0A0() {
    if ((_134 & 5) == 5) {
        if (NFP::instance()->sub_F45DC8()) {
            _134 &= ~0x30;
            return;
        }
        if ((_134 & 0x10) && NFP::instance()->sub_F45DFC())
            return;
        NFP::instance()->sub_F45CF0();
        _134 |= 0x10;
    } else {
        if (NFP::instance()->returnFalse())
            return;
        if (!NFP::instance()->sub_F45DC8()) {
            _134 &= ~0x30;
            return;
        }
        if ((_134 & 0x20) && NFP::instance()->sub_F45DFC())
            return;
        NFP::instance()->sub_F45D5C();
        _134 |= 0x20;
    }
}

bool AmiiboMgr::isAmiiboAllowed() {
    if (auto* gdm = ksys::gdt::Manager::instance()) {
        bool flag = false;
        gdm->getParam().get().getBool(&flag, "IsPlayed_Demo146_0");
        if (flag)
            return false;
        gdm->getParam().get().getBool(&flag, "IsPlayed_Demo142_0");
        if (flag)
            return false;
        gdm->getParam().get().getBool(&flag, "IsPlayed_Demo141_0");
        if (flag)
            return false;
        gdm->getParam().get().getBool(&flag, "IsPlayed_Demo141_1");
        if (flag)
            return false;
        gdm->getParam().get().getBool(&flag, "IsPlayed_Demo141_2");
        if (flag)
            return false;
        gdm->getParam().get().getBool(&flag, "IsPlayed_Demo141_3");
        if (flag)
            return false;
        gdm->getParam().get().getBool(&flag, "NakedIsland_ProhibitAmiibo");
        if (flag)
            return false;
    }
    return (_134 >> 6) & 1;
}

// NON_MATCHING: the original shares one `result = false` exit for the five prohibition checks and
// keeps the constant true in a register across the first call (the loop form is the closest tried).
bool AmiiboMgr::isMotorcycleAllowed() {
    if (auto* gdm = ksys::gdt::Manager::instance()) {
        bool flag = false;
        gdm->getParam().get().getBool(&flag, "IsPlayed_Demo146_0");
        if (flag)
            return true;
        for (const char* name : {"IsPlayed_Demo142_0", "IsPlayed_Demo141_0", "IsPlayed_Demo141_1",
                                 "IsPlayed_Demo141_2", "IsPlayed_Demo141_3"}) {
            gdm->getParam().get().getBool(&flag, name);
            if (flag)
                return false;
        }
        gdm->getParam().get().getBool(&flag, "NakedIsland_ProhibitAmiibo");
        if (flag)
            return true;
    }
    return (_134 >> 6) & 1;
}

}  // namespace uking
