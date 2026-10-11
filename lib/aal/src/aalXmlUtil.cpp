#include "aal/aalXmlUtil.h"

#include <prim/seadXmlDocument.h>
#include <prim/seadXmlElement.h>
#include <stream/seadRamStream.h>

namespace aal {

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
