/**
 * @file connections.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once


namespace messagequeue
{

enum StatusCode {
    SUCCESS = 0,
    NO_SUB,
    PROTOCOL_ERROR,
    SERVER_ERROR,
    SERVER_BUSY
};

}