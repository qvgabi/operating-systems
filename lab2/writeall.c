/*[writeall]*/
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

ssize_t writeall(int fd, const void *buf, size_t nbyte)
{
	ssize_t nwritten = 0, n;

	do {
		if ((n = write(fd, &((const char *)buf)[nwritten], nbyte - nwritten)) == -1) {
			if (errno == EINTR)
				continue;
			else
				return -1;
		}
		nwritten += n;
	} while (nwritten < nbyte);
	return nwritten;
}