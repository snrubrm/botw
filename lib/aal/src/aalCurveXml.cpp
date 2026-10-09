#include "aal/aalCurveXml.h"

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

}  // namespace aal
