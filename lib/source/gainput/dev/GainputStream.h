#ifndef GAINPUTSTREAM_H_
#define GAINPUTSTREAM_H_

#if defined(GAINPUT_PLATFORM_LINUX) || defined(GAINPUT_PLATFORM_ANDROID)
#include <arpa/inet.h>
#endif

namespace gainput {

class Stream
{
public:
	virtual size_t Read(void* dest, size_t length) = 0;
	virtual size_t Write(const void* src, size_t length) = 0;

	virtual size_t GetSize() const = 0;
	virtual size_t GetLeft() const = 0;

	virtual bool SeekBegin(int offset) = 0;
	virtual bool SeekCurrent(int offset) = 0;

	virtual void Reset() = 0;

	virtual bool IsEof() const = 0;

	template<class T> size_t Read(T& dest) { return Read(&dest, sizeof(T)); }
	template<class T> size_t Write(const T& src) { return Write(&src, sizeof(T)); }

};

template<>
inline
size_t
Stream::Read(uint16_t& dest)
{
	const size_t result = Read(&dest, sizeof(dest));
	dest = ntohs(dest);
	return result;
}

template<>
inline
size_t
Stream::Read(int16_t& dest)
{
	const size_t result = Read(&dest, sizeof(dest));
	dest = ntohs((uint16_t)dest);
	return result;
}

template<>
inline
size_t
Stream::Read(uint32_t& dest)
{
	const size_t result = Read(&dest, sizeof(dest));
	dest = ntohl(dest);
	return result;
}

template<>
inline
size_t
Stream::Read(int32_t& dest)
{
	const size_t result = Read(&dest, sizeof(dest));
	dest = ntohl((uint32_t)dest);
	return result;
}

template<>
inline
size_t
Stream::Write(const uint16_t& src)
{
	const uint16_t tmp = htons(src);
	return Write(&tmp, sizeof(tmp));
}

template<>
inline
size_t
Stream::Write(const int16_t& src)
{
	const int16_t tmp = htons((uint16_t)src);
	return Write(&tmp, sizeof(tmp));
}

template<>
inline
size_t
Stream::Write(const uint32_t& src)
{
	const uint32_t tmp = htonl(src);
	return Write(&tmp, sizeof(tmp));
}

template<>
inline
size_t
Stream::Write(const int32_t& src)
{
	const int32_t tmp = htonl((uint32_t)src);
	return Write(&tmp, sizeof(tmp));
}


}

#endif
