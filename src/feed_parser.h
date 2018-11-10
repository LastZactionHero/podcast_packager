#ifndef SRC_FEED_PARSER_H_
#define SRC_FEED_PARSER_H_

#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string>
#include <vector>
#include "./episode.h"

class FeedParser {
 public:
  explicit FeedParser(const std::string &filename);
  ~FeedParser();

  std::string title();
  void episodes(std::vector<Episode> *episodes);

 private:
  xmlNodeSetPtr findNodesetByXpath(xmlDocPtr doc, const xmlChar *xpath);
  xmlNode* findNodeByXpath(xmlDocPtr doc, const xmlChar *xpath);
  xmlNode* findChildNode(xmlNode *node, std::string name);
  std::string nodeContent(xmlNode *node);
  std::string nodeProperty(xmlNode *node, std::string propertyName);

  std::string filename;
  xmlDocPtr doc;
};

#endif  // SRC_FEED_PARSER_H_
