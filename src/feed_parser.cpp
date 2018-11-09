#include "./feed_parser.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <iostream>

FeedParser::FeedParser(const std::string &filename) : filename(filename) {
  xmlInitParser();
  doc = xmlReadFile(filename.c_str(), NULL, 0);

  if (doc == NULL) {
    std::cout << "Could not open file " << filename << " for reading.\n";
  }
}

FeedParser::~FeedParser() {
  if (doc) {
    xmlFreeDoc(doc);
  }
  xmlCleanupParser();
}


std::string FeedParser::title() {
  if (doc == NULL) {
    return "";
  }

  xmlNode *titleNode = findNodeByXpath(
    doc,
    reinterpret_cast<const xmlChar*>("//title"));
  return nodeContent(titleNode);
}

void FeedParser::episodes() {

}

xmlNode* FeedParser::findNodeByXpath(xmlDocPtr doc, const xmlChar *xpath) {
  xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
  xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression(xpath, xpathCtx);

  if (xpathObj == NULL) {
    std::cout << "Could not evaluate expresssion\n";
    return NULL;
  }

  if (xpathObj->nodesetval->nodeNr == 0) {
    std::cout << "Node not found\n";
    return NULL;
  }

  return xpathObj->nodesetval->nodeTab[0];
}

std::string FeedParser::nodeContent(xmlNode *node) {
  std::string title = "";

  xmlChar *content = xmlNodeGetContent(node);
  if (content) {
    title = reinterpret_cast<const char*>(content);
    xmlFree(content);
  }

  return title;
}
