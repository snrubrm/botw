#include "aal/aalCustomCurveXml.h"
#include "aal/aalAttenuationXml.h"
#include "aal/aalXmlUtil.h"
#include <prim/seadXmlDocument.h>
#include <prim/seadXmlElement.h>

namespace aal {

// 0x7100BA8CAC
CustomCurveXmlReader::CustomCurveXmlReader(const sead::SafeString& category,
                                         const sead::SafeString& path, sead::Heap* heap) {
    mSegments.initOffset(offsetof(CustomCurveSegment, mListNode));
    mValid = loadSettingByXml_(category, path, heap);
}

// 0x7100BA8F58 / 0x7100BA8F5C
CustomCurveXmlReader::~CustomCurveXmlReader() {}

// 0x7100BA8F60
f32 CustomCurveXmlReader::getSegmentPos(s32 index) const {
    const CustomCurveSegment* segment = mSegments.nth(index);
    return segment ? segment->mPosition : 0.0f;
}

// 0x7100BA8F9C
f32 CustomCurveXmlReader::getSegmentValue(s32 index) const {
    const CustomCurveSegment* segment = mSegments.nth(index);
    return segment ? segment->mValue : 1.0f;
}

// 0x7100BA8FD8
CustomCurveType CustomCurveXmlReader::getSegmentType(s32 index) const {
    const CustomCurveSegment* segment = mSegments.nth(index);
    return segment ? segment->mType : CustomCurveType(0);
}

// 0x7100BA9018
f32 CustomCurveXmlReader::getSegmentCoef(s32 index) const {
    const CustomCurveSegment* segment = mSegments.nth(index);
    return segment ? segment->mCoefficient : 1.0f;
}

// 0x7100BA9054
CustomCurveXmlWriter::CustomCurveXmlWriter(sead::XmlDocument* document) : mDocument(document) {}

// NON_MATCHING: enum dispatch and string construction are grouped differently.
void CustomCurveXmlWriter::write(const CustomCurve& curve, sead::Heap* heap) {
    sead::XmlElement* root = mDocument->getRoot();
    root->setName("CustomCurve");
    sead::XmlElement* segments = XmlUtil::addChild(root, "Segments", heap);
    for (const auto& segment : curve.mSegments) {
        sead::XmlElement* element = XmlUtil::addChild(segments, "Segment", heap);
        for (s32 index = 0; index < AttenuationXml::CustomCurveSegmentElmType::size(); ++index) {
            AttenuationXml::CustomCurveSegmentElmType type(index);
            const sead::SafeString name = type.text();
            f32 value;
            switch (type.value()) {
            case AttenuationXml::CustomCurveSegmentElmType::Pos:
                value = segment.mPosition;
                break;
            case AttenuationXml::CustomCurveSegmentElmType::Value:
                value = segment.mValue;
                break;
            case AttenuationXml::CustomCurveSegmentElmType::Type:
                XmlUtil::addString(element, name, segment.mType.text(), heap);
                continue;
            case AttenuationXml::CustomCurveSegmentElmType::Coef:
                value = segment.mCoefficient;
                break;
            default:
                continue;
            }
            XmlUtil::addF32(element, name, value, heap);
        }
    }
}

// Host file output is compiled out in the native retail build.
bool CustomCurveXmlWriter::saveToHostFile(const sead::SafeString&, sead::Heap*, bool) {
    return false;
}

}  // namespace aal
