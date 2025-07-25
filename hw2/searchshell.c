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

// Feature test macro for strtok_r (c.f., Linux Programming Interface p. 63)
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "libhw1/CSE333.h"
#include "./CrawlFileTree.h"
#include "./DocTable.h"
#include "./MemIndex.h"

//////////////////////////////////////////////////////////////////////////////
// Helper function declarations, constants, etc
static void Usage(void);
static void ProcessQueries(DocTable *dt, MemIndex *mi);
static int GetNextLine(FILE *f, char **ret_str);


//////////////////////////////////////////////////////////////////////////////
// Main
int main(int argc, char **argv) {
  if (argc != 2) {
    Usage();
  }

  // Implement searchshell!  We're giving you very few hints
  // on how to do it, so you'll need to figure out an appropriate
  // decomposition into functions as well as implementing the
  // functions.  There are several major tasks you need to build:
  //
  //  - Crawl from a directory provided by argv[1] to produce and index
  //  - Prompt the user for a query and read the query from stdin, in a loop
  //  - Split a query into words (check out strtok_r)
  //  - Process a query against the index and print out the results
  //
  // When searchshell detects end-of-file on stdin (cntrl-D from the
  // keyboard), searchshell should free all dynamically allocated
  // memory and any other allocated resources and then exit.
  //
  // Note that you should make sure the fomatting of your
  // searchshell output exactly matches our solution binaries
  // to get full points on this part.
  DocTable *dt = NULL;
  MemIndex *mi = NULL;
  printf("Indexing '%s'\n", argv[1]);
  if (!CrawlFileTree(argv[1], &dt, &mi)) {
    fprintf(stderr, "directory '%s' does not exist\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  ProcessQueries(dt, mi);
  MemIndex_Free(mi);
  DocTable_Free(dt);
  return EXIT_SUCCESS;
}


//////////////////////////////////////////////////////////////////////////////
// Helper function definitions

static void Usage(void) {
  fprintf(stderr, "Usage: ./searchshell <docroot>\n");
  fprintf(stderr,
          "where <docroot> is an absolute or relative " \
          "path to a directory to build an index under.\n");
  exit(EXIT_FAILURE);
}

static void ProcessQueries(DocTable *dt, MemIndex *mi) {
  while (1) {
    printf("enter query: \n");
    char *input = NULL;
    if (GetNextLine(stdin, &input)) {
      free(input);
      printf("\nshutting down...\n");
      return;
    }

    char *words[100];
    int count = 0;
    char *word = strtok(input, " ");
    while (word && count < 100) {
      for (char *c = word; *c; c++) {
        *c = tolower(*c);
      }
      words[count++] = word;
      word = strtok(NULL, " ");
    }

    LinkedList *results = MemIndex_Search(mi, words, count);
    if (results) {
      LLIterator *it = LLIterator_Allocate(results);
      while (LLIterator_IsValid(it)) {
        SearchResult *r;
        LLIterator_Get(it, (LLPayload_t*)&r);
        printf(" %s (%d)\n", DocTable_GetDocName(dt, r->doc_id), r->rank);
        LLIterator_Next(it);
      }
      LLIterator_Free(it);
      LinkedList_Free(results, free);
    }
    
    free(input);
  }
}

static int GetNextLine(FILE *f, char **ret_str) {
  char *next_str = NULL;
  size_t len = 0;
  
  if (getline(&next_str, &len, f) == -1) {
    free(next_str);
    return -1;
  }
  
  len = strlen(next_str);
  if (len > 0 && next_str[len-1] == '\n') {
    next_str[len-1] = '\0';
  }
  
  *ret_str = next_str;
  return 0;
}
