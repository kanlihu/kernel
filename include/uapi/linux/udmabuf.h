/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _UAPI_LINUX_UDMABUF_H
#define _UAPI_LINUX_UDMABUF_H

#include <linux/types.h>
#include <linux/ioctl.h>

/**
 * DOC: udmabuf
 *
 * udmabuf is a device driver which allows userspace to create
 * dmabufs.  The memory used for these dmabufs must be backed by
 * memfd.  The memfd must have F_SEAL_SHRINK and it must not have
 * F_SEAL_WRITE.
 *
 * The driver has two ioctls, one to create a dmabuf from a single
 * memory block and one to create a dmabuf from a list of memory
 * blocks.
 *
 * UDMABUF_CREATE - _IOW('u', 0x42, udmabuf_create)
 *
 * UDMABUF_CREATE_LIST - _IOW('u', 0x43, udmabuf_create_list)
 */

#define UDMABUF_CREATE       _IOW('u', 0x42, struct udmabuf_create)
#define UDMABUF_CREATE_LIST  _IOW('u', 0x43, struct udmabuf_create_list)

#define UDMABUF_FLAGS_CLOEXEC	0x01

/**
 * struct udmabuf_create - create a dmabuf from a single memory block.
 *
 * @memfd: The file handle.
 * @offset: Start of the buffer (from memfd start).
 * Must be page aligned.
 * @size: Size of the buffer.  Must be rounded to page size.
 *
 * @flags:
 * UDMABUF_FLAGS_CLOEXEC: set CLOEXEC flag for the dmabuf.
 */
struct udmabuf_create {
	__u32 memfd;
	__u32 flags;
	__u64 offset;
	__u64 size;
};

/**
 * struct udmabuf_create_item - one memory block list item.
 *
 * @memfd: The file handle.
 * @__pad: Padding field (unused).
 * @offset: Start of the buffer (from memfd start).
 * Must be page aligned.
 * @size: Size of the buffer.  Must be rounded to page size.
 */
struct udmabuf_create_item {
	__u32 memfd;
	__u32 __pad;
	__u64 offset;
	__u64 size;
};

/**
 * struct udmabuf_create_list - create a dmabuf from a memory block list.
 *
 * @count: The number of list elements.
 * @list: The memory block list
 *
 * @flags:
 * UDMABUF_FLAGS_CLOEXEC: set CLOEXEC flag for the dmabuf.
 */
struct udmabuf_create_list {
	__u32 flags;
	__u32 count;
	struct udmabuf_create_item list[];
};

#endif /* _UAPI_LINUX_UDMABUF_H */
