#include "./file_download_service.h"
#include <curl/curl.h>
#include <iostream>
#include <fstream>

static int writer(char *data, size_t size, size_t nmemb, std::string *writerData);
static std::string buffer;

FileDownloadService::FileDownloadService(
  const std::string &url,
  const std::string &filename) :
  url(url),
  filename(filename) {}

bool FileDownloadService::download() {
  CURL *curl;
  CURLcode res;
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();

  buffer = "";

  /* Perform the request, res will get the return code */
  if (curl) {
    CURLcode code;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
    code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    if (code != CURLE_OK) {
      std::cout << "Failed to set writer " << std::endl;
      return false;
    }

    res = curl_easy_perform(curl);
    /* Check for errors */
    if (res != CURLE_OK) {
      std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
      return false;
    }

    int http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    if (http_code != 200) {
      std::cout << "Status code " << http_code << " fetching, URL " << url << std::endl;
      return false;
    }

    /* always cleanup */
    curl_easy_cleanup(curl);
  }

  std::ofstream outfile(filename);
  outfile << buffer;
  outfile.close();

  curl_global_cleanup();

  return true;
}

static int writer(char *data, size_t size, size_t nmemb, std::string *writerData) {
  if (writerData == NULL)
    return 0;
  writerData->append(data, size*nmemb);
  return size * nmemb;
}