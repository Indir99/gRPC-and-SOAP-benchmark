#pragma once

#include <string>
#include <vector>
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

struct TherapyData {
    Header header;
    std::string patientID;
    std::string patientFirstName;
    std::string patientLastName;
    std::string doctorID;
    std::string doctorFirstName;
    std::string doctortLastName;
    std::string therapyName;
    std::string therapyStatus;
    std::string time;
    void print(){
        std::cout<<" Patient ID: "<< patientID<<std::endl;
        std::cout<<" Patient Name: "<<patientFirstName<<std::endl;
        std::cout<<" Patient Last name: "<<patientLastName<<std::endl;
        std::cout<<" Doctor ID: "<< doctorID<<std::endl;
        std::cout<<" Doctor Name: "<<doctorFirstName<<std::endl;
        std::cout<<" Doctor Last name: "<<doctortLastName<<std::endl;
        std::cout<<" Therapy name: "<<therapyName<<std::endl;
        std::cout<<" Therapy status: "<<therapyStatus<<std::endl;
        std::cout<<" Report time: "<<time<<std::endl;
    }
};

struct TherapyList {
    Header header;
    std::vector<TherapyData> therapyList;
    void print(){
        for(auto& item : therapyList){
            std::cout<<" Therapy: "<<std::endl;
            item.print();
        }
    }
};

} // Domain

