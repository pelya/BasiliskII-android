#include <sys/types.h>
#include <sys/socket.h>

int
qemu_socket(int domain, int type, int protocol);

ssize_t
qemu_recv(int sockfd, void *buf, size_t len, int flags);

int
qemu_setsockopt(int sockfd, int level, int optname,
		const void *optval, socklen_t optlen);

void qemu_set_nonblock(int fd);

int
socket_set_fast_reuse(int fd);

void
socket_set_nodelay(int fd);

void
error_report(const char *format, ...);
void
g_warning(const char *format, ...);

#define QEMU_CLOCK_REALTIME 0
uint64_t
qemu_clock_get_ns(int type);
uint64_t
qemu_clock_get_ms(int type);

#define qemu_log_mask(a, b)

#define g_assert_not_reached()
#define g_malloc malloc
#define g_free free
#define g_strdup strdup

#define pstrcpy(dest, len, src) strncpy(dest, src, len)

#define g_new(type, num) malloc ((num) * sizeof(type))

#define ioctlsocket ioctl
#define closesocket close

void *
g_malloc0 (size_t sz);
