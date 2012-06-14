#ifndef SERIALIZEDMESSAGE_H
#define SERIALIZEDMESSAGE_H
#include <array>
#include <string>
#include <vector>

typedef uint32_t NumericMessageTypeDiscriminator_t;
struct SerializedMessage
{
public:
    SerializedMessage();
    SerializedMessage(NumericMessageTypeDiscriminator_t type,
                      std::vector<char>& data);

    void setTypeDiscriminator(const std::string& type);

    const std::string& getTypeDiscriminator() const;    
    NumericMessageTypeDiscriminator_t getNumericTypeDiscriminator() const;

    void setData(const std::string& input);
    std::string getDataAsString() const;

    void prepareForReceive();
    void prepareForSend();

    std::vector<size_t> data_size; // Needs to be a vector because boost::asio says so
    std::vector<NumericMessageTypeDiscriminator_t> message_type; // As above
    std::vector<char> data;
};

#endif // SERIALIZEDMESSAGE_H
