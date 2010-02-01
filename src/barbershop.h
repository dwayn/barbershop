/*
Copyright (c) 2010 Nick Gerakines <nick at gerakines dot net>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <event.h>

#define COMMAND_TOKEN 0
#define SUBCOMMAND_TOKEN 1
#define KEY_TOKEN 1
#define VALUE_TOKEN 2
#define MAX_TOKENS 8
#define SERVER_PORT    8002

struct client {
    struct event ev_read;
};

struct TreeNode {
    int item;
    int score;
    SearchTree  left;
    SearchTree  right;
};

struct member_el {
    int item;
    MemberBucket next;
};

struct bucket_el {
    int score;
    int count;
    MemberBucket members;
    ScoreBucket next;
};

typedef struct token_s {
    char *value;
    size_t length;
} token_t;

SearchTree items;
ScoreBucket scores;

static size_t tokenize_command(char *command, token_t *tokens, const size_t max_tokens);
void on_read(int fd, short ev, void *arg);
void on_accept(int fd, short ev, void *arg);
int main(int argc, char **argv);
int setnonblock(int fd);
void reply(int fd, char *buffer);

