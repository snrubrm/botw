#include "Game/AI/Behavior/behaviorGanonBeastFirstMessage.h"
#include "Game/AI/aiUnk_71025b2aa8.h"

namespace uking::behavior {

GanonBeastFirstMessage::GanonBeastFirstMessage(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void GanonBeastFirstMessage::m9() {
    if (*mOnce_s && _b0 >= 2)
        _b0 = 5;
    if (_b4 && _b0 <= 4) {
        --*mGanonBeastVoiceSequenceCount_a;
        _b4 = false;
    }
}

void GanonBeastFirstMessage::loadParams() {
    getStaticParam(&mCloseOption_s, "CloseOption");
    getStaticParam(&mDelayTimer_s, "DelayTimer");
    getStaticParam(&mType_s, "Type");
    getStaticParam(&mInterval_s, "Interval");
    getStaticParam(&mOnce_s, "Once");
    getStaticParam(&mmstxtName_s, "mstxtName");
    getStaticParam(&mlabelName_s, "labelName");
    getStaticParam(&mlabelName2_s, "labelName2");
    getStaticParam(&mlabelName3_s, "labelName3");
    getAITreeVariable(&mGanonBeastVoiceSequenceCount_a, "GanonBeastVoiceSequenceCount");
    getAITreeVariable(&mSimpleDialogUnit_a, "SimpleDialogUnit");
}

GanonBeastFirstMessage::~GanonBeastFirstMessage() {
    if (_a0) {
        auto* unit = sead::DynamicCast<Unk_71025b2aa8>(*_a0);
        if (unit && unit->_20 > 0 && --unit->_20 <= 0) {
            *_a0 = nullptr;
            delete unit;
        }
        _a0 = nullptr;
    }
}

}  // namespace uking::behavior
