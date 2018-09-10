/*
 * The B-tree header functions
 *
 * Copyright (C) 2018, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libfsapfs_btree_header.h"
#include "libfsapfs_libcerror.h"
#include "libfsapfs_libcnotify.h"

#include "fsapfs_btree.h"
#include "fsapfs_object.h"

/* Creates a B-tree header
 * Make sure the value btree_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsapfs_btree_header_initialize(
     libfsapfs_btree_header_t **btree_header,
     libcerror_error_t **error )
{
	static char *function = "libfsapfs_btree_header_initialize";

	if( btree_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid B-tree header.",
		 function );

		return( -1 );
	}
	if( *btree_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid B-tree header value already set.",
		 function );

		return( -1 );
	}
	*btree_header = memory_allocate_structure(
	                 libfsapfs_btree_header_t );

	if( *btree_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create B-tree header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *btree_header,
	     0,
	     sizeof( libfsapfs_btree_header_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear B-tree header.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *btree_header != NULL )
	{
		memory_free(
		 *btree_header );

		*btree_header = NULL;
	}
	return( -1 );
}

/* Frees a object map_btree
 * Returns 1 if successful or -1 on error
 */
int libfsapfs_btree_header_free(
     libfsapfs_btree_header_t **btree_header,
     libcerror_error_t **error )
{
	static char *function = "libfsapfs_btree_header_free";

	if( btree_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid B-tree header.",
		 function );

		return( -1 );
	}
	if( *btree_header != NULL )
	{
		memory_free(
		 *btree_header );

		*btree_header = NULL;
	}
	return( 1 );
}

/* Reads the object map_btree
 * Returns 1 if successful or -1 on error
 */
int libfsapfs_btree_header_read_data(
     libfsapfs_btree_header_t *btree_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libfsapfs_btree_header_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	size_t block_offset   = 0;
	uint16_t value_16bit  = 0;
#endif

	if( btree_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid B-tree header.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( ( data_size < sizeof( fsapfs_btree_header_t ) )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: B-tree header data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( fsapfs_btree_header_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	byte_stream_copy_to_uint16_little_endian(
	 ( (fsapfs_btree_header_t *) data )->flags,
	 btree_header->flags );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsapfs_btree_header_t *) data )->level,
	 btree_header->level );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsapfs_btree_header_t *) data )->number_of_keys,
	 btree_header->number_of_keys );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsapfs_btree_header_t *) data )->entries_data_offset,
	 btree_header->entries_data_offset );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsapfs_btree_header_t *) data )->entries_data_size,
	 btree_header->entries_data_size );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsapfs_btree_header_t *) data )->unused_data_offset,
	 btree_header->unused_data_offset );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsapfs_btree_header_t *) data )->unused_data_size,
	 btree_header->unused_data_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: flags\t\t\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 btree_header->flags );

		libcnotify_printf(
		 "%s: level\t\t\t\t\t: %" PRIu16 "\n",
		 function,
		 btree_header->level );

		libcnotify_printf(
		 "%s: number of keys\t\t\t: %" PRIu32 "\n",
		 function,
		 btree_header->number_of_keys );

		block_offset = sizeof( fsapfs_object_t ) + sizeof( fsapfs_btree_header_t );

		libcnotify_printf(
		 "%s: entries data offset\t\t\t: 0x%04" PRIx16 " (block offset: 0x%04" PRIzx ")\n",
		 function,
		 btree_header->entries_data_offset,
		 (size_t) btree_header->entries_data_offset + block_offset );

		block_offset += btree_header->entries_data_offset;

		libcnotify_printf(
		 "%s: entries data size\t\t\t: %" PRIu16 " (block offset: 0x%04" PRIzx ")\n",
		 function,
		 btree_header->entries_data_size,
		 (size_t) btree_header->entries_data_size + block_offset );

		block_offset += btree_header->entries_data_size;

		libcnotify_printf(
		 "%s: unused data offset\t\t\t: 0x%04" PRIx16 " (block offset: 0x%04" PRIzx ")\n",
		 function,
		 btree_header->unused_data_offset,
		 (size_t) btree_header->unused_data_offset + block_offset );

		block_offset += btree_header->unused_data_offset;

		libcnotify_printf(
		 "%s: unused data size\t\t\t: %" PRIu16 " (block offset: 0x%04" PRIzx ")\n",
		 function,
		 btree_header->unused_data_size,
		 (size_t) btree_header->unused_data_size + block_offset );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsapfs_btree_header_t *) data )->unknown5,
		 value_16bit );
		libcnotify_printf(
		 "%s: unknown5\t\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsapfs_btree_header_t *) data )->unknown6,
		 value_16bit );
		libcnotify_printf(
		 "%s: unknown6\t\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsapfs_btree_header_t *) data )->unknown7,
		 value_16bit );
		libcnotify_printf(
		 "%s: unknown7\t\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsapfs_btree_header_t *) data )->unknown8,
		 value_16bit );
		libcnotify_printf(
		 "%s: unknown8\t\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}
