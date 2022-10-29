/**
 * @file client.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <callback.h>
#include <connections.h>
#include <message.h>
#include <string>
#include <functional>

namespace messagequeue
{

/**
 * @brief client for connecting and interacting with server.
 * 
 */

class client_helper
{
public:

    using conn_handler = std::function<void(const std::string& conn)>;
    using disconn_handler = std::function<void(const std::string& cause, StatusCode)>;
    using mess_handler = std::function<void(const_message_ptr)>;
    void set_conn_handler(conn_handler cb);

    void set_conn_lost_handler(conn_handler cb);

    void set_disconnect_handler(disconn_handler cb);

    void set_message_callback(mess_handler cb);

    void connect();

    void disconnect();

    std::string get_client_id() const { return client_id_; }

    std::string get_server_uri() const { return server_id_ ; }

    bool is_connected();

    void publish(const_message_ptr msg);

    void subscribe(const std::string& topic);

    void start_reading();
    
    void stop_reading();

    const_message_ptr read_message();
};

class client
{
public:

    /**
     * @brief Construct a new client object to communicate with server
     * 
     * @param server 
     * @param clientId 
     */
    client(const std::string& server, const std::string& clientId);

    /**
     * @brief Destroy the client object
     * 
     */
    virtual ~client();

    virtual conn_response connect();

    virtual void disconnect(int timeoutMS = 500000);

    virtual std::string get_client_id() const { return cli_.get_client_id(); }

    virtual std::string get_server_uri() const { return cli_.get_server_uri(); }

    virtual topic get_topic(const std::string& topic);

    virtual bool is_connected() const { return cli_.is_connected();}

    virtual void publish(const_message_ptr msg) {
        cli_.publish(msg);
    }

    subscribe_response subscribe(const std::string& topicFilter);

    void start_reading() { cli_.start_reading();}

    void stop_reading() { cli_.stop_reading();}

    const_message_ptr read_message() { return cli_.read_message(); }

private:

    client_helper cli_;

};

}