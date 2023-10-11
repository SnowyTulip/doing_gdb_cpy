/* #include <stdnoreturn.h> */

int _read(int file, char *ptr, int len)
{
    return 0;
}

int _lseek(int file, int ptr, int dir)
{
    return 0;
}

int _open(const char *path, int flags)
{
    return 0;
}

int _close(int file)
{
    return 0;
}

char *_sbrk(int incr)
{
    return 0;
}

int _fstat(int file, void *st)
{
    return 0;
}

int _unlink()
{
    return -1;
}

int _isatty(fd)
int fd;
{
    return 0;
}

int _raise()
{
    return 0;
}

int _times()
{
    return 0;
}

int _kill(int pid, int sig)
{
    return 0;
}

int _getpid(void)
{
    return 0;
}
