
#ifndef RSSPARSER_H
#define RSSPARSER_H


#include <QtXml>


class RssParser : public QXmlDefaultHandler
{
public:
    explicit RssParser();
    virtual ~RssParser();
    void initialize();

public: // from QXmlDefaultHandler
    bool startElement( const QString&, const QString&, const QString& qName, const QXmlAttributes& atts );
    bool endElement( const QString&, const QString&, const QString& qName );
    bool characters( const QString& ch );

public: // new functions
    void parse( QString aFileName );

private:
    QXmlSimpleReader* iXmlSimpleReader;

};

#endif // RSSPARSER_H
