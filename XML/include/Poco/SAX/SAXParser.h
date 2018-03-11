//
// SAXParser.h
//
// Library: XML
// Package: SAX
// Module:  SAX
//
// Implementation of the XMLReader interface.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef SAX_SAXParser_INCLUDED
#define SAX_SAXParser_INCLUDED


#include "Poco/XML/XML.h"
#include "Poco/SAX/XMLReader.h"
#include "Poco/XML/ParserEngine.h"


namespace Poco {
namespace XML {


class XML_API SAXParser: public XMLReader
	/// This class provides a SAX2 (Simple API for XML) interface to expat,
	/// the XML parser toolkit.
	/// The following SAX2 features and properties are supported:
	///   * http://xml.org/sax/features/external-general-entities
	///   * http://xml.org/sax/features/external-parameter-entities
	///   * http://xml.org/sax/features/namespaces
	///   * http://xml.org/sax/features/namespace-prefixes
	///   * http://xml.org/sax/properties/lexical-handler
	///   * http://xml.org/sax/properties/declaration-handler
	///
	/// The following proprietary extensions are supported:
	///   * http://www.appinf.com/features/enable-partial-reads --
	///     see ParserEngine::setEnablePartialReads()
{
public:
	typedef AutoPtr<SAXParser> Ptr;

	SAXParser();
		/// Creates an SAXParser.

	SAXParser(const XMLString& encoding);
		/// Creates an SAXParser with the given encoding.
	
	void setEncoding(const XMLString& encoding);
		/// Sets the encoding used by the parser if no
		/// encoding is specified in the XML document.
		
	const XMLString& getEncoding() const;
		/// Returns the name of the encoding used by
		/// the parser if no encoding is specified in
		/// the XML document.

	void addEncoding(const XMLString& name, Poco::TextEncoding* pEncoding);
		/// Adds an encoding to the parser. Does not take ownership of the pointer!

	/// XMLReader
	void setEntityResolver(AutoPtr<EntityResolver> pResolver);
	AutoPtr<EntityResolver> getEntityResolver() const;
	void setDTDHandler(AutoPtr<DTDHandler> pDTDHandler);
	AutoPtr<DTDHandler> getDTDHandler() const;
	void setContentHandler(AutoPtr<ContentHandler> pContentHandler);
	AutoPtr<ContentHandler> getContentHandler() const;
	void setErrorHandler(AutoPtr<ErrorHandler> pErrorHandler);
	AutoPtr<ErrorHandler> getErrorHandler() const;
	void setFeature(const XMLString& featureId, bool state);
	bool getFeature(const XMLString& featureId) const;
	void setProperty(const XMLString& propertyId, const XMLString& value);
	void setProperty(const XMLString& propertyId, AutoPtr<SAXHandler> value);
	AutoPtr<SAXHandler> getProperty(const XMLString& propertyId) const;
	void parse(AutoPtr<InputSource> pSource);
	void parse(const XMLString& systemId);
	void parseMemoryNP(const char* xml, std::size_t size);

	/// Extensions
	void parseString(const std::string& xml);

	static const XMLString FEATURE_PARTIAL_READS;

protected:

	~SAXParser();
		/// Destroys the SAXParser.

	void setupParse();

private:
	ParserEngine::Ptr _pEngine;
	bool _namespaces;
	bool _namespacePrefixes;
};


} } // namespace Poco::XML


#endif // SAX_SAXParser_INCLUDED
