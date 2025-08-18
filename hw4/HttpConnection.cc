/*
 * Copyright ©2025 Hal Perkins.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Spring Quarter 2025 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <stdint.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <map>
#include <string>
#include <vector>

#include "./HttpRequest.h"
#include "./HttpUtils.h"
#include "./HttpConnection.h"

using std::map;
using std::string;
using std::vector;

namespace hw4 {

static const char *kHeaderEnd = "\r\n\r\n";
static const int kHeaderEndLen = 4;

bool HttpConnection::GetNextRequest(HttpRequest *const request) {
  // Use WrappedRead from HttpUtils.cc to read bytes from the files into
  // private buffer_ variable. Keep reading until:
  // 1. The connection drops
  // 2. You see a "\r\n\r\n" indicating the end of the request header.
  //
  // Hint: Try and read in a large amount of bytes each time you call
  // WrappedRead.
  //
  // After reading complete request header, use ParseRequest() to parse into
  // an HttpRequest and save to the output parameter request.
  //
  // Important note: Clients may send back-to-back requests on the same socket.
  // This means WrappedRead may also end up reading more than one request.
  // Make sure to save anything you read after "\r\n\r\n" in buffer_ for the
  // next time the caller invokes GetNextRequest()!

  // STEP 1:
  // look for end of header
  size_t end = buffer_.find(kHeaderEnd);
  while (end == string::npos) {
    unsigned char tmp[1024];
    int n = WrappedRead(fd_, tmp, sizeof(tmp));
    if (n <= 0) return false;
    buffer_.append(reinterpret_cast<char*>(tmp), n);
    end = buffer_.find(kHeaderEnd);
  }
  string hdr = buffer_.substr(0, end);
  *request = ParseRequest(hdr);
  buffer_.erase(0, end + kHeaderEndLen);
  return true;

  // return false;  // you may need to change this return value
}

bool HttpConnection::WriteResponse(const HttpResponse &response) const {
  // We use a reinterpret_cast<> to cast between unrelated pointer types, and
  // a static_cast<> to perform a conversion from an unsigned type to its
  // corresponding signed one.
  string str = response.GenerateResponseString();
  int res = WrappedWrite(fd_,
                         reinterpret_cast<const unsigned char*>(str.c_str()),
                         str.length());

  if (res != static_cast<int>(str.length()))
    return false;
  return true;
}

HttpRequest HttpConnection::ParseRequest(const string &request) const {
  HttpRequest req("/");  // by default, get "/".

  // Plan for STEP 2:
  // 1. Split the request into different lines (split on "\r\n").
  // 2. Extract the URI from the first line and store it in req.URI.
  // 3. For the rest of the lines in the request, track the header name and
  //    value and store them in req.headers_ (e.g. HttpRequest::AddHeader).
  //
  // Hint: Take a look at HttpRequest.h for details about the HTTP header
  // format that you need to parse.
  //
  // You'll probably want to look up boost functions for:
  // - Splitting a string into lines on a "\r\n" delimiter
  // - Trimming whitespace from the end of a string
  // - Converting a string to lowercase.
  //
  // Note: If a header is malformed, skip that line.

  // STEP 2:
  vector<string> lines;
  boost::split(lines, request, boost::is_any_of("\r\n"), boost::token_compress_on);

  if (lines.empty()) {
    req.set_uri("BAD_");
    return req;
  }

  vector<string> parts;
  boost::split(parts, lines[0], boost::is_any_of(" "), boost::token_compress_on);
  if (parts.size() != 3 || parts[0] != "GET") {
    req.set_uri("BAD_");
    return req;
  }

  req.set_uri(parts[1]);
  for (size_t i = 1; i < lines.size(); i++) {
    string l = lines[i];
    if (l.empty()) continue;
    size_t colon = l.find(':');
    if (colon == string::npos || colon == 0) continue;
    string name = l.substr(0, colon);
    string val  = l.substr(colon + 1);
    boost::algorithm::trim(name);
    boost::algorithm::trim(val);
    if (!name.empty() && !val.empty())
      req.AddHeader(name, val);
  }

  return req;
}

}  // namespace hw4
