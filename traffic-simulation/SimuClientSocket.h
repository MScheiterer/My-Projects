/*
 * SimuClientSocket.h
 *
 *  Created on: 9 Jan 2023
 *      Author: Micha
 */

#ifndef SIMUCLIENTSOCKET_H_
#define SIMUCLIENTSOCKET_H_

#pragma once

#include <string>
#include <sstream>
#include <boost/asio.hpp>

#ifndef DEBUG
#define DEBUG 0
#endif

using boost::asio::ip::tcp;

class SimuClientSocket {
public:
  SimuClientSocket();
  virtual ~SimuClientSocket() = default;
  bool Create();
  bool Connect(std::string address, std::string port);
  void Send(std::stringstream& msg);
  void Close();
private:
  boost::asio::io_context io_context;
  tcp::socket socket;
};

#endif /* SIMUCLIENTSOCKET_H_ */
