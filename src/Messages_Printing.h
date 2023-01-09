#ifndef MESSAGES_PRINTING_H
#define MESSAGES_PRINTING_H

#include "Libraries_And_Macros.h"

#define STR(a) #a
#define SHOW_DEFINE(a) STR(a)

#define CHANGE_COLOR(stream, a) fprintf(stream, "%s", SHOW_DEFINE(a))

#define DEFAULT_COLOR \033[0m
#define BOLD_DEFAULT_COLOR \033[1m
#define BLACK_COLOR \033[0;30m
#define BOLD_BLACK_COLOR \033[1;30m
#define RED_COLOR \033[0;31m
#define BOLD_RED_COLOR \033[1;31m
#define GREEN_COLOR \033[1;32m
#define BOLD_GREEN_COLOR \033[1;32m
#define YELLOW_COLOR \033[1;33m
#define BOLD_YELLOW_COLOR \033[1;33m
#define BLUE_COLOR \033[1;34m
#define BOLD_BLUE_COLOR \033[1;34m
#define PURPLE_COLOR \033[1;35m
#define BOLD_PURPLE_COLOR \033[1;35m
#define CYAN_COLOR \033[1;36m
#define BOLD_CYAN_COLOR \033[1;36m
#define WHITE_COLOR \033[1;37m
#define BOLD_WHITE_COLOR \033[1;37m

bool is_string_empty(char* message);

void change_color(FILE* stream, char* color);
void set_default_color(FILE* stream);

void print_message(FILE* stream, char* tag, char* message, char* tag_color, char* message_color);
void print_error(FILE* stream, char* tag, char* message);
void print_text(FILE* stream, char* tag, char* message);

void color_messages_printing_test();

#endif