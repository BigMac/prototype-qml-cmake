#ifndef UNSUPPORTEDMESSAGERECEIVED_H
#define UNSUPPORTEDMESSAGERECEIVED_H

#include <stdexcept>

template <typename Message_t>
class UnsupportedMessageReceived : public std::runtime_error
{
public:
    UnsupportedMessageReceived() : std::runtime_error("Unsupported message received") {}
};

#endif // UNSUPPORTEDMESSAGERECEIVED_H
