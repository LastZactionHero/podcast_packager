#ifndef SRC_FEED_PARSER_H_
#define SRC_FEED_PARSER_H_

#include <libxml/parser.h>
#include <string>

class FeedParser {
 public:
  explicit FeedParser(const std::string &filename);
  ~FeedParser();

  std::string title();
  void episodes();

 private:
  xmlNode* findNodeByXpath(xmlDocPtr doc, const xmlChar *xpath);
  std::string nodeContent(xmlNode *node);

  std::string filename;
  xmlDocPtr doc;
};

#endif  // SRC_FEED_PARSER_H_
