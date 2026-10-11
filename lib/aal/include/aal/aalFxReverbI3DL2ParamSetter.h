#pragma once

#include "aal/aalFxParamSetter.h"

namespace aal {

class FxReverbI3DL2ParamSetter : public FxParamSetter {
    SEAD_RTTI_OVERRIDE(FxReverbI3DL2ParamSetter, FxParamSetter)
public:
    FxReverbI3DL2ParamSetter();

    void resetImpl_() override;
    void setupByXmlDocument(sead::XmlDocument* document) override;
    void save() override {}
    void load() override {}

    void setRoom(s32 room, f32 fade_time);
    void setRoomHf(s32 room_hf);
    void setDecayTime(f32 time);
    void setReverb(s32 reverb);
    void setEarlyReflectionFeedback(f32 feedback);

private:
    // Native XML reader 1051604 independently names these parameter domains;
    // initialize 1051ef0, setupGains_1052958 and updateParam1052bf4 consume them.
    s32 mRoom;
    s32 mRoomHf;
    f32 mDecayTime;
    f32 mDecayHfRatio;
    s32 mReflections;
    f32 mReflectionsDelay;
    s32 mReverb;
    f32 mReverbDelay;
    f32 mDiffusion;
    f32 mDensity;
    f32 mHfReference;
    f32 mRoomFadeTime;
    f32 mEarlyReflectionDelay;
    f32 mEarlyReflectionFeedback;
};
static_assert(sizeof(FxReverbI3DL2ParamSetter) == 0x48, "FxReverbI3DL2ParamSetter size");

}  // namespace aal
