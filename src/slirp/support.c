#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdarg.h>

#include "qemu/osdep.h"
#include "slirp.h"
#include "main.h"
#include "socket.h"

int
qemu_socket(int domain, int type, int protocol)
{
  return socket(domain, type, protocol);
}

ssize_t
qemu_recv(int sockfd, void *buf, size_t len, int flags)
{
  return recv(sockfd, buf, len, flags);
}

int
qemu_setsockopt(int sockfd, int level, int optname,
		const void *optval, socklen_t optlen)
{
  return setsockopt(sockfd, level, optname,
		    optval, optlen);
}

void
qemu_set_nonblock(int fd)
{
       int opt = 1;
       
       ioctl(fd, FIONBIO, &opt);
}

int
socket_set_fast_reuse(int fd)
{
  int opt = 1;
  return setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,(char *)&opt,sizeof(int));
}

void
socket_set_nodelay(int fd)
{
  int opt = 1;
  setsockopt(fd,IPPROTO_TCP,TCP_NODELAY,(char *)&opt,sizeof(int));
}

ssize_t
slirp_send(struct socket *so, const void *buf, size_t len, int flags)
{
  return send(so->s, buf, len, flags);
}

void
error_report(const char *fmt, ...)
{
    va_list args;

    va_start (args, fmt);
    fprintf (stderr, fmt, args);
    va_end (args);
}

void
g_warning(const char *fmt, ...)
{
    va_list args;

    va_start (args, fmt);
    fprintf (stderr, fmt, args);
    va_end (args);
}

uint64_t
qemu_clock_get_ns(int type)
{
  struct timeval tv;

  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000000000LL + (tv.tv_usec * 1000);
}

uint64_t
qemu_clock_get_ms(int type)
{
  struct timeval tv;

  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000LL + (tv.tv_usec / 1000);
}

void *
g_malloc0 (size_t sz)
{
  void *ret = malloc (sz);
  if (ret)
    memset (ret, 0, sz);
  return ret;
}
