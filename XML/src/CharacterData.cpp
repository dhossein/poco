//
// CharacterData.cpp
//
// $Id: //poco/1.2/XML/src/CharacterData.cpp#1 $
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


#include "Poco/DOM/CharacterData.h"
#include "Poco/DOM/DOMException.h"
#include "Poco/String.h"


namespace Poco {
namespace XML {


CharacterData::CharacterData(Document* pOwnerDocument, const XMLString& data): 
	AbstractNode(pOwnerDocument),
	_data(data)
{
}


CharacterData::CharacterData(Document* pOwnerDocument, const CharacterData& data): 
	AbstractNode(pOwnerDocument, data),
	_data(data._data)
{
}


CharacterData::~CharacterData()
{
}


void CharacterData::setData(const XMLString& data)
{
	XMLString oldData = getData();
	_data = data;
	if (events()) dispatchCharacterDataModified(oldData, _data);
}


XMLString CharacterData::substringData(unsigned long offset, unsigned long count) const
{
	if (offset >= _data.length())
		throw DOMException(DOMException::INDEX_SIZE_ERR);

	return _data.substr(offset, count);
}


void CharacterData::appendData(const XMLString& arg)
{
	XMLString oldData = _data;
	_data.append(arg);
	if (events()) dispatchCharacterDataModified(oldData, _data);
}


void CharacterData::insertData(unsigned long offset, const XMLString& arg)
{
	if (offset > _data.length())
		throw DOMException(DOMException::INDEX_SIZE_ERR);

	XMLString oldData = _data;
	_data.insert(offset, arg);
	if (events()) dispatchCharacterDataModified(oldData, _data);
}


void CharacterData::deleteData(unsigned long offset, unsigned long count)
{
	if (offset >= _data.length())
		throw DOMException(DOMException::INDEX_SIZE_ERR);

	XMLString oldData = _data;
	_data.replace(offset, count, EMPTY_STRING);
	if (events()) dispatchCharacterDataModified(oldData, _data);
}


void CharacterData::replaceData(unsigned long offset, unsigned long count, const XMLString& arg)
{
	if (offset >= _data.length())
		throw DOMException(DOMException::INDEX_SIZE_ERR);

	XMLString oldData = _data;
	_data.replace(offset, count, arg);
	if (events()) dispatchCharacterDataModified(oldData, _data);
}


const XMLString& CharacterData::getNodeValue() const
{
	return _data;
}


void CharacterData::setNodeValue(const XMLString& value)
{
	setData(value);
}


XMLString CharacterData::trimmedData() const
{
	return Poco::trim(_data);
}


} } // namespace Poco::XML
