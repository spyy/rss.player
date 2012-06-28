import Qt 4.7


XmlListModel {
     query: "/rss/channel/item"     

     XmlRole { name: "title"; query: "title/string()" }
     XmlRole { name: "description"; query: "description/string()" }
     XmlRole { name: "link"; query: "link/string()" }
     XmlRole { name: "type"; query: "enclosure/@type/string()" }
     XmlRole { name: "url"; query: "enclosure/@url/string()" }
 }
