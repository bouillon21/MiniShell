int main()
{
	char tent_buf[1024];
	char tget_buf[1024];
	char* tget_ptr = &tget_buf[0];

	/* capabilities. */
	const char* cm;
	const char* sf;
	const char* cs;

	int lines;
	int columns;
	int ret;

	ret = tgetent(tent_buf, getenv("TERM"));
}
