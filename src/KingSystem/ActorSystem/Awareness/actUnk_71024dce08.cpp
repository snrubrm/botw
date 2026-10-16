#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessDefs.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldWeatherMgr.h"

namespace ksys::act {

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

}  // namespace ksys::act

// NON_MATCHING: placeholder destructor; the original (0x7100d81f74) also destroys members or bases
// this class does not declare yet.
Unk_71024dcf48::~Unk_71024dcf48() = default;
