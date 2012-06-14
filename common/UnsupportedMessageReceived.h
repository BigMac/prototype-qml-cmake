#ifndef UNSUPPORTEDMESSAGERECEIVED_H
#define UNSUPPORTEDMESSAGERECEIVED_H

#include <exception>

template <typename Message_t>
class UnsupportedMessageReceived : public std::exception
{
};

#endif // UNSUPPORTEDMESSAGERECEIVED_H
