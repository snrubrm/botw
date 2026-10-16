#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/Awareness/actAwarenessRequest.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessDefs.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldWeatherMgr.h"

namespace ksys::act {

// NON_MATCHING: ours inlines ObjArray::freeBuffer (the original calls it, 0x7100d78c98, after a buffer check).
Unk_71024dce08::~Unk_71024dce08() {
    _8.freeBuffer();
    _28.freeBuffer();
}

// 2026-10-07: the sensor clear method calls entry destruction out of line.
bool Unk_71024dce08::m7() { return true; }
void Unk_71024dce08::m8() {}
void Unk_71024dce08::m9() {}
bool Unk_71024dce08::m10() { return false; }
bool Unk_71024dce08::m11() { return true; }
void Unk_71024dce08::m13() {}
sead::BitFlag8* Unk_71024dce08::m16() { return nullptr; }
void Unk_71024dce08::m17() { _8.clear(); }

// NON_MATCHING: the original keeps the result in s8 on every path.
// NON_MATCHING: scheduling (the original converts the count after the subtraction).
s32 Unk_71024dce08::m15(f32 a, f32 b) {
    const s32 count = _48 >= 0 ? _48 : _40;
    if (count < 1)
        return 0;
    const f32 ratio = sead::Mathf::clamp(a * 2, 0.0f, 1.0f) * b / (m14() * _4c) - 0.3f;
    const s32 min = s32(count * std::max(ratio, 0.0f));
    if (min < count)
        return sead::GlobalRandom::instance()->getU32(count - min) + min;
    return count;
}

f32 Unk_71024dce08::sub_7100D8010C() const {
    if (!_51) {
        if (auto* manager = world::Manager::instance()) {
            if (auto* weather_mgr = manager->getWeatherMgr()) {
                const auto weather = weather_mgr->getWeather();
                if (u32(weather) <= 8)
                    return _4c * sub_7100D7A93C(_38, u32(weather));
            }
        }
    }
    return _4c;
}

sead::BitFlag8* Unk_71024dcea8::m16() {
    return &_68;
}

f32 Unk_71024dcd68::m14() {
    return _54;
}

// NON_MATCHING: ours inlines sub_7100D8010C (as Unk_71024dd070::m4).
bool Unk_71024dcd68::m4(Unk_71023e2708* request) {
    auto* req = sead::DynamicCast<Unk_71023e2750>(request);
    if (!req)
        return false;
    req->params = _58;
    req->_8 = _54 * sub_7100D8010C();
    return true;
}

// NON_MATCHING: the original copies 0x54-0x6c as 8 + 8 + 4 + 4 bytes; ours copies _54 and the
// block separately (exact member split unknown).
bool Unk_71024dcd68::m5(Unk_71023e2708* request) {
    auto* req = sead::DynamicCast<Unk_71023e2750>(request);
    if (!req)
        return false;
    req->_8 = _54;
    req->params = _58;
    return true;
}

// NON_MATCHING: as m5.
bool Unk_71024dcd68::m6(Unk_71023e2708* request) {
    auto* req = sead::DynamicCast<Unk_71023e2750>(request);
    if (!req)
        return false;
    _54 = req->_8;
    _58 = req->params;
    return true;
}

f32 Unk_71024dcfd0::m14() {
    return _54;
}

f32 Unk_71024dd070::m14() {
    return _54;
}

// NON_MATCHING: ours inlines sub_7100D8010C (it has more callers in the original TU).
bool Unk_71024dd070::m4(Unk_71023e2708* request) {
    auto* req = sead::DynamicCast<Unk_71023e2780>(request);
    if (!req)
        return false;
    req->_8 = _54 * sub_7100D8010C();
    return true;
}

bool Unk_71024dd070::m5(Unk_71023e2708* request) {
    auto* req = sead::DynamicCast<Unk_71023e2780>(request);
    if (!req)
        return false;
    req->_8 = _54;
    return true;
}

bool Unk_71024dd070::m6(Unk_71023e2708* request) {
    auto* req = sead::DynamicCast<Unk_71023e2780>(request);
    if (!req)
        return false;
    _54 = req->_8;
    return true;
}

}  // namespace ksys::act

// NON_MATCHING: placeholder destructor; the original (0x7100d81f74) also destroys members or bases
// this class does not declare yet.
Unk_71024dcf48::~Unk_71024dcf48() = default;
