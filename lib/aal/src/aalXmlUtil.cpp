#include "aal/aalXmlUtil.h"

#include <prim/seadXmlDocument.h>
#include <prim/seadXmlElement.h>
#include <prim/seadXmlUtil.h>
#include <stream/seadRamStream.h>

namespace aal {

sead::XmlElement* XmlUtil::addChild(sead::XmlElement* element, const sead::SafeString& name,
                                   sead::Heap* heap) {
    return sead::XmlUtil::createBackSiblingAndSetupElement(element, name,
                                                          sead::SafeString::cEmptyString, heap);
}

sead::XmlElement* XmlUtil::addString(sead::XmlElement* element, const sead::SafeString& name,
                                    const sead::SafeString& value, sead::Heap* heap) {
    return sead::XmlUtil::createBackSiblingAndSetupElement(element, name, value, heap);
}

void XmlUtil::addF32(sead::XmlElement* element, const sead::SafeString& name, f32 value,
                     sead::Heap* heap) {
    sead::FixedSafeString<64> content;
    content.format("%f", value);
    sead::XmlUtil::createBackSiblingAndSetupElement(element, name, content, heap);
}

void XmlUtil::addBool(sead::XmlElement* element, const sead::SafeString& name, bool value,
                      sead::Heap* heap) {
    sead::FixedSafeString<64> content;
    content.format("%s", value ? "true" : "false");
    sead::XmlUtil::createBackSiblingAndSetupElement(element, name, content, heap);
}

sead::XmlDocument* XmlUtil::createTextDocument(void* data, u32 size, sead::Heap* heap) {
    sead::RamReadStream stream(data, size, sead::Stream::Modes::Binary);
    return sead::XmlDocument::create(&stream, heap, false, 0x4000);
}

sead::SafeString XmlUtil::getElementContentString(sead::XmlElement* element,
                                                const sead::SafeString& path) {
    const auto* child = element->findElementByAbsolutePath_(path);
    if (child)
        return child->getContentString();
    return sead::SafeString::cEmptyString;
}

}  // namespace aal
