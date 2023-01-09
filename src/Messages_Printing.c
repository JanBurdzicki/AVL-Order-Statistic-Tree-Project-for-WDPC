#include "Messages_Printing.h"

bool is_string_empty(char* message)
{
	return (message[0] == '\0');
}

void change_color(FILE* stream, char* color)
{
	fprintf(stream, "%s", color);
}

void set_default_color(FILE* stream)
{
	fprintf(stream, "%s", SHOW_DEFINE(DEFAULT_COLOR));
}

void print_message(FILE* stream, char* tag, char* message, char* tag_color, char* message_color)
{
	change_color(stream, tag_color);

	if(!is_string_empty(tag))
	{
		fprintf(stream, "%s%s%s", "[", tag, "]: ");
	}

	change_color(stream, message_color);

	fprintf(stream, "%s", message);

	set_default_color(stream);
}

void print_error(FILE* stream, char* tag, char* message)
{
	char* tag_color = SHOW_DEFINE(BOLD_RED_COLOR);
	char* message_color = SHOW_DEFINE(RED_COLOR);

	print_message(stream, tag, message, tag_color, message_color);
}

void print_text(FILE* stream, char* tag, char* message)
{
	char* tag_color = SHOW_DEFINE(BOLD_CYAN_COLOR);
	char* message_color = SHOW_DEFINE(DEFAULT_COLOR);

	print_message(stream, tag, message, tag_color, message_color);
}

void color_messages_printing_test()
{
	print_message(stderr, "BOLD DEFAULT", "DEFAULT\n", SHOW_DEFINE(DEFAULT_COLOR), SHOW_DEFINE(BOLD_DEFAULT_COLOR));
	print_message(stderr, "BOLD BLACK", "BLACK\n", SHOW_DEFINE(BLACK_COLOR), SHOW_DEFINE(BOLD_BLACK_COLOR));
	print_message(stderr, "BOLD RED", "RED\n", SHOW_DEFINE(RED_COLOR), SHOW_DEFINE(BOLD_RED_COLOR));
	print_message(stderr, "BOLD GREEN", "GREEN\n", SHOW_DEFINE(GREEN_COLOR), SHOW_DEFINE(BOLD_GREEN_COLOR));
	print_message(stderr, "BOLD YELLOW", "YELLOW\n", SHOW_DEFINE(YELLOW_COLOR), SHOW_DEFINE(BOLD_YELLOW_COLOR));
	print_message(stderr, "BOLD BLUE", "BLUE\n", SHOW_DEFINE(BLUE_COLOR), SHOW_DEFINE(BOLD_BLUE_COLOR));
	print_message(stderr, "BOLD PURPLE", "PURPLE\n", SHOW_DEFINE(PURPLE_COLOR), SHOW_DEFINE(BOLD_PURPLE_COLOR));
	print_message(stderr, "BOLD CYAN", "CYAN\n", SHOW_DEFINE(CYAN_COLOR), SHOW_DEFINE(BOLD_CYAN_COLOR));
	print_message(stderr, "BOLD WHITE", "WHITE\n", SHOW_DEFINE(WHITE_COLOR), SHOW_DEFINE(BOLD_WHITE_COLOR));
}