# Web Search Engine

A multithreaded HTTP web server with integrated full-text search, written in C and C++. The system crawls a directory of documents, builds an inverted index, serializes it to a custom on-disk binary format, and serves both static files and ranked search results over HTTP through a web interface. Built for CSE 333 (Systems Programming) at the University of Washington.

**Note:** The project framework (header files, abstract classes, test harnesses, Makefiles, and utility functions) was provided by the course instructors. All implementation logic was written by me.

## How It Works

**Crawling and indexing.** The engine recursively walks a directory tree, parses every text file it finds, and tokenizes contents into words with byte offset tracking. The results are stored in an in-memory inverted index — a mapping from every word in the corpus to the set of documents and positions where it appears — backed by a custom hash table and linked list implemented in C.

**On-disk serialization.** The in-memory index is serialized into a compact binary `.idx` format using nested hash tables with checksums for integrity validation. Reader classes query the index directly from disk without loading the entire structure into memory.

**HTTP server.** The server binds to a TCP socket (IPv4/IPv6) and dispatches incoming connections to a pool of 8 worker threads via a synchronized task queue built on pthreads mutexes and condition variables. Each worker parses HTTP/1.1 requests, supporting persistent connections by buffering partial reads and splitting on `\r\n\r\n` boundaries.

**Request handling.** Requests route to either static file serving or search query processing. Static files are resolved against a base directory with MIME type detection and path traversal protection. Search queries are parsed from URL parameters, processed against one or more on-disk indices, and returned as ranked HTML results with hyperlinks to source documents. User input is HTML-escaped to prevent XSS.

**Shutdown.** The server supports graceful shutdown via `/quitquitquit` or SIGTERM, entering lame duck mode where in-flight requests finish but no new connections are accepted.

## Components

- **LinkedList / HashTable** — generic C data structures with `void*` payloads and iterator support, used throughout the system for indexing, document tracking, and file crawling
- **CrawlFileTree / FileParser** — recursive directory traversal and file tokenization with byte offset tracking
- **DocTable / MemIndex** — in-memory document table and inverted index built on top of the hash table
- **WriteIndex** — serializes the in-memory index into a checksummed binary `.idx` file
- **FileIndexReader / IndexTableReader / DocIDTableReader / DocTableReader** — reader classes for querying each layer of the on-disk index
- **QueryProcessor** — processes multi-word queries across multiple index files and returns ranked results
- **ServerSocket** — TCP socket binding, listening, and connection acceptance with DNS resolution
- **ThreadPool** — fixed-size worker pool with a synchronized task queue and graceful shutdown support
- **HttpConnection** — buffered HTTP request parsing with persistent connection support
- **HttpServer** — request routing, static file serving, and search result rendering
- **FileReader** — file reading with path safety validation
- **HttpUtils** — HTML escaping, URI decoding, URL parsing, path traversal prevention

## Usage
```bash
# Build
make

# Run the server
./http333d <port> <static_files_directory> <index_file(s)>

# Example
./http333d 5555 ../projdocs unit_test_indices/*
```

Access via browser at `http://localhost:<port>/`

## Tech Stack

- C, C++
- POSIX sockets and pthreads
- Boost (string algorithms)
- Google Test (unit testing)
- Make