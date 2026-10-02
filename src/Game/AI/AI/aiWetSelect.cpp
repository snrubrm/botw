#include "Game/AI/AI/aiWetSelect.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::ai {

WetSelect::WetSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WetSelect::~WetSelect() = default;

bool WetSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WetSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* chemical = mActor->getChemicalStuff();
    if (chemical) {
        const f32 wet = (chemical->_c & 0x1000000) ? 0.0f : chemical->_190;
        if (!(wet < *mWetRateThreashold_s)) {
            changeChild("濡れ", params);
            return;
        }
    }
    changeChild("乾燥", params);
}

void WetSelect::calc_() {}

void WetSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WetSelect::loadParams_() {
    getStaticParam(&mWetRateThreashold_s, "WetRateThreashold");
}

}  // namespace uking::ai
