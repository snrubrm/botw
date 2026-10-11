#include "aal/aalCurveXml.h"
#include "aal/aalAttenuationXml.h"
#include "aal/aalXmlUtil.h"
#include <prim/seadXmlDocument.h>
#include <prim/seadXmlElement.h>

namespace aal {

// 0x7100BB3F8C
RollOffCurveXmlReader::RollOffCurveXmlReader(const sead::SafeString& category,
                                           const sead::SafeString& path, sead::Heap* heap) {
    mValid = loadSettingByXml_(category, path, heap);
}

// 0x7100BB423C / 0x7100BB4240
RollOffCurveXmlReader::~RollOffCurveXmlReader() {}

// 0x7100BB5B38
UnitDistanceCurveXmlReader::UnitDistanceCurveXmlReader(const sead::SafeString& category,
                                                     const sead::SafeString& path,
                                                     sead::Heap* heap) {
    mValid = loadSettingByXml_(category, path, heap);
}

// 0x7100BB5DEC / 0x7100BB5DF0
UnitDistanceCurveXmlReader::~UnitDistanceCurveXmlReader() {}

// 0x7100BB4244
RollOffCurveXmlWriter::RollOffCurveXmlWriter(sead::XmlDocument* document) : mDocument(document) {}

// 0x7100BB5DF4
UnitDistanceCurveXmlWriter::UnitDistanceCurveXmlWriter(sead::XmlDocument* document) : mDocument(document) {}

// NON_MATCHING: enum dispatch and string construction are grouped differently.
void RollOffCurveXmlWriter::write(const RollOffCurve& curve, sead::Heap* heap) {
    sead::XmlElement* root = mDocument->getRoot();
    root->setName("RollOffCurve");
    for (s32 index = 0; index < AttenuationXml::RollOffCurveElmType::size(); ++index) {
        AttenuationXml::RollOffCurveElmType type(index);
        const sead::SafeString name = type.text();
        f32 value;
        switch (type.value()) {
        case AttenuationXml::RollOffCurveElmType::RollOffModel:
            XmlUtil::addString(root, name, curve.mModel.text(), heap);
            continue;
        case AttenuationXml::RollOffCurveElmType::RefDistance:
            value = curve.mRefDistance;
            break;
        case AttenuationXml::RollOffCurveElmType::MaxDistance:
            value = curve.mMaxDistance;
            break;
        case AttenuationXml::RollOffCurveElmType::RollOffFactor:
            value = curve.mRollOffFactor;
            break;
        case AttenuationXml::RollOffCurveElmType::StartValue:
            value = curve.mVolumeScale;
            break;
        case AttenuationXml::RollOffCurveElmType::IsIncreaseMode:
            XmlUtil::addBool(root, name, curve.mFlipped, heap);
            continue;
        case AttenuationXml::RollOffCurveElmType::CullingStartDistance:
            value = curve.getCullingStartDistance();
            break;
        default:
            continue;
        }
        XmlUtil::addF32(root, name, value, heap);
    }
}

// NON_MATCHING: enum dispatch and string construction are grouped differently.
void UnitDistanceCurveXmlWriter::write(const UnitDistanceCurve& curve, sead::Heap* heap) {
    sead::XmlElement* root = mDocument->getRoot();
    root->setName("UnitDistanceCurve");
    for (s32 index = 0; index < AttenuationXml::UnitDistanceCurveElmType::size(); ++index) {
        AttenuationXml::UnitDistanceCurveElmType type(index);
        const sead::SafeString name = type.text();
        f32 value;
        switch (type.value()) {
        case AttenuationXml::UnitDistanceCurveElmType::CurveType:
            XmlUtil::addString(root, name, curve.mCurveType.text(), heap);
            continue;
        case AttenuationXml::UnitDistanceCurveElmType::StartValue:
            value = curve.mStartValue;
            break;
        case AttenuationXml::UnitDistanceCurveElmType::EndValue:
            value = curve.mEndValue;
            break;
        case AttenuationXml::UnitDistanceCurveElmType::HoldDistance:
            value = curve.mHoldDistance;
            break;
        case AttenuationXml::UnitDistanceCurveElmType::UnitDistance:
            value = curve.mUnitDistance;
            break;
        case AttenuationXml::UnitDistanceCurveElmType::DecayRatio:
            value = curve.mDecayRatio;
            break;
        case AttenuationXml::UnitDistanceCurveElmType::CullingStartDistance:
            value = curve.getCullingStartDistance();
            break;
        default:
            continue;
        }
        XmlUtil::addF32(root, name, value, heap);
    }
}

}  // namespace aal
