/**
 * @file message.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <memory>
#include <string>

namespace messagequeue
{

typedef struct _message
{
public:

    // length of message payload in bytes
    int payloadlen;

    // pointer to the payload of message
    void *payload;

    int msgid;
}_msg;

/**
 * @brief A message objects holds required details to PUBLISH
 * message
 * 
 */
class message
{
public:

    using msg_ptr_t = std::shared_ptr<message>;

    using const_msg_ptr_t = std::shared_ptr<const message>;

    message();

    message(const std::string& topic, const void* payload, size_t len);

    message(const message& other);

    message(message&& other);

    ~message() {}

    static msg_ptr_t create(const std::string& topic, const void*payload, size_t len) {
        return std::make_shared<message>(topic, payload, len);
    }

    /**
     * @brief Copies another message to this one
     * 
     * @param rhs 
     * @return message& 
     */
    message& operator=(const message& rhs);

    /**
     * @brief Moves another message into this one
     * 
     * @param rhs 
     * @return message& 
     */
    message& operator=(message&& rhs);

    void set_topic(const std::string& topic){
        _topic = topic;
    }

    void set_payload(const void* payload, size_t n){
        __msg.payload = const_cast<void*>(payload);
        __msg.payloadlen = n;
    }

private:
    std::string _topic;
    _msg __msg;
    friend class client;
};


using msg_ptr = message::msg_ptr_t;
using const_message_ptr = message::const_msg_ptr_t;


class message_builder
{
    msg_ptr msg_;

public:

    using self = message_builder;

    message_builder() : msg_{ std::make_shared<message>() } {}

    auto topic(const std::string& topic) -> self& {
        msg_->set_topic(topic);
        return *this;
    }

    auto payload(const void*payload, size_t n) -> self& {
        msg_->set_payload(payload, n);
    }

    msg_ptr finalize() { return msg_; }
};

}

