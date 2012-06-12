#ifndef SERIALIZEDMESSAGE_H
#define SERIALIZEDMESSAGE_H
#include <string>
#include <vector>
#include <boost/serialization/access.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class SerializedMessage
{
public:
    SerializedMessage();
    void setTypeDiscriminator(const std::string& type);
    const std::string& getTypeDiscriminator() const;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & m_typeDiscriminator;
        ar & m_data;
    }

    std::string m_typeDiscriminator;
    std::vector<char> m_data;
};

#endif // SERIALIZEDMESSAGE_H
