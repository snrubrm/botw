#include "Game/AI/AI/aiCameraEventTalk.h"
#include <algorithm>
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

// NON_MATCHING: the original stores _5c and _60.._63 with one stp of two words (one 8-byte store here)
CameraEventTalk::CameraEventTalk(const InitArg& arg) : CameraEvent(arg) {}

f32 CameraEventTalk::m45() {
    return 0.0f;
}

bool CameraEventTalk::m46() {
    return false;
}

bool CameraEventTalk::m48() {
    return m47() == 0.0f;
}

void CameraEventTalk::m50() {}

// NON_MATCHING: _58 = min(m44(), 1) is `cmp #2; csinc` in the original, `cmp #0; cset` here
void CameraEventTalk::m40(ksys::act::ai::InlineParamPack* params) {
    _58 = std::min(m44(), 1u);
    m49();
    _48.reset();
    _5c = 2;
    _60.set(1);
    _61.makeAllZero();
    _62 = 0;
    _63 = 0;

    auto* camera = getCamera();
    if (!camera)
        return;

    camera->_860.sub_710079BD2C();
    if (!camera->_860._230.hasProc())
        m50();
}

// NON_MATCHING: the original loads _60 once for both checks and lays out the stick check differently
void CameraEventTalk::m41() {
    sub_710078E964();

    const s32 prev = _5c;
    if (prev == 2)
        _5c = !m46();
    else if (_60.isOn(1))
        _5c = 0;

    {
        sead::Vector2f stick = sead::Vector2f::zero;
        sub_7100924F08(&stick);
        if (stick.x != 0 || stick.y != 0)
            _5c = 1;
    }

    const s32 mode = _5c;
    if (_62 == 0 || _60.isOn(1)) {
        if (_62 != 0xff)
            ++_62;
    }

    if (mode != prev || _60.isOn(1)) {
        switch (mode) {
        case 0: {
            ksys::act::ai::InlineParamPack params;
            params.addFloat(m45(), "HeightOffset", -1);
            params.addBool(!getCurrentChild() && m48(), "NoConnect", -1);
            m51(&params);
            changeChild("オート", &params);
            break;
        }
        case 1: {
            ksys::act::ai::InlineParamPack params;
            params.addFloat(m45(), "HeightOffset", -1);
            params.addFloat(m47(), "Count", -1);
            params.addBool(!getCurrentChild() && m48(), "NoConnect", -1);
            m52(&params);
            changeChild("マニュアル", &params);
            break;
        }
        }
        _60.reset(1);
    }

    if (auto* child = getCurrentChild()) {
        if (child->isFinished())
            setFinished();
        else if (child->isFailed())
            setFailed();
    }
}

void CameraEventTalk::sub_710078E964() {
    auto* camera = getCamera();
    if (!camera)
        return;

    auto& link = camera->_860._230;
    if (!link.hasProc() || link == _48)
        return;

    _48 = link;
    if (_58)
        _60.set(1);
    if (!_60.isOn(1))
        return;

    camera->_860.sub_710079BC98();
    _61.set(1);
    if (_63 != 0xff)
        ++_63;
}

bool CameraEventTalk::isFinished() const {
    if (mFlags.isOn(Flag::Finished))
        return true;
    if (auto* child = getCurrentChild()) {
        if (child->isFinished())
            return true;
        if (child->isFailed())
            return false;
    }
    return false;
}

}  // namespace uking::ai
