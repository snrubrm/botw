#include "aal/aalFxReverbI3DL2InitializeArg.h"
#include "aal/aalFxReverbI3DL2ParamSetter.h"

#include <prim/seadStringUtil.h>
#include <prim/seadXmlDocument.h>
#include <prim/seadXmlElement.h>
#include "aal/aalXmlUtil.h"

namespace aal {

FxReverbI3DL2InitializeArg::FxReverbI3DL2InitializeArg()
    : mMaxReflectionsDelay(0.1f), mMaxReverbDelay(0.1f), mMinDiffusion(50.0f),
      mMaxEarlyReflectionDelay(0.3f), mDelayTableIndex(3) {}

FxReverbI3DL2ParamSetter::FxReverbI3DL2ParamSetter() {
    reset();
}

void FxReverbI3DL2ParamSetter::resetImpl_() {
    mRoom = -1000;
    mRoomHf = 0;
    mDecayTime = 1.0f;
    mDecayHfRatio = 0.5f;
    mReflections = -1000;
    mReflectionsDelay = 0.02f;
    mReverb = -1000;
    mReverbDelay = 0.04f;
    mDiffusion = 100.0f;
    mDensity = 100.0f;
    mHfReference = 5000.0f;
    mRoomFadeTime = 0.0f;
    mEarlyReflectionDelay = 0.03f;
    mEarlyReflectionFeedback = 0.0f;
}

void FxReverbI3DL2ParamSetter::setRoom(s32 room, f32 fade_time) {
    mRoom = room;
    mRoomFadeTime = fade_time;
    setModifiedFlagBit_(0);
}

void FxReverbI3DL2ParamSetter::setRoomHf(s32 room_hf) {
    mRoomHf = room_hf;
    setModifiedFlagBit_(1);
}

void FxReverbI3DL2ParamSetter::setDecayTime(f32 time) {
    mDecayTime = time;
    setModifiedFlagBit_(2);
}

void FxReverbI3DL2ParamSetter::setReverb(s32 reverb) {
    mReverb = reverb;
    setModifiedFlagBit_(6);
}

void FxReverbI3DL2ParamSetter::setEarlyReflectionFeedback(f32 feedback) {
    mEarlyReflectionFeedback = feedback;
    setModifiedFlagBit_(12);
}

void FxReverbI3DL2ParamSetter::setupByXmlDocument(sead::XmlDocument* document) {
    auto* root = document->getRoot();
    if (!root || root->getName() != "FxReverbI3DL2ExpParam")
        return;

    {
        const auto text = XmlUtil::getElementContentString(root, "Room");
        s32 value;
        if (!text.isEmpty() && sead::StringUtil::tryParseS32(&value, text, sead::StringUtil::CardinalNumber::BaseAuto)) {
            setRoom(value, 0.0f);
        }
    }

    {
        const auto text = XmlUtil::getElementContentString(root, "RoomHf");
        s32 value;
        if (!text.isEmpty() && sead::StringUtil::tryParseS32(&value, text, sead::StringUtil::CardinalNumber::BaseAuto)) {
            setRoomHf(value);
        }
    }

    {
        const auto text = XmlUtil::getElementContentString(root, "DecayTime");
        f32 value;
        if (!text.isEmpty() && sead::StringUtil::tryParseF32(&value, text)) {
            setDecayTime(value);
        }
    }

    {
        const auto text = XmlUtil::getElementContentString(root, "DecayHfRatio");
        f32 value;
        if (!text.isEmpty() && sead::StringUtil::tryParseF32(&value, text)) {
            mDecayHfRatio = value;
            setModifiedFlagBit_(3);
        }
    }

    {
        const auto text = XmlUtil::getElementContentString(root, "Reflections");
        s32 value;
        if (!text.isEmpty() && sead::StringUtil::tryParseS32(&value, text, sead::StringUtil::CardinalNumber::BaseAuto)) {
            mReflections = value;
            setModifiedFlagBit_(4);
        }
    }

    {
        const auto text = XmlUtil::getElementContentString(root, "ReflectionsDelay");
        f32 value;
        if (!text.isEmpty() && sead::StringUtil::tryParseF32(&value, text)) {
            mReflectionsDelay = value;
            setModifiedFlagBit_(5);
        }
    }

    {
        const auto text = XmlUtil::getElementContentString(root, "Reverb");
        s32 value;
        if (!text.isEmpty() && sead::StringUtil::tryParseS32(&value, text, sead::StringUtil::CardinalNumber::BaseAuto)) {
            setReverb(value);
        }
    }

    {
        const auto text = XmlUtil::getElementContentString(root, "ReverbDelay");
        f32 value;
        if (!text.isEmpty() && sead::StringUtil::tryParseF32(&value, text)) {
            mReverbDelay = value;
            setModifiedFlagBit_(7);
        }
    }

    {
        const auto text = XmlUtil::getElementContentString(root, "Diffusion");
        f32 value;
        if (!text.isEmpty() && sead::StringUtil::tryParseF32(&value, text)) {
            mDiffusion = value;
            setModifiedFlagBit_(8);
        }
    }

    {
        const auto text = XmlUtil::getElementContentString(root, "Density");
        f32 value;
        if (!text.isEmpty() && sead::StringUtil::tryParseF32(&value, text)) {
            mDensity = value;
            setModifiedFlagBit_(9);
        }
    }

    {
        const auto text = XmlUtil::getElementContentString(root, "HfReference");
        f32 value;
        if (!text.isEmpty() && sead::StringUtil::tryParseF32(&value, text)) {
            mHfReference = value;
            setModifiedFlagBit_(10);
        }
    }

    {
        const auto text = XmlUtil::getElementContentString(root, "EarlyReflectionDelay");
        f32 value;
        if (!text.isEmpty() && sead::StringUtil::tryParseF32(&value, text)) {
            mEarlyReflectionDelay = value;
            setModifiedFlagBit_(11);
        }
    }

    {
        const auto text = XmlUtil::getElementContentString(root, "EarlyReflectionFeedback");
        f32 value;
        if (!text.isEmpty() && sead::StringUtil::tryParseF32(&value, text)) {
            setEarlyReflectionFeedback(value);
        }
    }
}

}  // namespace aal
