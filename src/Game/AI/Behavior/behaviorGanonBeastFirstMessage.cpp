#include "Game/AI/Behavior/behaviorGanonBeastFirstMessage.h"
#include "Game/AI/aiUnk_71025b2aa8.h"
#include "KingSystem/System/Timer.h"

namespace uking::behavior {

GanonBeastFirstMessage::GanonBeastFirstMessage(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// NON_MATCHING: the original keeps the second cast's `unit ? unit + 8 : nullptr` as branches (ours uses a csel); everything
// else is identical (same as SimpleAtvUnitOpenSimpleDialog::sub_7100641EB8)
void GanonBeastFirstMessage::sub_7100624048() {
    Unk_71025b2aa8* unit = nullptr;
    if (_a0._0)
        unit = sead::DynamicCast<Unk_71025b2aa8>(*_a0._0);
    if (!unit || unit->mRefCount < 1) {
        _b0 = 5;
        return;
    }
    if (_ac >= 3) {
        _b0 = 4;
        return;
    }

    Unk_71025b2aa8Data::Request request;
    request._0 = &mmstxtName_s;
    switch (_ac) {
    case 2:
        request._8 = &mlabelName3_s;
        break;
    case 1:
        request._8 = &mlabelName2_s;
        break;
    default:
        request._8 = &mlabelName_s;
        break;
    }
    request._10 = *mCloseOption_s;
    request._14 = *mType_s;
    request._18 = _ac == 2 ? 90 : 240;
    _a0.getData()->sub_7100721DE4(&request);
    _b0 = 2;
    ++_ac;
}

// NON_MATCHING: the original keeps &_b0 in x22 (and the DynamicCast guard address in x23) across the calls; the logic and the
// block layout are identical
void GanonBeastFirstMessage::m7() {
    Unk_71025b2aa8* unit = nullptr;
    if (_a0._0)
        unit = sead::DynamicCast<Unk_71025b2aa8>(*_a0._0);
    if (!unit || unit->mRefCount < 1) {
        _b0 = 5;
        return;
    }

    if (_b0 == 1 || _b0 == 3) {
        ksys::Timer::update(&_a8, -1.0f);
        if (_a8 <= 0)
            sub_7100624048();
    } else if (_b0 == 2) {
        if (!_a0.getData()->sub_7100721FB4()) {
            if (*mInterval_s <= 0) {
                sub_7100624048();
            } else {
                _b0 = 3;
                _a8 = *mInterval_s;
            }
        }
    }

    if (_b4 && _b0 == 4) {
        --*mGanonBeastVoiceSequenceCount_a;
        _b4 = false;
    }
}

void GanonBeastFirstMessage::m8() {
    if (_b0 == 5) {
        _b4 = false;
        return;
    }
    ++*mGanonBeastVoiceSequenceCount_a;
    _b4 = true;
    _ac = 0;
    const int delay = *mDelayTimer_s;
    if (delay <= 0) {
        sub_7100624048();
    } else {
        _a8 = delay;
        _b0 = 1;
    }
}

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

GanonBeastFirstMessage::~GanonBeastFirstMessage() = default;

bool GanonBeastFirstMessage::m6(sead::Heap* heap) {
    if (!_a0.acquire(heap, static_cast<Unk_71025afb58**>(mSimpleDialogUnit_a)))
        return false;
    _b0 = 0;
    return true;
}

}  // namespace uking::behavior
