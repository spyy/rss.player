

#include "rssparser.h"


RssParser::RssParser()
{
    iXmlSimpleReader = 0;
}

RssParser::~RssParser()
{
    delete iXmlSimpleReader;
}


void RssParser::initialize()
{
    iXmlSimpleReader = new QXmlSimpleReader;

    iXmlSimpleReader->setContentHandler( this );
}


bool RssParser::startElement( const QString&, const QString&, const QString& /*qName*/, const QXmlAttributes& /*atts*/ )
{
    return true;
}

bool RssParser::endElement( const QString&, const QString&, const QString& /*qName*/ )
{
    return true;
}

bool RssParser::characters( const QString& /*ch*/ )
{
    return true;
}

void RssParser::parse( QString aFileName )
{
    QFile file( aFileName );
    QXmlInputSource source( &file );

    iXmlSimpleReader->parse( source );
}


