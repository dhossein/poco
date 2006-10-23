//
// Name.cpp
//
// $Id: //poco/1.2/XML/src/Name.cpp#1 $
//
// Library: XML
// Package: XML
// Module:  Name
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


#include "Poco/XML/Name.h"
#include <algorithm>


namespace Poco {
namespace XML {


const XMLString Name::EMPTY_NAME;


Name::Name()
{
}


Name::Name(const XMLString& qname):
	_qname(qname)
{
}


Name::Name(const XMLString& qname, const XMLString& namespaceURI):
	_qname(qname),
	_namespaceURI(namespaceURI),
	_localName(localName(qname))
{
}


Name::Name(const XMLString& qname, const XMLString& namespaceURI, const XMLString& localName):
	_qname(qname),
	_namespaceURI(namespaceURI),
	_localName(localName)
{
}


Name::Name(const Name& name):
	_qname(name._qname),
	_namespaceURI(name._namespaceURI),
	_localName(name._localName)
{
}

	
Name::~Name()
{
}


Name& Name::operator = (const Name& name)
{
	if (this != &name)
	{
		_qname        = name._qname;
		_namespaceURI = name._namespaceURI;
		_localName    = name._localName;
	}
	return *this;
}


void Name::swap(Name& name)
{
	std::swap(_qname, name._qname);
	std::swap(_namespaceURI, name._namespaceURI);
	std::swap(_localName, name._localName);
}


void Name::assign(const XMLString& qname)
{
	_qname        = qname;
	_namespaceURI.clear();
	_localName.clear();
}


void Name::assign(const XMLString& qname, const XMLString& namespaceURI)
{
	_qname        = qname;
	_namespaceURI = namespaceURI;
	_localName    = localName(qname);
}


void Name::assign(const XMLString& qname, const XMLString& namespaceURI, const XMLString& localName)
{
	_qname        = qname;
	_namespaceURI = namespaceURI;
	_localName    = localName;
}


bool Name::equals(const Name& name) const
{
	return name._namespaceURI == _namespaceURI && name._localName == _localName && name._qname == _qname;
}


bool Name::equals(const XMLString& qname, const XMLString& namespaceURI, const XMLString& localName) const
{
	return _namespaceURI == namespaceURI && _localName == localName && _qname == qname;
}


bool Name::equalsWeakly(const XMLString& qname, const XMLString& namespaceURI, const XMLString& localName) const
{
	return _qname == qname && !qname.empty() || _namespaceURI == namespaceURI && _localName == localName && !_localName.empty();
}


XMLString Name::prefix() const
{
	return prefix(_qname);
}


void Name::split(const XMLString& qname, XMLString& prefix, XMLString& localName)
{
	XMLString::size_type pos = qname.find(':');
	if (pos != XMLString::npos)
	{
		prefix.assign(qname, 0, pos);
		localName.assign(qname, pos + 1, qname.size() - pos - 1);
	}
	else
	{
		prefix.clear();
		localName.assign(qname);
	}
}


XMLString Name::localName(const XMLString& qname)
{
	XMLString::size_type pos = qname.find(':');
	if (pos != XMLString::npos) 
		return XMLString(qname, pos + 1, qname.size() - pos - 1);
	else
		return qname;
}


XMLString Name::prefix(const XMLString& qname)
{
	XMLString::size_type pos = qname.find(':');
	if (pos != XMLString::npos)
		return XMLString(qname, 0, pos);
	else
		return EMPTY_NAME;
}


} } // namespace Poco::XML
