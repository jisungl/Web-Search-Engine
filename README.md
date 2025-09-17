# Web Search Engine
Implementation of a Search Engine


**Note:** This project was part of the coursework for CSE 333 at the University of Washington.
The majority of the framework was provided by the instructors.

## Overview
Multithreaded HTTP web server with integrated search capabilities with static content and dynamic search results. The system processes search queries across multiple on-disk indices while maintaining robust security protections against web vulnerabilities.

### Features
- Thread pool implementation handling concurrent clients
- HTTP/1.1: Full request-response parsing with status codes
- Support for various MIME types (HTMLS, CSS, JS, images, docs)
- Path traversal prevention, XSS mitigation
- Non-blocking socket operations

**Test with**: ./http333d 5555 ../projdocs unit_test_indices/*
and access via browser: http://localhost:5555/
