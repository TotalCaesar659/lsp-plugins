/*
 * IClipStream.cpp
 *
 *  Created on: 14 нояб. 2017 г.
 *      Author: sadko
 */

#include <core/io/IInStream.h>
#include <core/status.h>

namespace lsp
{
    namespace io
    {
        
        IInStream::IInStream()
        {
            nErrorCode      = STATUS_OK;
        }
        
        IInStream::~IInStream()
        {
            nErrorCode      = STATUS_OK;
        }
    
        wssize_t IInStream::avail()
        {
            return - set_error(STATUS_NOT_IMPLEMENTED);
        }

        wssize_t IInStream::position()
        {
            return - set_error(STATUS_NOT_IMPLEMENTED);
        }

        ssize_t IInStream::read(void *dst, size_t count)
        {
            return - set_error(STATUS_NOT_IMPLEMENTED);
        }

        ssize_t IInStream::read_byte()
        {
            uint8_t byte;
            ssize_t nread = read(&byte, sizeof(byte));
            return (nread == STATUS_OK) ? byte : nread;
        }

        ssize_t IInStream::read_fully(void *dst, size_t count)
        {
            uint8_t *ptr    = reinterpret_cast<uint8_t *>(dst);
            size_t left     = count;
            while (left > 0)
            {
                ssize_t act_read = read(ptr, left);
                if (act_read < 0)
                {
                    if (left > count)
                        break;
                    else
                        return act_read;
                }

                left   -= act_read;
                ptr    += act_read;
            }

            return count - left;
        }

        status_t IInStream::read_block(void *dst, size_t count)
        {
            if (dst == NULL)
                return set_error(STATUS_BAD_ARGUMENTS);
            else if (count == 0)
                return STATUS_OK;

            ssize_t read = read_fully(dst, count);
            if (read < 0)
                return -read;

            return set_error((size_t(read) == count) ? STATUS_OK : STATUS_EOF);
        }

        wssize_t IInStream::seek(wsize_t position)
        {
            return - set_error(STATUS_NOT_IMPLEMENTED);
        }

        status_t IInStream::close()
        {
            return set_error(nErrorCode);
        }

    } /* namespace ws */
} /* namespace lsp */
