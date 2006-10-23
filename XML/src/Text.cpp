//
// Text.cpp
//
// $Id: //poco/1.2/XML/src/Text.cpp#1 $
//
// Library: XML
// Package: DOM
// Module:  DOM
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "Poco/DOM/Text.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/DOMException.h"


namespace Poco {
namespace XML {


const XMLString Text::NODE_NAME = toXMLString("#text");


Text::Text(Document* pOwnerDocument, const XMLString& data): 
	CharacterData(pOwnerDocument, data)
{
}


Text::Text(Document* pOwnerDocument, const Text& text): 
	CharacterData(pOwnerDocument, text)
{
}


Text::~Text()
{
}


Text* Text::splitText(unsigned long offset)
{
	Node* pParent = parentNode();
	if (!pParent) throw DOMException(DOMException::HIERARCHY_REQUEST_ERR);
	int n = length() - offset;
	Text* pNew = ownerDocument()->createTextNode(substringData(offset, n));
	deleteData(offset, n);
	pParent->insertBefore(pNew, nextSibling())->release();
	return pNew;
}


const XMLString& Text::nodeName() const
{
	return NODE_NAME;
}


unsigned short Text::nodeType() const
{
	return Node::TEXT_NODE;
}


XMLString Text::innerText() const
{
	return nodeValue();
}


Node* Text::copyNode(bool deep, Document* pOwnerDocument) const
{
	return new Text(pOwnerDocument, *this);
}


} } // namespace Poco::XML
