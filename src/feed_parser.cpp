#include "./feed_parser.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
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

void FeedParser::episodes(std::vector<Episode> *episodes) {
  if (doc == NULL) {
    return;
  }

  // Find list of episodes (item tag)
  xmlNodeSetPtr nodeSet = findNodesetByXpath(
    doc,
    reinterpret_cast<const xmlChar*>("//item"));

  // Parse each episode
  for (int i = 0; i < nodeSet->nodeNr; ++i) {
    xmlNodePtr node = nodeSet->nodeTab[i];

    xmlNodePtr child = node->children;

    xmlNode *titleNode = findChildNode(node, "title");
    std::string title = nodeContent(titleNode);

    xmlNode *pubDateNode = findChildNode(node, "pubDate");
    std::string pubDate = nodeContent(pubDateNode);

    xmlNode *enclosureNode = findChildNode(node, "enclosure");
    std::string url = nodeProperty(enclosureNode, "url");

    episodes->emplace_back(title, pubDate, url);
  }
}

xmlNode* FeedParser::findChildNode(xmlNode *node, std::string name) {
  xmlNodePtr child = node->children;
  while (child) {
    if (strcmp(name.c_str(), reinterpret_cast<const char*>(child->name)) == 0) {
      return child;
    }

    child = child->next;
  }
  return NULL;
}

xmlNodeSetPtr FeedParser::findNodesetByXpath(
  xmlDocPtr doc,
  const xmlChar *xpath) {
  xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
  xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression(xpath, xpathCtx);

  if (xpathObj == NULL) {
    std::cout << "Could not evaluate expresssion\n";
    return NULL;
  }

  return xpathObj->nodesetval;
}

xmlNode* FeedParser::findNodeByXpath(xmlDocPtr doc, const xmlChar *xpath) {
  xmlNodeSetPtr nodeSet = findNodesetByXpath(doc, xpath);

  if (nodeSet->nodeNr == 0) {
    std::cout << "Node not found\n";
    return NULL;
  }

  return nodeSet->nodeTab[0];
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

std::string FeedParser::nodeProperty(xmlNode *node, std::string propertyName) {
  _xmlAttr *attribute = node->properties;

  while (attribute) {
    if (strcmp(propertyName.c_str(),
        reinterpret_cast<const char*>(attribute->name)) == 0) {
      return nodeContent(attribute->children);
    }
    attribute = attribute->next;
  }

  return "";
}