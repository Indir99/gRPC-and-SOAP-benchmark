#pragma once

#include <string>
#include <iostream>

namespace Domain {

struct Header{
    std::string senderAddress;
    std::string receiverAddress;
    void print(){
        std::cout<<" Sender Address: "<<senderAddress<<std::endl;
        std::cout<<" Response should be sent to address: "<<receiverAddress<<std::endl;
    }
};

struct ProbeMatchData {
    Header header;
    std::string deviceName;
    void print(){
        header.print();
        std::cout<<" Device type: "<< deviceName <<std::endl;
    }
};

struct ProbeData {
    Header header;
    std::string deviceName;
    void print(){
        header.print();
        std::cout<<" Device type: "<< deviceName <<std::endl;
    }
};

} // Domain

