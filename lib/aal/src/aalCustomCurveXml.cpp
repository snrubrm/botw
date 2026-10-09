#include "aal/aalCustomCurveXml.h"

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

}  // namespace aal
