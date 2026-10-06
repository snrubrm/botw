#pragma once

#include "aal/aalFxParamSetter.h"

namespace aal {

class FxDelayParamSetter : public FxParamSetter {
    SEAD_RTTI_OVERRIDE(FxDelayParamSetter, FxParamSetter)
public:
    FxDelayParamSetter();
    ~FxDelayParamSetter() override = default;

    void resetImpl_() override;
    void setupByXmlDocument(sead::XmlDocument* document) override;
    void save() override {}
    void load() override {}

    void setDelay(f32 delay);
    void setFeedback(f32 feedback);
    void setOutGain(f32 gain, f32 gain2);
    void setLpf(f32 lpf);

private:
    f32 mDelay = 0.1f;
    f32 mFeedback = 0.4f;
    f32 mOutGain = 1.0f;
    f32 mOutGain2;
    f32 mLpf = 1.0f;
};

}  // namespace aal
