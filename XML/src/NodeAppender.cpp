//
// NodeAppender.cpp
//
// Library: XML
// Package: DOM
// Module:  NodeAppender
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/DOM/NodeAppender.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/DOMException.h"


namespace Poco {
namespace XML {


NodeAppender::NodeAppender(Element::Ptr parent):
	_pParent(parent),
	_pLast(0)
{
	poco_check_ptr (parent);

	_pLast = _pParent->lastChild().unsafeCast<AbstractNode>();
}


NodeAppender::~NodeAppender()
{
}


void NodeAppender::appendChild(Node::Ptr newChild)
{
	poco_check_ptr (newChild);
	poco_assert (_pLast.isNull() || _pLast->_pNext.isNull());

	if (newChild.unsafeCast<AbstractNode>()->_pOwner != _pParent->_pOwner)
		throw DOMException(DOMException::WRONG_DOCUMENT_ERR);
		
	if (newChild->nodeType() == Node::DOCUMENT_FRAGMENT_NODE)
	{
		AbstractContainerNode::Ptr pFrag = newChild.unsafeCast<AbstractContainerNode>();
		AbstractNode::Ptr pChild = pFrag->_pFirstChild;
		if (pChild)
		{
			if (_pLast)
				_pLast->_pNext = pChild;
			else
				_pParent->_pFirstChild = pChild;
			while (pChild)
			{
				_pLast = pChild;
				pChild->_pParent = _pParent;
				pChild = pChild->_pNext;
			}
			pFrag->_pFirstChild = 0;
		}
	}
	else
	{
		AbstractNode::Ptr pAN = newChild.unsafeCast<AbstractNode>();
		if (pAN->_pParent)
			pAN->_pParent->removeChild(pAN);
		pAN->_pParent = _pParent;
		if (_pLast)
			_pLast->_pNext = pAN;
		else
			_pParent->_pFirstChild = pAN;
		_pLast = pAN;
	}
}


} } // namespace Poco::XML
